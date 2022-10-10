/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */


#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "PlatformIntegrationSubsystem.generated.h"


class FJsonObject;
class FSubsystemCollectionBase;

DECLARE_DELEGATE_TwoParams(FOnRequestErrorDelegate, const FString, const FString);
DECLARE_DELEGATE_OneParam(FOnRequestProgressDelegate, const TSharedPtr<FJsonObject>);
DECLARE_DELEGATE_OneParam(FOnRequestCompleteDelegate, const TSharedPtr<FJsonObject>);

/**
 * A compact configuration for setting up a platform integration request. Use the methods in FWitRequestBuilder to construct this
 */
struct FRequestConfiguration
{
public:
	/**
	 * Default constructor
	 */
	FRequestConfiguration() = default;

	/** The base URL to use in the request */
	FString BaseUrl{};

	/** Optional version modifier string to use in the request */
	FString Version{};

	/** The server auth token to use in the request. Must be present */
	FString ServerAuthToken{};

	/** The verb (POST/GET) to use in the request */
	FString Verb{};

	/** The endpoint to use in the request */
	FString Endpoint{};

	/** The expect to use in the request */
	FString Accept{};

	/**  Unique_Identifier used by Java side to decide to reuse resources **/
	FString VoiceServiceUniqueIdentifier{};

	/** Optional set of URL parameters to use in the request */
	TMap<FString, FString> Parameters{};

	/** Optional content type pairs to use in the request */
	TMap<FString, FString> ContentTypes{};

	/** Optional callback to use when the request errors */
	FOnRequestErrorDelegate OnRequestError{};

	/** Optional callback to use when the request is in progress */
	FOnRequestProgressDelegate OnRequestProgress{};

	/** Optional callback to use when the request is complete */
	FOnRequestCompleteDelegate OnRequestComplete{};

	//TODO may not needed. check with the config on java side.
	// /** Tracks whether we should use the HTTP 1 chunked transfer protocol in the request */
	// bool bShouldUseChunkedTransfer{false};
};

/**
 * Inspired by WitRequestSubSystem.
 *  1. This class is doing traffic control, only one request a time, before response back or error or get deactivated, no one can make another call.
 *  2. The caller will need to call ActivateVoiceInput with config to occupy the subsystem
 *  3. To receive the responses, they caller need to bind to the config's delegate (subsystem wil then "call the registed callback"  same as WitRequestSubSystem, but much simple way, because jni callback can call this subsystem directly)
 *  4. The config will be hold for passing responses back to the caller.//TODO free the config after reponse received, and also unbind delegates in callers.
 *  4. Worth to mention: JNI callback is a static method, which can call this subsystem directly which is perfect! (inspired by Unreal's build-in Facebook plugin)
 */
UCLASS()
class PLATFORMINTEGRATION_API UPlatformIntegrationSubsystem final : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	bool IsOccupied() const;
	//UWitRequestSubsystem uses IsRequestInProgress() to indicate the subsystem is busy(is occupied), but IsRequestInProgress() conflict with IVoiceService's IsRequestInProgress(). So, to avoid confusing, I use IsOccupied here.//bIsRequestInProgress

	//below methods are IVoiceService methods, but with different params, so cannot inherit from it
	bool ActivateVoiceInput(const FRequestConfiguration& RequestConfiguration);
	bool ActivateVoiceInput(const FString& RequestOptions, const FRequestConfiguration& RequestConfiguration);
	bool ActivateVoiceInputImmediately(const FRequestConfiguration& RequestConfiguration);
	bool ActivateVoiceInputImmediately(const FString& RequestOptions, const FRequestConfiguration& RequestConfiguration);
	bool DeactivateVoiceInput(const FRequestConfiguration& RequestConfiguration);
	bool DeactivateAndAbortRequest(const FRequestConfiguration& RequestConfiguration);
	bool IsVoiceInputActive(const FRequestConfiguration& RequestConfiguration) const;
	bool IsSupported(const FRequestConfiguration& RequestConfiguration) const;
	// float GetVoiceInputVolume() const;// platformIntegration doesn't supply mic volume in this way, volume is on callback. 
	bool IsVoiceStreamingActive(const FRequestConfiguration& RequestConfiguration) const;
	bool IsRequestInProgress(const FRequestConfiguration& RequestConfiguration) const;
	void SendTranscription(const FString& Text, const FRequestConfiguration& RequestConfiguration);
	void SendTranscription(const FString& Text, const FString& RequestOptions, const FRequestConfiguration& RequestConfiguration);


	//delegate callback functions:
	void OnRequestProgress(const TSharedPtr<FJsonObject>);
	void OnRequestComplete(const TSharedPtr<FJsonObject>);
	void OnRequestError(const FString ErrorMessage);

private:
	bool bIsOccupied{false};

	bool bHasConfiguration{false};

	/** The current configuration setup */
	FRequestConfiguration Configuration{};
};
