// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraCtrl.h"
#include "Kismet/GameplayStatics.h"
#include "Net/buffer.h"
#include "Net/paquete.h"


// Sets default values
ACameraCtrl::ACameraCtrl()
  : m_oNetObserver(this)
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
    OurPlayerController->SetViewTarget(this);
  }

  Net::CManager::Init();
  m_pManager = Net::CManager::getSingletonPtr();
  m_pManager->activateAsClient();
  m_pManager->addObserver(&m_oNetObserver);
  m_pManager->connectTo("127.0.0.1", 65785, 1, 500u);
}

// Called every frame
void ACameraCtrl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  m_pManager->tick();
  if (m_pTarget)
  {
    FVector vNewPos = m_pTarget->GetActorTransform().GetTranslation();
    vNewPos.Z = m_fMinDistance + m_pTarget->GetVelocityMagnitude() * m_fDistanceFromVelocityFactor;
    FTransform oTransform = GetActorTransform();
    oTransform.SetTranslation(vNewPos);
    SetActorTransform(oTransform);
  }
}

//--------------------------------

void ACameraCtrl::CNetObserver::dataPacketReceived(Net::CPaquete* packet)
{
  // Creamos un buffer con los datos para leer de manera más cómoda
  Net::CBuffer data;
  data.write(packet->getData(), packet->getDataLength());
  data.reset();
  char sInfo[128];
  data.read(sInfo, data.getSize());
  if (GEngine)
  {
    // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, sInfo);
  }
  Net::CManager::getSingletonPtr()->send(data.getbuffer(), data.getSize());
}

//--------------------------------

void ACameraCtrl::CNetObserver::connexionPacketReceived(Net::CPaquete* packet)
{
}

//--------------------------------

void ACameraCtrl::CNetObserver::disconnexionPacketReceived(Net::CPaquete* packet)
{

}

