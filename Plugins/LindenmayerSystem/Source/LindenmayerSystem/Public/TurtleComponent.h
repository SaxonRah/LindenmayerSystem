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
