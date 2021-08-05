// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticProjectile.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSCharacter.h"

// Sets default values
AStaticProjectile::AStaticProjectile()
{
	SetReplicates(true);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(20.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->SetGenerateOverlapEvents(true);

	// Set as root component
	RootComponent = CollisionComp;

	// Use Static Mesh Component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/Meshes/Sphere.Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->BodyInstance.SetCollisionProfileName("NoCollision");

	//Set the Static Mesh and its scale if we successfully found a mesh asset to use.
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	}

	AmmoCount = 5;
}

// Called when the game starts or when spawned
void AStaticProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AStaticProjectile::OnBeginOverlap);
}
#define PRINT(...) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(__VA_ARGS__));
void AStaticProjectile::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Execute only on server
	if (GetLocalRole() != ROLE_Authority)
		return;

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
		if (Character)
		{
			Character->AddAmmo(AmmoCount);
			Destroy();
		}
	}
}


