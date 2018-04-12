
#include "FinishLine.h"
// include draw debu helpers header file
#include "DrawDebugHelpers.h"
#include "CheckPoint.h"

AFinishLine::AFinishLine()
{
  //Register Events
  OnActorEndOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
  for (ACheckPoint* pCP : m_vCheckPoints)
  {
    pCP->SetFinishLine(this);
  }
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
  Super::BeginPlay();

  DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

void AFinishLine::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
  // check if Actors do not equal nullptr and that 
  if (OtherActor && (OtherActor != this))
  {
    if (m_uPassedCheckPoints == m_vCheckPoints.Num())
    {
      ++m_uLaps;

      if (GEngine)
      {
        // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("meta!"));
      }
    }
    m_uPassedCheckPoints = 0u;
    if (GEngine)
    {
      // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("meta!"));
    }
  }
}

void AFinishLine::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
  if (OtherActor && (OtherActor != this))
  {
  }
}
