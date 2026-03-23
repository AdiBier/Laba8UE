// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Laba8UEPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config="Game")
class LABA8UE_API ALaba8UEPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	ALaba8UEPlayerController();

	/** Save current player state to default slot */
	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	bool SaveGame();

	/** Load current player state from default slot */
	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	bool LoadGame();

	/** Toggles paused state and pause menu visibility */
	UFUNCTION(BlueprintCallable, Category="UI|Pause")
	void TogglePauseMenu();

	/** Pauses game and shows pause menu */
	UFUNCTION(BlueprintCallable, Category="UI|Pause")
	void ShowPauseMenu();

	/** Unpauses game and hides pause menu */
	UFUNCTION(BlueprintCallable, Category="UI|Pause")
	void HidePauseMenu();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Pause menu widget to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI|Pause")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	/** Pointer to the pause menu widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenuWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;
};
