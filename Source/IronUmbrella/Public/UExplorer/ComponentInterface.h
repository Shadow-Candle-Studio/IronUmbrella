// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IRONUMBRELLA_API IComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ComponentInitialize() =0;
	virtual void ComponentDestroy() =0;
};
