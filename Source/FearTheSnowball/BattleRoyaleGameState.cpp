// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "BattleRoyaleGameState.h"
#include "Net/UnrealNetwork.h"
#include "BattleRoyaleGameMode.h"
#include "Floor.h"
#include "FPSController.h"
#include "GameFramework/PlayerState.h"

ABattleRoyaleGameState::ABattleRoyaleGameState()
{
	FloorClass = AFloor::StaticClass();
}

void ABattleRoyaleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleRoyaleGameState, PlayerStates);
}

void ABattleRoyaleGameState::BeginPlay()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FActorSpawnParameters Parameters;
		Parameters.Name = "Floor";
		Parameters.Owner = this;
		Floor = GetWorld()->SpawnActor<AFloor>(FloorClass, FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f), Parameters);
	}

	Super::BeginPlay();
}

void ABattleRoyaleGameState::OnRep_PlayerStates()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		OnPlayerJoined.Broadcast(PlayerStates.Top());
	}
}


void ABattleRoyaleGameState::AddPlayer(AFPSPlayerState* NewPlayer)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		PlayerStates.Add(NewPlayer);
		OnRep_PlayerStates();
	}
}