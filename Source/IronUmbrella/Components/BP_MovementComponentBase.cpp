// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MovementComponentBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IronUmbrella/IronMobileObject.h"


// Sets default values for this component's properties
UBP_MovementComponentBase::UBP_MovementComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}


void UBP_MovementComponentBase::Move_Implementation(APawn* Cha, float MoveValue)
{
	if(Cha!=nullptr)
	{
		if(MoveValue!=0.0f)
		{
			Cha->AddMovementInput
			(FVector
				(1.0f,
					0.0f,
					0.0f),MoveValue);
			
		}
	}
	
}

void UBP_MovementComponentBase::Dash_Implementation(float DashSpeed, float DashDuration)
{
	AIronMobileObject * Cha=Cast<AIronMobileObject>(OwningActor);
	if(Cha!=nullptr&&ChaMovementCompoRef!=nullptr)
	{
		
		if(!isPawnDashing&&CanYouDash)
		{
			CanYouDash=false;
			ChaMovementCompoRef->SetMovementMode(EMovementMode::MOVE_Falling);
			ChaMovementCompoRef->Velocity=FVector
			(Cha->GetYourCharacterSprite()->
				GetForwardVector()*DashSpeed);
			GetWorld()->GetTimerManager().
			SetTimer(DashTimerHandle,
				this,
				&UBP_MovementComponentBase::CheckDashOver,
				DashDuration,false,-1);
			isPawnDashing=true;
			Delegate_DashStateChanged.Broadcast();
			GetWorld()->GetTimerManager().SetTimer
			(DashCDTimerHandle,
				this,&UBP_MovementComponentBase::AllowDashAgain,
				DashingCDTimeInterVal,
				false,
				-1);
		}
	}
}

void UBP_MovementComponentBase::Jump_Implementation(float JumpVelocity)
{
	
	AIronMobileObject * Cha=Cast<AIronMobileObject>(OwningActor);
	if(Cha!=nullptr)
	{
		if(JumpCount<JumpMaxCountLimit&&!isPawnDashing)
		{
			
			Cha->GetCharacterMovement()->
			SetMovementMode(EMovementMode::MOVE_Falling);
			Cha->GetCharacterMovement()->
			Velocity=FVector(0,0,JumpVelocity);
			GetWorld()->GetTimerManager().
			SetTimer(JumpTimerHandle,
				this,&UBP_MovementComponentBase::CheckJumpOver,
				0.1,true,-1);
			isPawnFalling=true;
			Delegate_JumpStateChanged.Broadcast();
			JumpCount++;
		}
		
	}
}

// Called when the game starts
void UBP_MovementComponentBase::BeginPlay()
{
	Super::BeginPlay();
	// ...
	OwningActor=GetOwner();
	ChaMovementCompoRef=Cast<UCharacterMovementComponent>(
		OwningActor->GetComponentByClass
		(UCharacterMovementComponent::StaticClass()));
	
	
}


void UBP_MovementComponentBase::CheckDashOver()
{
	AIronMobileObject * Cha=Cast<AIronMobileObject>(OwningActor);
	if(Cha!=nullptr)
	{
		isPawnDashing=false;
		Delegate_DashStateChanged.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(DashTimerHandle);
		Cha->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void UBP_MovementComponentBase::CheckJumpOver()
{
	
	AIronMobileObject * Cha=Cast<AIronMobileObject>(OwningActor);
	if(Cha!=nullptr&&abs(Cha->GetVelocity().Z)<=0.0f&&isPawnFalling)
	{
		isPawnFalling=false;
		GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
		Cha->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		JumpCount=0;
		Delegate_JumpStateChanged.Broadcast();
	}
}

// Called every frame
void UBP_MovementComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

