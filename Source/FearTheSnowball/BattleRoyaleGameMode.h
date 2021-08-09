// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BattleRoyaleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FEARTHESNOWBALL_API ABattleRoyaleGameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ABattleRoyaleGameState* BRGameState;

protected:
	// Active players
	UPROPERTY(BlueprintReadOnly)
	TArray<class AFPSController*> PlayerControllers;

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:

	ABattleRoyaleGameMode();
};
