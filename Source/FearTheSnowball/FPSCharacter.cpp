// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(120.f, 0.f, 50.f));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector(), Val);
}

void AFPSCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector(), Val);
}

void AFPSCharacter::Fire_Implementation()
{
	const FRotator SpawnRotation = GetControlRotation();
	// SpawnLocation is in camera space, so transform it to world space before offsetting from the character location to find the final spawn position
	const FVector SpawnLocation = ((ProjectileSpawn != nullptr) ? ProjectileSpawn->GetComponentLocation() : GetActorLocation());

	// Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ActorSpawnParams.Owner = this;
	ActorSpawnParams.Instigator = GetInstigator();

	// spawn the projectile at the muzzle
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}

void AFPSCharacter::Turn(float Val)
{
	AddControllerYawInput(Val);
}

void AFPSCharacter::LookUp(float Val)
{
	AddControllerPitchInput(Val);
}