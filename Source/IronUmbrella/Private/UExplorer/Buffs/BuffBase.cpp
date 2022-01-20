// Fill out your copyright notice in the Description page of Project Settings.


#include "UExplorer/Buffs/BuffBase.h"
#include "UExplorer/BuffManager.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABuffBase::ABuffBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TryLoadDataTable();
}

void ABuffBase::AcquireBuffInfoFromDataTable()
{
	if(BuffTable==nullptr)return;
	auto InfoPtr = BuffTable->FindRow<FBuffInfo>(*FString::FromInt(Id),FString(""));
	if(InfoPtr)
	{
		Info = *InfoPtr;
		UDebugHelper::PrintDebugMessage(Info.Name.ToString());
	}
	else
	{
		UDebugHelper::PrintDebugMessage("Acquire Buff Info Failed");
	}
}

bool ABuffBase::BuffAwake_Implementation()
{
	return IBuffInterface::BuffAwake_Implementation();
}

bool ABuffBase::BuffStart_Implementation()
{
	return IBuffInterface::BuffStart_Implementation();
}

bool ABuffBase::BuffRunning_Implementation()
{
	return IBuffInterface::BuffRunning_Implementation();
}

bool ABuffBase::BuffFinished_Implementation()
{
	return IBuffInterface::BuffFinished_Implementation();
}

bool ABuffBase::BuffDestroy_Implementation()
{
	return IBuffInterface::BuffDestroy_Implementation();
}


void ABuffBase::Overlay()
{
	
}

void ABuffBase::SetBuffState(const EBuffState InState)
{
	if(State!=InState)
	{
		GetWorldTimerManager().UnPauseTimer(StatuHandle);
	} 
	State = InState;
}

void ABuffBase::TryAwakeBuff(AActor* InCaster,AActor* InOwner)
{
	AcquireBuffInfoFromDataTable();
	GetEssentialVar(InCaster,InOwner);
	if(BuffTable==nullptr)return;
	Execute_BuffAwake(this);
	GetWorldTimerManager().SetTimer(StatuHandle,this,&ABuffBase::UpdateBuffState,0.1f,true);
}

void ABuffBase::GetEssentialVar(AActor* InCaster,AActor* InOwner)
{
	Caster = InCaster;
	Effector = InOwner;
	if(!Effector)return;
	auto tmpPtr = Effector->GetComponentByClass(UBuffManager::StaticClass());
	
	if(!tmpPtr)return;
	BuffManager = Cast<UBuffManager>(tmpPtr);
	
	tmpPtr = Effector->GetComponentByClass(UPropertyManager::StaticClass());
	if(!tmpPtr)return;
	
	PropertyManager = Cast<UPropertyManager>(tmpPtr);
	
	tmpPtr = Effector->GetComponentByClass(UStateManager::StaticClass());
	
	if(!tmpPtr)return;
	StateManager = Cast<UStateManager>(tmpPtr);
}

void ABuffBase::TryLoadDataTable()
{
	ConstructorHelpers::FObjectFinder<UDataTable> findInfo(*BuffDataAddr);
	if(findInfo.Succeeded())
	{
		BuffTable = findInfo.Object;
		UE_LOG(LogTemp,Warning,TEXT("Load Buff Table Success"));
	}
}

void ABuffBase::UpdateBuffState()
{
	if(State==EBuffState::Waiting)
	{
		GetWorldTimerManager().PauseTimer(StatuHandle);
		Execute_BuffStart(this);
	}
	else if(State==EBuffState::Running)
	{
		GetWorldTimerManager().PauseTimer(StatuHandle);
		BuffManager->AddBuff(this);
		Execute_BuffRunning(this);
	}
	else if(State==EBuffState::Finished)
	{
		GetWorldTimerManager().PauseTimer(StatuHandle);
		Execute_BuffFinished(this);
		BuffManager->RemoveBuffByClass(this->StaticClass());
	}
	else if(State==EBuffState::Dead)
	{
		GetWorldTimerManager().ClearTimer(StatuHandle);
		Execute_BuffDestroy(this);
	}
}

// Called when the game starts or when spawned
void ABuffBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuffBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

