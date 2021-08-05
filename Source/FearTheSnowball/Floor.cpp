// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "AmmoSpawnerComponent.h"

// Sets default values
AFloor::AFloor()
{
	SetReplicates(true);

	StartAreaSize = 3.0;
	EndAreaSize = 0.5;
	AmmoSpawnerClass = UAmmoSpawnerComponent::StaticClass();

	// Set Static Mesh Component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/Meshes/Floor.Floor"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeScale3D(FVector(StartAreaSize, StartAreaSize, 1.f));
	}
	RootComponent = StaticMesh;
}

void AFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate current area size
	DOREPLIFETIME(AFloor, CurrentAreaSize);
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	// Create Ammo Spawner only on server side
	if (GetLocalRole() == ROLE_Authority)
	{
		AmmoSpawner = NewObject<UAmmoSpawnerComponent>(this, AmmoSpawnerClass);
		AmmoSpawner->RegisterComponent();
		AddOwnedComponent(AmmoSpawner);
		AmmoSpawner->StartSpawningAmmo();
	}

	Super::BeginPlay();
}

void AFloor::OnRep_CurrentAreaSize()
{
	OnAreaSizeUpdate();
}

void AFloor::OnAreaSizeUpdate()
{
	// Resize static mesh
	StaticMesh->SetRelativeScale3D(FVector(CurrentAreaSize, CurrentAreaSize, 1.f));
	
	if (GetLocalRole() == ROLE_Authority)
	{
		// Set new radius of the ammo spawning area
		float NewSpawnRadius = FMath::Min(StaticMesh->Bounds.BoxExtent.X, StaticMesh->Bounds.BoxExtent.Y) - 200.f;
		NewSpawnRadius = FMath::Max(NewSpawnRadius, 100.f);
		AmmoSpawner->SpawnRadius = NewSpawnRadius;
	}
}

void AFloor::SetCurrentAreaSize(float AreaSize)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentAreaSize = FMath::Clamp(AreaSize, EndAreaSize, StartAreaSize);
		OnAreaSizeUpdate();
	}
}
