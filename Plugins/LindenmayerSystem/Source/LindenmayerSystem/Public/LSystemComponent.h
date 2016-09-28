// Robert Chubb a.k.a SaxonRah
#pragma once
#include "Components/ActorComponent.h"

#include "RenderLSystem.h"

#include "LSystemComponent.generated.h"

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
			auto TempVar = Info.Rules[ruleCounter];
			if (TempVar.IsVariableAMatch(variable))
				return TempVar.GetReplacement();
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
		{
		}
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINDENMAYERSYSTEM_API ULSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULSystemComponent();
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	// Actual LSystem String Rewriting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem")
		FLSystem LSystem;

	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void SetupLSystem(FLSInfo Info);
	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void GrowLSystem();
	UFUNCTION(BlueprintCallable, Category = "LSystem")
		void GrowLSystemBy(int32 Generations = 0);

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
