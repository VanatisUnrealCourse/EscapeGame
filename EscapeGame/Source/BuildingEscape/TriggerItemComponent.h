// Copyright Cédric Van de Walle 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TriggerItemComponent.generated.h"

class AOpenableDoor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerEnterRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerLeaveRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UTriggerItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerItemComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ActivateTrigger(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION()
	void ResetTrigger(AActor* FirstActor, AActor* SecondActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* TriggerActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AOpenableDoor* DoorToOpen = nullptr;

private:
	//Exposed variables in editor
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DropVolume = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerEnterRequest OnTriggerEnterRequest;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerLeaveRequest OnTriggerLeaveRequest;

	bool bCanActivate = true;
};
