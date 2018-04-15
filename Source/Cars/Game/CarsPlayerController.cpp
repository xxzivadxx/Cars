// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsPlayerController.h"
#include "Game/CameraCtrl.h"


ACarsPlayerController::ACarsPlayerController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  bAutoManageActiveCameraTarget = false;
}


