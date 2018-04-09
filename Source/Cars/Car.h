// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

UCLASS()
class CARS_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
  float _acel = 120.f;
  float _drag = 50.f;
  float _brakeAcel = 300.f;
  float _maxVelocity = 250.f;

  FVector m_vVelocity = FVector::ZeroVector;

  //Input variables
  FVector m_vMovementInput;

  //Input functions
  void Move(float AxisValue);
  void Turn(float AxisValue);
  FVector CalculateAceleration(float DeltaTime);
  void CalculateVelocity(FVector _vAcel, float DeltaTime);
	
};
