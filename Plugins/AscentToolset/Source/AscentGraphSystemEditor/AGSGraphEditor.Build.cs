using UnrealBuildTool;

public class AGSGraphEditor : ModuleRules
{
	public AGSGraphEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Error;

        PublicIncludePaths.AddRange(
			new string[] {
                //"AscentGraphSystemEditor/Public",
                //"AscentGraphSystemRuntime/Public"
				// ... add public include paths required here ...
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
                // ... add other private include paths required here ...
                "AscentGraphSystemEditor/Private",
               // "AscentGraphSystemRuntime/Private"
            }
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "AGSGraphRuntime",
                "Core",
				"CoreUObject",
                "Engine",
				"ToolMenus",
                "AssetTools",
                "Slate",
                "SlateCore",
                "GraphEditor",
                "PropertyEditor",
                "EditorStyle",
                "Kismet",
                "KismetWidgets",
                "ApplicationCore",
                "ToolMenus",
                "InputCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                
                "AssetTools",
                "Slate",
                "SlateCore",
                "GraphEditor",
                "PropertyEditor",
                "EditorStyle",
                "Kismet",
                "KismetWidgets",
                "ApplicationCore",
                "UnrealEd"
				// ... add private dependencies that you statically link with here ...
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
            }
			);
	}
}