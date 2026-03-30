// Copyright Epic Games, Inc. All Rights Reserved.


#include "Variant_Shooter/AI/ShooterNPC.h"
#include "ShooterWeapon.h"
#include "Variant_Shooter/AmmoSystem/AmmoComponent.h"
#include "Variant_Shooter/AmmoSystem/ShooterAmmoLog.h"
#include "Variant_Shooter/AmmoSystem/AmmoPickup.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "ShooterGameMode.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

AShooterNPC::AShooterNPC()
{
	AmmoComponent = CreateDefaultSubobject<UAmmoComponent>(TEXT("AmmoComponent"));
	AmmoComponent->MaxAmmo = 5;
	AmmoComponent->InitialAmmo = 2;
}

void AShooterNPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AmmoComponent))
	{
		// Force low starting ammo for NPCs so they seek crates regularly.
		AmmoComponent->MaxAmmo = 5;
		AmmoComponent->InitialAmmo = 2;
		AmmoComponent->ApplyInitialAmmo();
		AmmoComponent->OnAmmoDepleted.AddDynamic(this, &AShooterNPC::HandleAmmoDepleted);
		AmmoComponent->OnAmmoChanged.AddDynamic(this, &AShooterNPC::HandleAmmoChanged);
	}

	// spawn the weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapon = GetWorld()->SpawnActor<AShooterWeapon>(WeaponClass, GetActorTransform(), SpawnParams);
}

void AShooterNPC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// clear the death timer
	GetWorld()->GetTimerManager().ClearTimer(DeathTimer);
}

float AShooterNPC::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// ignore if already dead
	if (bIsDead)
	{
		return 0.0f;
	}

	// Reduce HP
	CurrentHP -= Damage;

	// Have we depleted HP?
	if (CurrentHP <= 0.0f)
	{
		Die();
	}

	return Damage;
}

void AShooterNPC::AttachWeaponMeshes(AShooterWeapon* WeaponToAttach)
{
	const FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);

	// attach the weapon actor
	WeaponToAttach->AttachToActor(this, AttachmentRule);

	// attach the weapon meshes
	WeaponToAttach->GetFirstPersonMesh()->AttachToComponent(GetFirstPersonMesh(), AttachmentRule, FirstPersonWeaponSocket);
	WeaponToAttach->GetThirdPersonMesh()->AttachToComponent(GetMesh(), AttachmentRule, ThirdPersonWeaponSocket);
}

void AShooterNPC::PlayFiringMontage(UAnimMontage* Montage)
{
	// unused
}

void AShooterNPC::AddWeaponRecoil(float Recoil)
{
	// unused
}

void AShooterNPC::UpdateWeaponHUD(int32 CurrentAmmo, int32 MagazineSize)
{
	// unused
}

FVector AShooterNPC::GetWeaponTargetLocation()
{
	// start aiming from the camera location
	const FVector AimSource = GetFirstPersonCameraComponent()->GetComponentLocation();

	FVector AimDir, AimTarget = FVector::ZeroVector;

	// do we have an aim target?
	if (CurrentAimTarget)
	{
		// target the actor location
		AimTarget = CurrentAimTarget->GetActorLocation();

		// apply a vertical offset to target head/feet
		AimTarget.Z += FMath::RandRange(MinAimOffsetZ, MaxAimOffsetZ);

		// get the aim direction and apply randomness in a cone
		AimDir = (AimTarget - AimSource).GetSafeNormal();
		AimDir = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(AimDir, AimVarianceHalfAngle);

		
	} else {

		// no aim target, so just use the camera facing
		AimDir = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(GetFirstPersonCameraComponent()->GetForwardVector(), AimVarianceHalfAngle);

	}

	// calculate the unobstructed aim target location
	AimTarget = AimSource + (AimDir * AimRange);

	// run a visibility trace to see if there's obstructions
	FHitResult OutHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(OutHit, AimSource, AimTarget, ECC_Visibility, QueryParams);

	// return either the impact point or the trace end
	return OutHit.bBlockingHit ? OutHit.ImpactPoint : OutHit.TraceEnd;
}

void AShooterNPC::AddWeaponClass(const TSubclassOf<AShooterWeapon>& InWeaponClass)
{
	// unused
}

void AShooterNPC::OnWeaponActivated(AShooterWeapon* InWeapon)
{
	// unused
}

void AShooterNPC::OnWeaponDeactivated(AShooterWeapon* InWeapon)
{
	// unused
}

void AShooterNPC::OnSemiWeaponRefire()
{
	// are we still shooting?
	if (bIsShooting)
	{
		if (IsValid(AmmoComponent) && !AmmoComponent->HasAmmo())
		{
			UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Brak amunicji przy refire - NPC przerywa strzelanie."), *GetNameSafe(this));
			StopShooting();
			SeekNearestAmmoPickup();
			return;
		}

		// fire the weapon
		Weapon->StartFiring();
	}
}

