// Robert Chubb a.k.a SaxonRah
#include "LindenmayerSystemPrivatePCH.h"

#include "Kismet/KismetMathLibrary.h"

#include "TurtleComponent.h"

// Sets default values for this component's properties
UTurtleComponent::UTurtleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTurtleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTurtleComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

FTransform UTurtleComponent::GetSurfaceTransformFromHit(FVector ImpactPoint, FVector HitNormal)
{
	FTransform temp;
	FVector TempHitNormal = UKismetMathLibrary::Multiply_VectorFloat(HitNormal, -1);
	
	temp.SetLocation(ImpactPoint + HitNormal);
	temp.SetRotation(FQuat(UKismetMathLibrary::MakeRotFromYZ(GetComponentTransform().GetRotation().GetRightVector(), TempHitNormal)));
	temp.SetScale3D(GetComponentScale());
	return temp;
}

//////////////////////////////////////////////////////////////////////////
// Turtle Commands
FTransform UTurtleComponent::Move(float length)
{
	// Setup Current Location
	FTransform StartTransform = GetComponentTransform();
	FVector StartPosition	= StartTransform.GetLocation();
	FVector ForwardVector	= StartTransform.GetRotation().GetForwardVector();
	FVector UpVector		= StartTransform.GetRotation().GetUpVector();
	FVector ForwardLength	= UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector UpLength		= UKismetMathLibrary::Multiply_VectorFloat(UpVector, length);
	FVector FinalPosForward = StartPosition + ForwardLength;
	FVector FinalPosDown	= StartPosition - UpLength;
	FTransform TempFinalTransform;

	FVector TempHitNormal;

	ETeleportType TeleType = ETeleportType::None;

	//Actor to Ignore
	AActor* ActorToIgnore = GetOwner();

	FHitResult hitForward(ForceInit), hitDown(ForceInit);

	// Trace move before move, if path is not clear set transform based on trace hit
	//If Trace Hits anything
	if (Trace(GetWorld(), ActorToIgnore, StartPosition, FinalPosForward, hitForward))
	{
		TempFinalTransform = GetSurfaceTransformFromHit(hitForward.ImpactPoint, hitForward.ImpactNormal);
		// Move Turtle To Hit
		SetWorldTransform(TempFinalTransform, false, &TempHit, TeleType);
	}
	else
	{
		// Move Turtle To final Forward
		SetWorldLocation(FinalPosForward, false, &TempHit, TeleType);

		// otherwise if path is clear set transform on final location and trace down 
		//If Trace Hits anything	
		if (Trace(GetWorld(), ActorToIgnore, StartPosition, FinalPosDown, hitDown))
		{
			TempFinalTransform = GetSurfaceTransformFromHit(hitDown.ImpactPoint, hitDown.ImpactNormal);
			// Move Turtle To Hit
			SetWorldTransform(TempFinalTransform, false, &TempHit, TeleType);
		}
	}
	TurtleInfo.Transform = GetComponentTransform();
	return TurtleInfo.Transform;
}

void UTurtleComponent::Draw(float length)
{
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
}

void UTurtleComponent::DrawLeaf(float angle, float length)
{
	Draw(length);
}

void UTurtleComponent::TurnRight(float angle)
{
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch,
		TempTransform.Rotator().Yaw + angle,
		TempTransform.Rotator().Roll),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::TurnLeft(float angle)
{
	// Pitch Yaw Roll
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch,
		TempTransform.Rotator().Yaw - angle,
		TempTransform.Rotator().Roll),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::Turn180()
{
	TurnRight(180);
}

