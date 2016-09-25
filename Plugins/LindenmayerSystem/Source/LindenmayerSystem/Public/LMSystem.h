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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* RootComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ULSystemComponent* LSystemComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTurtleComponent* TurtleComp;

	UFUNCTION(BlueprintCallable, Category = "LSystem|Components")
		UPrimitiveComponent* CreateProceduralComponent(UClass* Type, const FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "LSystem|Render")
		void RenderLSystem(FLSystem System, FRLSRenderInfo RenderInfo);

	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void SetSplineMeshes();

	UFUNCTION(BlueprintCallable, Category = "LSystem|Spline")
		void RenderSplineLSystem(FLSystem System, FRLSRenderInfo RenderInfo);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UStaticMesh* SplineDrawMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UMaterial* SplineDrawMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UStaticMesh* SplineDrawLeafMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		UMaterial* SplineDrawLeafMaterial;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		//TArray<UMaterialInstanceDynamic*> Materials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		TArray<USplineMeshComponent*> SplineMeshComponents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSystem|Spline")
		TArray<USplineComponent*> SplineComponents;
	

	
};
