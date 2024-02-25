// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "FloatingBalloon.generated.h"

UCLASS()
class CPPPRACTICE_API AFloatingBalloon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingBalloon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	USceneComponent* RootComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BalloonMesh;
	UPROPERTY(EditAnywhere)
	UCableComponent* WireCable;
	//Control the floating force. Work with simulate physics. Value need to be set quite high
	UPROPERTY(EditAnywhere, Category="FloatingBalloon")
	float UpliftingForce = 1500;
	UPROPERTY(EditAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint;
	FVector CableOrigin;

	UFUNCTION(BlueprintCallable, Category=FloatingBalloon)
	void AttachTarget(UPrimitiveComponent* HitComponent, FVector HitLocation, FName HitBoneName);

};
