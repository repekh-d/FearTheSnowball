// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "FPSCharacter.h"

void AFPSController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind movement
    InputComponent->BindAxis("MoveForward", this, &AFPSController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AFPSController::MoveRight);

    // Bind actions
    InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSController::OnFire);

    // Bind rotation
    InputComponent->BindAxis("Turn", this, &AFPSController::Turn);
    InputComponent->BindAxis("LookUp", this, &AFPSController::LookUp);
}

void AFPSController::BeginPlay()
{
    ControlledCharacter = Cast<AFPSCharacter>(GetCharacter());

    Super::BeginPlay();
}

void AFPSController::OnFire()
{
    if (!IsValid(ControlledCharacter))
        return;
    ControlledCharacter->Fire();
}

void AFPSController::MoveForward(float Val)
{
    if (!IsValid(ControlledCharacter))
        return;
    ControlledCharacter->MoveForward(Val);
}

void AFPSController::MoveRight(float Val)
{
    if (!IsValid(ControlledCharacter))
        return;
    ControlledCharacter->MoveRight(Val);
}

void AFPSController::Turn(float Val)
{
    if (!IsValid(ControlledCharacter))
        return;
    ControlledCharacter->Turn(Val);
}

void AFPSController::LookUp(float Val)
{
    if (!IsValid(ControlledCharacter))
        return;
    ControlledCharacter->LookUp(Val);
}
