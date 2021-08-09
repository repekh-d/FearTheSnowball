// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleRoyaleGameMode.h"
#include "BattleRoyaleGameState.h"
#include "FPSController.h"
#include "FPSPlayerState.h"


ABattleRoyaleGameMode::ABattleRoyaleGameMode()
{
	GameStateClass = ABattleRoyaleGameState::StaticClass();
}

void ABattleRoyaleGameMode::BeginPlay()
{
	BRGameState = GetGameState<ABattleRoyaleGameState>();

	Super::BeginPlay();
}

void ABattleRoyaleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AFPSController* Controller = Cast<AFPSController>(NewPlayer);
	if (Controller)
	{
		PlayerControllers.Add(Controller);
		AFPSPlayerState* PlayerState = Controller->GetPlayerState<AFPSPlayerState>();
		if (PlayerState)
		{
			BRGameState->AddPlayer(PlayerState);
		}
	}
}