// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Floor.h"
#include "BattleRoyaleGameState.generated.h"


class AFPSController;

USTRUCT(BlueprintType)
struct FDeathEventData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	class AFPSPlayerState* Killed;

	UPROPERTY(BlueprintReadWrite)
	class AFPSPlayerState* KilledBy;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinedDelegate, AFPSPlayerState*, PlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedDelegate3, FDeathEventData, DeathEventData);


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
	void OnRep_PlayerStates(const TArray<class AFPSPlayerState*>& Previous);

public:
	ABattleRoyaleGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Fires when new player joins the game
	UPROPERTY(BlueprintAssignable, Category = "BattleRoyalGameState")
	FOnPlayerJoinedDelegate OnPlayerJoined;

	UFUNCTION()
	void AddPlayer(AFPSPlayerState* NewPlayer);

	UPROPERTY(BlueprintAssignable, Category = "BattleRoyalGameState")
	FOnPlayerDiedDelegate3 OnPlayerDied;

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_AnnounceDeath(FDeathEventData Data);
};
