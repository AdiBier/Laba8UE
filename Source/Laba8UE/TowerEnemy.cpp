// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerEnemy.h"
#include "Laba8UECharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATowerEnemy::ATowerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Tworzenie mesh'u wieżyczki
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = TowerMesh;
	TowerMesh->SetCollisionProfileName(FName("Pawn"));
}

void ATowerEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Wyszukanie gracza w świecie (pierwszy gracz)
	PlayerCharacter = Cast<ALaba8UECharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("TowerEnemy: Nie znaleziono gracza w świecie!"));
	}
}

void ATowerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// NAJPIERW - Sprawdzamy widzenie gracza (żeby mieć świeży stan bCanSeePlayer)
	UpdateVision();

	// POTEM - Obracamy wieżyczkę w stronę gracza (jeśli go widzi)
	RotateTowardsPlayer(DeltaTime);

	// DEBUG: Rysowanie wizualizacji
	DrawDebugVision();
}

void ATowerEnemy::UpdateVision()
{
	if (!PlayerCharacter)
	{
		if (bCanSeePlayer)
		{
			bCanSeePlayer = false;
			OnPlayerLost();
		}
		return;
	}

	bool bPreviouslySeenPlayer = bCanSeePlayer;
	bCanSeePlayer = CanSeePlayer();

	// Jeśli zmienił się stan widzenia
	if (bCanSeePlayer && !bPreviouslySeenPlayer)
	{
		// Gracz wejdził w zasięg
		OnPlayerSpotted();
	}
	else if (!bCanSeePlayer && bPreviouslySeenPlayer)
	{
		// Gracz wyszedł z zasięgu lub schował się
		OnPlayerLost();
	}
}

bool ATowerEnemy::CanSeePlayer()
{
	if (!PlayerCharacter)
	{
		return false;
	}

	// 1. Sprawdzenie odległości
	float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
	if (DistanceToPlayer > VisionRange)
	{
		return false;
	}

	// 2. Sprawdzenie przeszkód (line of sight) - NAJPIERW bo to jest droższe obliczeniowo
	if (!HasLineOfSightToPlayer())
	{
		return false;
	}

	// 3. Sprawdzenie kąta widzenia (field of view) - OPCJONALNIE
	// Jeśli VisionAngle = 360, wieżyczka widzi we wszystkich kierunkach
	if (VisionAngle < 360.0f && !IsPlayerInFieldOfView())
	{
		return false;
	}

	return true;
}

bool ATowerEnemy::IsPlayerInFieldOfView()
{
	if (!PlayerCharacter)
	{
		return false;
	}

	// Kierunek do gracza - użyjemy pozycji kamery jeśli jest dostępna
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	if (PlayerCharacter->GetFirstPersonCameraComponent())
	{
		PlayerLocation = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	}

	FVector ToPlayer = (PlayerLocation - GetActorLocation()).GetSafeNormal();

	// Przód wieżyczki (gdzie patrzy)
	FVector TowerForward = GetActorForwardVector();

	// Cosinus kąta między tymi wektorami
	float DotProduct = FVector::DotProduct(TowerForward, ToPlayer);

	// Konwersja zakresu widzenia na cosinus
	float FOVCosine = FMath::Cos(FMath::DegreesToRadians(VisionAngle * 0.5f));

	bool bInFOV = DotProduct >= FOVCosine;
	if (!bInFOV)
	{
		UE_LOG(LogTemp, Verbose, TEXT("TowerEnemy: Player outside FOV. Dot=%f FOVCosine=%f"), DotProduct, FOVCosine);
	}

	return bInFOV;
}

