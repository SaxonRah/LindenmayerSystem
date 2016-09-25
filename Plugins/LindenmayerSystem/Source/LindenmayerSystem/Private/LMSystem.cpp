// Robert Chubb a.k.a SaxonRah
#include "LindenmayerSystemPrivatePCH.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "LMSystem.h"

ALMSystem::ALMSystem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create and Set our root as the RootComponent
	RootComp = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root Component"));
	RootComp->SetMobility(EComponentMobility::Static);
	RootComponent = RootComp;

	// Create LSystem Component
	LSystemComp = ObjectInitializer.CreateDefaultSubobject<ULSystemComponent>(this, TEXT("LSystem Component"));
	//LSystemComp->AddToRoot();
	//LSystemComp->RegisterComponent();

	// Create Turtle
	TurtleComp = ObjectInitializer.CreateDefaultSubobject<UTurtleComponent>(this, TEXT("Turtle Component"));
	TurtleComp->SetMobility(EComponentMobility::Movable);

	// Create Spline
	//RenderSplineComponents = ObjectInitializer.CreateDefaultSubobject<USplineMeshComponent>(this, TEXT("Render Spline Component"));
	//RenderSplineComponents->SetMobility(EComponentMobility::Movable);

};

// Render
void ALMSystem::RenderLSystem(FLSystem System, FRLSRenderInfo RenderInfo)
{
	//Save(); Restore();
	// Loop through entire string state
	FString TempString = System.Info.States.Last();
	for (int32 i = 0; i < TempString.Len(); ++i)
	{
		// loop through rules
		for (int32 r = 0; r < RenderInfo.Rules.Num(); ++r)
		{
			// check if character == variable
			if (TempString[i] == RenderInfo.Rules[r].Variable[0])
			{
				// loop through rules for each variable
				for (int32 rt = 0; rt < RenderInfo.Rules[r].RuleType.Num(); ++rt)
				{
					// Switch on each rule from RuleType Array
					switch (RenderInfo.Rules[r].RuleType[rt])
					{
						default:
						{ 
							break; 
						}
						case ERLSRenderRuleType::LSRR_DoNothing:
						{ 
							break; 
						}
						case ERLSRenderRuleType::LSRR_Move:
						{
							TurtleComp->Move(RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_Draw:
						{
							TurtleComp->Draw(RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_DrawLeaf:
						{
							TurtleComp->DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_TurnRight:
						{
							TurtleComp->TurnRight(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_TurnLeft:
						{
							TurtleComp->TurnLeft(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_Turn180:
						{
							TurtleComp->Turn180();
							break;
						}
						case ERLSRenderRuleType::LSRR_PitchDown:
						{
							TurtleComp->PitchDown(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_PitchUp:
						{
							TurtleComp->PitchUp(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_RollRight:
						{
							TurtleComp->RollRight(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_RollLeft:
						{
							TurtleComp->RollLeft(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_Save:
						{
							TurtleComp->Save();
							break;
						}
						case ERLSRenderRuleType::LSRR_Restore:
						{
							TurtleComp->Restore();
							break;
						}
						case ERLSRenderRuleType::LSRR_COUNT:
						{
							break;
						}
					}
				}
			}
		}
	}
	TurtleComp->SetWorldTransform(this->GetActorTransform());
	TurtleComp->TurtleInfo.Transform = TurtleComp->GetComponentTransform();
}

void ALMSystem::SetSplineMeshes()
{
	// Clean up old Spline Meshes / Materials
	for (int32 smc = 0; smc < SplineMeshComponents.Num(); ++smc)
	{
		SplineMeshComponents[smc]->DestroyComponent(false);
	}
	SplineMeshComponents.Empty();
	/*
	for (int32 m = 0; m < Materials.Num(); ++m)
	{
		Materials[m]->MarkPendingKill();
	}
	Materials.Empty();
	*/
	if (SplineComponents.Num() >= 1 && SplineDrawMesh->IsValidLowLevel() && SplineDrawMaterial->IsValidLowLevel())
	{
		for (int32 sc = 0; sc < SplineComponents.Num(); ++sc)
		{
			for (int32 sp = 0; sp < SplineComponents[sc]->GetNumberOfSplinePoints() - 1; ++sp)
			{
				//Set the color!
				UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(SplineDrawMaterial, this);
				dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.5f, 0.3f, 0.1f, 1.0f));
				
				USplineMeshComponent* SplineMesh;
				FTransform Temp; Temp = FTransform(FRotator(0, 0, 0), SplineComponents[sc]->GetLocationAtSplinePoint(sp, ESplineCoordinateSpace::Local), FVector(1, 1, 1));
				SplineMesh = (USplineMeshComponent*)CreateProceduralComponent(USplineMeshComponent::StaticClass(), Temp);
				SplineMesh->SetMobility(EComponentMobility::Movable);
				//SplineMesh->AttachToComponent(SplineComponents[sc]->GetChildComponent(0), FAttachmentTransformRules::KeepWorldTransform, NAME_None);

				//Width of the mesh 
				/*
				float StartSize = 0.2f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
				float EndSize = 0.1f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
				SplineMesh->SetStartScale(FVector2D(StartSize, StartSize), true);
				SplineMesh->SetEndScale(FVector2D(EndSize, EndSize), true);
				*/

				SplineMesh->SetStartScale(FVector2D(1.0f, 1.0f), true);
				SplineMesh->SetEndScale(FVector2D(1.0f, 1.0f), true);

				FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
				SplineComponents[sc]->GetLocalLocationAndTangentAtSplinePoint(sp, pointLocationStart, pointTangentStart);
				SplineComponents[sc]->GetLocalLocationAndTangentAtSplinePoint(sp + 1, pointLocationEnd, pointTangentEnd);

				SplineMesh->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, false);

				SplineMesh->bCastDynamicShadow = false;
				SplineMesh->SetStaticMesh(SplineDrawMesh);
				SplineMesh->SetMaterial(0, dynamicMat);
				// Materials.Add(dynamicMat);
				SplineMeshComponents.Add(SplineMesh);
			}
		}
	} 
}

UPrimitiveComponent* ALMSystem::CreateProceduralComponent(UClass* Type, const FTransform& Transform)
{
	UPrimitiveComponent* CreatedComponent = NewObject<UPrimitiveComponent>(this, Type);
	if (!CreatedComponent)
	{
		return (UPrimitiveComponent*)nullptr;
	}

	CreatedComponent->RegisterComponent(); //You must NewObject<>() with a valid Outer that has world, this == Outer
	CreatedComponent->SetWorldLocation(Transform.GetLocation());
	CreatedComponent->SetWorldRotation(Transform.GetRotation());
	CreatedComponent->AttachToComponent(RootComp, FAttachmentTransformRules::SnapToTargetIncludingScale, NAME_None);
	return CreatedComponent;
}

// SplineComponents is a TArray of USplineComponents
// We need a new spline component for every position from a save to restore
// We first add one spline which goes from the origin of the system until a restore takes place,
// Restore will move the turtle and add a new spline component at the new location.
// We Then target this new index in the TArray of USplineComponents to add points on.

void ALMSystem::RenderSplineLSystem(FLSystem System, FRLSRenderInfo RenderInfo)
{
	// Setup Index var and empty spline array.
	int32 CurrentSplineIndex = 0, PointIndex = 0;;
	SplineComponents.Empty();

	// Clean up old Spline Meshes
	for (int32 smc = 0; smc < SplineMeshComponents.Num(); ++smc)
	{
		SplineMeshComponents[smc]->DestroyComponent(false);
	}
	SplineMeshComponents.Empty();

	// Create, Setup and Add Component to Array
	USplineComponent* RootSplineTemp;
	FTransform Temp = TurtleComp->GetComponentTransform();
	RootSplineTemp = (USplineComponent*)CreateProceduralComponent(USplineComponent::StaticClass(), Temp);
	RootSplineTemp->SetClosedLoop(false);
	RootSplineTemp->ClearSplinePoints(false);
	RootSplineTemp->AddSplineLocalPoint(Temp.GetLocation());

	CurrentSplineIndex = SplineComponents.Add(RootSplineTemp);

	// Loop through entire string state
	FString TempString = System.Info.States.Last();
	for (int32 i = 0; i < TempString.Len(); ++i)
	{
		// loop through rules
		for (int32 r = 0; r < RenderInfo.Rules.Num(); ++r)
		{
			// check if character == variable
			if (TempString[i] == RenderInfo.Rules[r].Variable[0])
			{
				// loop through rules for each variable
				for (int32 rt = 0; rt < RenderInfo.Rules[r].RuleType.Num(); ++rt)
				{
					// Switch on each rule from RuleType Array
					switch (RenderInfo.Rules[r].RuleType[rt])
					{
					default:
					{
						break;
					}
					case ERLSRenderRuleType::LSRR_DoNothing:
					{
						break;
					}
					case ERLSRenderRuleType::LSRR_Move:
					{
						TurtleComp->Move(RenderInfo.Rules[r].Length);
						//SplineMove(RenderInfo.Rules[r].Length);
						break;
					}
					case ERLSRenderRuleType::LSRR_Draw:
					{
						if (SplineDrawMesh->IsValidLowLevel() && SplineDrawMaterial->IsValidLowLevel())
						{
							// Draw then Add a new point to the current spline
							TurtleComp->Draw(RenderInfo.Rules[r].Length);
							//SplineDraw(RenderInfo.Rules[r].Length, i);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(TurtleComp->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;

							//Set the color!
							UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(SplineDrawMaterial, this);
							dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.5f, 0.3f, 0.1f, 1.0f));

							USplineMeshComponent* SplineMesh;
							Temp = TurtleComp->GetComponentTransform();
							SplineMesh = (USplineMeshComponent*)CreateProceduralComponent(USplineMeshComponent::StaticClass(), Temp);
							SplineMesh->SetMobility(EComponentMobility::Movable);

							//Width of the mesh 
							/*
							float StartSize = 0.2f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
							float EndSize = 0.1f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
							SplineMesh->SetStartScale(FVector2D(StartSize, StartSize), true);
							SplineMesh->SetEndScale(FVector2D(EndSize, EndSize), true);
							*/

							SplineMesh->SetStartScale(FVector2D(1.0f, 1.0f), true);
							SplineMesh->SetEndScale(FVector2D(1.0f, 1.0f), true);

							FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
							if (PointIndex == 0 && SplineComponents[CurrentSplineIndex]->GetNumberOfSplinePoints() >= 2)
							{
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex, pointLocationStart, pointTangentStart);
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex + 1, pointLocationEnd, pointTangentEnd);
							}
							else if (PointIndex >= 1 && SplineComponents[CurrentSplineIndex]->GetNumberOfSplinePoints() >= 2)
							{
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex - 1, pointLocationStart, pointTangentStart);
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex, pointLocationEnd, pointTangentEnd);
							}

							SplineMesh->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, false);

							SplineMesh->bCastDynamicShadow = false;
							SplineMesh->SetStaticMesh(SplineDrawMesh);
							SplineMesh->SetMaterial(0, dynamicMat);
							// Materials.Add(dynamicMat);
							SplineMeshComponents.Add(SplineMesh);
							break;
						} 
						else 
						{
							// Draw then Add a new point to the current spline
							TurtleComp->Draw(RenderInfo.Rules[r].Length);
							//SplineDraw(RenderInfo.Rules[r].Length, i);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(TurtleComp->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;
							break;
						}
					}
					case ERLSRenderRuleType::LSRR_DrawLeaf:
					{
						if (SplineDrawLeafMesh->IsValidLowLevel() && SplineDrawLeafMaterial->IsValidLowLevel())
						{
							// Draw Leaf then Add a new point to the current spline
							TurtleComp->DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							//SplineDrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(TurtleComp->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;

							//Set the color!
							UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(SplineDrawLeafMaterial, this);
							dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.0f, 0.5f, 0.0f, 1.0f));

							USplineMeshComponent* SplineMesh;
							Temp = TurtleComp->GetComponentTransform();
							SplineMesh = (USplineMeshComponent*)CreateProceduralComponent(USplineMeshComponent::StaticClass(), Temp);
							SplineMesh->SetMobility(EComponentMobility::Movable);

							//Width of the mesh 
							/*
							float StartSize = 0.2f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
							float EndSize = 0.1f * (SplineComponents[sc]->GetNumberOfSplinePoints() - sp);
							SplineMesh->SetStartScale(FVector2D(StartSize, StartSize), true);
							SplineMesh->SetEndScale(FVector2D(EndSize, EndSize), true);
							*/

							SplineMesh->SetStartScale(FVector2D(1.0f, 1.0f), true);
							SplineMesh->SetEndScale(FVector2D(1.0f, 1.0f), true);

							FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
							if (PointIndex == 0 && SplineComponents[CurrentSplineIndex]->GetNumberOfSplinePoints() >= 2)
							{
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex, pointLocationStart, pointTangentStart);
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex + 1, pointLocationEnd, pointTangentEnd);
							}
							else if (PointIndex >= 1 && SplineComponents[CurrentSplineIndex]->GetNumberOfSplinePoints() >= 2)
							{
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex - 1, pointLocationStart, pointTangentStart);
								SplineComponents[CurrentSplineIndex]->GetLocalLocationAndTangentAtSplinePoint(PointIndex, pointLocationEnd, pointTangentEnd);
							}

							SplineMesh->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, false);

							SplineMesh->bCastDynamicShadow = false;
							SplineMesh->SetStaticMesh(SplineDrawLeafMesh);
							SplineMesh->SetMaterial(0, dynamicMat);
							// Materials.Add(dynamicMat);
							SplineMeshComponents.Add(SplineMesh);
							break;
						} 
						else 
						{ // Draw Leaf then Add a new point to the current spline
							TurtleComp->DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							//SplineDrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(TurtleComp->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;
							break; 
						}
					}
					case ERLSRenderRuleType::LSRR_TurnRight:
					{
						TurtleComp->TurnRight(RenderInfo.Rules[r].Angle);
						//SplineTurnRight(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_TurnLeft:
					{
						TurtleComp->TurnLeft(RenderInfo.Rules[r].Angle);
						//SplineTurnLeft(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_Turn180:
					{
						TurtleComp->Turn180();
						//SplineTurn180();
						break;
					}
					case ERLSRenderRuleType::LSRR_PitchDown:
					{
						TurtleComp->PitchDown(RenderInfo.Rules[r].Angle);
						//SplinePitchDown(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_PitchUp:
					{
						TurtleComp->PitchUp(RenderInfo.Rules[r].Angle);
						//SplinePitchUp(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_RollRight:
					{
						TurtleComp->RollRight(RenderInfo.Rules[r].Angle);
						//SplineRollRight(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_RollLeft:
					{
						TurtleComp->RollLeft(RenderInfo.Rules[r].Angle);
						//SplineRollLeft(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_Save:
					{
						TurtleComp->Save();
						//SplineSave();
						break;
					}
					case ERLSRenderRuleType::LSRR_Restore:
					{
						TurtleComp->Restore();
						//SplineRestore();

						// Restore turtle position then start a new spline
						USplineComponent* SplineTemp;
						Temp = TurtleComp->GetComponentTransform();
						SplineTemp = (USplineComponent*)CreateProceduralComponent(USplineComponent::StaticClass(), Temp);
						SplineTemp->SetClosedLoop(false);
						SplineTemp->ClearSplinePoints(false);

						// Add point at restores spline index
						SplineTemp->AddSplineLocalPoint(Temp.GetLocation());
						PointIndex = 0;
						CurrentSplineIndex = SplineComponents.Add(SplineTemp);
						break;
					}
					case ERLSRenderRuleType::LSRR_COUNT:
					{
						break;
					}
					}
				}
			}
		}
	}

	TurtleComp->SetWorldTransform(this->GetActorTransform());
	TurtleComp->TurtleInfo.Transform = TurtleComp->GetComponentTransform();

	//SetSplineMeshes();

	RegisterAllComponents();
}
