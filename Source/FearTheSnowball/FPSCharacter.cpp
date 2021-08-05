// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(120.f, 0.f, 50.f));

	AmmoCount = 5;
}

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSCharacter, AmmoCount);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (AmmoCount < 1)
		return;

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
	AddAmmo(-1);
}

void AFPSCharacter::Turn(float Val)
{
	AddControllerYawInput(Val);
}

void AFPSCharacter::LookUp(float Val)
{
	AddControllerPitchInput(Val);
}

void AFPSCharacter::OnRep_AmmoCount()
{

}

void AFPSCharacter::SetAmmoCount(int32 NewAmmoCount)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AmmoCount = FMath::Max(NewAmmoCount, 0);
		OnRep_AmmoCount();
	}
}

void AFPSCharacter::AddAmmo(int32 Count)
{
	SetAmmoCount(Count + AmmoCount);
}