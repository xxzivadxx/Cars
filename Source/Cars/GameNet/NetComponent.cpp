// Fill out your copyright notice in the Description page of Project Settings.

#include "NetComponent.h"
#include "GameFramework/Actor.h"
#include "GameNet/GameBuffer.h"
#include "Net/Manager.h"
#include "Engine/World.h"
#include "CarsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Car.h"


// Sets default values for this component's properties
UNetComponent::UNetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

  m_pManager = Net::CManager::getSingletonPtr();
	// ...
}


// Called when the game starts
void UNetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UNetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  ACarsGameModeBase* pGameMode = Cast<ACarsGameModeBase>(GetWorld()->GetAuthGameMode());
  if (pGameMode)
  {
    if (pGameMode->GetGameNetMgr().GetOwnCar() == GetOwner())
    {
      CGameBuffer oBuffer;
      oBuffer.write(NetMessageType::ACTOR_MSG);
      oBuffer.write(m_pManager->getID());
      oBuffer.write(m_vMovementInput);
      m_pManager->send(oBuffer.getbuffer(), oBuffer.getSize());
    }
    else
    {
      //ACar* pCar = Cast<ACar>(GetOwner());
      //if (pCar)
      //{
      //  pCar->SetInput(m_vMovementInput);
      //}
    }
  }
}

