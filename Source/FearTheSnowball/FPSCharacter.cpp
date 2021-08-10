// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "FPSPlayerState.h"
#include "BattleRoyaleGameState.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(120.f, 0.f, 50.f));

	AmmoCount = 5;
	LastHit.Player = nullptr;
	LastHit.Time = 0.f;
	IsAlive = true;
}

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSCharacter, AmmoCount);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < 0.f && IsAlive)
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			ABattleRoyaleGameState* GameState = GetWorld()->GetGameState<ABattleRoyaleGameState>();
			if (GameState)
			{
				FDeathEventData Data;
				Data.Killed = GetPlayerState<AFPSPlayerState>();
				if (GetWorld()->GetTimeSeconds() - LastHit.Time < 2.f && LastHit.Player)
				{
					// Killed by other player
					Data.KilledBy = LastHit.Player->GetPlayerState<AFPSPlayerState>();
				}
				else
				{
					// Killed by natural cause
					Data.KilledBy = nullptr;
				}
				GameState->Multicast_AnnounceDeath(Data);
				IsAlive = false;
			}
		}
	}
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
	if (GetLocalRole() != ROLE_Authority)
	{
		OnAmmoCountChanged.Broadcast(AmmoCount);
	}
}

int32 AFPSCharacter::GetAmmoCount()
{
	return AmmoCount;
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

void AFPSCharacter::SetLastHitBy(AFPSCharacter* Player)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		LastHit.Player = Player;
		LastHit.Time = GetWorld()->GetTimeSeconds();
	}
}
