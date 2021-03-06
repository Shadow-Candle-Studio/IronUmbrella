// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "IronUmbrella/IronMobileObject.h"
#include "SimpleAIComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerActorPointerValueChanged);

UCLASS(ClassGroup=(Custom),Blueprintable,BlueprintType)
class IRONUMBRELLA_API USimpleAIComponentBase : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USimpleAIComponentBase();
private:
	AActor* PlayerPointer;
	FVector Player_LastAppearancePosition;
	FTimerHandle AiUpdateTimer;
	int PlayerCommingToMyFieldTimes=0;
protected:
	FOnPlayerActorPointerValueChanged WhenPlayerActorPointerValueChanged;
	const static FName PlayerTag;
	AActor* OwningCharacter;
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	//Moving acceleration multiplier
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovingInputAdditionMultiplier=200;
	//Speed of the ai updating timer when player comes into the field of a monster
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float AiUpdateTimerSpeed=0.1f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float AcceptableAttackingRadius=10.0f;
	//set the tracking target pointer
	UFUNCTION(BlueprintCallable)
	void SetPlayerPointer(AActor* in_Pplayer);

	//Get the player pointer function
	UFUNCTION(BlueprintCallable)
	AActor* GetPlayerPointer() const
	{
		return PlayerPointer;
	}
	UFUNCTION(BlueprintCallable)
	AIronMobileObject* GetOwningCharacter() const
	{
		return Cast<AIronMobileObject>(OwningCharacter);
	}
	UFUNCTION(BlueprintCallable)
	void ActivateAiLoop();
	UFUNCTION(BlueprintCallable)
	void DeactivateAiLoop();
	UFUNCTION(BlueprintNativeEvent)
	void WhenPlayerEnterDetectingArea(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
	UFUNCTION(BlueprintNativeEvent)
	void WhenPlayerOutOfDetectingArea(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent)
	void WhenPlayerPointerValueChanged();

	UFUNCTION(BlueprintNativeEvent)
	void AiUpdateEvent();

	UFUNCTION(BlueprintCallable)
	void DestroyAiLoop();
};
