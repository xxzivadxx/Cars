// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "../Net/Manager.h"
#include "GameCamera.generated.h"

class ACar;

UCLASS()
class CARS_API AGameCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
  class CNetObserver : public Net::CManager::IObserver
  {
  public:
    CNetObserver() : m_pController(nullptr) { }
    CNetObserver(AGameCamera* _pController) : m_pController(_pController) { }
    // Net::CManager::IObserver
    virtual void dataPacketReceived(Net::CPaquete* packet);
    virtual void connexionPacketReceived(Net::CPaquete* packet);
    virtual void disconnexionPacketReceived(Net::CPaquete* packet);
  private:
    AGameCamera* m_pController;
  };

	// Sets default values for this actor's properties
	AGameCamera();
  // Called every frame
  virtual void Tick(float DeltaTime) override;
  //
  inline void SetTarget(ACar* _pTarget) { m_pTarget = _pTarget; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
  UPROPERTY(EditAnywhere)
    ACar* m_pTarget;
  UPROPERTY(EditAnywhere)
    float m_fMinDistance = 200.f;
  UPROPERTY(EditAnywhere)
    float m_fDistanceFromVelocityFactor = 0.6f;

  Net::CManager* m_pManager = nullptr;
  CNetObserver m_oNetObserver;
	
};
