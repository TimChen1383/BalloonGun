// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingBalloon.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AFloatingBalloon::AFloatingBalloon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components for floating balloon 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
	BalloonMesh->SetSimulatePhysics(true);
	WireCable = CreateDefaultSubobject<UCableComponent>(TEXT("Wire"));
	WireCable->EndLocation = FVector(0,0,0);
	WireCable->SolverIterations = 10;
	BalloonMesh->SetupAttachment(RootComponent);
	WireCable->SetupAttachment(BalloonMesh);
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetLinearXLimit(LCM_Limited, 300);
	PhysicsConstraint->SetLinearYLimit(LCM_Limited, 300);
	PhysicsConstraint->SetLinearZLimit(LCM_Limited, 300);
	PhysicsConstraint->ComponentName2.ComponentName = TEXT("BalloonMesh");
	PhysicsConstraint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFloatingBalloon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingBalloon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add floating force to the balloon evey tick
	BalloonMesh->AddForceAtLocation(UpliftingForce*FVector(0,0,1),BalloonMesh->GetComponentLocation());
}

void AFloatingBalloon::AttachTarget(UPrimitiveComponent* HitComponent, FVector HitLocation, FName HitBoneName)
{
	//setup physics constraint with balloon and hit target
	PhysicsConstraint->SetConstrainedComponents(BalloonMesh, TEXT("None"),HitComponent, HitBoneName);
	//setup cable between balloon and hit target
	WireCable->SetAttachEndToComponent(HitComponent, HitBoneName);
}

