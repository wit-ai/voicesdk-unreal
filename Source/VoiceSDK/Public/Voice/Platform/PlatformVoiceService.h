/*
* Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "CoreMinimal.h"
#include "Voice/Service/VoiceService.h"
#include "PlatformVoiceService.generated.h"


UCLASS(ClassGroup=(Meta), meta=(BlueprintSpawnableComponent))
class VOICESDK_API UPlatformVoiceService final : public UVoiceService
{
	GENERATED_BODY()

public:
	
	UPlatformVoiceService();

	/**
	 * IVoiceServiceBase overrides
	 */
	virtual bool ActivateVoiceInput() override;
	virtual bool ActivateVoiceInputWithRequestOptions(const FString& RequestOptions) override;
	virtual bool ActivateVoiceInputImmediately() override;
	virtual bool ActivateVoiceInputImmediatelyWithRequestOptions(const FString& RequestOptions) override;
	virtual bool DeactivateVoiceInput() override;
	virtual bool DeactivateAndAbortRequest() override;
	virtual bool IsVoiceInputActive() const override;
	virtual bool IsVoiceStreamingActive() const override;
	virtual bool IsRequestInProgress() const override;
	virtual float GetVoiceInputVolume() const override;
	virtual void SendTranscription(const FString& Text) override;
	virtual void SendTranscriptionWithRequestOptions(const FString& Text, const FString& RequestOptions) override;
	
	bool IsSupported() const;
	
private:

#if WITH_EDITOR

	/** Write the captured voice input to a wav file */
	static void WriteRawPCMDataToWavFile(const uint8* RawPCMData, int32 RawPCMDataSize, int32 NumChannels, int32 SampleRate);

#endif

	bool DeactivateVoiceInput(bool bIsAbortRequestNeeded);
	bool DoDeactivateVoiceInput(bool bIsAbortRequestNeeded);
	void OnSpeechRequestProgress(const TSharedPtr<FJsonObject> PartialJsonResponse);
	void OnSpeechRequestComplete(const TSharedPtr<FJsonObject> JsonResponse);
	void OnRequestError(const FString ErrorMessage, const FString HumanReadableErrorMessage);

	FString PlatformVoiceServiceID {};
};
