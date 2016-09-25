// Robert Chubb a.k.a SaxonRah
#pragma once
#include "Components/SceneComponent.h"

#include "RenderLSystem.h"

#include "TurtleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINDENMAYERSYSTEM_API UTurtleComponent : public USceneComponent
{
	GENERATED_BODY()

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

	// Spline Not used 
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
};
