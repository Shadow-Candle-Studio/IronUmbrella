// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "Components/ActorComponent.h"
#include "Pixel2DPawnSensingComponent.generated.h"

class AActor;
class AController;
class APawn;

/**
* SensingComponent encapsulates sensory (ie sight) settings and functionality for an Actor,
* allowing the actor to see Pawns in the world. It does nothing on network clients.
*/
UCLASS(ClassGroup = AI, HideCategories = (Activation, "Components|Activation", Collision), meta = (BlueprintSpawnableComponent))
class PIXEL2D_API UPixel2DPawnSensingComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeePawnDelegate, APawn*, Pawn);

	/** Max distance at which a makenoise(1.0) loudness sound can be heard, regardless of occlusion */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float HearingThreshold;

	/** Max distance at which a makenoise(1.0) loudness sound can be heard if unoccluded (LOSHearingThreshold should be > HearingThreshold) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float LOSHearingThreshold;

	/** Maximum sight distance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float SightRadius;

	/** Amount of time between pawn sensing updates. Use SetSensingInterval() to adjust this at runtime. A value <= 0 prevents any updates. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	float SensingInterval;

	// Max age of sounds we can hear. Should be greater than SensingInterval, or you might miss hearing some sounds!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float HearingMaxSoundAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pixel2DAI)
	float MinSightDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pixel2DAI)
	float MaxSightDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pixel2DAI)
	float StartAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pixel2DAI)
	float EndAngle;


public:

	/**
	* Changes the SensingInterval.
	* If we are currently waiting for an interval, this can either extend or shorten that interval.
	* A value <= 0 prevents any updates.
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "AI|Components|PawnSensing")
	virtual void SetSensingInterval(const float NewSensingInterval);

	/** Enables or disables sensing updates. The timer is reset in either case. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "AI|Components|PawnSensing")
	virtual void SetSensingUpdatesEnabled(const bool bEnabled);

	/** Sets PeripheralVisionAngle. Calculates PeripheralVisionCosine from PeripheralVisionAngle */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "AI|Components|PawnSensing")
	virtual void SetPeripheralVisionAngle(const float NewPeripheralVisionAngle);

	UFUNCTION(BlueprintCallable, Category = "AI|Components|PawnSensing")
	float GetPeripheralVisionAngle() const;

	UFUNCTION(BlueprintCallable, Category = "AI|Components|PawnSensing")
	float GetPeripheralVisionCosine() const;

	UFUNCTION(BlueprintCallable, Category = "AI|Components|PawnSensing")
	void SetStartAngle(float NewAngle);

	UFUNCTION(BlueprintCallable, Category = "AI|Components|PawnSensing")
	void SetEndAngle(float NewAngle);

	/** If true, component will perform sensing updates. At runtime change this using SetSensingUpdatesEnabled(). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	uint32 bEnableSensingUpdates : 1;

	/** If true, will only sense player-controlled pawns in the world. Default: true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	uint32 bOnlySensePlayers : 1;

	/** If true, we will perform visibility tests and will trigger notifications when a Pawn is visible. Default: true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	uint32 bSeePawns : 1;


	/** Is the given actor our owner? Used to ensure that we are not trying to sense our self / our owner. */
	virtual bool IsSensorActor(const AActor* Actor) const;

	/** Are we capable of sensing anything (and do we have any callbacks that care about sensing)? If so UpdateAISensing() will be called every sensing interval. */
	virtual bool CanSenseAnything() const;

	/** Returns true if we should check whether the given Pawn is visible (because we can see things, the Pawn is not hidden, and if the Pawn is a player and we only see players) */
	virtual bool ShouldCheckVisibilityOf(APawn* Pawn) const;

	/**
	* Chance of seeing other pawn decreases with increasing distance or angle in peripheral vision
	* @param bMaySkipChecks if true allows checks to be sometimes skipped if target is far away (used by periodic automatic visibility checks)
	* @return true if the specified pawn Other is potentially visible (within peripheral vision, etc.) - still need to do LineOfSightTo() check to see if actually visible.
	*/
	virtual bool CouldSeePawn(const APawn* Other, bool bMaySkipChecks = false) const;

	/**
	* Check line to other actor.
	* @param Other is the actor whose visibility is being checked.
	* @param ViewPoint is eye position visibility is being checked from.
	* @return true if controller's pawn can see Other actor.
	*/
	virtual bool HasLineOfSightTo(const AActor* Other) const;

	//~ Begin UActorComponent Interface.
	virtual void InitializeComponent() override;
	//~ End UActorComponent Interface.

	/** Get position where seeing occurs (i.e. eye position).  If we ever need different positions for seeing, we'll deal with that then! */
	virtual FVector GetSensorLocation() const;

	/**  Get the rotation of this sensor. We need this for the sight component */
	virtual FRotator GetSensorRotation() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

protected:

	/** See if there are interesting sounds and sights that we want to detect, and respond to them if so. */
	virtual void SensePawn(APawn& Pawn);

	/** Update function called on timer intervals. */
	virtual void OnTimer();

	/** Handle for efficient management of OnTimer timer */
	FTimerHandle TimerHandle_OnTimer;

	/** Modify the timer to fire in TimeDelay seconds. A value <= 0 disables the timer. */
	virtual void SetTimer(const float TimeDelay);

	/** Calls SensePawn on any Pawns that we are allowed to sense. */
	virtual void UpdateAISensing();

	AActor* GetSensorActor() const;	// Get the actor used as the actual sensor location is derived from this actor.
	AController* GetSensorController() const; // Get the controller of the sensor actor.

public:
	/** Delegate to execute when we see a Pawn. */
	UPROPERTY(BlueprintAssignable)
	FSeePawnDelegate OnSeePawn;

protected:

	// Broadcasts notification that our sensor sees a Pawn, using the OnSeePawn delegates.
	virtual void BroadcastOnSeePawn(APawn& Pawn);

	/** How far to the side AI can see, in degrees. Use SetPeripheralVisionAngle to change the value at runtime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	float PeripheralVisionAngle;

	/** Cosine of limits of peripheral vision. Computed from PeripheralVisionAngle. */
	UPROPERTY()
	float PeripheralVisionCosine;


	UPROPERTY()
	float StartAngleCosine;

	UPROPERTY()
	float StartAngleSine;

	UPROPERTY()
	float StartAngleRad;

	UPROPERTY()
	float EndAngleCosine;

	UPROPERTY()
	float EndAngleSine;

	UPROPERTY()
	float EndAngleRad;

};



inline float UPixel2DPawnSensingComponent::GetPeripheralVisionAngle() const
{
	return PeripheralVisionAngle;
}

inline float UPixel2DPawnSensingComponent::GetPeripheralVisionCosine() const
{
	return PeripheralVisionCosine;
}


