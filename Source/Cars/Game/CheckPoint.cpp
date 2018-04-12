
#include "CheckPoint.h"
// include draw debu helpers header file
#include "DrawDebugHelpers.h"
#include "FinishLine.h"

ACheckPoint::ACheckPoint()
{
  //Register Events
  OnActorEndOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
  OnActorEndOverlap.AddDynamic(this, &ACheckPoint::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
  Super::BeginPlay();

  DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

void ACheckPoint::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
  // check if Actors do not equal nullptr and that 
  if (OtherActor && (OtherActor != this))
  {
  }
}

void ACheckPoint::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
  if (OtherActor && (OtherActor != this))
  {
  }
}
