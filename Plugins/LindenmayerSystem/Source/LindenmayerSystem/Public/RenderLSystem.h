// Robert Chubb a.k.a SaxonRah
#pragma once
#include <stack>

//#include "Components\StaticMeshComponent.h"
#include "RenderLSystem.generated.h"

#define LS_PI 3.14159265359

USTRUCT(BlueprintType)
struct FRLSTInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		float Thickness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		float Reduction;

	FRLSTInfo()
	{
		Transform = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0));
		Thickness = 1.0f;
		Reduction = 0.95f;
	}

	void SetReduction(float length)
	{
		Reduction = length / 100;
	}

	void SetThickness(float length)
	{
		Thickness = length / 100;
	}

	void Thicken(float length)
	{
		Thickness += Thickness * length / 100;
	}

	void Narrow(float length)
	{
		Thicken(-length);
	}
};

UENUM(BlueprintType)
enum class ERLSRenderRuleType : uint8
{
	LSRR_DoNothing		UMETA(DisplayName = "Do Nothing"),
	LSRR_Move			UMETA(DisplayName = "Move"),
	LSRR_Draw			UMETA(DisplayName = "Draw"),
	LSRR_DrawLeaf		UMETA(DisplayName = "Draw Leaf"),
	LSRR_TurnRight		UMETA(DisplayName = "Turn Right"),
	LSRR_TurnLeft		UMETA(DisplayName = "Turn Left"),
	LSRR_Turn180		UMETA(DisplayName = "Turn 180"),
	LSRR_PitchDown		UMETA(DisplayName = "Pitch Down"),
	LSRR_PitchUp		UMETA(DisplayName = "Pitch Up"),
	LSRR_RollRight		UMETA(DisplayName = "Roll Right"),
	LSRR_RollLeft		UMETA(DisplayName = "Roll Left"),
	LSRR_Save			UMETA(DisplayName = "Save Place"),
	LSRR_Restore		UMETA(DisplayName = "Restore Place"),
	LSRR_COUNT			UMETA(DisplayName = "COUNT")
};

USTRUCT(BlueprintType)
struct FRLSRenderRule
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render|Rule")
		FString	Variable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render|Rule")
		TArray<ERLSRenderRuleType> RuleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render|Rule")
		float Angle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render|Rule")
		float Length;

	FRLSRenderRule(FString _Variable, TArray<ERLSRenderRuleType> _RuleType, float _Angle, float _Length) :
		Variable(_Variable),
		RuleType(_RuleType),
		Angle(_Angle),
		Length(_Length)
	{}

	FRLSRenderRule() :
		Variable(FString(TEXT(""))),
		Angle(0.0f),
		Length(0.0f)
	{
		RuleType.Empty();
	}
};

USTRUCT(BlueprintType)
struct FRLSRenderInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		TArray<FRLSRenderRule> Rules;

	FRLSRenderInfo(TArray<FRLSRenderRule> _Rules) :
		Rules(_Rules)
	{}

	FRLSRenderInfo()
	{}
};

