using System.IO;
using UnrealBuildTool;

public class ZXing : ModuleRules
{
	public ZXing(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ZXingSourcePath, "core", "src"));

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ZXignIntermediatePath, "Win64", "core", "Release", "ZXing.lib"));
			RuntimeDependencies.Add(Path.Combine(ZXingBinariesPath, "Win64", "ZXing.dll"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ZXignIntermediatePath, "Mac", "core", "libZXing.a"));
			RuntimeDependencies.Add(Path.Combine(ZXingBinariesPath, "Mac", "libZXing.dylib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			if (BuildHostPlatform.Current.Platform == UnrealTargetPlatform.Mac)
				PublicAdditionalLibraries.Add(Path.Combine(ZXignIntermediatePath, "Android", "core", "Release", "libZXing.a"));
			else if (BuildHostPlatform.Current.Platform == UnrealTargetPlatform.Win64)
				PublicAdditionalLibraries.Add(Path.Combine(ZXignIntermediatePath, "Android", "core", "Release", "libZXing.a"));

			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "ZXing_APL.xml"));
			RuntimeDependencies.Add(Path.Combine(ZXingBinariesPath, "Android", "libZXing.so"));
		}
	}

	private string ZXingSourcePath => Path.Combine(ModuleDirectory, "zxing-cpp");

	private string ZXignIntermediatePath => Path.Combine(PluginDirectory, "Intermediate", "ThirdParty", "ZXing");

	private string ZXingBinariesPath => Path.Combine(PluginDirectory, "Binaries");
}