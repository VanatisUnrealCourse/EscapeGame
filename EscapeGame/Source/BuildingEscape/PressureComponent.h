// Copyright Cédric Van de Walle 2017

#pragma once

#include "Components/ActorComponent.h"
#include "PressureComponent.generated.h"

class AOpenableDoor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoorRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressureComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPressureComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float GetTotalMassOfActorsOnPlate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AOpenableDoor* DoorToOpen = nullptr;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 30.f;

	UPROPERTY(BlueprintAssignable)
		FOnOpenDoorRequest OnOpenDoorRequest;

	UPROPERTY(BlueprintAssignable)
		FOnCloseDoorRequest OnCloseDoorRequest;

	bool bCanActivate = true;
	
};
