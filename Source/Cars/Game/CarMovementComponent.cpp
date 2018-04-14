// Fill out your copyright notice in the Description page of Project Settings.

#include "CarMovementComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UCarMovementComponent::UCarMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  FVector vAccel = CalculateAceleration();
  UpdateVelocity(m_vVelocity, vAccel, DeltaTime);
  MoveActor(m_vVelocity, DeltaTime);
}

FVector UCarMovementComponent::CalculateAceleration()
{
  FVector acel;
  if (m_vMovementInput.Y > 0.f)
    acel = m_fAcel * m_vMovementInput.Y * GetOwner()->GetActorForwardVector();
  else if (m_vMovementInput.Y == 0.f)
    acel = -m_fDrag * GetOwner()->GetActorForwardVector();
  else
    acel = m_fBrakeAcel * m_vMovementInput.Y * GetOwner()->GetActorForwardVector();

  acel += m_vMovementInput.X * m_vVelocity.Size() * m_fRotationFactor * GetOwner()->GetActorRightVector();

  return acel;
}

void UCarMovementComponent::UpdateVelocity(FVector& _vVelocity_, const FVector& _vAcel, float DeltaTime)
{
  _vVelocity_ += _vAcel * DeltaTime;

  if (_vVelocity_ != FVector::ZeroVector &&
    FMath::Acos(FVector::DotProduct(_vVelocity_, GetOwner()->GetActorForwardVector())) > 1.f) // +-60º
    _vVelocity_ = FVector::ZeroVector;

  else if (_vVelocity_.Size() > m_fMaxVelocity)
    _vVelocity_ *= m_fMaxVelocity / _vVelocity_.Size();
}

void UCarMovementComponent::MoveActor(const FVector& _vVelocity, float DeltaTime)
{
  auto oTrans = GetOwner()->GetActorTransform();
  oTrans.AddToTranslation(_vVelocity * DeltaTime);
  FVector PlayerLoc = GetOwner()->GetActorLocation();
  GetOwner()->SetActorTransform(oTrans);
  if (_vVelocity != FVector::ZeroVector)
  {
    FRotator Rot = FRotationMatrix::MakeFromX(_vVelocity).Rotator();
    GetOwner()->SetActorRotation(Rot);
  }
}
