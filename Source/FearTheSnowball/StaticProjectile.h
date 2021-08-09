// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticProjectile.generated.h"

USTRUCT(BlueprintType)
struct FPickedUpEventInfo
{
	GENERATED_BODY()

	UPROPERTY()
	class AFPSCharacter* Player;

	UPROPERTY()
	int32 Count;

	UPROPERTY()
	TSubclassOf<class AStaticProjectile> ProjectileClass;
};

UCLASS()
class FEARTHESNOWBALL_API AStaticProjectile : public AActor
{
	GENERATED_BODY()
	
	// Collision component
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	class USphereComponent* CollisionComp;

	// Static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	// Amount of ammunition that will be picked up
	UPROPERTY(EditDefaultsOnly)
	int32 AmmoCount;

public:	
	// Sets default values for this actor's properties
	AStaticProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OnBeginOverlap(
		class UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
