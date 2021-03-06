// Copyright Cédric Van de Walle 2017

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Keep grabbed object moving
	if (!PhysicsHandlePtr) { return; }
	if (PhysicsHandlePtr->GrabbedComponent)
	{
		PhysicsHandlePtr->SetTargetLocation(GetReachLineEnd());
		PhysicsHandlePtr->GrabbedComponent->SetMobility(EComponentMobility::Movable);
	}
}

void UGrabber::Grab()
{
	FHitResult hitResult = GetFirstPhysicsBodyInReach();
	if (hitResult.GetActor())
	{
		UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
		PhysicsHandlePtr->GrabComponentAtLocationWithRotation(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			componentToGrab->GetOwner()->GetActorRotation());

		//componentToGrab->SetMobility(EComponentMobility::Static);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandlePtr) { return; }
	if (PhysicsHandlePtr->GrabbedComponent)
	{
		PhysicsHandlePtr->ReleaseComponent();
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandlePtr = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandlePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandleComponent"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponentPtr = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponentPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *(GetOwner()->GetName()));
	}
	else
	{
		InputComponentPtr->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponentPtr->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult hitResult;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams);
	
	return hitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

	return location;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

	return location + rotation.Vector() * Reach;
}
