// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Net/buffer.h"
#include <iostream>


void ACarsGameModeBase::CServerObserver::dataPacketReceived(Net::CPaquete* packet)
{

}

//--------------------------------

void ACarsGameModeBase::CServerObserver::connexionPacketReceived(Net::CPaquete* packet)
{
  // Creamos un buffer con los datos para leer de manera más cómoda
  Net::CBuffer data;
  const char* sHellow = "Connected";
  data.write(sHellow, sizeof(sHellow));
  m_pManager->send(data.getbuffer(), data.getSize());
  std::cout << "Client connected! ";
}

//--------------------------------

void ACarsGameModeBase::CServerObserver::disconnexionPacketReceived(Net::CPaquete* packet)
{

}

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer), oObserver(this)
{
  PlayerControllerClass = ACarsPlayerController::StaticClass();
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

void ACarsGameModeBase::OnServerButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server"));

  Net::CManager::Init();
  m_pManager = Net::CManager::getSingletonPtr();
  m_pManager->addObserver(&oObserver);
  m_pManager->activateAsServer(65785);
}

void ACarsGameModeBase::OnClientButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Client"));
}

void ACarsGameModeBase::OnServerStartButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server Start!"));
}

