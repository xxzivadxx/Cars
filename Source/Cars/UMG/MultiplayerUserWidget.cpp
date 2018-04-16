// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerUserWidget.h"

void UMultiplayerUserWidget::HandleOnServerButtonClick()
{
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *FString("Server"));
}


