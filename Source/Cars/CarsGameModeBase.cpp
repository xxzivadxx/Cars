// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"
#include "Blueprint/UserWidget.h"

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer)
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
}

void ACarsGameModeBase::OnClientButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Client"));
}

void ACarsGameModeBase::OnServerStartButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server Start!"));
}

