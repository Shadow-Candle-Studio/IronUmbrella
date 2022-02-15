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
	OnComponentBeginOverlap.AddDynamic(this,&USimpleAIComponentBase::WhenPlayerEnterDetectingArea);
	OnComponentEndOverlap.AddDynamic(this,&USimpleAIComponentBase::USimpleAIComponentBase::WhenPlayerOutOfDetectingArea);
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

void USimpleAIComponentBase::ActivateAiLoop()
{
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

void USimpleAIComponentBase::DeactivateAiLoop()
{
	if(GetWorld()->GetTimerManager().TimerExists(AiUpdateTimer))
	{
		GetWorld()->GetTimerManager().PauseTimer(AiUpdateTimer);
	}
	else
	{
		
	}
}

void USimpleAIComponentBase::DestroyAiLoop()
{
	if(GetWorld()->GetTimerManager().TimerExists(AiUpdateTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(AiUpdateTimer);
	}
}

void USimpleAIComponentBase::AiUpdateEvent_Implementation()
{
	//YellSomething("Oh i am running the ai update!");
}

void USimpleAIComponentBase::WhenPlayerPointerValueChanged_Implementation()
{
	//Player detected
	if(this->PlayerPointer!=nullptr)
	{
		++PlayerCommingToMyFieldTimes;
		ActivateAiLoop();
		
	}
	else //player coming out of field or dead
	{
		DeactivateAiLoop();
	}
}

void USimpleAIComponentBase::WhenPlayerEnterDetectingArea_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                      AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                      const FHitResult& SweepResult)
{
	if(OtherActor!=nullptr&&OtherActor->ActorHasTag(PlayerTag))
	{
		SetPlayerPointer(OtherActor);
	}
}


void USimpleAIComponentBase::WhenPlayerOutOfDetectingArea_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor!=nullptr&&OtherActor->ActorHasTag(PlayerTag))
	{
		SetPlayerPointer(nullptr);
		Player_LastAppearancePosition=OtherActor->GetActorLocation();
	}
}


