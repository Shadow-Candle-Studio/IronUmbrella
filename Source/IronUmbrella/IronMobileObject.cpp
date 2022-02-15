// Fill out your copyright notice in the Description page of Project Settings.


#include "IronMobileObject.h"

#include "Pixel2DComponent.h"

void AIronMobileObject::ChangeFaceDirection(bool bDesireFaceRight)
{
	check(GetSprite()!=nullptr)
	
	bool currentDir=GetSprite()->GetRelativeRotation().Yaw==0?(OriginDirection==OriginSpriteDirectionEnum::Right?true:false):((OriginDirection==OriginSpriteDirectionEnum::Right?false:true));
	if(currentDir!=bDesireFaceRight)
	{
		GetSprite()->SetRelativeRotation(
			FRotator(0,bDesireFaceRight?
			(OriginDirection==Right?0:180):
			((OriginDirection==Right?180:0)),
			0));
	}
}

void AIronMobileObject::AutoAdaptSpriteToVelocityDirection(float VelocityXValue)
{
	if(VelocityXValue>0.0f)
	{
		ChangeFaceDirection(LastDirection=true);
	}
	else if(VelocityXValue<0.0f)
	{
		ChangeFaceDirection(LastDirection=false);
	}
	else
	{
		ChangeFaceDirection(LastDirection);
	}
}
