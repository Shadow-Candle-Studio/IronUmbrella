/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-15 
Description: This file contains the declaration of:UBP_AttackComponentBase
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "NiagaraCommon.h"
#include "Components/ActorComponent.h"
#include "BP_AttackComponentBase.generated.h"



//delegates of attack component
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);
/*
 *UBP_AttackComponentBase is responsible for
 *implementing various ways of attacking: Melee Attack ,
 *Projectile Attack, and Special Attack etc..
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable)
class IRONUMBRELLA_API UBP_AttackComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBP_AttackComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Pixel component ref in the owner, convenient for us to access
	class UPixel2DComponent* OwnerPixelCompoRef;
	//handle of the timer that enables the attack detecting
	FTimerHandle EnableAttackTimerHandle;
	//Owner as the actor
	AActor* OwningChaRef;
	//Attack detecting timer interval
	float TimerInterval=0.01f;
	//Timer function for checking the sprite frame that contains end socket, attack socket or other useful information
	void TimerFunc_CheckPossibleAttacks();
	//function for processing the hit results
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ProcessAttackHitResults(const TArray<FHitResult>& ResultsToProcess);
	void ProcessAttackHitResults_Implementation(const TArray<FHitResult>& ResultsToProcess);
	//function for checking whether the sprite contains valid attacking animation
	bool CheckIfAnyAttackExists() const;
	//float value that defines the boundary limit of the existence of attack action or not
	float AttacksocketDistAccuracy=1.0f;
	//should we pause the timer to save computing resources
	

	//Niagara system component for showing the blade vfx
	UNiagaraComponent* BladeTrailVFX;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttackEnd FOnAttackEndEvent;
	//Attack sockets prefix 
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FName AttackSocketNamePrefix="Attack_";
	//Melee Attack: event type function
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void TryMeleeAttack();
	void TryMeleeAttack_Implementation();
	UFUNCTION(BlueprintCallable)
	bool CheckIfHasAttackEndSign() const;
	//Sphere trace radius used for multi-sphere trace function
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float SphereTraceRadius=2.0f;

	virtual void DestroyComponent(bool bPromoteChildren) override;
	
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FName AttackEndSocketName="AttackEnd";
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float fAttackEndSignRelativeXvalue=1000.0f;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void enableAttackVFX(FTransform Trans);
	void enableAttackVFX_Implementation(FTransform Trans);

	//Niagara system pointer to the template BP of blade VFX
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UNiagaraSystem* TrailVFXtemplate;
};
