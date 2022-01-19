// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_AttackComponentBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BP_MovementComponentBase.h"
#include "Pixel2DComponent.h"
#include "IronUmbrella/Controllable2DPawnBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UBP_AttackComponentBase::UBP_AttackComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	
	
	// ...
}


// Called when the game starts
void UBP_AttackComponentBase::BeginPlay()
{
	Super::BeginPlay();
	OwningChaRef=GetOwner();
	AControllable2DPawnBase * Cha=Cast<AControllable2DPawnBase>(OwningChaRef);
	if(Cha!=nullptr)
	{
		OwnerPixelCompoRef=Cast
		<UPixel2DComponent>(Cha->GetYourCharacterSprite());
	}
	if(nullptr==OwningChaRef||OwnerPixelCompoRef==nullptr)
	{
		
	}
	if(OwnerPixelCompoRef!=nullptr)
	{
		
		BladeTrailVFX=
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,
			TrailVFXtemplate,
			OwnerPixelCompoRef->GetComponentLocation(),
			FRotator::ZeroRotator,
			FVector(0.1),
			false,
			false,ENCPoolMethod::None);
		if(BladeTrailVFX==nullptr)
		{
			YellSomething(TEXT("UBP_AttackComponentBase: spawned VFX is not usable!"))
		}
	}
}

void UBP_AttackComponentBase::TimerFunc_CheckPossibleAttacks()
{
	//pause the timer if the timer is active and we have a attack end sign
	if(CheckIfHasAttackEndSign()&&
		GetWorld()->GetTimerManager().IsTimerActive(EnableAttackTimerHandle))
	{
		//UE_LOG(LogTemp,Warning,L"Pause timer")
		GetWorld()->GetTimerManager().PauseTimer(EnableAttackTimerHandle);
	}
	//process all attack collision
	if(CheckIfAnyAttackExists())
	{
		TArray<FName> Attacksockets;
		int i=0;
		while(i<50)
		{
			FString Socket_i(AttackSocketNamePrefix.ToString());
			Socket_i.AppendInt(i++);
			if(OwnerPixelCompoRef->DoesSocketExist(FName(*Socket_i)))
			{
				Attacksockets.Emplace(*Socket_i);
			}
			else
			{
				break;
			}
		}
		for(int index=0;index<Attacksockets.Num()-1;index++)
		{
			FString Socket_i(AttackSocketNamePrefix.ToString());
			Socket_i.AppendInt(index);
			
			FString Socket_i_plus_1(AttackSocketNamePrefix.ToString());
			Socket_i_plus_1.AppendInt(index+1);
			TArray<FHitResult> OutResults;
			FCollisionShape SweepShape=FCollisionShape::MakeSphere(SphereTraceRadius);
			FCollisionQueryParams CQueryParams=FCollisionQueryParams::DefaultQueryParam;
			FCollisionResponseParams CResponseParams=FCollisionResponseParams::DefaultResponseParam;
			//Fcollision sweeping
			CQueryParams.bTraceComplex=true;
			CQueryParams.AddIgnoredActor(OwningChaRef);
			GetWorld()->SweepMultiByChannel(OutResults,
				OwnerPixelCompoRef->GetSocketLocation(FName(*Socket_i)),
				OwnerPixelCompoRef->GetSocketLocation(FName(*Socket_i_plus_1)),
				FQuat::Identity,ECollisionChannel::ECC_Camera,
				SweepShape,
				CQueryParams,
				CResponseParams);
			if(OutResults.Num()>0)
			{
				ProcessAttackHitResults(OutResults);
			}
			
		}
		
	}
}

void UBP_AttackComponentBase::ProcessAttackHitResults(const TArray<FHitResult>& ResultsToProcess)
{
	for(auto &p:ResultsToProcess)
	{
		if(p.Actor.IsValid()&&OwningChaRef!=nullptr)
		{
			// auto m=Cast<UBP_MovementComponentBase>(Cast<AControllable2DPawnBase>(p.Actor)->
			// 	GetComponentByClass(UBP_MovementComponentBase::StaticClass()));
			// if(m!=nullptr)
			// {
			// 	m->Jump(400);
			// }
			FTransform m(FRotator::ZeroRotator,p.ImpactPoint,FVector(0.01));
			enableAttackVFX(m);
			UE_LOG(LogTemp,Warning,L"We have attacked %s",*p.Actor->GetName())
			if(Cast<AControllable2DPawnBase>(OwningChaRef)!=nullptr)
			UGameplayStatics::ApplyDamage(p.Actor.Get(),
				100,
				Cast<AControllable2DPawnBase>(OwningChaRef)->GetController(),
				OwningChaRef,
				UDamageType::StaticClass());
		}
		
	}
}

bool UBP_AttackComponentBase::CheckIfAnyAttackExists() const
{
	if(OwnerPixelCompoRef!=nullptr&&OwnerPixelCompoRef->HasAnySockets())
	{
		FString Socket1=AttackSocketNamePrefix.ToString();
		Socket1.AppendInt(0);
		FString Socket2=AttackSocketNamePrefix.ToString();
		Socket2.AppendInt(1);
		if(OwnerPixelCompoRef->DoesSocketExist(FName(*Socket1))&&
			OwnerPixelCompoRef->DoesSocketExist(FName(*Socket2))&&
			FVector::Distance(OwnerPixelCompoRef->GetSocketLocation(FName(*Socket1)),
				OwnerPixelCompoRef->GetSocketLocation(FName(*Socket2)))>AttacksocketDistAccuracy)
					return true;
		
		
	}
	return false;
}

bool UBP_AttackComponentBase::CheckIfHasAttackEndSign() const
{
	if(OwnerPixelCompoRef!=nullptr&&OwnerPixelCompoRef->HasAnySockets())
	{
		if(abs((OwnerPixelCompoRef->GetSocketLocation(AttackEndSocketName)-
			OwnerPixelCompoRef->GetComponentLocation()).X)==
			fAttackEndSignRelativeXvalue)
		{
			return true;
		}
		
	}
	return false;
}

void UBP_AttackComponentBase::TryMeleeAttack_Implementation()
{
	FTimerManager& TimerManagerInUse=GetWorld()->GetTimerManager();
	if(TimerManagerInUse.TimerExists(EnableAttackTimerHandle))
	{
		//if the timer is not active which means that it is paused
		if(!TimerManagerInUse.IsTimerActive(EnableAttackTimerHandle))
		{
			//UE_LOG(LogTemp,Warning,L"Unpause timer")
			TimerManagerInUse.UnPauseTimer(EnableAttackTimerHandle);
		}
	}
	else
	{
		//UE_LOG(LogTemp,Warning,L"New timer")
		TimerManagerInUse.SetTimer
		(EnableAttackTimerHandle,
			this,&UBP_AttackComponentBase::TimerFunc_CheckPossibleAttacks,
			TimerInterval,
			true,
			-1);
	}
}

void UBP_AttackComponentBase::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
	//DestroyComponent(TrailVFXtemplate);
	
	
}

void UBP_AttackComponentBase::enableAttackVFX_Implementation(FTransform Trans)
{
	if(BladeTrailVFX!=nullptr)
	{
		BladeTrailVFX->SetWorldTransform(Trans);
		BladeTrailVFX->Activate(true);
	}
}



