// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
#include "DebugHelper.h"
#include "ComponentInterface.h"
#include "WeaponComponent.h"
#include "PropertyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageCritEvent,bool,bIsCrit,EDamageType,DamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedEvent,EPropertyValueType,ChangedValueType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IRONUMBRELLA_API UPropertyManager : public UActorComponent,public IComponentInterface
{
	GENERATED_BODY()
public:
	// 数据表
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UDataTable* PropertyData;

	// 从数据表获取属性列表
	UFUNCTION(BlueprintCallable)
	void AcquirePropertiesFromDataTable();

	
	// 初始化
	UFUNCTION(BlueprintCallable)
	virtual void ComponentInitialize() override;
	
	// 销毁
	UFUNCTION(BlueprintCallable)
	virtual void ComponentDestroy() override;

	// 计算自己的攻击伤害
	UFUNCTION(BlueprintCallable)
	float GaveAttackDamage();
	
	// 计算别人对自己造成的伤害
	UFUNCTION(BlueprintCallable)
	float TakeDamage(const FTakeDamageInfo& DamageInfo);
	
	// 修改属性值
	UFUNCTION(BlueprintCallable)
	bool ModifyProperty(const EProperty PropertyType,const EModifyPropertyMethodType ModifyMethod,const float InValue);
	
	// 代理
	UPROPERTY(BlueprintAssignable)
	FOnDamageCritEvent CritEvent;		

	UPROPERTY(BlueprintAssignable)
	FOnValueChangedEvent ValueChangedEvent;
	
	// 获取属性的值
	UFUNCTION(BlueprintCallable)
	inline float GetPropertyValue(const EProperty PropertyType);

	UPROPERTY(BlueprintReadOnly)
	AActor* Owner;

	UPROPERTY(BlueprintReadOnly)
	UWeaponComponent* WeaponComponent;

	UFUNCTION(BlueprintCallable)
	TArray<FPropertyStruct> GetPropertyPool()const;

	// 属性池
	UPROPERTY(BlueprintReadOnly,Category = "Variables")
	TArray<FPropertyStruct> PropertyPool;
protected:
	// 通过种类获得属性
	const FPropertyStruct* GetPropertyByType(const EProperty PropertyType);

	inline uint8 GetPropertyIndexByType(const EProperty PropertyType);

	// 获得百分比叠加之后的值
	float GetRatioVal(float BaseVal,float Ratio);

	// 限制数值范围
	float GetClampPropertyValue(const uint8 PropertyIndex,const float Infloat);

	bool CheckIsInit()const;
public:	

	UPropertyManager();
protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};



