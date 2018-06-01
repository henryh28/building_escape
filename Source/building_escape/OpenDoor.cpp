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
	Owner = GetOwner();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s Missing pressure plate"), *GetOwner()->GetName());
	}

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	if (MassOfActor() > TriggerMass) {
		OnDoorOpen.Broadcast();
	}
	else {
		OnDoorClose.Broadcast();
	}
}

float UOpenDoor::MassOfActor() {
	float TotalMass = 0.f;

	// Get list of all actors that are in trigger space and save to OverlappingActors TArray
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { TotalMass; }
	PressurePlate->GetOverlappingActors(OverlappingActors);

	// Iterate through OverlappingActors and add their weight
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on plate."), *Actor->GetName());
	}

	return TotalMass;
}

