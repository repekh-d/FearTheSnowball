// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FEARTHESNOWBALL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	// Projectiles spawn position
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	USceneComponent* ProjectileSpawn;

	// Class of projectile to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

protected:
	// Amount of posessed ammo
	UPROPERTY(ReplicatedUsing = OnRep_AmmoCount)
	int32 AmmoCount;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// AmmoCount replication callback
	UFUNCTION()
	void OnRep_AmmoCount();

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	// AmmoCount setter
	UFUNCTION(BlueprintCallable)
	void SetAmmoCount(int32 NewAmmoCount);

	// AmmoCount setter
	UFUNCTION(BlueprintCallable)
	void AddAmmo(int32 Count);
};
