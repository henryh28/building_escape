// Copyright Henry Hsu 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupInputComponent();

private:
	float Reach = 100.0f;
	
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	class UInputComponent* InputComponent = nullptr;
	
	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void setupInputComponent();

	// Return first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetLineStart() const;
	FVector GetLineEnd() const;
};
