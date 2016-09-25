// Robert Chubb a.k.a SaxonRah
#include "LindenmayerSystemPrivatePCH.h"

#include "LSystemComponent.h"


// Sets default values for this component's properties
ULSystemComponent::ULSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULSystemComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


// LSystem
void ULSystemComponent::SetupLSystem(FLSInfo Info)
{
	LSystem = FLSystem(Info);
}

void ULSystemComponent::GrowLSystem()
{
	LSystem.GrowLSystem();
}

void ULSystemComponent::GrowLSystemBy(int32 Generations)
{
	LSystem.GrowLSystemBy(Generations);
}


// Examples
FLSInfo ULSystemComponent::Algae(int32 Generations)
{
	FLSInfo AlgaeInfo;
	AlgaeInfo.Generations = Generations;
	AlgaeInfo.Axiom = TEXT("D");
	AlgaeInfo.AddRule(TEXT("D"), TEXT("DM"));
	AlgaeInfo.AddRule(TEXT("M"), TEXT("D"));
	return AlgaeInfo;
}

FLSInfo ULSystemComponent::PythagorasTree(int32 Generations)
{
	FLSInfo PythagorasTreeInfo;
	PythagorasTreeInfo.Generations = Generations;
	PythagorasTreeInfo.Axiom = TEXT("L");
	PythagorasTreeInfo.AddRule(TEXT("L"), TEXT("D[L]L"));
	PythagorasTreeInfo.AddRule(TEXT("D"), TEXT("DD"));
	return PythagorasTreeInfo;
}

FLSInfo ULSystemComponent::KochCurve(int32 Generations)
{
	FLSInfo KochCurveInfo;
	KochCurveInfo.Generations = Generations;
	KochCurveInfo.Axiom = TEXT("D");
	KochCurveInfo.AddRule(TEXT("D"), TEXT("D+D−D−D+D"));
	return KochCurveInfo;
}

FLSInfo ULSystemComponent::FractalPlant(int32 Generations)
{
	FLSInfo FractalPlantInfo;
	FractalPlantInfo.Generations = Generations;
	FractalPlantInfo.Axiom = TEXT("M");
	FractalPlantInfo.AddRule(TEXT("M"), TEXT("D−[[M]+M]+D[+DM]−M"));
	FractalPlantInfo.AddRule(TEXT("D"), TEXT("DD"));
	return FractalPlantInfo;
}

FLSInfo ULSystemComponent::RahSystem(int32 Generations)
{
	FLSInfo RahSystemInfo;
	RahSystemInfo.Generations = Generations;
	RahSystemInfo.Axiom = TEXT("M");
	RahSystemInfo.AddRule(TEXT("M"), TEXT("DD[+D][-D][vD][^D][>D][<D]"));
	RahSystemInfo.AddRule(TEXT("N"), TEXT("MND"));
	RahSystemInfo.AddRule(TEXT("D"), TEXT("DDN"));
	RahSystemInfo.AddRule(TEXT("L"), TEXT("L[DL]"));
	RahSystemInfo.AddRule(TEXT("+"), TEXT("[MM+MND-L]"));
	RahSystemInfo.AddRule(TEXT("-"), TEXT("[MM-MDN+L]"));
	RahSystemInfo.AddRule(TEXT("v"), TEXT("[MMvMND^L]"));
	RahSystemInfo.AddRule(TEXT("^"), TEXT("[MM^MDNvL]"));
	RahSystemInfo.AddRule(TEXT(">"), TEXT("[MM>MND<L]"));
	RahSystemInfo.AddRule(TEXT("<"), TEXT("[MM<MDN>L]"));
	return RahSystemInfo;
}

FRLSRenderInfo ULSystemComponent::RenderPythagorasTree()
{
	TArray<ERLSRenderRuleType> RenderRuleTypeArray; RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_DrawLeaf);
	FRLSRenderRule DRule = FRLSRenderRule(TEXT("L"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Draw);
	FRLSRenderRule MRule = FRLSRenderRule(TEXT("D"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Save);
	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnLeft);
	FRLSRenderRule SaveRule = FRLSRenderRule(TEXT("["), RenderRuleTypeArray, 45.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Restore);
	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnRight);
	FRLSRenderRule RetRule = FRLSRenderRule(TEXT("]"), RenderRuleTypeArray, 45.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	FRLSRenderInfo Info;
	Info.Rules.Add(DRule);
	Info.Rules.Add(MRule);
	Info.Rules.Add(SaveRule);
	Info.Rules.Add(RetRule);

	return Info;
}

