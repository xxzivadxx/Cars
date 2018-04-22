// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameNet/GameBuffer.h"
#include "Net/paquete.h"
#include <iostream>

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer), m_oObserver(this)
{
  PrimaryActorTick.bCanEverTick = true;
  PlayerControllerClass = ACarsPlayerController::StaticClass();
  m_pManager = Net::CManager::getSingletonPtr();
}

ACarsGameModeBase::~ACarsGameModeBase()
{
}

void ACarsGameModeBase::Destroyed()
{

}

APawn* ACarsGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
  return nullptr;
}

void ACarsGameModeBase::BeginPlay()
{
  Super::BeginPlay();
  ChangeMenuWidget(StartingWidgetClass);
  m_pManager->addObserver(&m_oObserver);
}

void ACarsGameModeBase::EndPlay(EEndPlayReason::Type eEndPlayReason)
{
  Super::EndPlay(eEndPlayReason);
  m_pManager->removeObserver(&m_oObserver);
}

void ACarsGameModeBase::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
  if(CurrentWidget)
    m_oObserver.Tick();
}

void ACarsGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
  if (CurrentWidget != nullptr)
  {
    CurrentWidget->RemoveFromViewport();
    CurrentWidget = nullptr;
  }
  if (NewWidgetClass != nullptr)
  {
    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
    if (CurrentWidget != nullptr)
    {
      CurrentWidget->AddToViewport();
    }
  }
}

void ACarsGameModeBase::OnServerButtonClick(FString sPort)
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server"));

  m_pManager->activateAsServer(FCString::Atoi(*sPort));
}

void ACarsGameModeBase::OnClientButtonClick(FString sIP, FString sPort)
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Client"));

  m_pManager->activateAsClient();
  m_pManager->connectTo(TCHAR_TO_ANSI(*sIP), FCString::Atoi(*sPort));
}

void ACarsGameModeBase::OnServerStartButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server Start!"));
  UGameplayStatics::OpenLevel(GetWorld(), "Circuit1");
  CGameBuffer data;
  NetMessageType iID = NetMessageType::LOAD_MAP;
  data.write(iID);
  const char* sLevel = "Circuit1";
  data.write(sLevel);
  m_pManager->send(data.getbuffer(), data.getSize());
}

