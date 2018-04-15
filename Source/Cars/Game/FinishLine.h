#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FinishLine.generated.h"

class ACheckPoint;

UCLASS()
class CARS_API AFinishLine : public ATriggerBox
{
  GENERATED_BODY()

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // constructor sets default values for this actor's properties
  AFinishLine();

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ACheckPoint*> m_vCheckPoints;
};