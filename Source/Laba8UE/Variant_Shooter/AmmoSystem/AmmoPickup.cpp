// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Shooter/AmmoSystem/AmmoPickup.h"
#include "AmmoComponent.h"
#include "Variant_Shooter/AmmoSystem/ShooterAmmoLog.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

AAmmoPickup::AAmmoPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(80.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldStatic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereCollision->bFillCollisionUnderneathForNavmesh = true;
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickup::OnOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetCollisionProfileName(FName("NoCollision"));
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	bIsAvailable = true;
}

void AAmmoPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);
}

void AAmmoPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TryGiveAmmoTo(OtherActor);
}

bool AAmmoPickup::TryGiveAmmoTo(AActor* OtherActor)
{
	if (!bIsAvailable)
	{
		return false;
	}

	UAmmoComponent* AmmoComp = OtherActor ? OtherActor->FindComponentByClass<UAmmoComponent>() : nullptr;
	if (!IsValid(AmmoComp))
	{
		UE_LOG(LogShooterAmmo, Verbose, TEXT("[AmmoPickup][%s] Overlap/try bez AmmoComponent dla aktora %s."), *GetNameSafe(this), *GetNameSafe(OtherActor));
		return false;
	}

	const int32 Before = AmmoComp->GetCurrentAmmo();
	AmmoComp->RefillAmmo(AmmoAmount);
	const int32 After = AmmoComp->GetCurrentAmmo();

	if (After <= Before)
	{
		UE_LOG(LogShooterAmmo, Verbose, TEXT("[AmmoPickup][%s] Aktor %s nie otrzymal ammo (przed=%d, po=%d)."), *GetNameSafe(this), *GetNameSafe(OtherActor), Before, After);
		return false;
	}

	UE_LOG(LogShooterAmmo, Warning, TEXT("[AmmoPickup][%s] %s dostal ammo: %d -> %d."), *GetNameSafe(this), *GetNameSafe(OtherActor), Before, After);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.5f,
			FColor::Green,
			FString::Printf(TEXT("[AmmoPickup] %s: %d -> %d"), *GetNameSafe(OtherActor), Before, After)
		);
	}

	// mark unavailable
	bIsAvailable = false;

	// hide the crate
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	// schedule respawn
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &AAmmoPickup::RespawnPickup, RespawnTime, false);

	return true;
}

void AAmmoPickup::RespawnPickup()
{
	SetActorHiddenInGame(false);
	BP_OnRespawn();

	// if Blueprint doesn't call FinishRespawn, do it automatically
	FinishRespawn();
}

void AAmmoPickup::FinishRespawn()
{
	SetActorEnableCollision(true);
	bIsAvailable = true;
}
