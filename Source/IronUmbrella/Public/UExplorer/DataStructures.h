#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataStructures.generated.h"


UENUM(BlueprintType)
enum class EProperty:uint8
{
	Health						UMETA(DisplayName = "生命值"),
	JumpCount					UMETA(DisplayName = "跳跃次数"),
	MoveSpeed					UMETA(DisplayName = "移动速度"),
	DodgeCount					UMETA(DisplayName = "闪避次数"),
	DodgeCoolDown				UMETA(DisplayName = "闪避CD"),
	LifeCount					UMETA(DisplayName = "生命次数"),
	InjuredReduceMultiplier		UMETA(DisplayName = "减伤率"),
	BaseDamageMultiplier		UMETA(DisplayName = "基础伤害乘数"),
	ManaDamageMultiplier		UMETA(DisplayName = "魔法伤害乘数"),
	StanceDamageMultiplier      UMETA(DisplayName = "架势伤害乘数"),
	StanceCritChanceMultiplier  UMETA(DisplayName = "架势暴击几率乘数"),
	StanceCritDamageMultiplier  UMETA(DisplayName = "架势暴击伤害乘数"),
	MagicCritChanceMultiplier   UMETA(DisplayName = "魔法暴击几率乘数"),
	MagicCritDamageMultiplier	UMETA(DisplayName = "魔法暴击伤害乘数"),
};

//修改属性的方式
UENUM(BlueprintType)
enum class EModifyPropertyMethodType:uint8
{
	InitValDirectStack,
	InitValRatioStack,
	FinalValDirectStack,
	FinalValRatioStack,
};

//属性结构
USTRUCT(BlueprintType)
struct FPropertyStruct:public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	EProperty PropertyType;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float InitVal;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float FinalVal;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MaxVal;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MinVal;
};

// 属性数值种类
UENUM(BlueprintType)
enum class EPropertyValueType:uint8
{
	InitValue,
	FinalValue,
	MaxValue,
	MinValue
};

// 伤害类型
UENUM(BlueprintType)
enum class EDamageType:uint8
{
	PhysicalDamage,
	MagicDamage,
	TrueDamage,
};

// 得到的伤害信息
USTRUCT(BlueprintType)
struct FTakeDamageInfo
{
	GENERATED_BODY()
	FTakeDamageInfo():DamageType(EDamageType::PhysicalDamage),Damage(0.0f),GuardSuccess(false),ParrySuccess(false),ParryValue(0.0f),IgnoreArmor(false){};
	FTakeDamageInfo(const EDamageType& InDamageType,
					float InDamage,
					bool InGuard,
					bool InParry,
					float InPaVal,
					bool InIgnoreArmor):DamageType(InDamageType),Damage(InDamage),GuardSuccess(InGuard),ParrySuccess(InParry),ParryValue(InPaVal),IgnoreArmor(InIgnoreArmor){};
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="伤害类型"))
	EDamageType DamageType;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="伤害值"))
	float Damage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="防御是否成功"))
	bool GuardSuccess;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="弹反是否成功"))
	bool ParrySuccess;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="弹反数值"))
	float ParryValue;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="是否无视护甲(减伤率)"))
	bool IgnoreArmor;
};



// 武器类型
UENUM(BlueprintType)
enum class EWeaponType:uint8
{
	Dagger			UMETA(DisplayName="匕首"),
	Umbrella		UMETA(DisplayName="千机伞"),
	Hammer			UMETA(DisplayName="铁锤"),
	Axe				UMETA(DisplayName="斧头"),
	GreatSword		UMETA(DisplayName="大剑"),
};

// 武器信息
USTRUCT(BlueprintType)
struct FWeaponInfo:public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName WeaponName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WeaponDamage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="武器格挡系数"))
	float GuardMultiplier;
};


// 状态
UENUM(BlueprintType)
enum class EState:uint8
{
	Idle,			
	Walk,			
	Run,
	Jump,
	Attack,
	ToggleWeapon,
	GuardStance,
	Dodge,
	Stun,
	Dead
};

UENUM(BlueprintType)
enum class ECombatState:uint8
{
	CommonAtk,	
	SpecialAtk,
	Parry,
	NULLState
};

UENUM(BlueprintType)
enum class EStunType:uint8
{
	Fear,
	Stiff,
	StepBack,
	Root,
	NULLState
};

UENUM(BlueprintType)
enum class EDebuffState:uint8
{
	OnFired,
	Poison,
	Moist,
};


// BUff相关

UENUM(BlueprintType)
enum class EBuffLifespanType:uint8
{
	Permanent,
	Duration,
	Counter,
};


UENUM(BlueprintType)
enum class EBuffRarity:uint8
{
	Normal,
	Rare,
	Legend
};

UENUM(BlueprintType)
enum class EBuffStackMethod:uint8
{
	Stackable,
	Override,
	Refresh
};


UENUM(BlueprintType)
enum class EBuffState:uint8
{
	Waiting,
	Running,
	Finished,
	Dead,
};

UENUM(BlueprintType)
enum class EBuffStatus:uint8
{
	PropertyModifier,
	MotionModifier,
	Another
};

UENUM(BlueprintType)
enum class EBuffTriggerMethod:uint8
{
	Time,
	Condition,
	Action
};

UENUM(BlueprintType)
enum class EBuffTimeTriggerMethod:uint8
{
	Interval,
	Delay,
};

UENUM(BlueprintType)
enum class EBuffType:uint8
{
	Buff,
	DeBuff
};

USTRUCT(BlueprintType,Blueprintable)
struct FBuffLifespanInfo:public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffLifespanType LifespanType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 Counter;
};


USTRUCT(BlueprintType)
struct FBuffTimeTriggerInfo:public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffTimeTriggerMethod Method;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DelayTrigger;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float IntervalTrigger;
};



USTRUCT(BlueprintType)
struct FBuffInfo:public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffType Type;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffStackMethod OverlayMethod;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffRarity Rarity;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBuffLifespanInfo LifespanInfo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBuffTriggerMethod TriggerMethod;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBuffTimeTriggerInfo TimeTriggerInfo;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Icon;
};