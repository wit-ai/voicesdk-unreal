/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "PlatformIntegrationPrivatePCH.h"
#include "IPlatformIntegration.h"

DEFINE_LOG_CATEGORY(LogPlatformIntegration);

#define LOCTEXT_NAMESPACE "PlatformIntegration"

class FPlatformIntegration : public IPlatformIntegration
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FPlatformIntegration, PlatformIntegration)

void FPlatformIntegration::StartupModule()
{
#if PLATFORM_ANDROID
	UPlatformIntegrationBridge::SetupBridge();
#endif
}


void FPlatformIntegration::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
