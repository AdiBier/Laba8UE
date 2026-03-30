#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"

class ATargetPoint;

UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class LABA8UE_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPatrolRouteComponent();

protected:
	/** Punkty patrolowe ustawiane ręcznie dla instancji NPC-a w levelu */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	/** Czy po dojściu do końca listy wrócić na początek */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patrol")
	bool bLoopPatrol = true;

public:
	UFUNCTION(BlueprintPure, Category="Patrol")
	int32 GetPatrolPointCount() const;

	UFUNCTION(BlueprintPure, Category="Patrol")
	ATargetPoint* GetPatrolPoint(int32 Index) const;

	/** Zwraca kolejny poprawny punkt patrolowy z pominięciem pustych wpisów */
	UFUNCTION(BlueprintCallable, Category="Patrol")
	bool GetNextPatrolPoint(int32 CurrentIndex, int32& OutNextIndex, ATargetPoint*& OutPatrolPoint) const;
};

