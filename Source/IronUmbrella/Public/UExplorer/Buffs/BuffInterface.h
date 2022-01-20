// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuffInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuffInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IRONUMBRELLA_API IBuffInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool BuffAwake();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool BuffStart();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool BuffRunning();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool BuffFinished();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool BuffDestroy();
};
