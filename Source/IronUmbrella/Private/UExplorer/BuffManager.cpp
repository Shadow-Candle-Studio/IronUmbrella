// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/BuffManager.h"

// Sets default values for this component's properties
UBuffManager::UBuffManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UBuffManager::ComponentInitialize()
{
	GetEssentialVar();
	ClearBuffPool();
}

void UBuffManager::ComponentDestroy()
{
	ClearBuffPool();
}

void UBuffManager::GetEssentialVar()
{
	Owner = GetOwner();
	auto tmpPtr = Owner->GetComponentByClass(UPropertyManager::StaticClass());
	if(!tmpPtr)
	{
		UDebugHelper::PrintDebugMessage(FString("Buff Manager Get Essential Var Failed!"));
	}
	OwnerProperty = Cast<UPropertyManager>(tmpPtr);
	tmpPtr = Owner->GetComponentByClass(UStateManager::StaticClass());
	if(!tmpPtr)
	{
		UDebugHelper::PrintDebugMessage(FString("Buff Manager Get Essential Var Failed!"));
	}
	OwnerState = Cast<UStateManager>(tmpPtr);
}

void UBuffManager::ClearBuffPool()
{
	if(BuffPool.Num()>0)
	{
		for(auto Buff:BuffPool)
		{
			RemoveBuffByClass(Buff->StaticClass());
		}
	}
}

void UBuffManager::AcquiredBuff(TSubclassOf<ABuffBase> BuffClass, AActor* Effector,AActor* Caster)
{
	if(!BuffClass||!Effector)return;
	if(Effector!=Owner)
	{
		const auto ptr = Effector->GetComponentByClass(this->StaticClass());
		if(!ptr)return;
		UBuffManager* Manager = Cast<UBuffManager>(ptr);
		Manager->AcquiredBuff(BuffClass,Effector,Caster);
	}
	// Buff存在
	if(IsBuffContains(BuffClass))
	{
		const uint8 Index = GetBuffIndexByClass(BuffClass);
		BuffPool[Index]->Overlay();
	}
	// Buff不存在
	else
	{
		ABuffBase* BuffActor = GetWorld()->SpawnActor<ABuffBase>(BuffClass,FVector::ZeroVector,FRotator::ZeroRotator);
		BuffActor->TryAwakeBuff(Caster,Effector);
	}
}

void UBuffManager::AddBuff(ABuffBase* BuffActor)
{
	BuffPool.Add(BuffActor);
	if(BuffRunEvent.IsBound())
	{
		BuffRunEvent.Broadcast(BuffActor->StaticClass());
	}
}

void UBuffManager::RemoveBuffByClass(TSubclassOf<ABuffBase> Class)
{
	if(IsBuffContains(Class))
	{
		const auto Index = GetBuffIndexByClass(Class);
		BuffPool.RemoveAt(Index);
		if(BuffRunEvent.IsBound())
		{
			BuffRunEvent.Broadcast(Class);
		}
	}
}

bool UBuffManager::IsBuffContains(TSubclassOf<ABuffBase> Class) const
{
	for(const ABuffBase* Buff:BuffPool)
	{
		if(Buff->StaticClass()==Class)return true;
	}
	return false;
}

uint8 UBuffManager::GetBuffIndexByClass(TSubclassOf<ABuffBase> Class)
{
	uint8 Index = -1;
	for(Index = 0;Index<BuffPool.Num();++Index)
	{
		if(BuffPool[Index]->StaticClass()==Class)return Index;
	}
	return Index;
}


// Called when the game starts
void UBuffManager::BeginPlay()
{
	Super::BeginPlay();
	ComponentInitialize();
	// ...
}


// Called every frame
void UBuffManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

