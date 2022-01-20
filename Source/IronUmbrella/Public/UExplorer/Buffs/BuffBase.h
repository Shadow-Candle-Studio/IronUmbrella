// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffInterface.h"
#include "GameFramework/Actor.h"
#include "UExplorer/DataStructures.h"
#include "UExplorer/DebugHelper.h"
#include "BuffBase.generated.h"

UCLASS(Abstract)
class IRONUMBRELLA_API ABuffBase : public AActor,public IBuffInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABuffBase();
	void AcquireBuffInfoFromDataTable();
	
	virtual bool BuffAwake_Implementation()override;

	virtual bool BuffStart_Implementation() override;

	virtual bool BuffRunning_Implementation()override;
	
	virtual bool BuffFinished_Implementation() override;
	
	virtual bool BuffDestroy_Implementation() override;

	void Overlay();

	UFUNCTION(BlueprintCallable)
	void SetBuffState(const EBuffState InState);
	
	inline void TryAwakeBuff(AActor* InCaster,AActor* InOwner);
	inline void GetEssentialVar(AActor* InCaster,AActor* InOwner);

	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	FBuffInfo Info;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BuffInfo")
	uint8 Id;

	UDataTable* BuffTable;
	FString BuffDataAddr{"/Game/Private/UExplorer/DataTable/BuffTable.BuffTable"};
	void TryLoadDataTable();

	// 发起者
	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	AActor* Caster;

	// Buff作用对象
	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	AActor* Effector;

	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	class UBuffManager* BuffManager;
	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	class UPropertyManager* PropertyManager;
	UPROPERTY(BlueprintReadOnly,Category="BuffInfo")
	class UStateManager* StateManager;
protected:
	void UpdateBuffState();
private:
	FTimerHandle StatuHandle;
	// 状态
	UPROPERTY(VisibleDefaultsOnly,Category="BuffInfo")
	EBuffState State;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
