// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/buffer.h"
#include "Math/Vector.h"

enum class NetMessageType;
/**
 * 
 */
class CGameBuffer : public Net::CBuffer
{
public:
  CGameBuffer(size_t initsize = 500, size_t delta = 100);
  virtual ~CGameBuffer();

  using Net::CBuffer::write;
  void write(NetMessageType data);
  void write(const FVector& data);
  using Net::CBuffer::read;
  void read(NetMessageType& data);
  void read(FVector& data);
};
