// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameNet/GameBuffer.h"
#include "Net/paquete.h"
#include <iostream>

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer)
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
}

void ACarsGameModeBase::EndPlay(EEndPlayReason::Type eEndPlayReason)
{
  Super::EndPlay(eEndPlayReason);
}

void ACarsGameModeBase::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
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
}

void ACarsGameModeBase::OnClientButtonClick(FString sIP, FString sPort)
{
}

void ACarsGameModeBase::OnServerStartButtonClick()
{
}

