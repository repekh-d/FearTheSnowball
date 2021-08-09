// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSController.generated.h"

/**
 * 
 */
UCLASS()
class FEARTHESNOWBALL_API AFPSController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class AFPSCharacter* ControlledCharacter;

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	// Fires a projectile.
	void OnFire();

	// Handles moving forward/backward
	void MoveForward(float Val);

	// Handles moving left/right
	void MoveRight(float Val);

	// Handles horizontal rotation
	void Turn(float Val);

	// Handles vertical rotation
	void LookUp(float Val);

public:


};
