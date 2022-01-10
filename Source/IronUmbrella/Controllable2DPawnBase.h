/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-9 
Description: This file contains the declaration of: TriggerbleEventInterface,  AControllable2DPawnBase
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "AllInputEventsInterface.h"
#include "AllStructuresAndEnums.h"

#include "Pixel2DCharacter.h"



#include "Controllable2DPawnBase.generated.h"





/**
 * AControllable2DPawnBase
 * implemented the basic facility of supporting input processing
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AControllable2DPawnBase : public APixel2DCharacter, public IAllInputEventsInterface
{
	GENERATED_BODY()

public:
	GenerateButtonSructVar(LStick)
	
	GenerateInputActionEvent(LStick)
	
	GenerateButtonSructVar(RStick)
	GenerateInputActionEvent(RStick)
	
	GenerateButtonSructVar(RBG_LEFT)
	GenerateInputActionEvent(RBG_LEFT)
	
	GenerateButtonSructVar(RBG_RIGHT)
	GenerateInputActionEvent(RBG_RIGHT)
	
	GenerateButtonSructVar(RBG_TOP)
	GenerateInputActionEvent(RBG_TOP)
	
	GenerateButtonSructVar(RBG_DOWN)
	GenerateInputActionEvent(RBG_DOWN)
	
	GenerateButtonSructVar(LBG_LEFT)
	GenerateInputActionEvent(LBG_LEFT)
	
	GenerateButtonSructVar(LBG_RIGHT)
	GenerateInputActionEvent(LBG_RIGHT)
	
	GenerateButtonSructVar(LBG_TOP)
	GenerateInputActionEvent(LBG_TOP)
	
	GenerateButtonSructVar(LBG_DOWN)
	GenerateInputActionEvent(LBG_DOWN)
	
	GenerateButtonSructVar(SP_LEFT)
	GenerateInputActionEvent(SP_LEFT)
	
	GenerateButtonSructVar(SP_RIGHT)
	GenerateInputActionEvent(SP_RIGHT)
	
	GenerateButtonSructVar(LB)
	GenerateInputActionEvent(LB)
	
	GenerateButtonSructVar(RB)
	GenerateInputActionEvent(RB)
	
	GenerateButtonSructVar(RT)
	GenerateInputActionEvent(RT)
	
	GenerateButtonSructVar(LT)
	GenerateInputActionEvent(LT)
//Set up input mapping 
virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
