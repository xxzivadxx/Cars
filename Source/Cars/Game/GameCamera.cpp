// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCamera.h"
#include "Car.h"
#include "Kismet/GameplayStatics.h"
#include "Net/buffer.h"
#include "Net/paquete.h"


// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
  Super::BeginPlay();
  SetTarget();
}

void AGameCamera::SetTarget()
{
  if (!m_pTarget)
  {
    //Find the actor that handles control for the local player.
    APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (OurPlayerController)
    {
      OurPlayerController->SetViewTarget(this);
      m_pTarget = Cast<ACar>(OurPlayerController->GetPawn());
    }
  }
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  SetTarget();
  if (m_pTarget)
  {
    FVector vNewPos = m_pTarget->GetActorTransform().GetTranslation();
    vNewPos.Z = m_fMinDistance + m_pTarget->GetVelocityMagnitude() * m_fDistanceFromVelocityFactor;
    FTransform oTransform = GetActorTransform();
    oTransform.SetTranslation(vNewPos);
    SetActorTransform(oTransform);
  }
}

