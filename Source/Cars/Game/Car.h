// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

class UCarMovementComponent;

UCLASS()
class CARS_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
  //Mesh
  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* m_pMesh;
};
