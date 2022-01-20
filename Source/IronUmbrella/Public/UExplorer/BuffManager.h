// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentInterface.h"
#include "DataStructures.h"
#include "PropertyManager.h"
#include "StateManager.h"
#include "UExplorer/Buffs/BuffBase.h"
#include "Components/ActorComponent.h"
#include "BuffManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffRunning,TSubclassOf<ABuffBase>,BuffClass);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffFinished,TSubclassOf<ABuffBase>,BuffClass);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IRONUMBRELLA_API UBuffManager : public UActorComponent,public IComponentInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UBuffManager();
	virtual void ComponentInitialize() override;
	virtual void ComponentDestroy() override;

	void GetEssentialVar();
	UFUNCTION(BlueprintCallable)
	void AcquiredBuff(TSubclassOf<ABuffBase>BuffClass,AActor* Effector,AActor* Caster);

	UPROPERTY(BlueprintAssignable)
	FOnBuffRunning BuffRunEvent;

	UPROPERTY(BlueprintAssignable)
	FOnBuffFinished BuffFinishedEvent;

	UFUNCTION(BlueprintCallable)
	void ClearBuffPool();
	
	void AddBuff(ABuffBase* BuffActor);
	void RemoveBuffByClass(TSubclassOf<ABuffBase> Class);
	bool IsBuffContains(TSubclassOf<ABuffBase> Class)const;
	uint8 GetBuffIndexByClass(TSubclassOf<ABuffBase> Class);
	
private:
	AActor* Owner;
	UPropertyManager* OwnerProperty;
	UStateManager* OwnerState;
	TArray<ABuffBase*> BuffPool;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};



