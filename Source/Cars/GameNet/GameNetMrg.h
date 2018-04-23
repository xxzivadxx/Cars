// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/Manager.h"

class ACarsGameModeBase;
class ACar;

enum class NetMessageType {
  COMMAND,
  START_GAME,
  END_GAME,
  LOAD_MAP,
  LOAD_PLAYER,
  MAP_LOADED,
  PLAYER_LOADED,
  ACTOR_MSG,
  ASSIGNED_ID
};

/**
*
*/
class CGameNetMrg : public Net::CManager::IObserver
{
public:
  CGameNetMrg();
  CGameNetMrg(ACarsGameModeBase* _pController);
  virtual ~CGameNetMrg() { }

  // Net::CManager::IObserver
  virtual void dataPacketReceived(Net::CPaquete* packet);
  virtual void connexionPacketReceived(Net::CPaquete* packet);
  virtual void disconnexionPacketReceived(Net::CPaquete* packet);

  void Tick();
private:
  Net::CManager* m_pManager = nullptr;
  ACarsGameModeBase* m_pController;
  std::map<unsigned int, ACar*> m_vPlayers;
  unsigned int m_uMapLoadedNotifications = 0u;
};
