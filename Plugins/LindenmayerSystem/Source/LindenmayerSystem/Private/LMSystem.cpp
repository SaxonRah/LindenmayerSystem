// Robert Chubb a.k.a SaxonRah
#include "LindenmayerSystemPrivatePCH.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "LMSystem.h"

ALMSystem::ALMSystem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create and Set our root as the RootComponent
	RootComp = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root Component"));
	RootComp->SetMobility(EComponentMobility::Static);
	RootComponent = RootComp;

	// Create Turtle
	RenderTurtle = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Turtle Control"));
	RenderTurtle->SetMobility(EComponentMobility::Movable);

	// Create Spline
	//RenderSplineComponents = ObjectInitializer.CreateDefaultSubobject<USplineMeshComponent>(this, TEXT("Render Spline Component"));
	//RenderSplineComponents->SetMobility(EComponentMobility::Movable);

};

// LSystem
void ALMSystem::SetupLSystem(FLSInfo Info)
{
	LSystem = FLSystem(Info);
}

void ALMSystem::GrowLSystem()
{
	LSystem.GrowLSystem();
}

void ALMSystem::GrowLSystemBy(int32 Generations)
{
	LSystem.GrowLSystemBy(Generations);
}

// Turtle Commands
FTransform ALMSystem::Move(float length)
{
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = RenderTurtle->GetComponentTransform().GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FHitResult hit;
	// Move Turtle
	RenderTurtle->SetWorldLocation(FinalPosition, false, &hit, ETeleportType::None);
	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
	return TurtleInfo.Transform;
}

void ALMSystem::Draw(float length)
{
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, FColor(139, 69, 19), false, 10.0f, 0, 7.0f);
}

void ALMSystem::DrawLeaf(float angle, float length)
{
	//TurnRight(angle);
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, FColor(139, 69, 19), false, 10.0, 0, 3.0f);
	DrawDebugAltCone(GetWorld(), FinalPosition, RenderTurtle->GetComponentTransform().Rotator(), length*2, angle, (angle+(length/2)), FColor(34, 139, 34), false, 10.0, 0, 3.0f);
}

