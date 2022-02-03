// Fill out your copyright notice in the Description page of Project Settings.


#include "IronStaticObject.h"

#include "Pixel2DComponent.h"
#include "GameFramework/PawnMovementComponent.h"

const FName AIronStaticObject::PixelComponentName(TEXT("IronStaticObject"));
AIronStaticObject::AIronStaticObject()
{
	// Try to create the sprite component
	PixelComponent = CreateOptionalDefaultSubobject<UPixel2DComponent>(AIronStaticObject::PixelComponentName);
	if (PixelComponent)
	{
		PixelComponent->AlwaysLoadOnClient = true;
		PixelComponent->AlwaysLoadOnServer = true;
		PixelComponent->bOwnerNoSee = false;
		PixelComponent->bAffectDynamicIndirectLighting = true;
		PixelComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		PixelComponent->SetupAttachment(GetRootComponent());
		static FName CollisionProfileName(TEXT("CharacterAnimInstance"));
		PixelComponent->SetCollisionProfileName(CollisionProfileName);
		PixelComponent->SetGenerateOverlapEvents(false);
	}
}

void AIronStaticObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!IsPendingKill())
	{
		if (PixelComponent)
		{
			// force animation tick after movement component updates
			if (PixelComponent->PrimaryComponentTick.bCanEverTick )
			{
				//PixelComponent->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(), GetCharacterMovement()->PrimaryComponentTick);
			}
		}
	}
}
