// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/WeaponComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeaponComponent::ComponentInitialize()
{
	ToggleWeaponById(WeaponId);
	Owner = GetOwner();
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

bool UWeaponComponent::ToggleWeaponById(uint8 Id)
{
	return GetWeaponInfoFromDataTable(Id);
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

