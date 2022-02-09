// Fill out your copyright notice in the Description page of Project Settings.


#include "IronBasicObject.h"

#include "AllStructuresAndEnums.h"
#include "Pixel2DComponent.h"
#include "Components/CapsuleComponent.h"
const float AIronBasicObject::AllObjectsYBaseLineValue=0.0f;

void AIronBasicObject::RepairYlineOffset()
{
	FVector Location=GetActorLocation();
	SetActorLocation(FVector(Location.X,AllObjectsYBaseLineValue,Location.Z));
}

AIronBasicObject::AIronBasicObject()
{
	
}

void AIronBasicObject::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AIronBasicObject::OnCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,&AIronBasicObject::OnCapsuleComponentHit);
}

UPrimitiveComponent* AIronBasicObject::GetYourCharacterSprite() const
{
	return GetSprite();
}

void AIronBasicObject::OnCapsuleComponentHit_Implementation(UPrimitiveComponent* hitCompo, AActor* OtherActor,
                                                            UPrimitiveComponent* OtherCompo, FVector NormalImpulse, const FHitResult& SweepResult)
{
	//YellSomething("I AM hit")
	RepairYlineOffset();
}

void AIronBasicObject::OnCapsuleBeginOverlap_Implementation(
	class UPrimitiveComponent* overlappedCompo,
		class AActor* OtherActor ,
		class UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)
{
	RepairYlineOffset();
}
