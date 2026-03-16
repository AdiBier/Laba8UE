// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PortalTravelConfirmWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPortalTravelDecisionSignature);

/**
 * Lightweight confirmation widget API used by C++ portal actors.
 * Blueprint should call ConfirmTravel or CancelTravel from button events.
 */
UCLASS(Abstract, Blueprintable)
class LABA8UE_API UPortalTravelConfirmWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Broadcast when user confirms level travel. */
	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FPortalTravelDecisionSignature OnConfirmed;

	/** Broadcast when user cancels level travel. */
	UPROPERTY(BlueprintAssignable, Category = "Portal")
	FPortalTravelDecisionSignature OnCancelled;

	/** Called by Blueprint (for example button click) to accept travel. */
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void ConfirmTravel();

	/** Called by Blueprint (for example button click) to reject travel. */
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void CancelTravel();

	/** Updates prompt text and forwards it to Blueprint visuals. */
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void SetPromptText(const FText& InPromptText);

protected:
	/** Text value that Blueprint can directly bind to. */
	UPROPERTY(BlueprintReadOnly, Category = "Portal")
	FText PromptText;

	/** Event for Blueprint to refresh text widgets. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Portal", meta = (DisplayName = "Prompt Updated"))
	void BP_OnPromptUpdated(const FText& InPromptText);
};

