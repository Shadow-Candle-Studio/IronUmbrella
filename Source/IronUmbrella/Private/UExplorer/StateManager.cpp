// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/StateManager.h"

// Sets default values for this component's properties
UStateManager::UStateManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UStateManager::ComponentInitialize()
{
	Owner = GetOwner();
	ResetState();
	ClearDebuffPool();
}

void UStateManager::ComponentDestroy()
{
	Owner = nullptr;
}

void UStateManager::SetCurrentState(const EState InState)
{
	if(InState!=State)
	{
		StateChangeEvent.Broadcast(InState);
	}
	State = InState;
	if(State!=EState::Attacking)
	{
		SetCombatState(ECombatState::NULLState);
	}
	if(State!=EState::Stun)
	{
		SetStunState(EStunType::NULLState);
	}
}

EState UStateManager::GetCurrentState() const
{
	return State;
}

void UStateManager::ResetState()
{
	SetCurrentState(EState::Idle);
	SetStunState(EStunType::NULLState);
	SetCombatState(ECombatState::NULLState,1);
}

void UStateManager::SetCombatState(const ECombatState InCombat, uint8 AttackIndex)
{
	CombatStateEvent.Broadcast(InCombat,AttackIndex);
	CombatState = InCombat;
}

ECombatState UStateManager::GetCombatState() const
{
	return CombatState;
}

void UStateManager::SetStunState(const EStunType InStun)
{
	if(StunState!=InStun)
	{
		StunStateChangeEvent.Broadcast(InStun);
	}
	StunState = InStun;
}

EStunType UStateManager::GetStunState() const
{
	return StunState;
}

void UStateManager::AddDebuffState(const EDebuffState InDebuff)
{
	// Debuff池里面没有包含该Debuff
	if(!DebuffPool.Contains(InDebuff))
	{
		DebuffActiveEvent.Broadcast(InDebuff);
	}
	DebuffPool.Add(InDebuff);
}

void UStateManager::RemoveDebuff(const EDebuffState InDebuff)
{
	if(!DebuffPool.Contains(InDebuff))return;
	DebuffPool.Remove(InDebuff);
	DebuffDeActiveEvent.Broadcast(InDebuff);
}

void UStateManager::ClearDebuffPool()
{
	for(auto& Debuff:DebuffPool)
	{
		RemoveDebuff(Debuff);
	}
}

// Called when the game starts
void UStateManager::BeginPlay()
{
	Super::BeginPlay();
	ComponentInitialize();
	// ...
}


// Called every frame
void UStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

