/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: Junlin Sun
Date:2022-02-3 
Description:
Basic features supported:
1. Align the object to the Ybaseline When collided or overlaaped
2. AllObjectsYBaseLineValue
**************************************************/ 
#pragma once

#include "CoreMinimal.h"
#include "Pixel2DCharacter.h"
#include "IronBasicObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable,ShowCategories=("Pixel2D character"))
class IRONUMBRELLA_API AIronBasicObject : public APixel2DCharacter
{
	GENERATED_BODY()

protected:
	void RepairYlineOffset();
public:
	AIronBasicObject();
	static const float AllObjectsYBaseLineValue;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void OnCapsuleBeginOverlap(
		class UPrimitiveComponent* overlappedCompo,
		class AActor* OtherActor ,
		class UPrimitiveComponent* OtherCompo,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent)
	void OnCapsuleComponentHit(class UPrimitiveComponent* hitCompo,class AActor* OtherActor ,
		class UPrimitiveComponent* OtherCompo,
		FVector NormalImpulse,const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetYourCharacterSprite() const;
};
