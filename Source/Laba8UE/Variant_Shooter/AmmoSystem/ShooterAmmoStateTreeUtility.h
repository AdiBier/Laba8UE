// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

#include "ShooterAmmoStateTreeUtility.generated.h"

class AShooterNPC;
class AAIController;
class AAmmoPickup;

////////////////////////////////////////////////////////////////////
// Condition: Has Ammo
////////////////////////////////////////////////////////////////////

/**
 *  Instance data for FStateTreeHasAmmoCondition
 */
USTRUCT()
struct FStateTreeHasAmmoConditionInstanceData
{
	GENERATED_BODY()

	/** NPC whose ammo is checked */
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AShooterNPC> Character;
};
STATETREE_POD_INSTANCEDATA(FStateTreeHasAmmoConditionInstanceData);

/**
 *  StateTree condition – passes when the NPC still has ammo remaining.
 *  Negate it in the StateTree editor to trigger the "seek ammo" transition.
 */
USTRUCT(DisplayName="Has Ammo", Category="Shooter|Ammo")
struct FStateTreeHasAmmoCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeHasAmmoConditionInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	FStateTreeHasAmmoCondition() = default;

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
		const IStateTreeBindingLookup& BindingLookup,
		EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif
};

////////////////////////////////////////////////////////////////////
// Task: Seek Ammo
////////////////////////////////////////////////////////////////////

/**
 *  Instance data for FStateTreeSeekAmmoTask
 */
USTRUCT()
struct FStateTreeSeekAmmoInstanceData
{
	GENERATED_BODY()

	/** The NPC looking for ammo */
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AShooterNPC> Character;

	/** The AI controller driving the NPC */
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AAIController> Controller;

	/** The closest available ammo pickup found by EQS (output) */
	UPROPERTY(EditAnywhere, Category="Output")
	TObjectPtr<AAmmoPickup> FoundPickup;

	/** Acceptance radius for "we've reached the pickup" check */
	UPROPERTY(EditAnywhere, Category="Parameter", meta=(ClampMin=10.0f, Units="cm"))
	float AcceptanceRadius = 150.0f;

	/** EQS query to run */
	UPROPERTY(EditAnywhere, Category="Parameter")
	TObjectPtr<UEnvQuery> AmmoEQSQuery;

	/** Id of the in-progress EQS query */
	int32 EQSQueryID = INDEX_NONE;

	/** True once EQS has returned a result */
	bool bEQSComplete = false;
};

/**
 *  StateTree task that uses EQS to find the nearest ammo crate and moves the NPC towards it.
 *  Succeeds when the NPC reaches the crate (the crate's OnOverlap will refill the ammo).
 *  Fails if no crate is found.
 */
USTRUCT(meta=(DisplayName="Seek Ammo Pickup", Category="Shooter|Ammo"))
struct FStateTreeSeekAmmoTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeSeekAmmoInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView,
		const IStateTreeBindingLookup& BindingLookup,
		EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif
};
