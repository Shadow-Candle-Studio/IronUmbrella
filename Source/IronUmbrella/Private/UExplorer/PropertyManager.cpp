// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/PropertyManager.h"



void UPropertyManager::AcquirePropertiesFromDataTable()
{
	if(!PropertyData)return;
	for(const auto &RowName:PropertyData->GetRowNames())
	{
		FPropertyStruct* Property = PropertyData->FindRow<FPropertyStruct>(RowName,FString(""));
		if(Property)
		{
			PropertyPool.Add(*Property);
		}
	}
}

void UPropertyManager::PrintProperties()
{
	if(PropertyPool.Num()>0)
	{
		for(const auto& Property:PropertyPool)
		{
			FString message;
			message+=UEnum::GetValueAsString(Property.PropertyType);
			UDebugHelper::PrintDebugMessage(message);
		}
	}
}

void UPropertyManager::ComponentInitialize()
{
	AcquirePropertiesFromDataTable();
	Owner = GetOwner();
	UActorComponent* Component = Owner->GetComponentByClass(UWeaponComponent::StaticClass());
	WeaponComponent = Cast<UWeaponComponent>(Component);
}

void UPropertyManager::ComponentDestroy()
{
	Owner = nullptr;
	WeaponComponent = nullptr;
}

// 计算自己的攻击伤害
float UPropertyManager::GaveAttackDamage(float StanceDamage)
{
	auto BaseDamageMultiplier = GetPropertyByType(EProperty::BaseDamageMultiplier);
	auto StanceDamageMultiplier = GetPropertyByType(EProperty::StanceDamageMultiplier);
	auto CritChance = GetPropertyByType(EProperty::StanceCritChanceMultiplier);
	auto CritDamage = GetPropertyByType(EProperty::StanceCritDamageMultiplier);
	float Damage = 0;
	if(!BaseDamageMultiplier||!StanceDamageMultiplier||!CritChance||!CritDamage)return Damage;
	float WeaponDamage = WeaponComponent->GetWeaponDamage();
	// 武器伤害
	Damage = WeaponDamage;
	
	// *基础伤害
	Damage = GetRatioVal(Damage,BaseDamageMultiplier->FinalVal);
	bool CritFlag = false;
	// *暴击
	if(FMath::RandRange(0,100)<=100*CritChance->FinalVal)
	{
		CritFlag = true;
		
		Damage = GetRatioVal(Damage,CritDamage->FinalVal);
	}
	// Delegate
	if(CritEvent.IsBound())
	{
		CritEvent.Broadcast(CritFlag,EDamageType::PhysicalDamage);
	}
	
	// *架势加成
	Damage = GetRatioVal(Damage,StanceDamageMultiplier->FinalVal+StanceDamage);

	UE_LOG(LogTemp,Warning,TEXT("暴击:%d  伤害:%f"),CritFlag,Damage);
	return Damage;
}

// 计算别人对自己造成的伤害
float UPropertyManager::TakeDamage(const FTakeDamageInfo& DamageInfo)
{
	float Damage = DamageInfo.Damage;
	
	// 没有无视减伤率
	if(!DamageInfo.IgnoreArmor)
	{
		// 计算减伤率
		Damage -=  Damage*GetPropertyValue(EProperty::InjuredReduceMultiplier);
		Damage = FMath::Clamp<float>(Damage,0,Damage);
	}
	
	// 物理伤害计算
	if(DamageInfo.DamageType==EDamageType::PhysicalDamage)
	{
		// 防御成功
		if(DamageInfo.GuardSuccess)
		{
			Damage-=Damage*WeaponComponent->GetWeaponGuardMultiplier();
			Damage = FMath::Clamp<float>(Damage,0,Damage);
		}
		// 防御不成功
		else 
		{
			//弹反成功
			if(DamageInfo.ParrySuccess)
			{
				Damage-=Damage*DamageInfo.ParryValue;
				Damage = FMath::Clamp<float>(Damage,0,Damage);
			}
		}
	}
	// 魔法伤害
	else if(DamageInfo.DamageType==EDamageType::MagicDamage)
	{
		
	}
	// 真实伤害
	else if(DamageInfo.DamageType==EDamageType::TrueDamage)
	{
		
	}
	return Damage;
}

