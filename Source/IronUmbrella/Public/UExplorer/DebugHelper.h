#pragma once
#include "CoreMinimal.h"
#include "Engine.h"
#include "DebugHelper.generated.h"

#define COMBAT_DEBUG(format,...) UE_LOG(LogTemp,Warning,TEXT(format),##__VA_ARGS__)
#define SCREEN_MESSAGE(format) GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,format);
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
