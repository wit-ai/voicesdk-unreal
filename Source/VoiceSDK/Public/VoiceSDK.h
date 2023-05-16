/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"

class FVoiceSDKModule final : public IModuleInterface
{
public:

	/**
	 * Voice SDK name
	 */
	static const FString Name;

	/**
	 * Voice SDK API version
	 */
	const FString& SdkVersion = Version;

	/**
	 * IModuleInterface implementation
	 */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return singleton instance, loading the module on demand if needed
	 */
	VOICESDK_API static FVoiceSDKModule& Get();

private:

	/** Voice SDK API version */
	FString Version;

	/** Singleton for the module while loaded and available */
	static FVoiceSDKModule* Singleton;
};
