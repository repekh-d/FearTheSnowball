// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FEARTHESNOWBALL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move character along forward vector
	void MoveForward(float Val);

	// Move character along right vector
	void MoveRight(float Val);

	// Fire the projectile
	void Fire();

	// Horizontal rotation
	void Turn(float Val);

	// Vertical rotation
	void LookUp(float Val);
};
