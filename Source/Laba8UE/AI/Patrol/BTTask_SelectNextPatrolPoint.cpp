#include "AI/Patrol/BTTask_SelectNextPatrolPoint.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "AI/Patrol/PatrolRouteComponent.h"

UBTTask_SelectNextPatrolPoint::UBTTask_SelectNextPatrolPoint()
{
	NodeName = TEXT("Select Next Patrol Point");

	PatrolPointKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SelectNextPatrolPoint, PatrolPointKey), AActor::StaticClass());
	PatrolIndexKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SelectNextPatrolPoint, PatrolIndexKey));
}

EBTNodeResult::Type UBTTask_SelectNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!AIController || !BlackboardComponent)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	const UPatrolRouteComponent* PatrolRouteComponent = ControlledPawn->FindComponentByClass<UPatrolRouteComponent>();
	if (!PatrolRouteComponent)
	{
		return EBTNodeResult::Failed;
	}

	int32 CurrentIndex = INDEX_NONE;
	if (BlackboardComponent->GetValueAsObject(PatrolPointKey.SelectedKeyName) != nullptr)
	{
		CurrentIndex = BlackboardComponent->GetValueAsInt(PatrolIndexKey.SelectedKeyName);
	}

	int32 NextIndex = INDEX_NONE;
	ATargetPoint* NextPatrolPoint = nullptr;
	if (!PatrolRouteComponent->GetNextPatrolPoint(CurrentIndex, NextIndex, NextPatrolPoint))
	{
		BlackboardComponent->ClearValue(PatrolPointKey.SelectedKeyName);
		BlackboardComponent->ClearValue(PatrolIndexKey.SelectedKeyName);
		return EBTNodeResult::Failed;
	}

	BlackboardComponent->SetValueAsObject(PatrolPointKey.SelectedKeyName, NextPatrolPoint);
	BlackboardComponent->SetValueAsInt(PatrolIndexKey.SelectedKeyName, NextIndex);
	return EBTNodeResult::Succeeded;
}

