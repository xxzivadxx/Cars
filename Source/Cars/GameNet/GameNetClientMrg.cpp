// Fill out your copyright notice in the Description page of Project Settings.

#include "GameNetClientMrg.h"
#include "Net/buffer.h"
#include "Net/paquete.h"

CGameNetClientMrg::CGameNetClientMrg() : m_pController(nullptr)
{
  m_pManager = Net::CManager::getSingletonPtr();
  m_pManager->addObserver(this);
}

CGameNetClientMrg::CGameNetClientMrg(ACarsGameModeBase* _pController) : m_pController(_pController)
{
  m_pManager = Net::CManager::getSingletonPtr();
  m_pManager->addObserver(this);
}

void CGameNetClientMrg::dataPacketReceived(Net::CPaquete* packet)
{
  if (m_pManager->getID() == Net::ID::SERVER)
  {
  }
  else
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
  }
}

//--------------------------------

void CGameNetClientMrg::connexionPacketReceived(Net::CPaquete* packet)
{
  if (m_pManager->getID() == Net::ID::SERVER)
  {
    // Creamos un buffer con los datos para leer de manera más cómoda
    Net::CBuffer data;
    const char* sHello = "Connected";
    data.write(sHello, sizeof(sHello));
    m_pManager->send(data.getbuffer(), data.getSize());
    if (GEngine)
    {
      // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Client connected! ");
    }
  }
  else
  {

  }
}

//--------------------------------

void CGameNetClientMrg::disconnexionPacketReceived(Net::CPaquete* packet)
{

}