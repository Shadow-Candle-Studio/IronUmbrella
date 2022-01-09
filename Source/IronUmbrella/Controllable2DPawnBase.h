/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-01-9 
Description: This file contains the declaration of: TriggerbleEventInterface,  AControllable2DPawnBase
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "AllInputEventsInterface.h"
#include "Pixel2DCharacter.h"
#include "Controllable2DPawnBase.generated.h"
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AControllable2DPawnBase : public APixel2DCharacter, public IAllInputEventsInterface
{
	GENERATED_BODY()

public:
	//
	void BindAllInputFromIAllInputEventsInterface();

	
};
