// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LevelDesign3D : ModuleRules
{
	public LevelDesign3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","AIModule","GameplayTasks","NavigationSystem","UMG","Slate","SlateCore"});
    }
}
