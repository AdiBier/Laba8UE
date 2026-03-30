#include "AI/Patrol/PatrolRouteComponent.h"

#include "Engine/TargetPoint.h"

UPatrolRouteComponent::UPatrolRouteComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UPatrolRouteComponent::GetPatrolPointCount() const
{
	return PatrolPoints.Num();
}

ATargetPoint* UPatrolRouteComponent::GetPatrolPoint(int32 Index) const
{
	return PatrolPoints.IsValidIndex(Index) ? PatrolPoints[Index] : nullptr;
}

bool UPatrolRouteComponent::GetNextPatrolPoint(int32 CurrentIndex, int32& OutNextIndex, ATargetPoint*& OutPatrolPoint) const
{
	OutNextIndex = INDEX_NONE;
	OutPatrolPoint = nullptr;

	const int32 PointCount = PatrolPoints.Num();
	if (PointCount == 0)
	{
		return false;
	}

	int32 CandidateIndex = CurrentIndex;

	for (int32 Attempt = 0; Attempt < PointCount; ++Attempt)
	{
		CandidateIndex = (CandidateIndex == INDEX_NONE) ? 0 : CandidateIndex + 1;

		if (CandidateIndex >= PointCount)
		{
			if (!bLoopPatrol)
			{
				return false;
			}

			CandidateIndex = 0;
		}

		if (ATargetPoint* CandidatePoint = PatrolPoints[CandidateIndex])
		{
			OutNextIndex = CandidateIndex;
			OutPatrolPoint = CandidatePoint;
			return true;
		}
	}

	return false;
}

