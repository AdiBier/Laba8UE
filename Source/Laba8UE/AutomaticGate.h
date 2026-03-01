// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutomaticGate.generated.h"

class ALaba8UECharacter;

/**
 * Automatyczne wrota podwójne (drzwi przesuwane)
 * Otwierają się gdy gracz zbliży się do nich
 * Zamykają się automatycznie po określonym czasie
 */
UCLASS()
class LABA8UE_API AAutomaticGate : public AActor
{
	GENERATED_BODY()

public:
	AAutomaticGate();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	/** Lewe skrzydło wrót */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* LeftDoor;

	/** Prawe skrzydło wrót */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* RightDoor;

	/** Punkt obrotu lewych drzwi */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* LeftDoorPivot;

	/** Punkt obrotu prawych drzwi */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* RightDoorPivot;

	/** Zasięg detekcji - na ile jednostek gracz musi być blisko */
	UPROPERTY(EditAnywhere, Category = "Gate|Behavior", meta = (ClampMin = "100.0", ClampMax = "5000.0"))
	float DetectionRange = 500.0f;

	/** Odległość przesunięcia drzwi przy otwarciu (w lokalnych jednostkach Y) */
	UPROPERTY(EditAnywhere, Category = "Gate|Behavior", meta = (ClampMin = "10.0", ClampMax = "1000.0"))
	float SlideDistance = 100.0f;

	/** Prędkość otwierania/zamykania */
	UPROPERTY(EditAnywhere, Category = "Gate|Behavior", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float OpenSpeed = 2.0f;

	/** Czas przed automatycznym zamknięciem (w sekundach) */
	UPROPERTY(EditAnywhere, Category = "Gate|Behavior", meta = (ClampMin = "0.5", ClampMax = "30.0"))
	float AutoCloseDelay = 3.0f;

	/** Czy wrota są aktualnie otwarte */
	UPROPERTY(BlueprintReadOnly, Category = "Gate|State")
	bool bIsOpen = false;

	/** Czy wrota są w trakcie otwierania/zamykania */
	UPROPERTY(BlueprintReadOnly, Category = "Gate|State")
	bool bIsMoving = false;

	/** Referencja do gracza */
	UPROPERTY(Transient)
	ALaba8UECharacter* PlayerCharacter = nullptr;

	/** Timer do automatycznego zamknięcia */
	float CloseTimer = 0.0f;

	/** Aktualny offset (local Y) lewych drzwi */
	float LeftDoorCurrentOffset = 0.0f;

	/** Aktualny offset (local Y) prawych drzwi */
	float RightDoorCurrentOffset = 0.0f;

	/** Czy pokazywać debug visualization */
	UPROPERTY(EditAnywhere, Category = "Gate|Debug")
	bool bShowDebugVisualization = true;

public:
	/** Otwórz wrota */
	UFUNCTION(BlueprintCallable, Category = "Gate|Control")
	void OpenGate();

	/** Zamknij wrota */
	UFUNCTION(BlueprintCallable, Category = "Gate|Control")
	void CloseGate();

	/** Przełącz stan wrót */
	UFUNCTION(BlueprintCallable, Category = "Gate|Control")
	void ToggleGate();

protected:
	/** Główna logika - sprawdza czy gracz jest w zasięgu */
	void UpdateGateState();

	/** Rysuje debug visualization */
	void DrawDebugGate();

	/** Called gdy wrota się otworzą */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Gate|Events")
	void OnGateOpened();

	/** Called gdy wrota się zamkną */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Gate|Events")
	void OnGateClosed();
};
