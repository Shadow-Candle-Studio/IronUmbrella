/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author:  U
Date:2022-02-3 
Description: UStateManager
Basic features supported:
1. store all states information: idle,attack, ....etc
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "ComponentInterface.h"
#include "DataStructures.h"
#include "Components/ActorComponent.h"
#include "StateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChanged,const EState&,ChangToState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCombatStateChanged,const ECombatState&,ChangToState,uint8,AtkIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStunStateChanged,const EStunType&,ChangToState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebuffActive,const EDebuffState&,DebuffType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebuffDeActive,const EDebuffState&,DebuffType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IRONUMBRELLA_API UStateManager : public UActorComponent,public IComponentInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UStateManager();

	UFUNCTION(BlueprintCallable)
	virtual void ComponentInitialize() override;
	UFUNCTION(BlueprintCallable)
	virtual void ComponentDestroy() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnStateChanged StateChangeEvent;

	UPROPERTY(BlueprintAssignable)
	FOnCombatStateChanged CombatStateEvent;

	UPROPERTY(BlueprintAssignable)
	FOnStunStateChanged StunStateChangeEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDebuffActive DebuffActiveEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDebuffDeActive DebuffDeActiveEvent;

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(const EState InState);

	UFUNCTION(BlueprintCallable)
	EState GetCurrentState()const;

	UFUNCTION(BlueprintCallable)
	void ResetState();
	
	UFUNCTION(BlueprintCallable)
	void SetCombatState(const ECombatState InCombat,uint8 AttackIndex=1);

	UFUNCTION(BlueprintCallable)
	ECombatState GetCombatState()const;

	UFUNCTION(BlueprintCallable)
	void SetStunState(const EStunType InStun);

	UFUNCTION(BlueprintCallable)
	EStunType GetStunState()const;
	
	void AddDebuffState(const EDebuffState InDebuff);

	void RemoveDebuff(const EDebuffState InDebuff);

	void ClearDebuffPool();
private:
	UPROPERTY()
	AActor* Owner;
	EState State;
	ECombatState CombatState;
	EStunType StunState;
	TArray<EDebuffState> DebuffPool;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};


