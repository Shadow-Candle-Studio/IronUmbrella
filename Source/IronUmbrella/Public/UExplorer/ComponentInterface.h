/************************************************* 
Copyright: All rights reserved for Shadow Candle Studio 
Author: U
Date:2022-02-3 
Description:
Component interfaces
**************************************************/ 
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
