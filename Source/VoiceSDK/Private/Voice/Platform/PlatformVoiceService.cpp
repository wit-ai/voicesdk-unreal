/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "Voice/Platform/PlatformVoiceService.h"
#include "Utilities/VoiceSDKLog.h"

#include "Subsystem/PlatformIntegrationSubsystem.h"
#include "PlatformIntegration/Classes/PlatformIntegrationBridge.h"
#include "JsonObjectConverter.h"
#include "Engine.h"


UPlatformVoiceService::UPlatformVoiceService()
	: Super()
{
	PlatformVoiceServiceID = MakeUniqueObjectName(this, UPlatformVoiceService::StaticClass(), "PIVS_ID_").ToString();
}

bool UPlatformVoiceService::ActivateVoiceInput()
{
	return ActivateVoiceInputWithRequestOptions(FString());
}

bool UPlatformVoiceService::ActivateVoiceInputWithRequestOptions(const FString& RequestOptions)
{
	UE_LOG(LogVoiceSDK, Display, TEXT("UPlatformVoiceService ActivateVoiceInput called"));

	// Configuration is required as we need the access token
	
	const bool bHasConfiguration = Configuration != nullptr && !Configuration->Application.ClientAccessToken.IsEmpty();
	
	if (!bHasConfiguration)
	{
		UE_LOG(LogVoiceSDK, Warning, TEXT("PlatformIntegration cannot active voice input because no configuration found. Please assign a configuration and access token"));
		return false;
	}

#if WITH_EDITORONLY_DATA
	
	if (Configuration->Voice.bIsWavFileRecordingEnabled)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("PlatformIntegration VoiceService cannot record voice to Wav file"));
	}

#endif

	UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("ActivateVoiceInput: VoiceSDKSubsystem is NULL."));
		return false;
	}

	if (VoiceSDKSubsystem->IsOccupied())
	{
		UE_LOG(LogVoiceSDK, Warning,
		       TEXT(
			       "ActivateVoiceInput: cannot ActivateVoiceInput because it is active already. Please wait or deactivate first."
		       ));

		return false;
	}
	
	FRequestConfiguration RequestConfiguration{};
	//TODO change to uproperty, a service can only have one config a time.  need to unbind before create. also unbind after response and unbind in deactivate.
	RequestConfiguration.ServerAuthToken = Configuration->Application.ClientAccessToken;
	RequestConfiguration.Version = Configuration->Application.Advanced.ApiVersion;
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;

	RequestConfiguration.OnRequestError.BindUObject(this, &UPlatformVoiceService::OnRequestError);
	RequestConfiguration.OnRequestProgress.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestProgress);
	RequestConfiguration.OnRequestComplete.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestComplete);
	
	if(RequestOptions.IsEmpty())
	{
		return VoiceSDKSubsystem->ActivateVoiceInput(RequestConfiguration);
	}

	return VoiceSDKSubsystem->ActivateVoiceInput(RequestOptions, RequestConfiguration);
}

bool UPlatformVoiceService::ActivateVoiceInputImmediately()
{
	return ActivateVoiceInputImmediatelyWithRequestOptions(FString());
}

bool UPlatformVoiceService::ActivateVoiceInputImmediatelyWithRequestOptions(const FString& RequestOptions)
{
	UE_LOG(LogVoiceSDK, Display, TEXT("UPlatformVoiceService ActivateVoiceInputImmediately called"));

	// Configuration is required as we need the access token
	
	const bool bHasConfiguration = Configuration != nullptr && !Configuration->Application.ClientAccessToken.IsEmpty();
	
	if (!bHasConfiguration)
	{
		UE_LOG(LogVoiceSDK, Warning, TEXT("PlatformIntegration cannot active voice input because no configuration found. Please assign a configuration and access token"));
		return false;
	}

	UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("ActivateVoiceInputImmediately: VoiceSDKSubsystem is NULL."));
		return false;
	}

	if (VoiceSDKSubsystem->IsOccupied())
	{
		UE_LOG(LogVoiceSDK, Warning,
		       TEXT(
			       "ActivateVoiceInputImmediately: cannot ActivateVoiceInputImmediately because it is active already. Please wait or deactivate first."
		       ));

		return false;
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.ServerAuthToken = Configuration->Application.ClientAccessToken;
	RequestConfiguration.Version = Configuration->Application.Advanced.ApiVersion;
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;

	RequestConfiguration.OnRequestError.BindUObject(this, &UPlatformVoiceService::OnRequestError);
	RequestConfiguration.OnRequestProgress.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestProgress);
	RequestConfiguration.OnRequestComplete.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestComplete);
	
	if(RequestOptions.IsEmpty())
	{
		return VoiceSDKSubsystem->ActivateVoiceInputImmediately(RequestConfiguration);
	}

	return VoiceSDKSubsystem->ActivateVoiceInputImmediately(RequestOptions, RequestConfiguration);
}

bool UPlatformVoiceService::DeactivateAndAbortRequest()
{
	return DeactivateVoiceInput(true);
}

