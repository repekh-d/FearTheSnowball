// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomDelegate, int32, AmmoCount);


USTRUCT(BlueprintType)
struct FLastHit
{
	GENERATED_BODY()

	UPROPERTY()
	class AFPSCharacter* Player;

	UPROPERTY()
	float Time;
};


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

	// Information about last collision with projectile
	UPROPERTY()
	FLastHit LastHit;

	UPROPERTY()
	bool bIsAlive;

	virtual void Tick(float DeltaTime) override;

	// AmmoCount replication callback
	UFUNCTION()
	void OnRep_AmmoCount();

	class AFPSPlayerState* GetKiller() const;

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

	// AmmoCount getter
	UFUNCTION(BlueprintCallable)
	int32 GetAmmoCount();

	// AmmoCount setter
	UFUNCTION(BlueprintCallable)
	void SetAmmoCount(int32 NewAmmoCount);

	// AmmoCount setter
	UFUNCTION(BlueprintCallable)
	void AddAmmo(int32 Count);

	// Set instiator of the last hit
	UFUNCTION(BlueprintCallable)
	void SetLastHitBy(AFPSCharacter* Player);

	// Event - fires on the change of ammo amount
	UPROPERTY(BlueprintAssignable, Category = "FPSCharacter")
	FCustomDelegate OnAmmoCountChanged;
};
