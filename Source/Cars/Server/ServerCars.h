#pragma once
#include "Net/Manager.h"

class CServerCars : public Net::CManager::IObserver
{
public:
  CServerCars();
  ~CServerCars();

  void Step();

  // Net::CManager::IObserver
  virtual void dataPacketReceived(Net::CPaquete* packet);
  virtual void connexionPacketReceived(Net::CPaquete* packet);
  virtual void disconnexionPacketReceived(Net::CPaquete* packet);
private:
  Net::CManager* m_pManager = nullptr;
};

