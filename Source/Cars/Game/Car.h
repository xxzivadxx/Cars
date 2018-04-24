// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

class UCarMovementComponent;
class UNetComponent;

UCLASS()
class CARS_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();
  // Called every frame
  virtual void Tick(float DeltaTime) override;
  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  // Velocity magnitude
  float GetVelocityMagnitude();

  void SetInput(FVector2D _vInput) { m_vMovementInput = _vInput; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  //Input functions
  void Move(float AxisValue);
  void Turn(float AxisValue);

protected:
  //Input variables
  FVector2D m_vMovementInput = FVector2D::ZeroVector;
  //Movement
  UPROPERTY(EditAnywhere)
  UCarMovementComponent* m_pCarMovement;
  //Net
  UPROPERTY(EditAnywhere)
  UNetComponent* m_pNet;
  //Mesh
  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* m_pMesh;
  bool m_bBind = false;
};
