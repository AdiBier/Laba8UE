#include "AI/Patrol/PatrolAIController.h"

#include "AI/Patrol/PatrolNPCCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

void APatrolAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const APatrolNPCCharacter* PatrolCharacter = Cast<APatrolNPCCharacter>(InPawn);
	if (!PatrolCharacter)
	{
		return;
	}

	UBehaviorTree* BehaviorTreeAsset = PatrolCharacter->GetBehaviorTreeAsset();
	if (!BehaviorTreeAsset || !BehaviorTreeAsset->BlackboardAsset)
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = nullptr;
	UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent);
	RunBehaviorTree(BehaviorTreeAsset);
}
