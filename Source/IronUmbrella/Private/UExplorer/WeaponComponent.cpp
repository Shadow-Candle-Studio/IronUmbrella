// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/WeaponComponent.h"
#include "UExplorer/StateManager.h"
#include "UExplorer/StateManager.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UWeaponComponent::ComponentInitialize()
{
	ToggleWeaponById(WeaponId);
	Owner = GetOwner();
	const auto tmp = Owner->GetComponentByClass(UStateManager::StaticClass());
	if(tmp)
	{
		StateManager = Cast<UStateManager>(tmp);
		StateManager->CombatStateEvent.AddDynamic(this,&UWeaponComponent::ChangeStanceDamage);
	}
}

void UWeaponComponent::ChangeStanceDamage(const ECombatState& InState,uint8 AttackIndex)
{
	if(InState==ECombatState::CommonAtk)
	{
		StanceDamage = *WeaponInfo.StanceDamageMap.Find(AttackIndex);
	}
}

void UWeaponComponent::ComponentDestroy()
{
	Owner = nullptr;
}


bool UWeaponComponent::GetWeaponInfoFromDataTable(uint8 Id)
{
	if(!WeaponTable)
	{
		UDebugHelper::PrintDebugMessage(FString("WeaponTable Is Not Valid!"));
		return false;
	}
	
	FWeaponInfo* InfoPtr = WeaponTable->FindRow<FWeaponInfo>(*FString::FromInt(Id),FString(""));
	if(InfoPtr)
	{
		WeaponInfo = *InfoPtr;
		return true;
	}else
	{
		UDebugHelper::PrintDebugMessage(FString("Not Found Weapon!"));
		return false;
	}
}

float UWeaponComponent::GetWeaponDamage()const
{
	return WeaponInfo.WeaponDamage;
}

float UWeaponComponent::GetWeaponGuardMultiplier()const
{
	return WeaponInfo.GuardMultiplier;
}

float UWeaponComponent::GetStanceDamage() const
{
	return StanceDamage;
}


float UWeaponComponent::GetSpecialAtkDamage() const
{
	return WeaponInfo.SpecialAtkDamagMultiplier;
}

bool UWeaponComponent::ToggleWeaponById(uint8 Id)
{
	return GetWeaponInfoFromDataTable(Id);
}

float UWeaponComponent::GetParryMuptiplier(const EParryType ParryType)
{
	return *WeaponInfo.ParryMap.Find(ParryType);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	ComponentInitialize();
	// ...
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

