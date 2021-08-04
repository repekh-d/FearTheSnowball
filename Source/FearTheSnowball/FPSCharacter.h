// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FEARTHESNOWBALL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* ProjectileSpawn;

	// Class of projectile to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Move character along forward vector
	void MoveForward(float Val);

	// Move character along right vector
	void MoveRight(float Val);

	// Fire the projectile
	UFUNCTION(Server, Reliable)
	void Fire();

	// Horizontal rotation
	void Turn(float Val);

	// Vertical rotation
	void LookUp(float Val);
};
