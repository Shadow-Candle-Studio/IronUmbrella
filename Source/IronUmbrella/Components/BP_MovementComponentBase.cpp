// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MovementComponentBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IronUmbrella/Controllable2DPawnBase.h"


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
	AControllable2DPawnBase * Cha=Cast<AControllable2DPawnBase>(OwningActor);
	if(Cha!=nullptr&&ChaMovementCompoRef!=nullptr)
	{
		
		if(!Cha->isDashing)
		{
			//UE_LOG(LogTemp,Warning,L"Check dashed ")
			ChaMovementCompoRef->SetMovementMode(EMovementMode::MOVE_Falling);
			ChaMovementCompoRef->Velocity=FVector
			(Cha->GetYourCharacterSprite()->
				GetForwardVector()*DashSpeed);
			GetWorld()->GetTimerManager().
			SetTimer(DashTimerHandle,
				this,
				&UBP_MovementComponentBase::CheckDashOver,
				DashDuration,false,-1);
			Cha->isDashing=true;
			
		}
	}
}

void UBP_MovementComponentBase::Jump_Implementation(float JumpVelocity)
{
	AControllable2DPawnBase * Cha=Cast<AControllable2DPawnBase>(OwningActor);
	if(Cha!=nullptr)
	{
		if(JumpCount<JumpMaxCountLimit&&!Cha->isDashing)
		{
			Cha->GetCharacterMovement()->
			SetMovementMode(EMovementMode::MOVE_Falling);
			Cha->GetCharacterMovement()->
			Velocity=FVector(0,0,JumpVelocity);
			GetWorld()->GetTimerManager().
			SetTimer(JumpTimerHandle,
				this,&UBP_MovementComponentBase::CheckJumpOver,
				0.1,true,-1);
			Cha->isFalling=true;
			JumpCount++;
			///UE_LOG(LogTemp,Warning,L"Jump")
			
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
	AControllable2DPawnBase * Cha=Cast<AControllable2DPawnBase>(OwningActor);
	if(Cha!=nullptr)
	{
		Cha->isDashing=false;
		GetWorld()->GetTimerManager().ClearTimer(DashTimerHandle);
		Cha->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void UBP_MovementComponentBase::CheckJumpOver()
{
	//UE_LOG(LogTemp,Warning,L"JumpOverChecking")
	AControllable2DPawnBase * Cha=Cast<AControllable2DPawnBase>(OwningActor);
	if(Cha!=nullptr&&abs(Cha->GetVelocity().Z)<=0.0f&&Cha->isFalling)
	{
		Cha->isFalling=false;
		GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
		Cha->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		JumpCount=0;
		
	}
}

// Called every frame
void UBP_MovementComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

