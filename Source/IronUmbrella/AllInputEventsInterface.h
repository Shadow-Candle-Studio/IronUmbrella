/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-9 
Description: This file contains the declaration of: UAllInputEventsInterface, and IAllInputEventsInterface
**************************************************/ 
#pragma once

//include files
#include "CoreMinimal.h"
#include "AllStructuresAndEnums.h"
#include "../../Plugins/ElectronicNodes/Source/ElectronicNodes/Private/Lib/HotPatch.h"
#include "AllInputEventsInterface.generated.h"



//Generate the code of binding input to Action events
#define BindButtonMacro(ButtonName,PlayerInputComponent,AControllable2DPawnBase) \
PlayerInputComponent->BindAction(#ButtonName, IE_Pressed, this, &AControllable2DPawnBase::ButtonName##_StartPressAction);\
PlayerInputComponent->BindAction(#ButtonName, IE_Released, this, &AControllable2DPawnBase::ButtonName##_EndPressAction);\


//Generate the corresponding actions triggered by pressed or released event of specific button
#define GenerateInputActionEvent(ButtonName) \
void ButtonName##_StartPressAction()\
{\
ButtonName.LastPressTime=GetGameTimeSinceCreation();\
ButtonName.PressState=E_PressState::WaitingForLightOverSign;\
ButtonName.LightPressStartSign=true;\
GetWorldTimerManager().SetTimer(ButtonName##TimerHandler, this, &AControllable2DPawnBase::ButtonName##_TimerFunc, ButtonName.BoundaryOfLightAndCharge, false, 0);\
Execute_BP_LightPressStartEvent_##ButtonName(this);\
\
}\
void ButtonName##_EndPressAction()   \
{\
ButtonName.LastReleaseTime=GetGameTimeSinceCreation();\
ButtonName.PressState=E_PressState::Released;\
GetWorldTimerManager().ClearTimer(ButtonName##TimerHandler);\
float duration=ButtonName.LastReleaseTime-ButtonName.LastPressTime;\
if(duration<=ButtonName.BoundaryOfLightAndCharge)\
{\
	ButtonName.LightPressOverSign=true;\
	Execute_BP_LightPressOverEvent_##ButtonName(this,duration);\
}\
else\
{\
	ButtonName.ChargeOverSign=true;\
	Execute_BP_ChargePressOverEvent_##ButtonName(this,duration);\
}\
}\
void ButtonName##_TimerFunc()\
{\
ButtonName.PressState=E_PressState::WaitingForChargeOverSign;\
ButtonName.ChargeStartSign=true;\
Execute_BP_ChargePressStartEvent_##ButtonName(this);\
}\

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
	

	//Lstick Axis BPevents declaration
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
    void BP_LStickAxisEvent_X(float ValueX);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
	void BP_LStickAxisEvent_Y(float ValueY);
	
	//Lstick button BPevents declaration
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
    void BP_LightPressStartEvent_LStick();
    UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
    void BP_LightPressOverEvent_LStick(float Duration);
    UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
    void BP_ChargePressStartEvent_LStick();
    UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
    void BP_ChargePressOverEvent_LStick(float Duration);
	
	//RStick Axis BPevents declaration
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
	void BP_RStickAxisEvent_X(float ValueX);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
	void BP_RStickAxisEvent_Y(float ValueY);
	
	//Rstick button BPevents declaration
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RStick();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RStick(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RStick();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RStick(float Duration);


	//RBG_LEFT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RBG_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RBG_LEFT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RBG_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RBG_LEFT(float Duration);
	
	//RBG_RIGHT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RBG_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RBG_RIGHT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RBG_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RBG_RIGHT(float Duration);

	//RBG_TOP
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RBG_TOP();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RBG_TOP(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RBG_TOP();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RBG_TOP(float Duration);

	//RBG_DOWN
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RBG_DOWN();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RBG_DOWN(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RBG_DOWN();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RBG_DOWN(float Duration);
	
	//LBG_LEFT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_LBG_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LBG_LEFT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LBG_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LBG_LEFT(float Duration);
	//LBG_RIGHT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_LBG_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LBG_RIGHT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LBG_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LBG_RIGHT(float Duration);

	//LBG_TOP
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_LBG_TOP();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LBG_TOP(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LBG_TOP();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LBG_TOP(float Duration);

	//LBG_DOWN
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_LBG_DOWN();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LBG_DOWN(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LBG_DOWN();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LBG_DOWN(float Duration);

	//SP_LEFT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_SP_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_SP_LEFT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_SP_LEFT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_SP_LEFT(float Duration);
	
	//SP_RIGHT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_SP_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_SP_RIGHT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_SP_RIGHT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_SP_RIGHT(float Duration);

	
	//LB
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
    void BP_LightPressStartEvent_LB();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LB(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LB();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LB(float Duration);

	//RB
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RB();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RB(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RB();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RB(float Duration);

	//RT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_RT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_RT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_RT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_RT(float Duration);

	//RT Axis
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
	void BP_AxisEvent_RT(float AxisValue);
	
	//LT
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressStartEvent_LT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_LightPressOverEvent_LT(float Duration);
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressStartEvent_LT();
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction")
	void BP_ChargePressOverEvent_LT(float Duration);

	//LT Axis
	UFUNCTION(BlueprintImplementableEvent,Category="ButtonAction") 
    void BP_AxisEvent_LT(float AxisValue);

	
	
};
