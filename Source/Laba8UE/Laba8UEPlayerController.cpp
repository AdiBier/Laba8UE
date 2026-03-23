// Copyright Epic Games, Inc. All Rights Reserved.


#include "Laba8UEPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputCoreTypes.h"
#include "InputMappingContext.h"
#include "Laba8UECameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Laba8UE.h"
#include "SaveGameManager.h"
#include "Widgets/Input/SVirtualJoystick.h"

ALaba8UEPlayerController::ALaba8UEPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ALaba8UECameraManager::StaticClass();
}

void ALaba8UEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PauseMenuWidget = nullptr;

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogLaba8UE, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ALaba8UEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		FInputKeyBinding& PauseKeyBinding = InputComponent->BindKey(EKeys::P, IE_Pressed, this, &ALaba8UEPlayerController::TogglePauseMenu);
		PauseKeyBinding.bExecuteWhenPaused = true;
	}

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

void ALaba8UEPlayerController::TogglePauseMenu()
{
	if (IsPaused())
	{
		HidePauseMenu();
	}
	else
	{
		ShowPauseMenu();
	}
}

void ALaba8UEPlayerController::ShowPauseMenu()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	SetPause(true);

	if (PauseMenuWidgetClass && !PauseMenuWidget)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(this, PauseMenuWidgetClass);
	}

	if (PauseMenuWidget && !PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->AddToViewport(10);
	}

	// GameAndUI avoids focus errors when widget root is not focusable.
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void ALaba8UEPlayerController::HidePauseMenu()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	SetPause(false);

	if (PauseMenuWidget && PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->RemoveFromParent();
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}

bool ALaba8UEPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

bool ALaba8UEPlayerController::SaveGame()
{
	return USaveGameManager::SaveGameToSlot(this, TEXT("SaveGame"));
}

bool ALaba8UEPlayerController::LoadGame()
{
	return USaveGameManager::LoadGameFromSlot(this, TEXT("SaveGame"));
}
