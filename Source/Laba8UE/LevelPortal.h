// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPortal.generated.h"

class UBoxComponent;
class UPortalTravelConfirmWidget;
class UStaticMeshComponent;

/**
 * Portal actor that can move player to another level.
 * Supports optional confirmation UI before travel.
 */
UCLASS(Blueprintable)
class LABA8UE_API ALevelPortal : public AActor
{
	GENERATED_BODY()

public:
	ALevelPortal();

	/** Accept travel from UI or external Blueprint call. */
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void ConfirmPortalTravel();

	/** Cancel travel from UI or external Blueprint call. */
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void CancelPortalTravel();

protected:
	virtual void BeginPlay() override;

	/** Root scene component. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> PortalRoot;

	/** Visual mesh for the portal (for example door mesh). */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PortalMesh;

	/** Trigger volume used to detect player entry. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerVolume;

	/** Destination level package name (without extension). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	FName TargetLevelName;

	/** Enables confirmation popup before travel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	bool bRequireConfirmation = true;

	/** Prompt text shown in confirmation UI. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	FText ConfirmationMessage = FText::FromString(TEXT("Go to the next level?"));

	/** Widget class used to display confirmation prompt. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	TSubclassOf<UPortalTravelConfirmWidget> ConfirmWidgetClass;

	/** Prevents repeated triggers while waiting for decision or loading. */
	UPROPERTY(BlueprintReadOnly, Category = "Portal|State")
	bool bTravelLocked = false;

	UFUNCTION()
	void OnPortalBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPortalEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	void ShowConfirmationUI();
	void HideConfirmationUI(bool bRestoreGameInput);
	void TravelToTargetLevel();
	bool IsLocalPlayerActor(const AActor* OtherActor) const;

	UPROPERTY(Transient)
	TObjectPtr<UPortalTravelConfirmWidget> ActiveConfirmWidget;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> CachedPlayerController;
};

