// Copyright Cédric Van de Walle 2017

#include "BuildingEscape.h"
#include "Grabber.h"
#include "OpenableDoor.h"
#include "TriggerItemComponent.h"


// Sets default values for this component's properties
UTriggerItemComponent::UTriggerItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void UTriggerItemComponent::BeginPlay()
{
	Super::BeginPlay();
	DropVolume->OnActorBeginOverlap.AddDynamic(this, &UTriggerItemComponent::ActivateTrigger);
	DropVolume->OnActorEndOverlap.AddDynamic(this, &UTriggerItemComponent::ResetTrigger);
}

void UTriggerItemComponent::ActivateTrigger(AActor* FirstActor, AActor* SecondActor)
{
	if (!ensure(DropVolume) || !ensure(TriggerActor) || !bCanActivate || SecondActor != GetOwner())
	{
		return;
	}

	bCanActivate = false;

	UGrabber* grabber = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UGrabber>();
	grabber->Release();

	OnTriggerEnterRequest.Broadcast();
	TriggerActor->SetActorHiddenInGame(true);
}

void UTriggerItemComponent::ResetTrigger(AActor* FirstActor, AActor* SecondActor)
{
	if (!ensure(DropVolume) || !ensure(TriggerActor) || SecondActor != GetOwner())
	{
		return;
	}

	bCanActivate = true;
	OnTriggerLeaveRequest.Broadcast();
	TriggerActor->SetActorHiddenInGame(false);
}