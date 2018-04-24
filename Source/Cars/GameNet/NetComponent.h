// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetComponent.generated.h"

namespace Net
{
  class CManager;
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARS_API UNetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetComponent();
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
  // Input
  void SetInput(FVector2D _vInput) { m_vMovementInput = _vInput; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
  //Input vector
  FVector2D m_vMovementInput = FVector2D::ZeroVector;
  Net::CManager* m_pManager = nullptr;	
};
