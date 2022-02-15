// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAIComponentBase.h"

#include "IronUmbrella/AllStructuresAndEnums.h"
#include "IronUmbrella/IronMobileObject.h"

const FName USimpleAIComponentBase::PlayerTag=FName(TEXT("MainPlayer"));
// Sets default values for this component's properties
USimpleAIComponentBase::USimpleAIComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	
	// ...
}


// Called when the game starts
void USimpleAIComponentBase::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this,&USimpleAIComponentBase::WhenComponentBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this,&USimpleAIComponentBase::WhenComponentEndOverlap);
	WhenPlayerActorPointerValueChanged.AddDynamic(this,&USimpleAIComponentBase::WhenPlayerPointerValueChanged);

	
	OwningCharacter=GetOwner();
	if(OwningCharacter==nullptr)
	{
		YellSomething("Ai pawn owner getting failure")
	}
	else
	{
		AIronMobileObject* Cha=Cast<AIronMobileObject>(OwningCharacter);
		if(Cha!=nullptr)
		{
			
		}
	}

	
	// ...
	
}

void USimpleAIComponentBase::SetPlayerPointer(AActor* in_Pplayer)
{
	if(in_Pplayer!=this->PlayerPointer)
	{
		this->PlayerPointer=in_Pplayer;
		WhenPlayerActorPointerValueChanged.Broadcast();
	}
}

void USimpleAIComponentBase::AiUpdateEvent_Implementation()
{
	;
}

void USimpleAIComponentBase::WhenPlayerPointerValueChanged_Implementation()
{
	//Player detected
	if(this->PlayerPointer!=nullptr)
	{
		++PlayerCommingToMyFieldTimes;
		//timer exists so you only need to unpause it and use it
		if(GetWorld()->GetTimerManager().TimerExists(AiUpdateTimer))
		{
			GetWorld()->GetTimerManager().UnPauseTimer(AiUpdateTimer);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer
			(AiUpdateTimer,this,
				&USimpleAIComponentBase::AiUpdateEvent,
				AiUpdateTimerSpeed,
				true,
				-1);
		}
	}
	else //player coming out of field or dead
	{
		if(GetWorld()->GetTimerManager().TimerExists(AiUpdateTimer))
		{
			GetWorld()->GetTimerManager().PauseTimer(AiUpdateTimer);
		}
	}
}

void USimpleAIComponentBase::WhenComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                      AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                      const FHitResult& SweepResult)
{
	if(OtherActor!=nullptr&&OtherActor->ActorHasTag(PlayerTag))
	{
		SetPlayerPointer(OtherActor);
	}
}


void USimpleAIComponentBase::WhenComponentEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor!=nullptr&&OtherActor->ActorHasTag(PlayerTag))
	{
		SetPlayerPointer(nullptr);
	}
}


