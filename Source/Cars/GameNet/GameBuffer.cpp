// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBuffer.h"


CGameBuffer::CGameBuffer(size_t initsize, size_t delta) : Net::CBuffer(initsize, delta)
{
}

CGameBuffer::~CGameBuffer()
{
}

void CGameBuffer::write(NetMessageType data)
{
  write(&data, sizeof(data));
}

void CGameBuffer::write(const FVector& data)
{
  write(data.X);
  write(data.Y);
  write(data.Z);
}

void CGameBuffer::read(NetMessageType& data)
{
  read(&data, sizeof(data));
}

void CGameBuffer::read(FVector& data)
{
  read(data.X);
  read(data.Y);
  read(data.Z);
}
