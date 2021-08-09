// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleLogEntryInfo.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Death		UMETA(DisplayName = "Death"),
	Kill		UMETA(DisplayName = "Kill"),
	PickUp		UMETA(DisplayName = "PickUp"),
	Joined		UMETA(DisplayName = "Joined"),
	Left		UMETA(DisplayName = "Left"),
	Respawned	UMETA(DisplayName = "Respawned")
};

/**
 * 
 */
UCLASS(Blueprintable)
class FEARTHESNOWBALL_API UBattleLogEntryInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionType ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToLive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Entry1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Entry2;
	
};
