// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MovementComponentBase.h"


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
	
}

// Called when the game starts
void UBP_MovementComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBP_MovementComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

