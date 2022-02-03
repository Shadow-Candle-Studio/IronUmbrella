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

#include "IronStaticObject.generated.h"

/**
 * Static objects that can be simply placed in the game scene
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AIronStaticObject : public AActor
{
	GENERATED_BODY()
private:
	// Name of the Sprite component
	const static FName PixelComponentName;

	//pixel cartoon
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPixel2DComponent* PixelComponent;
public:
	AIronStaticObject();
	
	virtual void PostInitializeComponents() override;

	/** Returns Sprite subobject **/
	FORCEINLINE class UPixel2DComponent* GetSprite() const { return PixelComponent; }
};
