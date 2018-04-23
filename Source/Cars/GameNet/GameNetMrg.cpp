// Fill out your copyright notice in the Description page of Project Settings.

#include "GameNetMrg.h"
#include "GameNet/GameBuffer.h"
#include "Net/paquete.h"
#include "Kismet/GameplayStatics.h"
#include "CarsGameModeBase.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Game/Car.h"

CGameNetMrg::CGameNetMrg() : m_pController(nullptr)
{
  m_pManager = Net::CManager::getSingletonPtr();
}

CGameNetMrg::CGameNetMrg(ACarsGameModeBase* _pController) : m_pController(_pController)
{
  m_pManager = Net::CManager::getSingletonPtr();
}

void CGameNetMrg::dataPacketReceived(Net::CPaquete* packet)
{
  // Creamos un buffer con los datos para leer de manera más cómoda
  CGameBuffer data;
  data.write(packet->getData(), packet->getDataLength());
  data.reset();
  NetMessageType eMessageType;
  data.read(eMessageType);
  switch (eMessageType)
  {
  case NetMessageType::LOAD_MAP:
  {
    char sMap[128];
    data.read(sMap);
    UGameplayStatics::OpenLevel(m_pController->GetWorld(), sMap);
    NetMessageType iID = NetMessageType::MAP_LOADED;
    m_pManager->send(&iID, sizeof(iID));
    //ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(m_pController->GetWorld(), sMap);
    //ACar* pCar;
    //level->OnLevelLoaded.AddDynamic(this, &AClass::OnLevelStreamLoaded);
  } break;
  case NetMessageType::MAP_LOADED:
  {
    ++m_uMapLoadedNotifications;
    if (m_uMapLoadedNotifications >= m_pManager->getConnections().size())
    {
      for (auto client : m_pManager->getConnections())
      {
        CGameBuffer data;
        NetMessageType iID = NetMessageType::LOAD_PLAYER;
        data.write(iID);
        data.write(client.first);
        FVector vPos(220, -310.f + client.first * 40.f, 0.f);
        data.write(vPos);
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.Name = FName("Car", client.first);
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        ACar* pCar = m_pController->GetWorld()->SpawnActor<ACar>(vPos, FRotator::ZeroRotator, SpawnInfo);
        if (pCar)
        {
          m_vPlayers[client.first] = pCar;
          m_pManager->send(data.getbuffer(), data.getSize());
        }
      }
    }
  } break;
  case NetMessageType::LOAD_PLAYER:
  {
    unsigned int uClient;
    data.read(uClient);
    FVector vPos;
    data.read(vPos);
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.Name = FName("Car", uClient);
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    if (m_pController->GetWorld())
    {
      ACar* pCar = m_pController->GetWorld()->SpawnActor<ACar>(vPos, FRotator::ZeroRotator, SpawnInfo);
      if (pCar)
      {
        m_vPlayers[uClient] = pCar;
        if (uClient == m_pManager->getID())
        {
          APlayerController* OurPlayerController = GEngine->GetFirstLocalPlayerController(m_pController->GetWorld());
          if (OurPlayerController)
          {
            OurPlayerController->SetPawn(pCar);
          }
          pCar->AutoPossessPlayer = EAutoReceiveInput::Player0;
        }
      }
    }
  } break;
  default:
    break;
  }
}

//--------------------------------

void CGameNetMrg::connexionPacketReceived(Net::CPaquete* packet)
{
}

//--------------------------------

void CGameNetMrg::disconnexionPacketReceived(Net::CPaquete* packet)
{
}

//--------------------------------

void CGameNetMrg::Tick()
{
  m_pManager->tick();
}