// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
  RootComponent = BoxComponent;
  m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
  m_pMesh->SetupAttachment(RootComponent);
  static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Engine/BasicShapes/Cube"));
  if (BoxVisualAsset.Succeeded())
  {
    m_pMesh->SetStaticMesh(BoxVisualAsset.Object);
    static ConstructorHelpers::FObjectFinder<UMaterial> CarMaterial(TEXT("Material'/Game/Textures/Car'"));
    m_pMesh->SetMaterial(0, CarMaterial.Object);
  }
  SetActorScale3D(FVector(0.2f, 0.1f, 0.05f));
  SetActorRotation(FRotator(0.f, 270.f, 0.f));
  AutoPossessPlayer = EAutoReceiveInput::Player0;
  AutoPossessAI = EAutoPossessAI::Disabled;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

