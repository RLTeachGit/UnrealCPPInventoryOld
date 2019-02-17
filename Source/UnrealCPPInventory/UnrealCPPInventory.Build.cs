// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealCPPInventory : ModuleRules
{
	public UnrealCPPInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" ,"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
