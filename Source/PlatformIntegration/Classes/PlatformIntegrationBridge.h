/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#if PLATFORM_ANDROID
#include <jni.h>
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif
#include "PlatformIntegrationBridge.generated.h"

UCLASS(NotBlueprintable)
class PLATFORMINTEGRATION_API UPlatformIntegrationBridge : public UObject
{
	GENERATED_BODY()

public:
	UPlatformIntegrationBridge();

#if PLATFORM_ANDROID
	static void SetupBridge();
#endif

	static void ActivateVoiceInput(const FString& Tag, const FString& Token, const FString& SDKVersion);
	static void ActivateVoiceInputImmediately(const FString& Tag, const FString& Token, const FString& SDKVersion);
	static void ActivateVoiceInput(const FString& RequestOptions, const FString& Tag, const FString& Token, const FString& SDKVersion);
	static void ActivateVoiceInputImmediately(const FString& RequestOptions, const FString& Tag, const FString& Token, const FString& SDKVersion);
	static void DeactivateVoiceInput(const FString& Tag);
	static void DeactivateAndAbortRequest(const FString& Tag);
	static void SendTranscription(const FString& Text, const FString& Tag, const FString& Token,
	const FString& SDKVersion);
	static void SendTranscription(const FString& Text, const FString& RequestOptions, const FString& Tag, const FString& Token,
								  const FString& SDKVersion);
	static bool IsSupported(const FString& Tag);
	static bool IsVoiceInputActive(const FString& Tag);
	static bool IsVoiceStreamingActive(const FString& Tag);
	static bool IsRequestInProgress(const FString& Tag);
};
