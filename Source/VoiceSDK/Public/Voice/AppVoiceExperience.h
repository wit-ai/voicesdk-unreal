/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "CoreMinimal.h"
#include "Wit/Voice/WitVoiceService.h"
#include "Voice/Experience/VoiceExperience.h"
#include "Voice/Platform/PlatformVoiceService.h"
#include "AppVoiceExperience.generated.h"

/**
 * Top level actor for App voice interactions. You can create a blueprint class off this actor and add whatever intent and entity matchers
 * you need to implement your voice experience
 */
UCLASS(Blueprintable)
class VOICESDK_API AAppVoiceExperience : public AVoiceExperience
{
	GENERATED_BODY()

public:

	/**
	 * Sets default values for this actor's properties
	 */
	AAppVoiceExperience();

	/**
	 * The wit voice service
	 */
	UPROPERTY()
	UWitVoiceService* WitVoiceService{};
	
	/**
	 * The platform voice service
	 */
	UPROPERTY()
	UPlatformVoiceService* PlatformVoiceService{};
	
protected:

	virtual void BeginPlay() override;
	
};
