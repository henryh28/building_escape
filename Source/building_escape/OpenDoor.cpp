// Copyright Henry Hsu 2018

#include "OpenDoor.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Opener = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	DoorOwner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	DoorOwner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(Opener)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

