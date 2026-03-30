#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolNPCCharacter.generated.h"

class UBehaviorTree;
class UPatrolRouteComponent;

UCLASS()
class LABA8UE_API APatrolNPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APatrolNPCCharacter();

protected:
	/** Komponent przechowujący punkty patrolowe ustawiane w levelu */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPatrolRouteComponent> PatrolRouteComponent;

	/** Drzewo zachowań uruchamiane po przejęciu NPC-a przez kontroler */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

public:
	UFUNCTION(BlueprintPure, Category="AI")
	UPatrolRouteComponent* GetPatrolRouteComponent() const { return PatrolRouteComponent; }

	UFUNCTION(BlueprintPure, Category="AI")
	UBehaviorTree* GetBehaviorTreeAsset() const { return BehaviorTreeAsset; }
};

