// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Components/InputComponent.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
  m_vMovementInput.Set(0.f, 0.f, 0.f);
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  FVector vAccel = CalculateAceleration(DeltaTime);
  CalculateVelocity(vAccel, DeltaTime);
  auto oTrans = GetActorTransform();
  oTrans.AddToTranslation(m_vVelocity * DeltaTime);
  FVector PlayerLoc = GetActorLocation();
  SetActorTransform(oTrans);
  if (m_vVelocity != FVector::ZeroVector)
  {
    FRotator Rot = FRotationMatrix::MakeFromX(m_vVelocity).Rotator();
    SetActorRotation(Rot);
  }
}

FVector ACar::CalculateAceleration(float DeltaTime)
{
  FVector acel;
  if (m_vMovementInput.Y > 0.f)
    acel = _acel * m_vMovementInput.Y * GetActorForwardVector();
  else if (m_vMovementInput.Y == 0.f)
    acel = -_drag * GetActorForwardVector();
  else
    acel = _brakeAcel * m_vMovementInput.Y * GetActorForwardVector();

  acel += m_vMovementInput.X * m_vVelocity.Size() * GetActorRightVector();

  return acel;
}

void ACar::CalculateVelocity(FVector acel, float DeltaTime)
{
  m_vVelocity += acel * DeltaTime;

  if (m_vVelocity != FVector::ZeroVector && 
      FMath::Acos(FVector::DotProduct(m_vVelocity, GetActorForwardVector())) > 1.f) // +-60º
    m_vVelocity = FVector::ZeroVector;

  else if (m_vVelocity.Size() > _maxVelocity)
    m_vVelocity *= _maxVelocity / m_vVelocity.Size();
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAxis("Move", this, &ACar::Move);
  PlayerInputComponent->BindAxis("Turn", this, &ACar::Turn);

}

//Input functions
void ACar::Move(float AxisValue)
{
  m_vMovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACar::Turn(float AxisValue)
{
  m_vMovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

