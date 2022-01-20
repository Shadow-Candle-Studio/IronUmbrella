/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-15 
Description: This file contains the declaration of:UBP_MovementComponentBase
**************************************************/ 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BP_MovementComponentBase.generated.h"

//responsible for movement of a controllable2Dpawnbase instance
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IRONUMBRELLA_API UBP_MovementComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:

	
	
	// Sets default values for this component's properties
	UBP_MovementComponentBase();

	//Max times you can jum continuously
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	uint8 JumpMaxCountLimit=2;

	//Move function to mave the pawn
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Move(APawn* Cha,float MoveValue);
	void Move_Implementation(APawn* Cha,float MoveValue);

	//Dash function performs dash action of a pawn
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Dash(float DashSpeed,float DashDuration);
	void Dash_Implementation(float DashSpeed, float DashDuration);

	//jump function for performing jump action of a pawn
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Jump(float JumpVelocity);
	void Jump_Implementation(float JumpVelocity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//referrence of character movement component constructed primitively in OwningActor
	class UCharacterMovementComponent* ChaMovementCompoRef;

	//owner of this component
	AActor* OwningActor;

	//TimerHandle for Dash controlling
	FTimerHandle DashTimerHandle;

	//TimerHandle for Jump controlling
	FTimerHandle JumpTimerHandle;

	//jump count is used to constrain the ability of jumping for the player
	UPROPERTY(BlueprintReadOnly)
	uint8 JumpCount=0;

	//Check dash over is a designed-for-timer function to
	//stop dashing when specific requirements are met 
	void CheckDashOver();

	//Check jump over repeatedly detects the velocity on Z axis and
	//stop jumping when abs(Z) is nearly zero
	void CheckJumpOver();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
