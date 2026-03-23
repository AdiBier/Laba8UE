#include "SaveGameManager.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

namespace
{
	const TCHAR* DefaultSaveSlot = TEXT("SaveGame");
}

bool USaveGameManager::SaveGameToSlot(APlayerController* PlayerController, const FString& SlotName)
{
	const FString ResolvedSlot = SlotName.IsEmpty() ? FString(DefaultSaveSlot) : SlotName;

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[SAVE] Invalid controller."));
		return false;
	}

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("[SAVE] Player pawn is null."));
		return false;
	}

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (!SaveGameInstance) return false;

	SaveGameInstance->PlayerLocation = PlayerPawn->GetActorLocation();
	SaveGameInstance->PlayerRotation = PlayerPawn->GetActorRotation();

	bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveGameInstance, ResolvedSlot, 0);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SAVE] Saved to slot: %s | Location: %.2f, %.2f, %.2f"),
			*ResolvedSlot,
			SaveGameInstance->PlayerLocation.X,
			SaveGameInstance->PlayerLocation.Y,
			SaveGameInstance->PlayerLocation.Z);
	}

	return bSuccess;
}

bool USaveGameManager::LoadGameFromSlot(APlayerController* PlayerController, const FString& SlotName)
{
	const FString ResolvedSlot = SlotName.IsEmpty() ? FString(DefaultSaveSlot) : SlotName;

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[LOAD] Invalid controller."));
		return false;
	}

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("[LOAD] Player pawn is null."));
		return false;
	}

	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(ResolvedSlot, 0));
	if (!LoadedGame)
	{
		UE_LOG(LogTemp, Error, TEXT("[LOAD] Failed to load from slot: %s"), *ResolvedSlot);
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("[LOAD] Loaded from slot: %s | Location: %.2f, %.2f, %.2f"),
		*ResolvedSlot,
		LoadedGame->PlayerLocation.X,
		LoadedGame->PlayerLocation.Y,
		LoadedGame->PlayerLocation.Z);

	const bool bTeleported = PlayerPawn->TeleportTo(LoadedGame->PlayerLocation, LoadedGame->PlayerRotation, false, true);
	PlayerController->SetControlRotation(LoadedGame->PlayerRotation);

	UE_LOG(LogTemp, Warning, TEXT("[LOAD] Teleport result: %s | Pawn location now: %.2f, %.2f, %.2f"),
		bTeleported ? TEXT("true") : TEXT("false"),
		PlayerPawn->GetActorLocation().X,
		PlayerPawn->GetActorLocation().Y,
		PlayerPawn->GetActorLocation().Z);

	return bTeleported;
}

bool USaveGameManager::QuickSave(UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	return SaveGameToSlot(PC, FString(DefaultSaveSlot));
}

bool USaveGameManager::QuickLoad(UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	return LoadGameFromSlot(PC, FString(DefaultSaveSlot));
}
