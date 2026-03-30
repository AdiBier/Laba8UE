// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoDepletedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChangedDelegate, int32, CurrentAmmo, int32, MaxAmmo);

/**
 *  Component that tracks ammo reserves for an NPC.
 *  When ammo reaches zero, it broadcasts OnAmmoDepleted so the AI can react.
 */
UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent), DisplayName="Ammo Component")
class LABA8UE_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UAmmoComponent();

	/** Maximum ammo this NPC can carry */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ammo", meta=(ClampMin=1))
	int32 MaxAmmo = 5;

	/** Ammo available at begin play */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ammo", meta=(ClampMin=0))
	int32 InitialAmmo = 2;

	/** Current ammo count */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ammo")
	int32 CurrentAmmo;

	/** Called when ammo reaches zero */
	UPROPERTY(BlueprintAssignable, Category="Ammo")
	FOnAmmoDepletedDelegate OnAmmoDepleted;

	/** Called whenever ammo value changes */
	UPROPERTY(BlueprintAssignable, Category="Ammo")
	FOnAmmoChangedDelegate OnAmmoChanged;

protected:

	virtual void BeginPlay() override;

public:

	/**
	 * Applies InitialAmmo (clamped to [0, MaxAmmo]) and broadcasts ammo change.
	 */
	UFUNCTION(BlueprintCallable, Category="Ammo")
	void ApplyInitialAmmo();

	/**
	 * Consumes one unit of ammo.
	 * @return true if ammo was available and consumed, false if already empty.
	 */
	UFUNCTION(BlueprintCallable, Category="Ammo")
	bool ConsumeAmmo();

	/**
	 * Refills ammo by the specified amount (clamped to MaxAmmo).
	 */
	UFUNCTION(BlueprintCallable, Category="Ammo")
	void RefillAmmo(int32 Amount);

	/** Returns true if there is at least one ammo round remaining */
	UFUNCTION(BlueprintPure, Category="Ammo")
	bool HasAmmo() const;

	/** Returns the current ammo count */
	UFUNCTION(BlueprintPure, Category="Ammo")
	int32 GetCurrentAmmo() const { return CurrentAmmo; }

	/** Returns the maximum ammo count */
	UFUNCTION(BlueprintPure, Category="Ammo")
	int32 GetMaxAmmo() const { return MaxAmmo; }
};
