// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoSpawnerComponent.h"
#include "StaticProjectile.h"

// Sets default values for this component's properties
UAmmoSpawnerComponent::UAmmoSpawnerComponent() :
	TimerHandle(),
	ProjectileClass(AStaticProjectile::StaticClass()),
	SpawnRadius(20.f),
	SpawnFrequency(5.f)
{

}

void UAmmoSpawnerComponent::SpawnAmmo()
{
	FVector2D SpawnPoint = FMath::RandPointInCircle(SpawnRadius);
	FVector SpawnLocation = FVector(SpawnPoint, 50.f);

	// Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// spawn the projectile
	GetWorld()->SpawnActor<AStaticProjectile>(ProjectileClass, SpawnLocation, FRotator(0.f, 0.f, 0.f), ActorSpawnParams);
}

void UAmmoSpawnerComponent::StartSpawningAmmo()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAmmoSpawnerComponent::SpawnAmmo, SpawnFrequency, true, 3.0f);
}

void UAmmoSpawnerComponent::StopSpawningAmmo()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
