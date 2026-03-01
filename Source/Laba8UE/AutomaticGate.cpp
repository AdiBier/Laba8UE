// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutomaticGate.h"
#include "Laba8UECharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AAutomaticGate::AAutomaticGate()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root scene component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Lewe skrzydło - pivot i mesh
	LeftDoorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("LeftDoorPivot"));
	LeftDoorPivot->SetupAttachment(RootComponent);
	LeftDoorPivot->SetRelativeLocation(FVector(0, -50.0f, 0));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(LeftDoorPivot);
	LeftDoor->SetCollisionProfileName(FName("BlockAll"));

	// Prawe skrzydło - pivot i mesh
	RightDoorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RightDoorPivot"));
	RightDoorPivot->SetupAttachment(RootComponent);
	RightDoorPivot->SetRelativeLocation(FVector(0, 50.0f, 0));

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(RightDoorPivot);
	RightDoor->SetCollisionProfileName(FName("BlockAll"));
}

void AAutomaticGate::BeginPlay()
{
	Super::BeginPlay();

	// Wyszukanie gracza
	PlayerCharacter = Cast<ALaba8UECharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AutomaticGate: Nie znaleziono gracza w świecie!"));
	}

	// Wyzerowanie offsetów
	LeftDoorCurrentOffset = 0.0f;
	RightDoorCurrentOffset = 0.0f;
	CloseTimer = 0.0f;
}

void AAutomaticGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sprawdzenie stanu wrót (czy gracz jest w zasięgu)
	UpdateGateState();

	// Animacja otwierania/zamykania
	if (bIsMoving)
	{
		if (bIsOpen)
		{
			// Otwieramy - przesuwamy lewe drzwi na lewo (-Y), prawe na prawo (+Y)
			LeftDoorCurrentOffset = FMath::FInterpTo(LeftDoorCurrentOffset, -SlideDistance, DeltaTime, OpenSpeed);
			RightDoorCurrentOffset = FMath::FInterpTo(RightDoorCurrentOffset, SlideDistance, DeltaTime, OpenSpeed);
		}
		else
		{
			// Zamykamy - powrót do pozycji początkowej (0)
			LeftDoorCurrentOffset = FMath::FInterpTo(LeftDoorCurrentOffset, 0.0f, DeltaTime, OpenSpeed);
			RightDoorCurrentOffset = FMath::FInterpTo(RightDoorCurrentOffset, 0.0f, DeltaTime, OpenSpeed);
		}

		// Aplikujemy translację do meshow (lokalna pozycja względem pivotu)
		if (LeftDoor)
		{
			LeftDoor->SetRelativeLocation(FVector(0.0f, LeftDoorCurrentOffset, 0.0f));
		}
		if (RightDoor)
		{
			RightDoor->SetRelativeLocation(FVector(0.0f, RightDoorCurrentOffset, 0.0f));
		}

		// Sprawdzenie czy osiągnęliśmy cel
		if (bIsOpen)
		{
			if (FMath::IsNearlyEqual(LeftDoorCurrentOffset, -SlideDistance, 1.0f))
			{
				bIsMoving = false;
				CloseTimer = AutoCloseDelay;
				OnGateOpened();
			}
		}
		else
		{
			if (FMath::IsNearlyEqual(LeftDoorCurrentOffset, 0.0f, 1.0f))
			{
				bIsMoving = false;
				OnGateClosed();
			}
		}
	}

	// Odbieranie czasu do zamknięcia
	if (bIsOpen && !bIsMoving)
	{
		CloseTimer -= DeltaTime;
		if (CloseTimer <= 0.0f)
		{
			CloseGate();
		}
	}

	// Debug visualization
	DrawDebugGate();
}

void AAutomaticGate::UpdateGateState()
{
	if (!PlayerCharacter)
	{
		return;
	}

	// Sprawdzenie odległości do gracza
	float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());

	if (DistanceToPlayer <= DetectionRange)
	{
		// Gracz zbliżył się - otwórz wrota
		if (!bIsOpen && !bIsMoving)
		{
			OpenGate();
		}
		// Reset timer, gdy gracz jest w zasięgu
		CloseTimer = AutoCloseDelay;
	}
}

void AAutomaticGate::OpenGate()
{
	if (bIsOpen || bIsMoving)
	{
		return;
	}

	bIsOpen = true;
	bIsMoving = true;
	CloseTimer = AutoCloseDelay;

	UE_LOG(LogTemp, Log, TEXT("AutomaticGate: Otwieranie wrót"));
}

void AAutomaticGate::CloseGate()
{
	if (!bIsOpen || bIsMoving)
	{
		return;
	}

	bIsOpen = false;
	bIsMoving = true;

	UE_LOG(LogTemp, Log, TEXT("AutomaticGate: Zamykanie wrót"));
}

void AAutomaticGate::ToggleGate()
{
	if (bIsMoving)
	{
		return;
	}

	if (bIsOpen)
	{
		CloseGate();
	}
	else
	{
		OpenGate();
	}
}

void AAutomaticGate::DrawDebugGate()
{
	if (!bShowDebugVisualization)
	{
		return;
	}

	FVector GateLocation = GetActorLocation();

	// Rysowanie sfery detekcji
	FColor DetectionColor = bIsOpen ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), GateLocation, DetectionRange, 12, DetectionColor, false, 0.02f, 0, 1.0f);

	// Rysowanie linii pokazujące kierunek otwarcia
	DrawDebugLine(GetWorld(), GateLocation, GateLocation + GetActorForwardVector() * 200.0f, FColor::Yellow, false, 0.02f, 0, 2.0f);
}
