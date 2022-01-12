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
	
	
	GenerateInputActionEvent(LStick)
	GenerateInputActionEvent(RStick)
	GenerateInputActionEvent(RBG_LEFT)
	GenerateInputActionEvent(RBG_RIGHT)
	GenerateInputActionEvent(RBG_TOP)
	GenerateInputActionEvent(RBG_DOWN)
	
	GenerateInputActionEvent(LBG_LEFT)
	
	GenerateInputActionEvent(LBG_RIGHT)
	
	GenerateInputActionEvent(LBG_TOP)

	GenerateInputActionEvent(LBG_DOWN)
	
	
	GenerateInputActionEvent(SP_LEFT)
	
	GenerateInputActionEvent(SP_RIGHT)
	
	GenerateInputActionEvent(LB)
	
	GenerateInputActionEvent(RB)
	
	GenerateInputActionEvent(RT)
	
	GenerateInputActionEvent(LT)
	
	void LStick_X(float LStick_XValue)
	{
		LStick.AxisXValue=LStick_XValue;
		Execute_BP_LStickAxisEvent_X(this,LStick_XValue);
	}
	void LStick_Y(float LStick_YValue)
	{
		LStick.AxisYValue=LStick_YValue;
		Execute_BP_LStickAxisEvent_Y(this,LStick_YValue);
	}
	void RStick_X(float RStick_XValue)
	{
		RStick.AxisXValue=RStick_XValue;
		Execute_BP_RStickAxisEvent_X(this,RStick_XValue);
		
	}
	void RStick_Y(float RStick_YValue)
	{
		RStick.AxisYValue=RStick_YValue;
		Execute_BP_RStickAxisEvent_Y(this,RStick_YValue);
	}
	void LT_Axis(float LT_AxisValue)
	{
		LT.AxisXValue=LT_AxisValue;
		Execute_BP_AxisEvent_LT(this,LT_AxisValue);
	}
	void RT_Axis(float RT_AxisValue)
	{
		RT.AxisXValue=RT_AxisValue;
		Execute_BP_AxisEvent_RT(this,RT_AxisValue);
	}
	//Key struct info area starts
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LStick;
	FTimerHandle LStickTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RStick;
	FTimerHandle RStickTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RBG_RIGHT;
	FTimerHandle RBG_RIGHTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RBG_LEFT;
	FTimerHandle RBG_LEFTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RBG_TOP;
	FTimerHandle RBG_TOPTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RBG_DOWN;
	FTimerHandle RBG_DOWNTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LBG_LEFT;
	FTimerHandle LBG_LEFTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LBG_RIGHT;
	FTimerHandle LBG_RIGHTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LBG_TOP;
	FTimerHandle LBG_TOPTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LBG_DOWN;
	FTimerHandle LBG_DOWNTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo SP_LEFT;
	FTimerHandle SP_LEFTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo SP_RIGHT;
	FTimerHandle SP_RIGHTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LB;
	FTimerHandle LBTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RB;
	FTimerHandle RBTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo RT;
	FTimerHandle RTTimerHandler;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Keyinfo")\
	FS_InputKeyInfo LT;
	FTimerHandle LTTimerHandler;
	//Key struct info area ends

	
    //Set up input mapping 
    virtual void SetupPlayerInputComponent(UInputComponent*
    	PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void BP_CopySignsToAnim(UPARAM(ref) FS_InputKeyInfo& Source,UPARAM(ref) FS_InputKeyInfo& Dest);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Appear(bool bShow);
	void Appear_Implementation(bool bShow);

	UFUNCTION(BlueprintCallable)
	void ChangeFaceDirection(bool bFaceRight);
	
};
