/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-02-3 
Description: Base class supporting all moveable object
Basic features supported:
1. Basic locomotion implementations
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "IronBasicObject.h"
#include "UObject/Object.h"
#include "IronMobileObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AIronMobileObject : public AIronBasicObject
{
	GENERATED_BODY()
	//change the facing direction right or left
	//UFUNCTION(BlueprintCallable)
	void ChangeFaceDirection(bool bFaceRight);
	//true is right, false is left
	bool LastDirection;
public:
	UFUNCTION(BlueprintCallable)
	void AutoAdaptSpriteToVelocityDirection(float VelocityXValue);
};
