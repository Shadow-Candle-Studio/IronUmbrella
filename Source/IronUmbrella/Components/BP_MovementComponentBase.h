// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BP_MovementComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IRONUMBRELLA_API UBP_MovementComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBP_MovementComponentBase();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	uint8 JumpMaxCountLimit;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Move(APawn* Cha,float MoveValue);
	void Move_Implementation(APawn* Cha,float MoveValue);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	class UCharacterMovementComponent* ChaMovementCompoRef;
	AActor* OwningActor;
	FTimerHandle DashTimerHanle;
	FTimerHandle JumpTimerHandle;
	BYTE JumpCount;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
