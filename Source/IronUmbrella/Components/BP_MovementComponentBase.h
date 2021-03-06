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


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStateUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashStateUpdate);

//responsible for movement of a controllable2Dpawnbase instance
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable)
class IRONUMBRELLA_API UBP_MovementComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float DashingCDTimeInterVal=1.0f;
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


	UPROPERTY(BlueprintAssignable)
	FOnDashStateUpdate Delegate_DashStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnJumpStateUpdate Delegate_JumpStateChanged;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void PerformBeingAttackedBehavior(FVector InComingImpactDirection,float FinalValueMultiplier);
	void PerformBeingAttackedBehavior_Implementation(FVector InComingImpactDirection,float FinalValueMultiplier);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//referrence of character movement component constructed primitively in OwningActor
	class UCharacterMovementComponent* ChaMovementCompoRef;

	//owner of this component
	AActor* OwningActor;

	//TimerHandle for IsDash controlling
	FTimerHandle DashTimerHandle;

	//TimerHandle for Dash controlling
	FTimerHandle DashCDTimerHandle;
	
	//TimerHandle for Jump controlling
	FTimerHandle JumpTimerHandle;

	//jump count is used to constrain the ability of jumping for the player
	UPROPERTY(BlueprintReadOnly)
	uint8 JumpCount=0;

	//true: you can dash false: you have dashed,until the CD time is expired, you can not dash now
	bool CanYouDash=true;
	//Check dash over is a designed-for-timer function to
	//stop dashing when specific requirements are met
	void CheckDashOver();

	//Check jump over repeatedly detects the velocity on Z axis and
	//stop jumping when abs(Z) is nearly zero
	void CheckJumpOver();

	//give back your right to dash Again
	void AllowDashAgain()
	{
		CanYouDash=true;
	}

	void AcquireOwnerAndMovementCompo();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
	//Detect whether this pawn is dashing
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="BaseInfo")
	bool isPawnDashing=false;
};
