// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARS_API UMultiplayerUserWidget : public UUserWidget
{
  GENERATED_BODY()

public:
  // expose this function so that it can be called via a node from BP
  UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
  void HandleOnServerButtonClick();
	
	
};