FRLSRenderInfo ULSystemComponent::RenderKochCurve()
{
	TArray<ERLSRenderRuleType> RenderRuleTypeArray; RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Draw);
	FRLSRenderRule DRule = FRLSRenderRule(TEXT("D"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnRight);
	FRLSRenderRule TRRule = FRLSRenderRule(TEXT("+"), RenderRuleTypeArray, 90.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnLeft);
	FRLSRenderRule TLRule = FRLSRenderRule(TEXT("-"), RenderRuleTypeArray, 90.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	FRLSRenderInfo Info;
	Info.Rules.Add(DRule);
	Info.Rules.Add(TRRule);
	Info.Rules.Add(TLRule);
	return Info;
}

FRLSRenderInfo ULSystemComponent::RenderFractalPlant()
{
	TArray<ERLSRenderRuleType> RenderRuleTypeArray; RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Draw);
	FRLSRenderRule DRule = FRLSRenderRule(TEXT("D"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Move);
	FRLSRenderRule MRule = FRLSRenderRule(TEXT("M"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnRight);
	FRLSRenderRule TRRule = FRLSRenderRule(TEXT("+"), RenderRuleTypeArray, 25.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnLeft);
	FRLSRenderRule TLRule = FRLSRenderRule(TEXT("-"), RenderRuleTypeArray, 25.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Save);
	FRLSRenderRule SaveRule = FRLSRenderRule(TEXT("["), RenderRuleTypeArray, 0.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Restore);
	FRLSRenderRule RetRule = FRLSRenderRule(TEXT("]"), RenderRuleTypeArray, 0.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	FRLSRenderInfo Info;
	Info.Rules.Add(DRule);
	Info.Rules.Add(MRule);
	Info.Rules.Add(TRRule);
	Info.Rules.Add(TLRule);
	Info.Rules.Add(SaveRule);
	Info.Rules.Add(RetRule);
	return Info;
}

FRLSRenderInfo ULSystemComponent::RenderRahSystem()
{
	TArray<ERLSRenderRuleType> RenderRuleTypeArray; RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Draw);
	FRLSRenderRule DRule = FRLSRenderRule(TEXT("D"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_DrawLeaf);
	FRLSRenderRule LRule = FRLSRenderRule(TEXT("L"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Move);
	FRLSRenderRule MRule = FRLSRenderRule(TEXT("M"), RenderRuleTypeArray, 0.0f, 35.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_DoNothing);
	FRLSRenderRule NRule = FRLSRenderRule(TEXT("N"), RenderRuleTypeArray, 0.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnRight);
	FRLSRenderRule TRRule = FRLSRenderRule(TEXT("+"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnLeft);
	FRLSRenderRule TLRule = FRLSRenderRule(TEXT("-"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_PitchDown);
	FRLSRenderRule PDRule = FRLSRenderRule(TEXT("v"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_PitchUp);
	FRLSRenderRule PURule = FRLSRenderRule(TEXT("^"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_RollRight);
	FRLSRenderRule RRRule = FRLSRenderRule(TEXT(">"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_RollLeft);
	FRLSRenderRule RLRule = FRLSRenderRule(TEXT("<"), RenderRuleTypeArray, 35.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Save);
	FRLSRenderRule SaveRule = FRLSRenderRule(TEXT("["), RenderRuleTypeArray, 0.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Restore);
	FRLSRenderRule RetRule = FRLSRenderRule(TEXT("]"), RenderRuleTypeArray, 0.0f, 0.0f);
	RenderRuleTypeArray.Empty();

	FRLSRenderInfo Info;
	Info.Rules.Add(DRule);
	Info.Rules.Add(LRule);
	Info.Rules.Add(NRule);
	Info.Rules.Add(MRule);
	Info.Rules.Add(TRRule);
	Info.Rules.Add(TLRule);
	Info.Rules.Add(PDRule);
	Info.Rules.Add(PURule);
	Info.Rules.Add(RRRule);
	Info.Rules.Add(RLRule);
	Info.Rules.Add(SaveRule);
	Info.Rules.Add(RetRule);
	return Info;
}
