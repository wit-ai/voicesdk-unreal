/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "Subsystem/PlatformIntegrationSubsystem.h"
#include "PlatformIntegrationBridge.h"
#include "PlatformIntegrationPrivatePCH.h"

void UPlatformIntegrationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UPlatformIntegrationSubsystem::Deinitialize()
{
}

bool UPlatformIntegrationSubsystem::ActivateVoiceInput(const FRequestConfiguration& RequestConfiguration)
{
	return ActivateVoiceInput(FString(), RequestConfiguration);
}

bool UPlatformIntegrationSubsystem::ActivateVoiceInput(const FString& RequestOptions,
                                                       const FRequestConfiguration& RequestConfiguration)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: ActivateVoiceInput."));
	if (bIsOccupied)
	//Same as Unity, no need to check isSupport and isActive, etc, just activate and let the platform to handle tell us if we can activate.
	{
		UE_LOG(LogPlatformIntegration, Warning,
		       TEXT(
			       "VoiceSDKSubsystem BeginRequest(ActivateVoiceInput): Attempting to begin request when one is already in progress"
		       ));
		return false;
	}

	bIsOccupied = true;
	Configuration = RequestConfiguration;
	bHasConfiguration = true;

	if (RequestOptions.IsEmpty())
	{
		UPlatformIntegrationBridge::ActivateVoiceInput(Configuration.VoiceServiceUniqueIdentifier,
		                                               Configuration.ServerAuthToken, Configuration.Version);
	}
	else
	{
		UPlatformIntegrationBridge::ActivateVoiceInput(RequestOptions, Configuration.VoiceServiceUniqueIdentifier,
		                                               Configuration.ServerAuthToken, Configuration.Version);
	}
	return true;
}

bool UPlatformIntegrationSubsystem::ActivateVoiceInputImmediately(const FRequestConfiguration& RequestConfiguration)
{
	return ActivateVoiceInputImmediately(FString(), RequestConfiguration);
}

bool UPlatformIntegrationSubsystem::ActivateVoiceInputImmediately(const FString& RequestOptions,
                                                                  const FRequestConfiguration& RequestConfiguration)
{
	UE_LOG(LogPlatformIntegration, Display,
	       TEXT("VoiceSDKSubsystem: ActivateVoiceInputImmediately."));
	if (bIsOccupied)
	{
		UE_LOG(LogPlatformIntegration, Warning,
		       TEXT(
			       "VoiceSDKSubsystem BeginRequest(ActivateVoiceInputImmediately): Attempting to begin request when one is already in progress"
		       ));
		return false;
	}
	bIsOccupied = true;
	Configuration = RequestConfiguration;
	bHasConfiguration = true;

	if (RequestOptions.IsEmpty())
	{
		UPlatformIntegrationBridge::ActivateVoiceInputImmediately(Configuration.VoiceServiceUniqueIdentifier,
		                                                          Configuration.ServerAuthToken, Configuration.Version);
	}
	else
	{
		UPlatformIntegrationBridge::ActivateVoiceInputImmediately(RequestOptions,
		                                                          Configuration.VoiceServiceUniqueIdentifier,
		                                                          Configuration.ServerAuthToken, Configuration.Version);
	}
	return true;
}

bool UPlatformIntegrationSubsystem::DeactivateVoiceInput(const FRequestConfiguration& RequestConfiguration)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: DeactivateVoiceInput."));
	UPlatformIntegrationBridge::DeactivateVoiceInput(RequestConfiguration.VoiceServiceUniqueIdentifier);
	bIsOccupied = false;
	return true;
}

bool UPlatformIntegrationSubsystem::DeactivateAndAbortRequest(const FRequestConfiguration& RequestConfiguration)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: DeactivateAndAbortRequest."));
	UPlatformIntegrationBridge::DeactivateAndAbortRequest(RequestConfiguration.VoiceServiceUniqueIdentifier);
	bIsOccupied = false;
	return true;
}

bool UPlatformIntegrationSubsystem::IsVoiceInputActive(const FRequestConfiguration& RequestConfiguration) const
{
	const bool bIsVoiceInputActive = UPlatformIntegrationBridge::IsVoiceInputActive(
		RequestConfiguration.VoiceServiceUniqueIdentifier);

	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: bIsVoiceInputActive = %s"),
	       bIsVoiceInputActive? TEXT("true") : TEXT("false"));
	return bIsVoiceInputActive;
}


