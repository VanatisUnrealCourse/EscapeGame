// Copyright Cédric Van de Walle 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"
#include "OpenableDoor.h"


// Sets default values
AOpenableDoor::AOpenableDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorMesh"));
	RootComponent = DoorMesh;
}