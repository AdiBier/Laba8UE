// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Laba8UE : ModuleRules
{
	public Laba8UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Laba8UE",
			"Laba8UE/Variant_Horror",
			"Laba8UE/Variant_Horror/UI",
			"Laba8UE/Variant_Shooter",
			"Laba8UE/Variant_Shooter/AI",
			"Laba8UE/Variant_Shooter/UI",
			"Laba8UE/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
