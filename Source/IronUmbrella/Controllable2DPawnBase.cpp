// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllable2DPawnBase.h"


void AControllable2DPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

	//PlayerInputComponent->BindAxis("")

	
	
}
