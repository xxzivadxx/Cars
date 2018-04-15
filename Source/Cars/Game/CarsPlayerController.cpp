// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsPlayerController.h"
#include "Game/GameCamera.h"


ACarsPlayerController::ACarsPlayerController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  bAutoManageActiveCameraTarget = false;
}


