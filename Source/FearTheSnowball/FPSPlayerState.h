// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

class UBattleLogEntryInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedDelegate2, UBattleLogEntryInfo*, Info);

/**
 * 
 */
UCLASS()
class FEARTHESNOWBALL_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:


public:
	AFPSPlayerState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PassCharacterEvent(UBattleLogEntryInfo* Entry);

	UPROPERTY(BlueprintAssignable, Category = "FPSPlayerState")
	FOnPlayerDiedDelegate2 OnPlayerDied;
};
