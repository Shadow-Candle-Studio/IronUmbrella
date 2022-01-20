// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentInterface.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
#include "DebugHelper.h"
#include "WeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IRONUMBRELLA_API UWeaponComponent : public UActorComponent,public IComponentInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	UFUNCTION(BlueprintCallable)
	virtual void ComponentInitialize() override;
	UFUNCTION(BlueprintCallable)
	virtual void ComponentDestroy() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UDataTable* WeaponTable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	uint8 WeaponId;

	UPROPERTY(BlueprintReadOnly)
	FWeaponInfo WeaponInfo;

	UPROPERTY(BlueprintReadOnly)
	AActor* Owner;
	
	UPROPERTY(BlueprintReadOnly)
	float StanceDamage;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<uint8,float> StanceMultiplMap;
	
	UPROPERTY(BlueprintReadOnly)
	class UStateManager* StateManager;

	void ChangeStanceDamage(const ECombatState& InState,uint8 AttackIndex);
	
	bool GetWeaponInfoFromDataTable(uint8 Id);

	UFUNCTION(BlueprintCallable)
	float GetWeaponDamage()const;

	UFUNCTION(BlueprintCallable)
	float GetWeaponGuardMultiplier()const;

	UFUNCTION(BlueprintCallable)
	float GetStanceDamage()const;

	UFUNCTION(BlueprintCallable)
	TMap<uint8,float> GetStanceMultiMap()const;
	
	UFUNCTION(BlueprintCallable)
	bool ToggleWeaponById(uint8 Id);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};