void UTurtleComponent::PitchUp(float angle)
{
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch + angle,
		TempTransform.Rotator().Yaw,
		TempTransform.Rotator().Roll),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::PitchDown(float angle)
{
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch - angle,
		TempTransform.Rotator().Yaw,
		TempTransform.Rotator().Roll),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::RollRight(float angle)
{
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch,
		TempTransform.Rotator().Yaw,
		TempTransform.Rotator().Roll + angle),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::RollLeft(float angle)
{
	// Move Turtle
	
	FTransform TempTransform = GetComponentTransform();
	SetWorldTransform(FTransform(FRotator(
		TempTransform.Rotator().Pitch,
		TempTransform.Rotator().Yaw,
		TempTransform.Rotator().Roll - angle),
		TempTransform.GetLocation(),
		TempTransform.GetScale3D()),
		false, &TempHit, ETeleportType::None);

	TurtleInfo.Transform = GetComponentTransform();
}

void UTurtleComponent::Save()
{
	FRLSTInfo ti;
	ti.Transform = TurtleInfo.Transform;
	ti.Reduction = TurtleInfo.Reduction;
	ti.Thickness = TurtleInfo.Thickness;

	State.Add(ti);
}

void UTurtleComponent::Restore()
{
	FRLSTInfo ti;
	ti = State.Last();
	State.RemoveAt(State.Num() - 1, 1, true);

	TurtleInfo.Transform = ti.Transform;
	TurtleInfo.Thickness = ti.Thickness;
	TurtleInfo.Reduction = ti.Reduction;

	// Move Turtle
	
	//SetRelativeTransform(TurtleInfo.Transform, false, &TempHit, ETeleportType::None);
	SetWorldTransform(TurtleInfo.Transform, false, &TempHit, ETeleportType::None);
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Rendering Debug Turtle Commands
void UTurtleComponent::DebugMove(float length)
{
	// Setup Current Location
	FVector StartPosition = GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FColor color(255, 0, 255);

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, color, false, 10.0f, 0, 7.0f);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 60), TEXT("Move : ") + FString().SanitizeFloat(length), (AActor*)0, color, -1.0f, false);
}

void UTurtleComponent::DebugDraw(float length)
{
	// Setup Current Location
	FVector StartPosition = GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FColor color(139, 69, 19);

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, color, false, 10.0f, 0, 7.0f);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 40), TEXT("Draw : ") + FString().SanitizeFloat(length), (AActor*)0, color, -1.0f, false);
}

void UTurtleComponent::DebugDrawLeaf(float angle, float length)
{
	// Setup Current Location
	FVector StartPosition = GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FColor lineColor(139, 69, 19), leafColor(34, 139, 34);

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, lineColor, false, 10.0, 0, 3.0f);
	DrawDebugAltCone(GetWorld(), FinalPosition, GetComponentTransform().Rotator(), length * 1.5, angle, (angle + (length / 2)), leafColor, false, 10.0, 0, 3.0f);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, -20), TEXT("Draw Leaf : ") + FString().SanitizeFloat(length), (AActor*)0, leafColor, -1.0f, false);
}

void UTurtleComponent::DebugTurnRight(float angle)
{
	TurnRight(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 15, 0), TEXT("Turn Right : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugTurnLeft(float angle)
{
	TurnLeft(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, -15, 0), TEXT("Turn Left : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugTurn180()
{
	TurnRight(180);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 15, 20), TEXT("Turn 180"), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugPitchUp(float angle)
{
	PitchUp(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 15), TEXT("Pitch Up : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugPitchDown(float angle)
{
	PitchDown(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, -15), TEXT("Pitch Down : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugRollRight(float angle)
{
	RollRight(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(15, 0, 0), TEXT("Roll Right : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugRollLeft(float angle)
{
	RollLeft(angle);
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(-15, 0, 0), TEXT("Roll Left : ") + FString().SanitizeFloat(angle), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugSave()
{
	Save();
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 25), TEXT("SAVE"), (AActor*)0, FColor::Red, -1.0f, false);
}

void UTurtleComponent::DebugRestore()
{
	Restore();
	DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 35), TEXT("RESTORE"), (AActor*)0, FColor::Cyan, -1.0f, false);
}
