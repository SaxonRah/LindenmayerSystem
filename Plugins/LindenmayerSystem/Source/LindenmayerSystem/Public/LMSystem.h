// Robert Chubb a.k.a SaxonRah
#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SplineComponent.h"
#include "Classes/Components/SplineMeshComponent.h"

#include "LSystemComponent.h"
#include "TurtleComponent.h"

#include "LMSystem.generated.h"

UCLASS()
class ALMSystem : public AActor
{
	GENERATED_BODY()
public:
	// Boilerplate
	ALMSystem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (ClampMin = 0, ClampMax = 10), EditAnywhere, BlueprintReadWrite, Category = "Default")
		int32 Generations;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* RootComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ULSystemComponent* LSystemComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTurtleComponent* TurtleComp;

	// Render Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		UStaticMesh* SplineDrawMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		UMaterial* SplineDrawMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		UStaticMesh* SplineDrawLeafMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		UMaterial* SplineDrawLeafMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		TArray<USplineComponent*> SplineComponents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		TArray<USplineMeshComponent*> SplineMeshComponents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline Component")
		TArray<UMaterialInstanceDynamic*> Materials;

	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void ClearSplineSystem(); 
	UFUNCTION(BlueprintCallable, Category = "LSystem|Debug")
		void ClearDebugRender();
	UFUNCTION(BlueprintCallable, Category = "LSystem|Components")
		UPrimitiveComponent* CreateProceduralComponent(UClass* Type, const FTransform& Transform);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void RenderSplineLSystem(FLSystem System, FRLSRenderInfo RenderInfo);
	UFUNCTION(BlueprintCallable, Category = "LSystem|Debug")
		void RenderDebugLSystem(FLSystem System, FRLSRenderInfo RenderInfo);

};
