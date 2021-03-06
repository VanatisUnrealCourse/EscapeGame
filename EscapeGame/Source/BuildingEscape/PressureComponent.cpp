// Copyright Cédric Van de Walle 2017

#include "BuildingEscape.h"
#include "PressureComponent.h"


// Sets default values for this component's properties
UPressureComponent::UPressureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPressureComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPressureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpenDoorRequest.Broadcast();
	}
	else
	{
		OnCloseDoorRequest.Broadcast();
	}
}

float UPressureComponent::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	if (!PressurePlate) { return TotalMass; }

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