void AShooterNPC::HandleAmmoDepleted()
{
	UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] NPC skonczyla sie amunicja - rozpoczynam szukanie skrzynki."), *GetNameSafe(this));
	UE_LOG(LogTemp, Warning, TEXT("[Ammo][%s] OUT OF AMMO -> SEEK PICKUP"), *GetNameSafe(this));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			4.0f,
			FColor::Yellow,
			FString::Printf(TEXT("[Ammo] %s: OUT OF AMMO"), *GetNameSafe(this))
		);
	}

	StopShooting();
	SeekNearestAmmoPickup();
}

void AShooterNPC::HandleAmmoChanged(int32 CurrentAmmo, int32 MaxAmmo)
{
	UE_LOG(LogTemp, Warning, TEXT("[Ammo][%s] Ammo changed: %d/%d"), *GetNameSafe(this), CurrentAmmo, MaxAmmo);

	// Resume combat after refill if we still have a known target.
	if (!bIsDead && CurrentAmmo > 0 && !bIsShooting && IsValid(CurrentAimTarget))
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Ammo refill detected - wznowienie strzelania do %s."), *GetNameSafe(this), *GetNameSafe(CurrentAimTarget));
		StartShooting(CurrentAimTarget);
	}
}

bool AShooterNPC::SeekNearestAmmoPickup()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Brak World - nie moge szukac skrzynki."), *GetNameSafe(this));
		return false;
	}

	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Brak AIController - nie moge ruszyc do skrzynki."), *GetNameSafe(this));
		return false;
	}

	AAmmoPickup* BestPickup = nullptr;
	float BestDistSq = MAX_flt;

	for (TActorIterator<AAmmoPickup> It(World); It; ++It)
	{
		AAmmoPickup* Candidate = *It;
		if (!IsValid(Candidate) || !Candidate->IsAvailable())
		{
			continue;
		}

		const float DistSq = FVector::DistSquared(GetActorLocation(), Candidate->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			BestPickup = Candidate;
		}
	}

	if (!IsValid(BestPickup))
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Nie znaleziono zadnej aktywnej skrzynki z amunicja."), *GetNameSafe(this));
		return false;
	}

	// If we're already very close, force a pickup attempt even if overlap did not fire.
	if (BestDistSq <= FMath::Square(220.0f))
	{
		if (BestPickup->TryGiveAmmoTo(this))
		{
			UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Otrzymano amunicje z bliskiej skrzynki %s bezposrednio."), *GetNameSafe(this), *GetNameSafe(BestPickup));
			return true;
		}
	}

	const EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(BestPickup, 80.0f);

	if (MoveResult == EPathFollowingRequestResult::Failed)
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] MoveToActor do skrzynki %s nieudane."), *GetNameSafe(this), *GetNameSafe(BestPickup));
		return false;
	}

	UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Fallback: ide po skrzynke %s (dist=%.0f)."), *GetNameSafe(this), *GetNameSafe(BestPickup), FMath::Sqrt(BestDistSq));
	return true;
}

void AShooterNPC::Die()
{
	// ignore if already dead
	if (bIsDead)
	{
		return;
	}

	// raise the dead flag
	bIsDead = true;

	// grant the death tag to the character
	Tags.Add(DeathTag);

	// call the delegate
	OnPawnDeath.Broadcast();

	// increment the team score
	if (AShooterGameMode* GM = Cast<AShooterGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->IncrementTeamScore(TeamByte);
	}

	// disable capsule collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// stop movement
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->StopActiveMovement();

	// enable ragdoll physics on the third person mesh
	GetMesh()->SetCollisionProfileName(RagdollCollisionProfile);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetPhysicsBlendWeight(1.0f);

	// schedule actor destruction
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AShooterNPC::DeferredDestruction, DeferredDestructionTime, false);
}

void AShooterNPC::DeferredDestruction()
{
	Destroy();
}

void AShooterNPC::StartShooting(AActor* ActorToShoot)
{
	if (IsValid(AmmoComponent) && !AmmoComponent->HasAmmo())
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Nie moge zaczac strzelac - brak amunicji."), *GetNameSafe(this));
		StopShooting();
		SeekNearestAmmoPickup();
		return;
	}

	// save the aim target
	CurrentAimTarget = ActorToShoot;

	// raise the flag
	bIsShooting = true;

	// signal the weapon
	Weapon->StartFiring();
}

void AShooterNPC::StopShooting()
{
	// lower the flag
	bIsShooting = false;

	// signal the weapon
	Weapon->StopFiring();
}