bool UPlatformVoiceService::DeactivateVoiceInput()
{
	return DeactivateVoiceInput(false);
}

bool UPlatformVoiceService::DeactivateVoiceInput(bool bIsAbortRequestNeeded)
{
	UE_LOG(LogVoiceSDK, Display, TEXT("UPlatformVoiceService DeactivateVoiceInput called"));

	const bool bDidDeactivate = DoDeactivateVoiceInput(bIsAbortRequestNeeded);
	const bool bShouldCallStopEvent = bDidDeactivate && Events != nullptr;
	if (bShouldCallStopEvent)
	{
		Events->OnStopVoiceInputDueToDeactivation.Broadcast();
	}

	return bDidDeactivate;
}

bool UPlatformVoiceService::DoDeactivateVoiceInput(bool bIsAbortRequestNeeded)
{
	UE_LOG(LogVoiceSDK, Display, TEXT("DeactivateVoiceInput: DoDeactivateVoiceInput called bIsAbortRequestNeeded=%s"), bIsAbortRequestNeeded ? TEXT("True") : TEXT("False"));
	
	UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("DoDeactivateVoiceInput: VoiceSDKSubsystem is NULL."));
		return false;
	}

	if (!IsVoiceInputActive())
	{
		UE_LOG(LogVoiceSDK, Warning,
		       TEXT(
			       "DeactivateVoiceInput: cannot deactivate voice input because it is not active, but will still make the call to reset other flags."
		       ));
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.ServerAuthToken = Configuration->Application.ClientAccessToken;
	RequestConfiguration.Version = Configuration->Application.Advanced.ApiVersion;
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;
	RequestConfiguration.OnRequestError.BindUObject(this, &UPlatformVoiceService::OnRequestError);
	if (bIsAbortRequestNeeded)
	{
		return VoiceSDKSubsystem->DeactivateAndAbortRequest(RequestConfiguration);
	}
	
	return VoiceSDKSubsystem->DeactivateVoiceInput(RequestConfiguration);
}

bool UPlatformVoiceService::IsSupported() const
{
	const UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("IsSupported: VoiceSDKSubsystem is NULL."));
		return false;
	}
	
	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;

	return VoiceSDKSubsystem->IsSupported(RequestConfiguration);
}

float UPlatformVoiceService::GetVoiceInputVolume() const
{
	//TODO we should get this from UPlatformIntegrationSubsystem's delegate (callback)
	// We may use this for later attention system. will implement this when doing the attention system. 
	UE_LOG(LogVoiceSDK, Error,
	       TEXT(
		       "PlatformIntegration VoiceService doesn't support GetVoiceInputVolume, should get it from platformIntegration callback."
	       ));
	return -1.0f;
}

bool UPlatformVoiceService::IsVoiceInputActive() const
{
	const UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("IsVoiceInputActive: VoiceSDKSubsystem is NULL."));
		return false;
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;
	
	return VoiceSDKSubsystem->IsVoiceInputActive(RequestConfiguration);
}

bool UPlatformVoiceService::IsVoiceStreamingActive() const
{
	const UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("IsVoiceStreamingActive: VoiceSDKSubsystem is NULL."));
		return false;
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;
	
	return VoiceSDKSubsystem->IsVoiceStreamingActive(RequestConfiguration);
}

bool UPlatformVoiceService::IsRequestInProgress() const
{
	const UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("IsRequestInProgress: VoiceSDKSubsystem is NULL."));
		return false;
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;
	
	return VoiceSDKSubsystem->IsRequestInProgress(RequestConfiguration);
}

void UPlatformVoiceService::SendTranscription(const FString& Text)
{
	SendTranscriptionWithRequestOptions(Text, FString());
}

void UPlatformVoiceService::SendTranscriptionWithRequestOptions(const FString& Text, const FString& RequestOptions)
{
	UE_LOG(LogVoiceSDK, Display, TEXT("UPlatformVoiceService SendTranscription called"));

	// Configuration is required as we need the access token
	
	const bool bHasConfiguration = Configuration != nullptr && !Configuration->Application.ClientAccessToken.IsEmpty();
	
	if (!bHasConfiguration)
	{
		UE_LOG(LogVoiceSDK, Warning, TEXT("SendTranscription: cannot send because no configuration found. Please assign a configuration and access token"));
		return;
	}

	UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
	if (VoiceSDKSubsystem == nullptr)
	{
		UE_LOG(LogVoiceSDK, Error, TEXT("SendTranscription: VoiceSDKSubsystem is NULL."));
		return;
	}
	if (VoiceSDKSubsystem->IsOccupied())
	{
		UE_LOG(LogVoiceSDK, Warning,
		       TEXT(
			       "SendTranscription: cannot SendTranscription because it is active already. Please wait or deactivate first."
		       ));
		return;
	}

	FRequestConfiguration RequestConfiguration{};
	RequestConfiguration.ServerAuthToken = Configuration->Application.ClientAccessToken;
	RequestConfiguration.Version = Configuration->Application.Advanced.ApiVersion;
	RequestConfiguration.VoiceServiceUniqueIdentifier = PlatformVoiceServiceID;

	RequestConfiguration.OnRequestError.BindUObject(this, &UPlatformVoiceService::OnRequestError);
	RequestConfiguration.OnRequestProgress.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestProgress);
	RequestConfiguration.OnRequestComplete.BindUObject(this, &UPlatformVoiceService::OnSpeechRequestComplete);

	if (RequestOptions.IsEmpty())
	{
		VoiceSDKSubsystem->SendTranscription(Text, RequestConfiguration);
	}
	else
	{
		VoiceSDKSubsystem->SendTranscription(Text, RequestOptions, RequestConfiguration);
	}
}

