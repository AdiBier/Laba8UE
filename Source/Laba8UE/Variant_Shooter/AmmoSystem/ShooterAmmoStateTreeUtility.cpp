// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Shooter/AmmoSystem/ShooterAmmoStateTreeUtility.h"
#include "Variant_Shooter/AmmoSystem/ShooterAmmoLog.h"
#include "ShooterNPC.h"
#include "AmmoComponent.h"
#include "AmmoPickup.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeAsyncExecutionContext.h"
#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"

////////////////////////////////////////////////////////////////////
// FStateTreeHasAmmoCondition
////////////////////////////////////////////////////////////////////

bool FStateTreeHasAmmoCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.Character))
	{
		return false;
	}

	if (UAmmoComponent* AmmoComp = InstanceData.Character->FindComponentByClass<UAmmoComponent>())
	{
		return AmmoComp->HasAmmo();
	}

	// no ammo component means unlimited ammo — always true
	return true;
}

#if WITH_EDITOR
FText FStateTreeHasAmmoCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	return FText::FromString("<b>Has Ammo</b>");
}
#endif

////////////////////////////////////////////////////////////////////
// FStateTreeSeekAmmoTask
////////////////////////////////////////////////////////////////////

EStateTreeRunStatus FStateTreeSeekAmmoTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType != EStateTreeStateChangeType::Changed)
	{
		return EStateTreeRunStatus::Running;
	}

	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	// reset state
	InstanceData.FoundPickup = nullptr;
	InstanceData.bEQSComplete = false;
	InstanceData.EQSQueryID = INDEX_NONE;

	if (!IsValid(InstanceData.AmmoEQSQuery))
	{
		// no query asset assigned – fail immediately so designer knows to fix the StateTree
		UE_LOG(LogShooterAmmo, Warning, TEXT("FStateTreeSeekAmmoTask: AmmoEQSQuery is not set!"));
		return EStateTreeRunStatus::Failed;
	}

	if (!IsValid(InstanceData.Character))
	{
		return EStateTreeRunStatus::Failed;
	}

	UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Brak amunicji - NPC zaczyna szukac skrzynki z amunicja (EQS)."), *GetNameSafe(InstanceData.Character.Get()));

	// Run an EQS query to find the nearest available ammo pickup.
	FEnvQueryRequest Request(InstanceData.AmmoEQSQuery, InstanceData.Character);

	// We use a weak execution context so the lambda is safe even if the StateTree exits.
	auto WeakCtx = Context.MakeWeakExecutionContext();

	InstanceData.EQSQueryID = Request.Execute(EEnvQueryRunMode::SingleResult,
		FQueryFinishedSignature::CreateLambda(
			[WeakCtx](TSharedPtr<FEnvQueryResult> Result)
			{
				const FStateTreeStrongExecutionContext StrongCtx = WeakCtx.MakeStrongExecutionContext();
				if (FInstanceDataType* Data = StrongCtx.GetInstanceDataPtr<FInstanceDataType>())
				{
					Data->bEQSComplete = true;
					Data->EQSQueryID = INDEX_NONE;

					if (Result.IsValid() && Result->IsSuccessful())
					{
						Data->FoundPickup = Cast<AAmmoPickup>(Result->GetItemAsActor(0));

						if (IsValid(Data->FoundPickup) && IsValid(Data->Controller))
						{
							UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Znaleziono skrzynke z amunicja: %s"), *GetNameSafe(Data->Character.Get()), *GetNameSafe(Data->FoundPickup.Get()));
							// start moving towards the pickup
							Data->Controller->MoveToActor(Data->FoundPickup, Data->AcceptanceRadius);
						}
						else
						{
							UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] EQS zwrocil wynik, ale pickup jest nieprawidlowy."), *GetNameSafe(Data->Character.Get()));
						}
					}
					else
					{
						UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] EQS nie znalazl skrzynki z amunicja."), *GetNameSafe(Data->Character.Get()));
					}
				}
			}
		)
	);

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeSeekAmmoTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	// Still waiting for EQS
	if (!InstanceData.bEQSComplete)
	{
		return EStateTreeRunStatus::Running;
	}

	// EQS finished but found nothing
	if (!IsValid(InstanceData.FoundPickup))
	{
		UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] Brak celu ammo pickup - task szukania konczy sie niepowodzeniem."), *GetNameSafe(InstanceData.Character.Get()));
		return EStateTreeRunStatus::Failed;
	}

	// Pickup disappeared or was taken
	if (!InstanceData.FoundPickup->IsAvailable())
	{
		// re-run next frame by resetting so EnterState fires again
		InstanceData.FoundPickup = nullptr;
		InstanceData.bEQSComplete = false;
		return EStateTreeRunStatus::Failed;
	}

	// Check if we've arrived (the overlap will handle actual ammo refill)
	if (IsValid(InstanceData.Character))
	{
		const float DistSq = FVector::DistSquared(
			InstanceData.Character->GetActorLocation(),
			InstanceData.FoundPickup->GetActorLocation()
		);

		if (DistSq <= FMath::Square(InstanceData.AcceptanceRadius * 1.5f))
		{
			if (InstanceData.FoundPickup->TryGiveAmmoTo(InstanceData.Character.Get()))
			{
				UE_LOG(LogShooterAmmo, Warning, TEXT("[Ammo][%s] StateTree: pickup %s uzupelnil amunicje."), *GetNameSafe(InstanceData.Character.Get()), *GetNameSafe(InstanceData.FoundPickup.Get()));
			}

			return EStateTreeRunStatus::Succeeded;
		}
	}

	return EStateTreeRunStatus::Running;
}

void FStateTreeSeekAmmoTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType != EStateTreeStateChangeType::Changed)
	{
		return;
	}

	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	// Stop movement; any late EQS callback is guarded by the weak StateTree context.
	InstanceData.EQSQueryID = INDEX_NONE;

	if (IsValid(InstanceData.Controller))
	{
		InstanceData.Controller->StopMovement();
	}

	InstanceData.FoundPickup = nullptr;
	InstanceData.bEQSComplete = false;
}

#if WITH_EDITOR
FText FStateTreeSeekAmmoTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
	const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	return FText::FromString("<b>Seek Ammo Pickup</b>");
}
#endif

