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


// Turtle Commands
FTransform UTurtleComponent::Move(float length)
{
	// Setup Current Location
	FVector StartPosition = this->GetComponentLocation();
	FVector ForwardVector = this->GetComponentTransform().GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FHitResult hit;
	// Move Turtle
	this->SetWorldLocation(FinalPosition, false, &hit, ETeleportType::None);
	//this->SetWorldLocation(FinalPosition, false, &hit, ETeleportType::None);
	TurtleInfo.Transform = this->GetComponentTransform();
	return TurtleInfo.Transform;
}

void UTurtleComponent::Draw(float length)
{
	// Setup Current Location
	FVector StartPosition = GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, FColor(139, 69, 19), false, 10.0f, 0, 7.0f);
}

void UTurtleComponent::DrawLeaf(float angle, float length)
{
	//TurnRight(angle);
	// Setup Current Location
	FVector StartPosition = this->GetComponentLocation();
	FVector ForwardVector = Move(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	DrawDebugLine(GetWorld(), StartPosition, FinalPosition, FColor(139, 69, 19), false, 10.0, 0, 3.0f);
	DrawDebugAltCone(GetWorld(), FinalPosition, this->GetComponentTransform().Rotator(), length * 2, angle, (angle + (length / 2)), FColor(34, 139, 34), false, 10.0, 0, 3.0f);
}

void UTurtleComponent::TurnRight(float angle)
{
	// Pitch Yaw Roll
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw + angle,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::TurnLeft(float angle)
{
	// Pitch Yaw Roll
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw - angle,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::Turn180()
{
	TurnRight(180);
}

void UTurtleComponent::PitchUp(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch + angle,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::PitchDown(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch - angle,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::RollRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll + angle),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::RollLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll - angle),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::Save()
{
	FRLSTInfo ti;
	ti.Transform = this->GetComponentTransform();
	ti.Reduction = TurtleInfo.Reduction;
	ti.Thickness = TurtleInfo.Thickness;
	State.Add(ti);

	//DrawDebugString(GetWorld(), ti.Transform.GetLocation() + FVector(0, 0, 25), TEXT("SAVE"), (AActor*)0, FColor::Red, -1.0f, false);
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
	FHitResult hit;
	this->SetWorldTransform(TurtleInfo.Transform, false, &hit, ETeleportType::None);

	//DrawDebugString(GetWorld(), TurtleInfo.Transform.GetLocation() + FVector(0, 0, 30), TEXT("RESTORE"), (AActor*)0, FColor::Cyan, -1.0f, false);
}


//////////////////////////////////////////////////////////////////////////

// Spline Turtle Commands
FTransform UTurtleComponent::SplineMove(float length)
{
	// Setup Current Location
	FVector StartPosition = this->GetComponentLocation();
	FVector ForwardVector = this->GetComponentTransform().GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

	FHitResult hit;
	// Move Turtle
	this->SetWorldLocation(FinalPosition, false, &hit, ETeleportType::None);
	TurtleInfo.Transform = this->GetComponentTransform();

	return TurtleInfo.Transform;
}

void UTurtleComponent::SplineDraw(float length, int32 index)
{
	// Setup Current Location
	FVector StartPosition = this->GetComponentLocation();
	FVector ForwardVector = SplineMove(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

}

void UTurtleComponent::SplineDrawLeaf(float angle, float length)
{
	// Setup Current Location
	FVector StartPosition = this->GetComponentLocation();
	FVector ForwardVector = SplineMove(length).GetRotation().GetForwardVector();
	FVector ForwardLength = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, length);
	FVector FinalPosition = StartPosition + ForwardLength;

}

void UTurtleComponent::SplineTurnRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw + angle,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplineTurnLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw - angle,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplineTurn180()
{
	SplineTurnRight(180);
}

void UTurtleComponent::SplinePitchUp(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch + angle,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplinePitchDown(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch - angle,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplineRollRight(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll + angle),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplineRollLeft(float angle)
{
	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(FTransform(FRotator(
		this->GetComponentTransform().Rotator().Pitch,
		this->GetComponentTransform().Rotator().Yaw,
		this->GetComponentTransform().Rotator().Roll - angle),
		this->GetComponentTransform().GetLocation(),
		this->GetComponentTransform().GetScale3D()),
		false, &hit, ETeleportType::None);

	TurtleInfo.Transform = this->GetComponentTransform();
}

void UTurtleComponent::SplineSave()
{
	FRLSTInfo ti;
	ti.Transform = this->GetComponentTransform();
	ti.Reduction = TurtleInfo.Reduction;
	ti.Thickness = TurtleInfo.Thickness;
	State.Add(ti);

}
void UTurtleComponent::SplineRestore()
{
	FRLSTInfo ti;
	ti = State.Last();
	State.RemoveAt(State.Num() - 1, 1, true);

	TurtleInfo.Transform = ti.Transform;
	TurtleInfo.Thickness = ti.Thickness;
	TurtleInfo.Reduction = ti.Reduction;

	// Move Turtle
	FHitResult hit;
	this->SetWorldTransform(TurtleInfo.Transform, false, &hit, ETeleportType::None);
}
