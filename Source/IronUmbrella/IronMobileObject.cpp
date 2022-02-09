// Fill out your copyright notice in the Description page of Project Settings.


#include "IronMobileObject.h"

#include "Pixel2DComponent.h"

void AIronMobileObject::ChangeFaceDirection(bool bDesireFaceRight)
{
	check(GetSprite()!=nullptr)
	bool currentDir=GetSprite()->GetRelativeRotation().Yaw==0?true:false;
	if(currentDir!=bDesireFaceRight)
	{
		GetSprite()->SetRelativeRotation(FRotator(0,bDesireFaceRight?0.0f:180.0f,0));
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
