// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class FEARTHESNOWBALL_API AFloor : public AActor
{
	GENERATED_BODY()

	// Static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	// Ammunition spawner
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAmmoSpawnerComponent* AmmoSpawner;

	// Class of the Ammo Spawner
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UAmmoSpawnerComponent> AmmoSpawnerClass;

protected:
	// x/y scale of the floor
	UPROPERTY(ReplicatedUsing = OnRep_CurrentAreaSize)
	float CurrentAreaSize;

public:
	// Initial size of the floor
	UPROPERTY(EditDefaultsOnly)
	float StartAreaSize;

	// Final size of the floor
	UPROPERTY(EditDefaultsOnly)
	float EndAreaSize;

public:
	// Sets default values for this actor's properties
	AFloor();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sets the x/y scale of the underlying static mesh
	UFUNCTION(BlueprintCallable)
	void SetCurrentAreaSize(float AreaSize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// CurrentAreaSize replication callback
	UFUNCTION()
	void OnRep_CurrentAreaSize();

	void OnAreaSizeUpdate();
};
