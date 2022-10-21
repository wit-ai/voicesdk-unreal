/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Voice/AppVoiceExperience.h"
#include "Utilities/VoiceSDKLog.h"

/**
 * Sets default values for this actor's properties
 */
AAppVoiceExperience::AAppVoiceExperience()
	: Super()
{
	WitVoiceService = CreateDefaultSubobject<UWitVoiceService>(TEXT("WitVoiceService"));
	PlatformVoiceService = CreateDefaultSubobject<UPlatformVoiceService>(TEXT("PlatformVoiceService"));

	VoiceService = WitVoiceService;
}

/**
 * Called when play starts. Decides which voice service to use
 */
void AAppVoiceExperience::BeginPlay()
{
	const bool bShouldUsePlatformIntegration = Configuration != nullptr && Configuration->Application.Advanced.bIsPlatformIntegrationEnabled;
		
	UE_LOG(LogVoiceSDK, Display, TEXT("Init VoiceService: bIsPlatformIntegrationEnabled=%s"), bShouldUsePlatformIntegration ? TEXT("true") : TEXT("false"));

	if (bShouldUsePlatformIntegration)
	{
		VoiceService = PlatformVoiceService;
	}
	else
	{
		VoiceService = WitVoiceService;
	}

	Super::BeginPlay();
}
