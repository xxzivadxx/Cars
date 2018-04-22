// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/Manager.h"

class ACarsGameModeBase;

/**
*
*/
class CGameNetClientMrg : public Net::CManager::IObserver
{
public:
  CGameNetClientMrg();
  CGameNetClientMrg(ACarsGameModeBase* _pController);
  virtual ~CGameNetClientMrg() { }

  // Net::CManager::IObserver
  virtual void dataPacketReceived(Net::CPaquete* packet);
  virtual void connexionPacketReceived(Net::CPaquete* packet);
  virtual void disconnexionPacketReceived(Net::CPaquete* packet);
private:
  Net::CManager* m_pManager = nullptr;
  ACarsGameModeBase* m_pController;
};
