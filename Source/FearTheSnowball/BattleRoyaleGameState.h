// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Floor.h"
#include "BattleRoyaleGameState.generated.h"


class AFPSController;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinedDelegate, AFPSPlayerState*, PlayerState);


/**
 * 
 */
UCLASS()
class FEARTHESNOWBALL_API ABattleRoyaleGameState : public AGameState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AFloor> FloorClass;

	UPROPERTY()
	class AFloor* Floor;

protected:

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStates)
	TArray<class AFPSPlayerState*> PlayerStates;

	void virtual BeginPlay() override;

	UFUNCTION()
	void OnRep_PlayerStates();

public:
	ABattleRoyaleGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Fires when new player joins the game
	UPROPERTY(BlueprintAssignable, Category = "BattleRoyalGameState")
	FOnPlayerJoinedDelegate OnPlayerJoined;

	UFUNCTION()
	void AddPlayer(AFPSPlayerState* NewPlayer);
};
