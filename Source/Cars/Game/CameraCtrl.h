// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Net/Manager.h"
#include "CameraCtrl.generated.h"

UCLASS()
class CARS_API ACameraCtrl : public AActor
{
	GENERATED_BODY()
	
public:
  class CNetObserver : public Net::CManager::IObserver
  {
  public:
    CNetObserver() : m_pController(nullptr) { }
    CNetObserver(ACameraCtrl* _pController) : m_pController(_pController) { }
    // Net::CManager::IObserver
    virtual void dataPacketReceived(Net::CPaquete* packet);
    virtual void connexionPacketReceived(Net::CPaquete* packet);
    virtual void disconnexionPacketReceived(Net::CPaquete* packet);
  private:
    ACameraCtrl* m_pController;
  };

	// Sets default values for this actor's properties
	ACameraCtrl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


  UPROPERTY(EditAnywhere)
    AActor* CameraOne;
private:
  Net::CManager* m_pManager = nullptr;
  CNetObserver m_oNetObserver;
	
};
