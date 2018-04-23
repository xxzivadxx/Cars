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

