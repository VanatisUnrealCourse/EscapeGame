// Copyright Cédric Van de Walle 2017

#pragma once

#include "GameFramework/Actor.h"
#include "OpenableDoor.generated.h"

class UOpenDoor;

UCLASS()
class BUILDINGESCAPE_API AOpenableDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenableDoor();

private:
	UOpenDoor* OpenDoorComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh = nullptr;
};
