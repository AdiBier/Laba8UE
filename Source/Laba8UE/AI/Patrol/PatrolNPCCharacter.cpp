#include "AI/Patrol/PatrolNPCCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/Patrol/PatrolAIController.h"
#include "AI/Patrol/PatrolRouteComponent.h"

APatrolNPCCharacter::APatrolNPCCharacter()
{
	PatrolRouteComponent = CreateDefaultSubobject<UPatrolRouteComponent>(TEXT("PatrolRouteComponent"));

	AIControllerClass = APatrolAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

