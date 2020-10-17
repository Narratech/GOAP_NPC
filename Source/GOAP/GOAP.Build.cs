// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GOAP : ModuleRules
{
	public GOAP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
