// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Shooter/AmmoSystem/AmmoComponent.h"

UAmmoComponent::UAmmoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentAmmo = 0;
}

void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	ApplyInitialAmmo();
}

void UAmmoComponent::ApplyInitialAmmo()
{
	CurrentAmmo = FMath::Clamp(InitialAmmo, 0, MaxAmmo);
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

bool UAmmoComponent::ConsumeAmmo()
{
	if (CurrentAmmo <= 0)
	{
		return false;
	}

	CurrentAmmo--;

	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);

	if (CurrentAmmo <= 0)
	{
		OnAmmoDepleted.Broadcast();
	}

	return true;
}

void UAmmoComponent::RefillAmmo(int32 Amount)
{
	const int32 OldAmmo = CurrentAmmo;
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);

	if (CurrentAmmo != OldAmmo)
	{
		OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
	}
}

bool UAmmoComponent::HasAmmo() const
{
	return CurrentAmmo > 0;
}
