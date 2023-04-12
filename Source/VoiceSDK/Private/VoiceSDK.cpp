/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "VoiceSDK.h"
#include "Interfaces/IPluginManager.h"
#include "Wit/Utilities/WitHelperUtilities.h"

#define LOCTEXT_NAMESPACE "FVoiceSDKModule"

IMPLEMENT_MODULE(FVoiceSDKModule, VoiceSDK)

const FString FVoiceSDKModule::Name = "VoiceSDK";

FVoiceSDKModule* FVoiceSDKModule::Singleton = nullptr;

void FVoiceSDKModule::StartupModule()
{
	Singleton = this;

	// find version code
	IPluginManager& PluginManager = IPluginManager::Get();
	TArray<TSharedRef<IPlugin>> Plugins = PluginManager.GetDiscoveredPlugins();
	for (const TSharedRef<IPlugin>& Plugin : Plugins)
	{
		if (Plugin->GetName() == Name)
		{
			const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
			Version = Descriptor.VersionName;

			const FString VersionCode = FString::Printf(TEXT("voicesdk-unreal-%s"), *Version);
			FWitHelperUtilities::AddRequestUserData(VersionCode, true);
			break;
		}
	}
}

void FVoiceSDKModule::ShutdownModule()
{
	Singleton = nullptr;
}

VOICESDK_API FVoiceSDKModule& FVoiceSDKModule::Get()
{
	if (Singleton == nullptr)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FVoiceSDKModule>(*Name);
	}

	check(Singleton != nullptr);
	return *Singleton;
}

#undef LOCTEXT_NAMESPACE
