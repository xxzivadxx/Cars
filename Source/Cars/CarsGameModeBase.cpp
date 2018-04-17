// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Net/buffer.h"
#include "Net/paquete.h"
#include <iostream>


ACarsGameModeBase::CServerObserver::CServerObserver() : m_pController(nullptr)
{
  if (!Net::CManager::getSingletonPtr())
  {
    Net::CManager::Init();
  }
  m_pManager = Net::CManager::getSingletonPtr();
}

ACarsGameModeBase::CServerObserver::CServerObserver(ACarsGameModeBase* _pController) : m_pController(_pController)
{
  if (!Net::CManager::getSingletonPtr())
  {
    Net::CManager::Init();
  }
  m_pManager = Net::CManager::getSingletonPtr();
}

void ACarsGameModeBase::CServerObserver::dataPacketReceived(Net::CPaquete* packet)
{
  if (m_pManager->getID() == Net::ID::SERVER)
  {
  }
  else
  {
    // Creamos un buffer con los datos para leer de manera más cómoda
    Net::CBuffer data;
    data.write(packet->getData(), packet->getDataLength());
    data.reset();
    char sInfo[128];
    data.read(sInfo, data.getSize());
    if (GEngine)
    {
      // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, sInfo);
    }
  }
}

//--------------------------------

void ACarsGameModeBase::CServerObserver::connexionPacketReceived(Net::CPaquete* packet)
{
  if (m_pManager->getID() == Net::ID::SERVER)
  {
    // Creamos un buffer con los datos para leer de manera más cómoda
    Net::CBuffer data;
    const char* sHello = "Connected";
    data.write(sHello, sizeof(sHello));
    m_pManager->send(data.getbuffer(), data.getSize());
    if (GEngine)
    {
      // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Client connected! ");
    }
  }
  else
  {

  }
}

//--------------------------------

void ACarsGameModeBase::CServerObserver::disconnexionPacketReceived(Net::CPaquete* packet)
{

}

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer), m_oObserver(this)
{
  PrimaryActorTick.bCanEverTick = true;
  PlayerControllerClass = ACarsPlayerController::StaticClass();
  if (!Net::CManager::getSingletonPtr())
  {
    Net::CManager::Init();
  }
  m_pManager = Net::CManager::getSingletonPtr();
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

void ACarsGameModeBase::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
  m_pManager->tick();
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

  m_pManager->addObserver(&m_oObserver);
  m_pManager->activateAsServer(FCString::Atoi(*sPort));
}

void ACarsGameModeBase::OnClientButtonClick(FString sIP, FString sPort)
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Client"));

  m_pManager->activateAsClient();
  m_pManager->addObserver(&m_oObserver);
  m_pManager->connectTo(TCHAR_TO_ANSI(*sIP), FCString::Atoi(*sPort));
}

void ACarsGameModeBase::OnServerStartButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server Start!"));
}

