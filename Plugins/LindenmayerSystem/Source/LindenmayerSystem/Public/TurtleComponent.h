// Robert Chubb a.k.a SaxonRah
#pragma once
#include "Components/SceneComponent.h"

#include "RenderLSystem.h"

#include "TurtleComponent.generated.h"



static FORCEINLINE bool TraceActor(
	UWorld* World,
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false
) {
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}



//Trace with an Array of Actors to Ignore
//   Ignore as many actors as you want!
static FORCEINLINE bool TraceActors(
	UWorld* World,
	TArray<AActor*>& ActorsToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false
) {
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorsToIgnore[0]);
	TraceParams.bTraceComplex = true;

	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActors(ActorsToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	return (HitOut.GetActor() != NULL);
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINDENMAYERSYSTEM_API UTurtleComponent : public USceneComponent
{
	GENERATED_BODY()

	FHitResult TempHit;

public:	
	// Sets default values for this component's properties
	UTurtleComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		TArray<FRLSTInfo> State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		FRLSRenderInfo LSystemRenderInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Render")
		FRLSTInfo TurtleInfo;

	FTransform GetSurfaceTransformFromHit(FVector ImpactPoint, FVector HitNormal);

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

	// Debug
	void DebugMove(float length);
	void DebugDraw(float length);
	void DebugDrawLeaf(float angle, float length);
	void DebugTurnRight(float angle);
	void DebugTurnLeft(float angle);
	void DebugTurn180();
	void DebugPitchUp(float angle);
	void DebugPitchDown(float angle);
	void DebugRollRight(float angle);
	void DebugRollLeft(float angle);
	void DebugSave();
	void DebugRestore();
};