// 修改属性值
bool UPropertyManager::ModifyProperty(const EProperty& PropertyType, const EModifyPropertyMethodType& ModifyMethod,
	const float InValue)
{
	const uint8 PropertyIndex = GetPropertyIndexByType(PropertyType);
	if(PropertyIndex==-1)return false;

	// 基础值直接叠加
	if(ModifyMethod == EModifyPropertyMethodType::InitValDirectStack)
	{
		PropertyPool[PropertyIndex].InitVal+= InValue;
		PropertyPool[PropertyIndex].InitVal = GetClampPropertyValue(PropertyIndex,PropertyPool[PropertyIndex].InitVal);
		if(ValueChangedEvent.IsBound())
		{
			ValueChangedEvent.Broadcast(EPropertyValueType::InitValue);
		}
	}
	// 基础值百分比叠加
	else if(ModifyMethod == EModifyPropertyMethodType::InitValRatioStack)
	{
		PropertyPool[PropertyIndex].InitVal = GetRatioVal(PropertyPool[PropertyIndex].InitVal,InValue);
		PropertyPool[PropertyIndex].InitVal = GetClampPropertyValue(PropertyIndex,PropertyPool[PropertyIndex].InitVal);
		if(ValueChangedEvent.IsBound())
		{
			ValueChangedEvent.Broadcast(EPropertyValueType::InitValue);
		}
	}
	// 最终值直接叠加
	else if(ModifyMethod == EModifyPropertyMethodType::FinalValDirectStack)
	{
		PropertyPool[PropertyIndex].FinalVal+=InValue;
		PropertyPool[PropertyIndex].FinalVal = GetClampPropertyValue(PropertyIndex,PropertyPool[PropertyIndex].FinalVal);
		if(ValueChangedEvent.IsBound())
		{
			ValueChangedEvent.Broadcast(EPropertyValueType::FinalValue);
		}
	}
	// 最终值百分比叠加
	else if(ModifyMethod == EModifyPropertyMethodType::FinalValRatioStack)
	{
		PropertyPool[PropertyIndex].FinalVal = GetRatioVal(PropertyPool[PropertyIndex].FinalVal,InValue);
		PropertyPool[PropertyIndex].FinalVal = GetClampPropertyValue(PropertyIndex,PropertyPool[PropertyIndex].FinalVal);
		if(ValueChangedEvent.IsBound())
		{
			ValueChangedEvent.Broadcast(EPropertyValueType::FinalValue);
		}
	}
	return true;
}

float UPropertyManager::GetPropertyValue(const EProperty& PropertyType)
{
	return GetPropertyByType(PropertyType)->FinalVal;
}

const FPropertyStruct* UPropertyManager::GetPropertyByType(const EProperty& PropertyType)
{
	for(const auto& Property:PropertyPool)
	{
		if(Property.PropertyType==PropertyType)
		{
			return &Property;
		}
	}
	return nullptr;
}

uint8 UPropertyManager::GetPropertyIndexByType(const EProperty& PropertyType)
{
	for(uint8 index = 0; index<PropertyPool.Num();++index)
	{
		if(PropertyPool[index].PropertyType==PropertyType)
		{
			return index;
		}
	}
	return -1;
}

float UPropertyManager::GetClampPropertyValue(uint8 PropertyIndex, float Infloat)
{
	return FMath::Clamp<float>(Infloat,PropertyPool[PropertyIndex].MinVal,PropertyPool[PropertyIndex].MaxVal);
}








// Sets default values for this component's properties
UPropertyManager::UPropertyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPropertyManager::BeginPlay()
{
	Super::BeginPlay();
	ComponentInitialize();
	// ...
	
}


// Called every frame
void UPropertyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

