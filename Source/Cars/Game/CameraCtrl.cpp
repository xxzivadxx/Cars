// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraCtrl.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraCtrl::ACameraCtrl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraCtrl::BeginPlay()
{
	Super::BeginPlay();

  //Find the actor that handles control for the local player.
  APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
  if (OurPlayerController)
  {
    OurPlayerController->SetViewTarget(CameraOne);
  }
}

// Called every frame
void ACameraCtrl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

