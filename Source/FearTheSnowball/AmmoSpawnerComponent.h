// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoSpawnerComponent.generated.h"


UCLASS(Blueprintable)
class FEARTHESNOWBALL_API UAmmoSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

	// Ammo spawning timer handle
	UPROPERTY()
	FTimerHandle TimerHandle;

	// Class of the projectiles that will be spawned
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AStaticProjectile> ProjectileClass;

public:	
	// Sets default values for this component's properties
	UAmmoSpawnerComponent();

	// Current spawn radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SpawnRadius;

	// Spawn interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SpawnFrequency;

	// Spawn single ammo instance in random location
	UFUNCTION()
	void SpawnAmmo();

	// Start spawning timer
	UFUNCTION(BlueprintCallable)
	void StartSpawningAmmo();

	// Stop spawning timer
	UFUNCTION(BlueprintCallable)
	void StopSpawningAmmo();
};