void ALMSystem::TurnRight(float angle)
{
	// Pitch Yaw Roll
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw + angle,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);
	
	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::TurnLeft(float angle)
{
	// Pitch Yaw Roll
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw - angle,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::Turn180()
{
	TurnRight(180);
}

void ALMSystem::PitchUp(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch + angle,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::PitchDown(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch - angle,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::RollRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll + angle),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::RollLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll - angle),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::Save()
{
	FRLSTInfo ti;
	ti.Transform = RenderTurtle->GetComponentTransform();
	ti.Reduction = TurtleInfo.Reduction;
	ti.Thickness = TurtleInfo.Thickness;
	State.Add(ti);

	//DrawDebugString(GetWorld(), ti.Transform.GetLocation() + FVector(0, 0, 25), TEXT("SAVE"), (AActor*)0, FColor::Red, -1.0f, false);
}

void ALMSystem::Restore()
{
	FRLSTInfo ti;
	ti = State.Last();
	State.RemoveAt(State.Num()-1, 1, true);

	TurtleInfo.Transform = ti.Transform;
	TurtleInfo.Thickness = ti.Thickness;
	TurtleInfo.Reduction = ti.Reduction;

	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(TurtleInfo.Transform, false, &hit, ETeleportType::None);

	//DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 30), TEXT("RESTORE"), (AActor*)0, FColor::Cyan, -1.0f, false);
}

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
							Move(RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_Draw:
						{
							Draw(RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_DrawLeaf:
						{
							DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							break;
						}
						case ERLSRenderRuleType::LSRR_TurnRight:
						{
							TurnRight(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_TurnLeft:
						{
							TurnLeft(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_Turn180:
						{
							Turn180();
							break;
						}
						case ERLSRenderRuleType::LSRR_PitchDown:
						{
							PitchDown(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_PitchUp:
						{
							PitchUp(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_RollRight:
						{
							RollRight(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_RollLeft:
						{
							RollLeft(RenderInfo.Rules[r].Angle);
							break;
						}
						case ERLSRenderRuleType::LSRR_Save:
						{
							Save();
							break;
						}
						case ERLSRenderRuleType::LSRR_Restore:
						{
							Restore();
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
	RenderTurtle->SetWorldTransform(this->GetActorTransform());
	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

// Spline Turtle Commands
FTransform ALMSystem::SplineMove(float length)
{
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = RenderTurtle->GetComponentTransform().GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FHitResult hit;
	// Move Turtle
	RenderTurtle->SetWorldLocation(FinalPosition, false, &hit, ETeleportType::None);
	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();

	return TurtleInfo.Transform;
}

void ALMSystem::SplineDraw(float length, int32 index)
{
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = SplineMove(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

}

void ALMSystem::SplineDrawLeaf(float angle, float length)
{
	// Setup Current Location
	FVector StartPosition = RenderTurtle->GetComponentLocation();
	FVector ForwardVector = SplineMove(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

}

void ALMSystem::SplineTurnRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw + angle,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplineTurnLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw - angle,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplineTurn180()
{
	SplineTurnRight(180);
}

void ALMSystem::SplinePitchUp(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch + angle,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplinePitchDown(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch - angle,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplineRollRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll + angle),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplineRollLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(FTransform(FRotator(
		RenderTurtle->GetComponentTransform().Rotator().Pitch,
		RenderTurtle->GetComponentTransform().Rotator().Yaw,
		RenderTurtle->GetComponentTransform().Rotator().Roll - angle),
		RenderTurtle->GetComponentTransform().GetLocation(),
		RenderTurtle->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();
}

void ALMSystem::SplineSave()
{
	FRLSTInfo ti;
	ti.Transform = RenderTurtle->GetComponentTransform();
	ti.Reduction = TurtleInfo.Reduction;
	ti.Thickness = TurtleInfo.Thickness;
	State.Add(ti);

}
void ALMSystem::SplineRestore()
{
	FRLSTInfo ti;
	ti = State.Last();
	State.RemoveAt(State.Num() - 1, 1, true);

	TurtleInfo.Transform = ti.Transform;
	TurtleInfo.Thickness = ti.Thickness;
	TurtleInfo.Reduction = ti.Reduction;

	// Move Turtle
	FHitResult hit;
	RenderTurtle->SetWorldTransform(TurtleInfo.Transform, false, &hit, ETeleportType::None);
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
	FTransform Temp = RenderTurtle->GetComponentTransform();
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
						Move(RenderInfo.Rules[r].Length);
						//SplineMove(RenderInfo.Rules[r].Length);
						break;
					}
					case ERLSRenderRuleType::LSRR_Draw:
					{
						if (SplineDrawMesh->IsValidLowLevel() && SplineDrawMaterial->IsValidLowLevel())
						{
							// Draw then Add a new point to the current spline
							Draw(RenderInfo.Rules[r].Length);
							//SplineDraw(RenderInfo.Rules[r].Length, i);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(RenderTurtle->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;

							//Set the color!
							UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(SplineDrawMaterial, this);
							dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.5f, 0.3f, 0.1f, 1.0f));

							USplineMeshComponent* SplineMesh;
							Temp = RenderTurtle->GetComponentTransform();
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
							Draw(RenderInfo.Rules[r].Length);
							//SplineDraw(RenderInfo.Rules[r].Length, i);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(RenderTurtle->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;
							break;
						}
					}
					case ERLSRenderRuleType::LSRR_DrawLeaf:
					{
						if (SplineDrawLeafMesh->IsValidLowLevel() && SplineDrawLeafMaterial->IsValidLowLevel())
						{
							// Draw Leaf then Add a new point to the current spline
							DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							//SplineDrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(RenderTurtle->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;

							//Set the color!
							UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(SplineDrawLeafMaterial, this);
							dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.0f, 0.5f, 0.0f, 1.0f));

							USplineMeshComponent* SplineMesh;
							Temp = RenderTurtle->GetComponentTransform();
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
							DrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);
							//SplineDrawLeaf(RenderInfo.Rules[r].Angle, RenderInfo.Rules[r].Length);

							SplineComponents[CurrentSplineIndex]->AddSplineLocalPoint(RenderTurtle->GetComponentTransform().GetLocation());
							PointIndex = PointIndex + 1;
							break; 
						}
					}
					case ERLSRenderRuleType::LSRR_TurnRight:
					{
						TurnRight(RenderInfo.Rules[r].Angle);
						//SplineTurnRight(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_TurnLeft:
					{
						TurnLeft(RenderInfo.Rules[r].Angle);
						//SplineTurnLeft(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_Turn180:
					{
						Turn180();
						//SplineTurn180();
						break;
					}
					case ERLSRenderRuleType::LSRR_PitchDown:
					{
						PitchDown(RenderInfo.Rules[r].Angle);
						//SplinePitchDown(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_PitchUp:
					{
						PitchUp(RenderInfo.Rules[r].Angle);
						//SplinePitchUp(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_RollRight:
					{
						RollRight(RenderInfo.Rules[r].Angle);
						//SplineRollRight(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_RollLeft:
					{
						RollLeft(RenderInfo.Rules[r].Angle);
						//SplineRollLeft(RenderInfo.Rules[r].Angle);
						break;
					}
					case ERLSRenderRuleType::LSRR_Save:
					{
						Save();
						//SplineSave();
						break;
					}
					case ERLSRenderRuleType::LSRR_Restore:
					{
						Restore();
						//SplineRestore();

						// Restore turtle position then start a new spline
						USplineComponent* SplineTemp;
						Temp = RenderTurtle->GetComponentTransform();
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

	RenderTurtle->SetWorldTransform(this->GetActorTransform());
	TurtleInfo.Transform = RenderTurtle->GetComponentTransform();

	//SetSplineMeshes();

	RegisterAllComponents();
}

// Examples
FLSInfo ALMSystem::Algae(int32 Generations)
{
	FLSInfo AlgaeInfo;
	AlgaeInfo.Generations = Generations;
	AlgaeInfo.Axiom = TEXT("D");
	AlgaeInfo.AddRule(TEXT("D"), TEXT("DM"));
	AlgaeInfo.AddRule(TEXT("M"), TEXT("D"));
	return AlgaeInfo;
}

FLSInfo ALMSystem::PythagorasTree(int32 Generations)
{
	FLSInfo PythagorasTreeInfo;
	PythagorasTreeInfo.Generations = Generations;
	PythagorasTreeInfo.Axiom = TEXT("L");
	PythagorasTreeInfo.AddRule(TEXT("L"), TEXT("D[L]L"));
	PythagorasTreeInfo.AddRule(TEXT("D"), TEXT("DD"));
	return PythagorasTreeInfo;
}

FLSInfo ALMSystem::KochCurve(int32 Generations)
{
	FLSInfo KochCurveInfo;
	KochCurveInfo.Generations = Generations;
	KochCurveInfo.Axiom = TEXT("D");
	KochCurveInfo.AddRule(TEXT("D"), TEXT("D+D−D−D+D"));
	return KochCurveInfo;
}

FLSInfo ALMSystem::FractalPlant(int32 Generations)
{
	FLSInfo FractalPlantInfo;
	FractalPlantInfo.Generations = Generations;
	FractalPlantInfo.Axiom = TEXT("M");
	FractalPlantInfo.AddRule(TEXT("M"), TEXT("D−[[M]+M]+D[+DM]−M"));
	FractalPlantInfo.AddRule(TEXT("D"), TEXT("DD"));
	return FractalPlantInfo;
}

FLSInfo ALMSystem::RahSystem(int32 Generations)
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

FRLSRenderInfo ALMSystem::RenderPythagorasTree()
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

FRLSRenderInfo ALMSystem::RenderKochCurve()
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

FRLSRenderInfo ALMSystem::RenderFractalPlant()
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

FRLSRenderInfo ALMSystem::RenderRahSystem()
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
