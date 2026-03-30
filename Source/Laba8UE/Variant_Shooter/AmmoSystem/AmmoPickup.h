// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UAmmoComponent;
class UPrimitiveComponent;

/**
 *  An ammo crate placed in the level.
 *  When an NPC with UAmmoComponent overlaps it, the crate refills their ammo
 *  and then disappears for a configurable amount of time before respawning.
 */
UCLASS(abstract, BlueprintType, Blueprintable)
class LABA8UE_API AAmmoPickup : public AActor
{
	GENERATED_BODY()

	/** Collision sphere that triggers the pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* SphereCollision;

	/** Visual mesh of the ammo crate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Mesh;

protected:

	/** How much ammo this crate gives */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pickup", meta=(ClampMin=1))
	int32 AmmoAmount = 15;

	/** Seconds before the crate respawns after being picked up */
	UPROPERTY(EditAnywhere, Category="Pickup", meta=(ClampMin=0.0f, Units="s"))
	float RespawnTime = 10.0f;

	/** True while the crate is available to pick up */
	bool bIsAvailable = true;

	/** Timer handle for respawn */
	FTimerHandle RespawnTimer;

public:

	AAmmoPickup();

	/**
	 * Tries to grant ammo to the provided actor.
	 * @return true if ammo was granted and pickup consumed.
	 */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	bool TryGiveAmmoTo(AActor* OtherActor);

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Called when another actor overlaps our sphere */
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	/** Called when RespawnTimer fires */
	void RespawnPickup();

	/** Blueprint hook – called just before the pickup becomes active again */
	UFUNCTION(BlueprintImplementableEvent, Category="Pickup", meta=(DisplayName="OnRespawn"))
	void BP_OnRespawn();

	/** Called from Blueprint (or automatically) to finish the respawn and re-enable collision */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void FinishRespawn();

public:

	/** Returns true if the pickup is currently available */
	UFUNCTION(BlueprintPure, Category="Pickup")
	bool IsAvailable() const { return bIsAvailable; }

	/** Returns the mesh component */
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
};
