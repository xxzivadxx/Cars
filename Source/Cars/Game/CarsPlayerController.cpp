// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsPlayerController.h"
#include "Game/GameCamera.h"
#include "Game/Car.h"


ACarsPlayerController::ACarsPlayerController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  bAutoManageActiveCameraTarget = false;
}
void ACarsPlayerController::BeginPlay()
{
  Super::BeginPlay();
  SetInputMode(FInputModeGameAndUI());
}

void ACarsPlayerController::SetPawn(APawn* pPawn)
{
  Super::SetPawn(pPawn);
  ACar* pCar = Cast<ACar>(GetPawn());
  if (pCar)
  {
    pCar->SetupPlayerInputComponent(InputComponent);
  }
}