bool UPlatformIntegrationSubsystem::IsVoiceStreamingActive(const FRequestConfiguration& RequestConfiguration) const
{
	const bool bIsVoiceStreamingActive = UPlatformIntegrationBridge::IsVoiceStreamingActive(
		RequestConfiguration.VoiceServiceUniqueIdentifier);

	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: bIsVoiceStreamingActive = %s"),
	       bIsVoiceStreamingActive? TEXT("true") : TEXT("false"));
	return bIsVoiceStreamingActive;
}

bool UPlatformIntegrationSubsystem::IsRequestInProgress(const FRequestConfiguration& RequestConfiguration) const
{
	const bool bIsRequestInProgress = UPlatformIntegrationBridge::IsRequestInProgress(
		RequestConfiguration.VoiceServiceUniqueIdentifier);

	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: bIsRequestInProgress = %s"),
	       bIsRequestInProgress? TEXT("true") : TEXT("false"));
	return bIsRequestInProgress;
}

bool UPlatformIntegrationSubsystem::IsOccupied() const
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: IsOccupied = %s"),
	       bIsOccupied? TEXT("true") : TEXT("false"));
	return bIsOccupied;
}

void UPlatformIntegrationSubsystem::SendTranscription(const FString& Text,
                                                      const FRequestConfiguration& RequestConfiguration)
{
	SendTranscription(Text, FString(), RequestConfiguration);
}

void UPlatformIntegrationSubsystem::SendTranscription(const FString& Text, const FString& RequestOption,
                                                      const FRequestConfiguration& RequestConfiguration)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: SendTranscription."));
	if (bIsOccupied)
	{
		UE_LOG(LogPlatformIntegration, Warning,
		       TEXT("VoiceSDKSubsystem BeginRequest: Attempting to begin request when one is already in progress"));
		return;
	}
	bIsOccupied = true;
	Configuration = RequestConfiguration;
	bHasConfiguration = true;
	if (RequestOption.IsEmpty())
	{
		UPlatformIntegrationBridge::SendTranscription(Text, Configuration.VoiceServiceUniqueIdentifier,
		                                              Configuration.ServerAuthToken, Configuration.Version);
	}
	else
	{
		UPlatformIntegrationBridge::SendTranscription(Text, RequestOption, Configuration.VoiceServiceUniqueIdentifier,
		                                              Configuration.ServerAuthToken, Configuration.Version);
	}
}

bool UPlatformIntegrationSubsystem::IsSupported(const FRequestConfiguration& RequestConfiguration) const
{
	const bool bIsSupported =
		UPlatformIntegrationBridge::IsSupported(RequestConfiguration.VoiceServiceUniqueIdentifier);

	UE_LOG(LogPlatformIntegration, Display, TEXT("VoiceSDKSubsystem: bIsSupported = %s"),
	       bIsSupported? TEXT("true") : TEXT("false"));
	return bIsSupported;
}

void UPlatformIntegrationSubsystem::OnRequestProgress(const TSharedPtr<FJsonObject> Json)
{
	if (!Configuration.OnRequestProgress.IsBound())
	{
		return;
	}

	(void)Configuration.OnRequestProgress.ExecuteIfBound(Json);
}

void UPlatformIntegrationSubsystem::OnRequestComplete(const TSharedPtr<FJsonObject> Json)
{
	if (!Configuration.OnRequestComplete.IsBound())
	{
		return;
	}
	(void)Configuration.OnRequestComplete.ExecuteIfBound(Json);
	bIsOccupied = false;

	Configuration.OnRequestError.Unbind();
	Configuration.OnRequestComplete.Unbind();
	Configuration.OnRequestComplete.Unbind();
	Configuration.OnRequestProgress.Unbind();
}

void UPlatformIntegrationSubsystem::OnRequestError(const FString ErrorMessage)
{
	UE_LOG(LogPlatformIntegration, Error, TEXT("Request failed with error: %s"), *ErrorMessage);
	//TODO PI doesn't support error code, will need to figure out this for PI.
	// const FString HumanReadableErrorMessage = FString::Format(TEXT("Request failed with error code {0}"), { Response->GetResponseCode()});

	if (!Configuration.OnRequestError.IsBound())
	{
		return;
	}
	Configuration.OnRequestError.ExecuteIfBound(ErrorMessage, ErrorMessage);
	bIsOccupied = false;
	Configuration.OnRequestError.Unbind();
	Configuration.OnRequestComplete.Unbind();
	Configuration.OnRequestProgress.Unbind();
}
