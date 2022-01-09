/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-9 
Description: This file contains the declaration of: UAllInputEventsInterface, and IAllInputEventsInterface
**************************************************/ 
#pragma once

//include files
#include "CoreMinimal.h"
#include "AllInputEventsInterface.generated.h"


//Macro for generating press event functions
#define GenerateFunctionsForOneButton(ButtonName) \
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="ButtonAction")\
void LightPressStartEvent_##ButtonName();\
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="ButtonAction")\
void LightPressOverEvent_##ButtonName(float Duration);\
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="ButtonAction")\
void ChargePressStartEvent_##ButtonName();\
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="ButtonAction")\
void ChargePressOverEvent_##ButtonName(float Duration);\

//Macro for generating Axis event functions
#define GenerateAxisFunction(AxisName,DimensionName)\
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="ButtonAction") void AxisName##AxisEvent_##DimensionName(float DimensionName##Axis);


//Reflection identifier
UINTERFACE(Blueprintable)
class IRONUMBRELLA_API UAllInputEventsInterface : public UInterface
{
	GENERATED_BODY()
};

//Declaration class of the interface,in which most of the events needed in our input system are declared
class IAllInputEventsInterface
{
	GENERATED_BODY()
	
public:
	

	//Lstick functions declaration
	GenerateAxisFunction(LStick,X)
	GenerateAxisFunction(LStick,Y)
	GenerateFunctionsForOneButton(LStick)

	//Rstick functions declaration
	GenerateAxisFunction(RStick,X)
	GenerateAxisFunction(RStick,Y)
	GenerateFunctionsForOneButton(RStick)

	//Right group buttons functions declaration
	GenerateFunctionsForOneButton(RBG_LEFT)
	GenerateFunctionsForOneButton(RBG_RIGHT)
	GenerateFunctionsForOneButton(RBG_TOP)
	GenerateFunctionsForOneButton(RBG_DOWN)

	//Left group buttons functions declaration
	GenerateFunctionsForOneButton(LBG_LEFT)
	GenerateFunctionsForOneButton(LBG_RIGHT)
	GenerateFunctionsForOneButton(LBG_TOP)
	GenerateFunctionsForOneButton(LBG_DOWN)

	//Special buttons functions declaration
	GenerateFunctionsForOneButton(SP_LEFT)
	GenerateFunctionsForOneButton(SP_RIGHT)

	//Shoulder buttons functions declaration
	GenerateFunctionsForOneButton(LB)
	GenerateFunctionsForOneButton(RB)

	//Trigger buttons functions declaration
	GenerateFunctionsForOneButton(RT)
	GenerateFunctionsForOneButton(LT)
	;
};