void UPlatformVoiceService::OnSpeechRequestProgress(const TSharedPtr<FJsonObject> PartialJsonResponse)
{
	//TODO similar code as wit, should extra them to a utilities class
	// The text field of the final response chunk represents the most recent transcription that Wit.ai was able to discern. We pass this to the user
	// registered callback as it can be used to display intermediate partial transcriptions which make the application feel more responsive
	//
	const FString PartialTranscription = PartialJsonResponse->GetStringField(TEXT("text"));

	UE_LOG(LogVoiceSDK, Display, TEXT("PlatformIntegration VoiceService OnSpeechRequestProgress = %s"),
		   *PartialTranscription);

	if (Events != nullptr)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, PartialTranscription]()
		{
			Events->OnPartialTranscription.Broadcast(PartialTranscription);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}
}

void UPlatformVoiceService::OnSpeechRequestComplete(const TSharedPtr<FJsonObject> JsonResponse)
{
	if (Events == nullptr)
	{
		return;
	}
	Events->WitResponse.Reset();
	//TODO similar code as wit, should extra them to a utilities class
	const bool bIsConversionError = !FJsonObjectConverter::JsonObjectToUStruct(
		JsonResponse.ToSharedRef(), &Events->WitResponse);
	if (bIsConversionError)
	{
		const FString message = TEXT("Failed to convert JSON response to UStruct");
		OnRequestError(message, message);
		return;
	}

	UE_LOG(LogVoiceSDK, Display, TEXT("Full transcription received (%s)"), *Events->WitResponse.Text);
	UE_LOG(LogVoiceSDK, Verbose, TEXT("UStruct - Text: %s"), *Events->WitResponse.Text);

	for (const auto& Intent : Events->WitResponse.Intents)
	{
		UE_LOG(LogVoiceSDK, Verbose, TEXT("UStruct - Intent: id (%lld) name (%s) confidence (%f)"), Intent.Id,
			   *Intent.Name, Intent.Confidence);
	}

	for (const auto& Entity : Events->WitResponse.Entities)
	{
		UE_LOG(LogVoiceSDK, Verbose,
			   TEXT(
				   "UStruct - Entity (%s): id (%lld) name (%s) value (%s) confidence (%f) unit (%s) start (%d) end (%d)"
			   ), *Entity.Key,
			   Entity.Value.Id, *Entity.Value.Name, *Entity.Value.Value, Entity.Value.Confidence, *Entity.Value.Unit,
			   Entity.Value.Start, Entity.Value.End);

		UE_LOG(LogVoiceSDK, Verbose, TEXT("UStruct - Entity (%s): normalized value (%s) normalized unit (%s)"),
			   *Entity.Key, *Entity.Value.Normalized.Value,
			   *Entity.Value.Normalized.Unit);
	}

	for (const auto& Trait : Events->WitResponse.Traits)
	{
		UE_LOG(LogVoiceSDK, Verbose, TEXT("UStruct - Trait (%s): id (%lld) value (%s) confidence (%f)"), *Trait.Key,
			   Trait.Value.Id, *Trait.Value.Value,
			   Trait.Value.Confidence);
	}

	FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
	{
			Events->OnFullTranscription.Broadcast(Events->WitResponse.Text);
			Events->OnWitResponse.Broadcast(true, Events->WitResponse);
	}, TStatId(), nullptr, ENamedThreads::GameThread);
}

void UPlatformVoiceService::OnRequestError(const FString ErrorMessage, const FString HumanReadableErrorMessage)
{
	if (Events != nullptr)
	{
		Events->WitResponse.Reset();
		Events->OnWitResponse.Broadcast(false, Events->WitResponse);
		Events->OnWitError.Broadcast(ErrorMessage, HumanReadableErrorMessage);
	}
}

#if WITH_EDITORONLY_DATA

/**
 * Write the captured voice input to a wav file. The output file will be written to the project folder's Saved/BouncedWavFiles folder as
 * Wit/RecordedVoiceInput.wav. This only works with 16-bit samples
 */
void UPlatformVoiceService::WriteRawPCMDataToWavFile(const uint8* RawPCMData, int32 RawPCMDataSize, int32 NumChannels,
                                                     int32 SampleRate)
{
	UE_LOG(LogVoiceSDK, Error, TEXT("PlatformIntegration VoiceService cannot record voice to Wav file"));
	//TODO if we still want to implement this, we will need to ask VoiceSDK C++ to do this for us (save into oculus.)
}

#endif
