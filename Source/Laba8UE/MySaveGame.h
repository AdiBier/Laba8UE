// UMySaveGame.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class LABA8UE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMySaveGame();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator PlayerRotation;
};

