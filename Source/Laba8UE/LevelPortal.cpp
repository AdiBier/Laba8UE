// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelPortal.h"
#include "PortalTravelConfirmWidget.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ALevelPortal::ALevelPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	PortalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(PortalRoot);

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(PortalRoot);
	PortalMesh->SetCollisionProfileName(FName(TEXT("BlockAll")));

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(PortalRoot);
	TriggerVolume->SetCollisionProfileName(FName(TEXT("Trigger")));
	TriggerVolume->SetBoxExtent(FVector(80.0f, 120.0f, 160.0f));
}

void ALevelPortal::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortal::OnPortalBeginOverlap);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ALevelPortal::OnPortalEndOverlap);
	}
}

void ALevelPortal::OnPortalBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bTravelLocked || !IsLocalPlayerActor(OtherActor))
	{
		return;
	}

	bTravelLocked = true;

	if (bRequireConfirmation)
	{
		ShowConfirmationUI();
		return;
	}

	TravelToTargetLevel();
}

void ALevelPortal::OnPortalEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!IsLocalPlayerActor(OtherActor))
	{
		return;
	}

	if (ActiveConfirmWidget)
	{
		CancelPortalTravel();
	}
}

void ALevelPortal::ShowConfirmationUI()
{
	CachedPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!CachedPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelPortal: Missing player controller, travel canceled."));
		bTravelLocked = false;
		return;
	}

	if (!ConfirmWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelPortal: ConfirmWidgetClass is empty, traveling immediately."));
		TravelToTargetLevel();
		return;
	}

	ActiveConfirmWidget = CreateWidget<UPortalTravelConfirmWidget>(CachedPlayerController, ConfirmWidgetClass);
	if (!ActiveConfirmWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelPortal: Failed to create confirmation widget."));
		bTravelLocked = false;
		return;
	}

	ActiveConfirmWidget->OnConfirmed.AddDynamic(this, &ALevelPortal::ConfirmPortalTravel);
	ActiveConfirmWidget->OnCancelled.AddDynamic(this, &ALevelPortal::CancelPortalTravel);
	ActiveConfirmWidget->SetPromptText(ConfirmationMessage);
	ActiveConfirmWidget->AddToViewport();

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(ActiveConfirmWidget->TakeWidget());
	InputMode.SetHideCursorDuringCapture(false);
	CachedPlayerController->SetInputMode(InputMode);
	CachedPlayerController->bShowMouseCursor = true;
}

void ALevelPortal::HideConfirmationUI(bool bRestoreGameInput)
{
	if (ActiveConfirmWidget)
	{
		ActiveConfirmWidget->OnConfirmed.RemoveDynamic(this, &ALevelPortal::ConfirmPortalTravel);
		ActiveConfirmWidget->OnCancelled.RemoveDynamic(this, &ALevelPortal::CancelPortalTravel);
		ActiveConfirmWidget->RemoveFromParent();
		ActiveConfirmWidget = nullptr;
	}

	if (bRestoreGameInput && CachedPlayerController)
	{
		FInputModeGameOnly InputMode;
		CachedPlayerController->SetInputMode(InputMode);
		CachedPlayerController->bShowMouseCursor = false;
	}
}

void ALevelPortal::TravelToTargetLevel()
{
	HideConfirmationUI(true);

	if (TargetLevelName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelPortal: TargetLevelName is empty."));
		bTravelLocked = false;
		return;
	}

	UGameplayStatics::OpenLevel(this, TargetLevelName);
}

void ALevelPortal::ConfirmPortalTravel()
{
	if (!bTravelLocked)
	{
		return;
	}

	TravelToTargetLevel();
}

void ALevelPortal::CancelPortalTravel()
{
	HideConfirmationUI(true);
	bTravelLocked = false;
}

bool ALevelPortal::IsLocalPlayerActor(const AActor* OtherActor) const
{
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	return PlayerCharacter && OtherActor == PlayerCharacter;
}

