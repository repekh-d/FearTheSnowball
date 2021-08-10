// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "BattleLogEntryInfo.h"


AFPSPlayerState::AFPSPlayerState()
{

}

void AFPSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
