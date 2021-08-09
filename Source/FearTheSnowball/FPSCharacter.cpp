// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "FPSPlayerState.h"
#include "BattleLogEntryInfo.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(120.f, 0.f, 50.f));

	LogMessageClass = UBattleLogEntryInfo::StaticClass();

	AmmoCount = 5;
	LastHit.Player = nullptr;
	LastHit.Time = 0.f;
	IsAlive = true;
}

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSCharacter, AmmoCount);
	DOREPLIFETIME(AFPSCharacter, LastHit);
	DOREPLIFETIME(AFPSCharacter, IsAlive);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < 0.f)
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			SetIsAlive(false);
			OnRep_IsAlive();
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

void AFPSCharacter::OnRep_IsAlive()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		if (!IsAlive)
		{
			UBattleLogEntryInfo* info = NewObject<UBattleLogEntryInfo>(this, LogMessageClass);
			info->Entry1 = GetName();
			if (GetWorld()->GetTimeSeconds() - LastHit.Time < 2.f && LastHit.Player)
			{
				// Killed by other player
				info->ActionType = EActionType::Kill;
				info->Entry2 = LastHit.Player->GetName();
			}
			else
			{
				// Killed by natural cause
				info->ActionType = EActionType::Death;
			}
			info->TimeToLive = 5.0;
			OnPlayerDied.Broadcast(info);
			AFPSPlayerState* GameState = GetPlayerState<AFPSPlayerState>();
			GameState->PassCharacterEvent(info);
		}
	}
}

void AFPSCharacter::SetIsAlive(bool NewAliveStatus)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		IsAlive = NewAliveStatus;
		//GetCharacterMovement()->StopMovementImmediately();
		OnRep_IsAlive();
	}
}