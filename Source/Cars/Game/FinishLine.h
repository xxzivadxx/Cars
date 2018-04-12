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


  // overlap begin function
  UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

  // overlap end function
  UFUNCTION()
    void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

  inline void AddPassedCheckPoint() { ++m_uPassedCheckPoints; }

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ACheckPoint*> m_vCheckPoints;

  unsigned int m_uPassedCheckPoints = 0u;
  unsigned int m_uLaps = 0u;
};