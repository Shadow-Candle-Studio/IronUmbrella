#pragma once
#include "CoreMinimal.h"
#include "Engine.h"
#include "DebugHelper.generated.h"




UCLASS()
class UDebugHelper:public UObject
{
	GENERATED_BODY()
public:
	static void PrintDebugMessage(FString str)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,*str);
	}
};
