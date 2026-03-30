#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_SelectNextPatrolPoint.generated.h"

UCLASS()
class LABA8UE_API UBTTask_SelectNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SelectNextPatrolPoint();

protected:
	/** Klucz Blackboard przechowujący aktualny punkt patrolowy */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector PatrolPointKey;

	/** Klucz Blackboard przechowujący indeks aktualnego punktu */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector PatrolIndexKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

