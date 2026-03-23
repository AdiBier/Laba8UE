#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveGameManager.generated.h"

UCLASS()
class LABA8UE_API USaveGameManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Zapisz grę do slotu
	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	static bool SaveGameToSlot(APlayerController* PlayerController, const FString& SlotName);

	// Wczytaj grę ze slotu
	UFUNCTION(BlueprintCallable, Category="SaveLoad")
	static bool LoadGameFromSlot(APlayerController* PlayerController, const FString& SlotName);

	// Najprostszy zapis (slot staly: "SaveGame")
	UFUNCTION(BlueprintCallable, Category="SaveLoad", meta=(WorldContext="WorldContextObject"))
	static bool QuickSave(UObject* WorldContextObject);

	// Najprostsze wczytanie (slot staly: "SaveGame")
	UFUNCTION(BlueprintCallable, Category="SaveLoad", meta=(WorldContext="WorldContextObject"))
	static bool QuickLoad(UObject* WorldContextObject);
};
