// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvQueryContext_AmmoPickup.generated.h"

/**
 *  EQS context that provides all available AAmmoPickup actors in the world.
 *  Use this context as "Queried Actor" items in an EnvQuery to find ammo crates.
 */
UCLASS()
class LABA8UE_API UEnvQueryContext_AmmoPickup : public UEnvQueryContext
{
	GENERATED_BODY()

public:

	/** Fills the context with all available ammo pickups in the current world */
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};

