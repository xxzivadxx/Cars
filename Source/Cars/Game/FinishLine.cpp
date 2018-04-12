
#include "FinishLine.h"
// include draw debu helpers header file
#include "DrawDebugHelpers.h"
#include "CheckPoint.h"

AFinishLine::AFinishLine()
{
  //Register Events
  OnActorEndOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
  OnActorEndOverlap.AddDynamic(this, &AFinishLine::OnOverlapEnd);
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
  }
}

void AFinishLine::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
  if (OtherActor && (OtherActor != this))
  {
  }
}
