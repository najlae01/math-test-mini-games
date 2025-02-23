// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class AndroidCam : ModuleRules
{
    public AndroidCam(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
				"Core"
            }
        );


        PrivateDependencyModuleNames.AddRange(
			new string[]
				{
					"CoreUObject",
					"Engine",
					"Slate",
					"SlateCore",
					"MediaAssets",
					"MediaUtils",
					"RHI",
					"RenderCore"
					// ... add private dependencies that you statically link with here ...	
				}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(pluginPath, "AndroidCam_APL.xml"));

            PrivateDependencyModuleNames.Add("Launch");
        }
    }
}
