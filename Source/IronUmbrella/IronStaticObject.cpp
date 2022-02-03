// Fill out your copyright notice in the Description page of Project Settings.


#include "IronStaticObject.h"

#include "GameFramework/PawnMovementComponent.h"

AIronStaticObject::AIronStaticObject()
{
	;
}

void AIronStaticObject::BeginPlay()
{
	Super::BeginPlay();
	GetMovementComponent()->Deactivate();
}
