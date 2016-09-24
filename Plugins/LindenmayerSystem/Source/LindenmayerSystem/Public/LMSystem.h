// Robert Chubb a.k.a SaxonRah
#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Components/SplineMeshComponent.h"

#include "RenderLSystem.h"

#include "LMSystem.generated.h"

USTRUCT(BlueprintType)
struct FLSRule
{
	GENERATED_USTRUCT_BODY()
public:

	// TODO Make into an TArray of these rules and Loop Through them, like the ruletypes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Rule")
		FString Variable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Rule")
		FString Replacement;

	FLSRule()
	{ 
		Variable = ""; Replacement = "";
	}

	FLSRule(FString variable, FString replacement)
	{ 
		Variable = variable; Replacement = replacement;
	}

	FString GetVariable()
	{
		return Variable;
	}

	FString GetReplacement()
	{
		return Replacement;
	}

	void SetVariable(FString variable)
	{ 
		Variable = variable;
	}

	void SetReplacement(FString replacement)
	{ 
		Replacement = replacement;
	}

	bool IsVariableAMatch(FString variable)
	{ 
		return variable == Variable;
	}
};


USTRUCT(BlueprintType)
struct FLSInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Info")
		int32 Generations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Info")
		FString Axiom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Info")
		TArray<FLSRule> Rules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Info")
		TArray<FString> States;

	FLSInfo()
	{
		Generations = 0; Axiom = ""; Rules.Empty(); States.Empty();
	}

	FLSInfo(int32 generations, FString axiom, TArray<FLSRule> rules, TArray<FString> states)
	{
		Generations = generations; Axiom = axiom; Rules = rules; States = states;
	}

	void AddRule(FString variable, FString replacement)
	{
		FLSRule TempRule(variable, replacement);
		TempRule.SetVariable(variable);
		TempRule.SetReplacement(replacement);
		Rules.Add(TempRule);
	}
};

USTRUCT(BlueprintType)
struct FLSystem
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem")
		FLSInfo Info;

	FLSystem()
	{
		Info.Generations = 0; Info.Axiom = ""; Info.Rules.Empty(); Info.States.Empty();
	}

	FLSystem(FLSInfo info)
	{
		Info.Generations = info.Generations;
		Info.Axiom = info.Axiom;
		Info.Rules = info.Rules;
		Info.States = info.States;
	}

	void SetInfo(FLSInfo info)
	{
		Info = info;
	}

	FString GetState(int32 index)
	{
		if (Info.States.IsValidIndex(index))
		{
			return Info.States[index];
		} 
		else
		{
			return "Invalid Index.";
		}
	}

	FString ReplaceVariableWithString(FString variable)
	{
		FString ReplacementString;
		ReplacementString.Empty();

		for (int32 ruleCounter = 0; ruleCounter < Info.Rules.Num(); ++ruleCounter)
		{
			if (Info.Rules[ruleCounter].IsVariableAMatch(variable))
				return Info.Rules[ruleCounter].GetReplacement();
		}

		ReplacementString.Append(variable);
		return ReplacementString;
	}

	void Iterate(int32 Generation)
	{
		//Info.States.Add(Info.Axiom);
		FString NewState;
		if (Info.States.IsValidIndex(Generation))
		{
			FString TempState = Info.States[Generation];
			for (int32 sCounter = 0; sCounter < TempState.Len(); ++sCounter)
			{
				FString Temp = ""; Temp.AppendChar(TempState[sCounter]);
				FString TempReplacement = ReplaceVariableWithString(Temp);

				for (int32 replacementCounter = 0; replacementCounter < TempReplacement.Len(); ++replacementCounter)
				{
					NewState.AppendChar(TempReplacement[replacementCounter]);
				}
			}
			Info.States.Add(NewState);
		}
		else
		{}
	}

	void GrowLSystem()
	{
		Info.States.Empty();
		Info.States.Add(Info.Axiom);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("LSystem State [ %d ] = %s"), 0, *GetState(0)));
		for (int32 g = 0; g <= Info.Generations; ++g)
		{
			Iterate(g);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("LSystem State [ %d ] = %s"), g, *GetState(g)));
		}
	}

	void GrowLSystemBy(int32 Generations)
	{
		Info.States.Empty();
		Info.States.Add(Info.Axiom);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("LSystem State [ %d ] = %s"), 0, *GetState(0)));
		for (int32 g = 0; g <= Generations; ++g)
		{
			Iterate(g);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("LSystem State [ %d ] = %s"), g, *GetState(g)));
		}
	}
};

UCLASS()
class ALMSystem : public AActor
{
	GENERATED_BODY()
public:
	// Boilerplate
	ALMSystem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
		USceneComponent* RootComp;

	// Actual LSystem String Rewriting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem")
		FLSystem LSystem;
	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void SetupLSystem(FLSInfo Info);
	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void GrowLSystem();
	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void GrowLSystemBy(int32 Generations = 0);

	
	// Turtle Rendering and Info
	FTransform Move(float length);
	void Draw(float length);
	void DrawLeaf(float angle, float length);
	void TurnRight(float angle);
	void TurnLeft(float angle);
	void Turn180();
	void PitchUp(float angle);
	void PitchDown(float angle);
	void RollRight(float angle);
	void RollLeft(float angle);
	void Save();
	void Restore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		TArray<FRLSTInfo> State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		FRLSRenderInfo LSystemRenderInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		FRLSTInfo TurtleInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		USceneComponent* RenderTurtle;
	UFUNCTION(BlueprintCallable, Category = "LSystem|Render")
		void RenderLSystem(FLSystem System, FRLSRenderInfo RenderInfo);
	
	// Spline
	FTransform SplineMove(float length);
	void SplineDraw(float length, int32 index);
	void SplineDrawLeaf(float angle, float length);
	void SplineTurnRight(float angle);
	void SplineTurnLeft(float angle);
	void SplineTurn180();
	void SplinePitchUp(float angle);
	void SplinePitchDown(float angle);
	void SplineRollRight(float angle);
	void SplineRollLeft(float angle);
	void SplineSave();
	void SplineRestore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		TArray<USplineComponent*> SplineComponents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UStaticMesh* SplineRenderMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UMaterial* SplineRenderMeshMaterial;

	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void SetSplinePoints();

	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		USplineComponent* CreateSplineComponent(const FTransform& Transform, const FName& AttachSocket = NAME_None);

	
	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void RenderSplineLSystem(FLSystem System, FRLSRenderInfo RenderInfo);
	
	// Examples
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FLSInfo Algae(int32 Generations);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FLSInfo PythagorasTree(int32 Generations);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FLSInfo KochCurve(int32 Generations);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FLSInfo FractalPlant(int32 Generations);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FLSInfo RahSystem(int32 Generations);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FRLSRenderInfo RenderPythagorasTree();
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FRLSRenderInfo RenderKochCurve();
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FRLSRenderInfo RenderFractalPlant();
	UFUNCTION(BlueprintCallable, Category = "LSystem|Example")
		FRLSRenderInfo RenderRahSystem();
};
