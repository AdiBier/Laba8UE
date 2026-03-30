// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Shooter/AmmoSystem/EnvQueryContext_AmmoPickup.h"
#include "AmmoPickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/World.h"
#include "EngineUtils.h"

void UEnvQueryContext_AmmoPickup::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UWorld* World = QueryInstance.World.Get();
	if (!World)
	{
		return;
	}

	TArray<AActor*> AvailablePickups;

	// iterate all ammo pickups in the world and collect only available ones
	for (TActorIterator<AAmmoPickup> It(World); It; ++It)
	{
		AAmmoPickup* Pickup = *It;
		if (IsValid(Pickup) && Pickup->IsAvailable())
		{
			AvailablePickups.Add(Pickup);
		}
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, AvailablePickups);
}

