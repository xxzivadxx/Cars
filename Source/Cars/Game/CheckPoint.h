#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckPoint.generated.h"

UCLASS()
class CARS_API ACheckPoint : public ATriggerBox
{
  GENERATED_BODY()

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // constructor sets default values for this actor's properties
  ACheckPoint();
};