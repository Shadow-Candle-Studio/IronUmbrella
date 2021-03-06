/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: U
Date:2022-02-3 
Description: weapon component 
Basic features supported:
1. store all weapon values
**************************************************/ 
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
	class UStateManager* StateManager;

	UFUNCTION(BlueprintCallable)
	void ChangeStanceDamage(const ECombatState& InState,uint8 AttackIndex);
	
	bool GetWeaponInfoFromDataTable(uint8 Id);

	UFUNCTION(BlueprintCallable)
	float GetWeaponDamage()const;

	UFUNCTION(BlueprintCallable)
	float GetWeaponGuardMultiplier()const;

	UFUNCTION(BlueprintCallable)
	float GetStanceDamage()const;
	
	UFUNCTION(BlueprintCallable)
	float GetSpecialAtkDamage()const;
	
	UFUNCTION(BlueprintCallable)
	bool ToggleWeaponById(uint8 Id);

	UFUNCTION(BlueprintCallable)
	float GetParryMuptiplier(const EParryType ParryType);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};



