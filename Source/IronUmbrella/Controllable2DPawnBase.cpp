// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllable2DPawnBase.h"

#include "Pixel2DComponent.h"


void AControllable2DPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Bind button type action
	BindButtonMacro(LStick,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RStick,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RBG_LEFT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RBG_RIGHT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RBG_TOP,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RBG_DOWN,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LBG_LEFT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LBG_RIGHT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LBG_TOP,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LBG_DOWN,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(SP_LEFT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(SP_RIGHT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LB,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RB,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(LT,PlayerInputComponent,AControllable2DPawnBase)
	BindButtonMacro(RT,PlayerInputComponent,AControllable2DPawnBase)

	//Bind axis values
	PlayerInputComponent->BindAxis("LStick_X",this,&AControllable2DPawnBase::LStick_X);
	PlayerInputComponent->BindAxis("LStick_Y",this,&AControllable2DPawnBase::LStick_Y);
	PlayerInputComponent->BindAxis("RStick_X",this,&AControllable2DPawnBase::RStick_X);
	PlayerInputComponent->BindAxis("RStick_Y",this,&AControllable2DPawnBase::RStick_Y);
	PlayerInputComponent->BindAxis("LT_Axis",this,&AControllable2DPawnBase::LT_Axis);
	PlayerInputComponent->BindAxis("RT_Axis",this,&AControllable2DPawnBase::RT_Axis);
	
}

void AControllable2DPawnBase::BP_CopySignsToAnim( FS_InputKeyInfo& Source,FS_InputKeyInfo& Dest)
{
	
	
	Dest=Source;
	Source.ChargeOverSign=false;
	Source.ChargeStartSign=false;
	Source.LightPressStartSign=false;
	Source.LightPressOverSign=false;
}

void AControllable2DPawnBase::Appear_Implementation(bool bShow)
{
	SetActorHiddenInGame(!bShow);
	SetActorEnableCollision(bShow);
}

void AControllable2DPawnBase::ChangeFaceDirection(bool bDesireFaceRight)
{
	check(GetSprite()!=nullptr)
	bool currentDir=GetSprite()->GetRelativeRotation().Yaw==0?true:false;
	if(currentDir!=bDesireFaceRight)
	{
		GetSprite()->SetRelativeRotation(FRotator(0,bDesireFaceRight?0.0f:180.0f,0));
	}
}

UPrimitiveComponent* AControllable2DPawnBase::GetYourCharacterSprite() const
{
	return GetSprite();
}


