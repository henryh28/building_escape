// Copyright Henry Hsu 2018

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("grabb here"));

	// Look for Physics component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("Physics component found"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Missing physics handle component"), *GetOwner()->GetName());
	}

	// Look for input component (only appear at runtime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Missing input handle component"), *GetOwner()->GetName());
	}

}

void UGrabber::Grab() {
	// 
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation, PlayerViewPointRotation);

	//// Display viewpoint info
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s , Rotation: %s"),
	//	*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector LinePreview = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Colorize LinePreview
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LinePreview, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	// Setup Query Params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line trace
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit, PlayerViewPointLocation, LinePreview, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters
	);

	// Log what actor was hit
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *(HitActor->GetName()))
	}
}

