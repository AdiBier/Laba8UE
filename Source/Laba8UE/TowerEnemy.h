// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerEnemy.generated.h"

class ALaba8UECharacter;

/**
 * Wieżyczka, która obserwuje gracza na określoną odległość
 * Jeśli gracz wejdzie w zasięg i jest widoczny (brak przeszkody), wieżyczka zwraca uwagę na gracza
 */
UCLASS()
class LABA8UE_API ATowerEnemy : public AActor
{
	GENERATED_BODY()

public:
	ATowerEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	/** Mesh wieżyczki */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* TowerMesh;

	/** Promień widzenia - na ile blisko musi być gracz */
	UPROPERTY(EditAnywhere, Category = "AI|Vision", meta = (ClampMin = "100.0", ClampMax = "5000.0"))
	float VisionRange = 1500.0f;

	/** Kąt widzenia w stopniach (field of view) */
	UPROPERTY(EditAnywhere, Category = "AI|Vision", meta = (ClampMin = "0.0", ClampMax = "360.0"))
	float VisionAngle = 360.0f;

	/** Czy wieżyczka aktualnie widzi gracza */
	UPROPERTY(BlueprintReadOnly, Category = "AI|State")
	bool bCanSeePlayer = false;

	/** Referencja do gracza */
	UPROPERTY(Transient)
	ALaba8UECharacter* PlayerCharacter = nullptr;

	/** Prędkość obracania wieżyczki (jak szybko patrzy na gracza) */
	UPROPERTY(EditAnywhere, Category = "AI|Vision", meta = (ClampMin = "0.1", ClampMax = "20.0"))
	float RotationSpeed = 5.0f;

	/** Czy pokazywać debug visualization (sfera zakresu) */
	UPROPERTY(EditAnywhere, Category = "AI|Debug")
	bool bShowDebugVisualization = true;

public:
	/** Główna funkcja sprawdzająca widzenie gracza */
	void UpdateVision();

	/** Sprawdza, czy gracz jest w zasięgu i bez przeszkód */
	bool CanSeePlayer();

	/** Getter dla stanu widzenia */
	FORCEINLINE bool IsPlayerVisible() const { return bCanSeePlayer; }

	/** Getter dla zakresu widzenia */
	FORCEINLINE float GetVisionRange() const { return VisionRange; }

	/** Setter dla zakresu widzenia */
	FORCEINLINE void SetVisionRange(float NewRange) { VisionRange = FMath::Clamp(NewRange, 100.0f, 5000.0f); }

protected:
	/** Called gdy gracz wejdzie w zasięg widzenia */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI|Events")
	void OnPlayerSpotted();

	/** Called gdy gracz opuści zasięg widzenia */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI|Events")
	void OnPlayerLost();

	/** Sprawdza, czy obiekt blokuje wzrok (line of sight check) */
	bool HasLineOfSightToPlayer();

	/** Sprawdza, czy gracz jest w polu widzenia (kąt) */
	bool IsPlayerInFieldOfView();

	/** Rysuje debug visualization */
	void DrawDebugVision();

	/** Obraca wieżyczkę w kierunku gracza (wywoływane w Tick) */
	void RotateTowardsPlayer(float DeltaTime);
};
