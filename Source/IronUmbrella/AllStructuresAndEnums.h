/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-9 
Description: E_PressState,FS_InputKeyInfo
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "AllStructuresAndEnums.generated.h"

#define YellSomething(Msg)\
if(GEngine)\
{\
 GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Yellow,Msg);\
}


/**
 * E_PressState records input state of phrases
 */
UENUM(BlueprintType,Blueprintable)
enum E_PressState
{
 Released,WaitingForLightOverSign,WaitingForChargeOverSign
};

/**
 * S_Inputkeyinfo contains all info needed about an input details
 */
USTRUCT(BlueprintType)
struct IRONUMBRELLA_API FS_InputKeyInfo
{
 
 GENERATED_BODY()
 //Detect whether this is 2D Axis like Lstick or Rstick
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 bool Is2DAxis=false;
 //Whether the player has launched a LightPressStartSign
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 bool LightPressStartSign=false;
 //Whether the player has launched a LightPressOverSign
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 bool LightPressOverSign=false;
 //Whether the player has launched a ChargeStartSign
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 bool ChargeStartSign=false;
 //Whether the player has launched a ChargeOverSIgn
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 bool ChargeOverSign=false;
 //Current State of the button
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 TEnumAsByte<E_PressState> PressState=E_PressState::Released;
 //Axis value if we have at least one dimension
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float AxisXValue=0.f;
 //The second axis value if we have two dimensions
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float AxisYValue=0.f;
//Last time when the button is pressed, this time recorded as tick counts of the game system
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float LastPressTime=0.f;
 //Last time when the button is released, this time recorded as tick counts of the game system
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float LastReleaseTime=0.f;
 //Boundary time when we want to distinguish between the light press and charge press start
 UPROPERTY(BlueprintReadWrite,EditAnywhere)
 float BoundaryOfLightAndCharge=0.15f;
};
