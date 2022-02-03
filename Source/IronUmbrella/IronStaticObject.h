/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-02-3 
Description: Object base for non-moveable objects or facilities
Basic features supported:
1. interact inferfaces
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "IronBasicObject.h"
#include "UObject/Object.h"
#include "IronStaticObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AIronStaticObject : public AIronBasicObject
{
	GENERATED_BODY()
public:
	AIronStaticObject();
	virtual void BeginPlay() override;
};
