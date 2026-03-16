// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalTravelConfirmWidget.h"

void UPortalTravelConfirmWidget::ConfirmTravel()
{
	OnConfirmed.Broadcast();
}

void UPortalTravelConfirmWidget::CancelTravel()
{
	OnCancelled.Broadcast();
}

void UPortalTravelConfirmWidget::SetPromptText(const FText& InPromptText)
{
	PromptText = InPromptText;
	BP_OnPromptUpdated(PromptText);
}

