// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARS_API ACarsPlayerController : public APlayerController
{
  GENERATED_BODY()
  
public:
  ACarsPlayerController(const class FObjectInitializer& ObjectInitializer);
  virtual void BeginPlay() override;

  virtual void SetPawn(APawn* pPawn) override;
};