bool ATowerEnemy::HasLineOfSightToPlayer()
{
	if (!PlayerCharacter)
	{
		return false;
	}

	FHitResult HitResult;
	FVector TowerLocation = GetActorLocation();
	
	// Start od środka wieżyczki
	FVector StartLocation = TowerLocation;
	
	// Jeśli postać ma kamerę pierwszoosobową, to używamy jej pozycji jako końca raycasta
	FVector EndLocation = PlayerCharacter->GetActorLocation();
	if (PlayerCharacter->GetFirstPersonCameraComponent())
	{
		EndLocation = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	}

	// Raycast w stronę gracza
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignoruj siebie
	if (TowerMesh)
	{
		CollisionParams.AddIgnoredComponent(TowerMesh);
	}

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (!bHit)
	{
		UE_LOG(LogTemp, Verbose, TEXT("TowerEnemy: LOS clear (no hit)"));
		// Nic nie trafiło - brak przeszkody
		return true;
	}

	FString HitActorName = HitResult.GetActor() ? HitResult.GetActor()->GetName() : TEXT("None");
	UE_LOG(LogTemp, Verbose, TEXT("TowerEnemy: LOS hit actor=%s at distance %f"), *HitActorName, HitResult.Distance);

	// Jeśli trafiliśmy bezpośrednio w aktora gracza lub wewnętrzny komponent należący do gracza
	if (HitResult.GetActor() == PlayerCharacter)
	{
		return true;
	}

	if (HitResult.Component.IsValid() && HitResult.Component->GetOwner() == PlayerCharacter)
	{
		return true;
	}

	// W innym przypadku przeszkoda blokuje widoczność
	return false;
}

void ATowerEnemy::RotateTowardsPlayer(float DeltaTime)
{
	if (!PlayerCharacter)
	{
		return;
	}

	// Obracamy TYLKO gdy rzeczywiście widzimy gracza (bCanSeePlayer == true)
	// Jeśli gracz jest za ścianą lub poza FOV, wieżyczka się nie obraca
	if (!bCanSeePlayer)
	{
		return;
	}

	// Oblicz kąt rotacji do gracza (użyj pozycji kamery jeśli istnieje)
	FVector TargetLocation = PlayerCharacter->GetActorLocation();
	if (PlayerCharacter->GetFirstPersonCameraComponent())
	{
		TargetLocation = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	}

	FVector DirectionToPlayer = (TargetLocation - GetActorLocation()).GetSafeNormal();
	if (DirectionToPlayer.IsNearlyZero())
	{
		return;
	}

	FRotator TargetRot = DirectionToPlayer.Rotation();
	// Ustaw nową rotację wieżyczki (tylko yaw - obrót w poziomie)
	FRotator Desired = FRotator(0, TargetRot.Yaw, 0);
	FRotator Current = GetActorRotation();
	FRotator SmoothRotation = FMath::RInterpTo(Current, Desired, DeltaTime, RotationSpeed);

	// Po prostu obracamy - bez teleportacji!
	SetActorRotation(SmoothRotation);
}

void ATowerEnemy::DrawDebugVision()
{
	// Rysowanie sfery zakresu widzenia - jeśli debug visualization jest włączone
	if (bShowDebugVisualization)
	{
		FVector TowerLocation = GetActorLocation();
		DrawDebugSphere(GetWorld(), TowerLocation, VisionRange, 12, FColor::Yellow, false, 0.02f, 0, 1.0f);
	}

	// Jeśli mamy gracza, rysujemy linię do celu
	if (PlayerCharacter)
	{
		FVector TowerLocation = GetActorLocation();
		FVector TargetLoc = PlayerCharacter->GetActorLocation();
		if (PlayerCharacter->GetFirstPersonCameraComponent())
		{
			TargetLoc = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
		}

		// Sprawdzenie odległości
		float DistanceToPlayer = FVector::Dist(TowerLocation, TargetLoc);
		bool bInRange = DistanceToPlayer <= VisionRange;

		// Linia - kolory zależne od stanu widzenia i logiki
		if (bInRange)
		{
			// Jeśli w zasięgu - sprawdzamy czy widzi (bez przeszkód i w FOV)
			if (bCanSeePlayer)
			{
				// Case 1: W zasięgu, bez przeszkód, w FOV -> ZIELONA (widzi i obraca się)
				DrawDebugLine(GetWorld(), TowerLocation, TargetLoc, FColor::Green, false, 0.02f, 0, 3.0f);
			}
			else
			{
				// Case 3: W zasięgu ale za ścianą lub poza FOV -> ŻÓŁTA (wiem że jest ale nie widzę)
				DrawDebugLine(GetWorld(), TowerLocation, TargetLoc, FColor::Yellow, false, 0.02f, 0, 2.0f);
			}
		}
		else
		{
			// Case 2: Poza zasięgiem -> CZERWONA (za daleko)
			DrawDebugLine(GetWorld(), TowerLocation, TargetLoc, FColor::Red, false, 0.02f, 0, 1.5f);
		}
	}
}
