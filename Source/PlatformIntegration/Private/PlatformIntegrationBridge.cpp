/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "PlatformIntegrationBridge.h"
#include "PlatformIntegrationPrivatePCH.h"
#include "Subsystem/PlatformIntegrationSubsystem.h"

#if PLATFORM_ANDROID
#include <jni.h>
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

#define CREATE_PROXY_FOR_JAVA_METHOD(name, signature) \
if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
	name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
	check(name != NULL); \
} else { \
	check(0); \
}

#define DECLARE_PROXY_FOR_JAVA_METHOD(name) \
static jmethodID name = NULL;

DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInput);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputWithRequestOptions);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediately);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediatelyWithRequestOptions);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateVoiceInput);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateAndAbortRequest);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscription);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscriptionWithRequestOptions);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsSupported);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceInputActive);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceStreamingActive);
DECLARE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsRequestInProgress);

void UPlatformIntegrationBridge::SetupBridge()
{
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInput, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputWithRequestOptions, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediately, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediatelyWithRequestOptions, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateVoiceInput, "(Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateAndAbortRequest, "(Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscription, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscriptionWithRequestOptions, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsSupported, "(Ljava/lang/String;)Z");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceInputActive, "(Ljava/lang/String;)Z");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceStreamingActive, "(Ljava/lang/String;)Z");
	CREATE_PROXY_FOR_JAVA_METHOD(AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsRequestInProgress, "(Ljava/lang/String;)Z");
}
#undef DECLARE_PROXY_FOR_JAVA_METHOD
#undef CREATE_PROXY_FOR_JAVA_METHOD

#endif

UPlatformIntegrationBridge::UPlatformIntegrationBridge()
	: Super()
{
}

void UPlatformIntegrationBridge::ActivateVoiceInput(const FString& Tag, const FString& Token, const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: ActivateVoiceInput, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInput, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}

void UPlatformIntegrationBridge::ActivateVoiceInput(const FString& RequestOptions, const FString& Tag,
                                                    const FString& Token, const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: ActivateVoiceInput with RequestOptions, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringRequestOptions = Env->NewStringUTF(TCHAR_TO_UTF8(*RequestOptions));
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputWithRequestOptions, JavaStringRequestOptions, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}


void UPlatformIntegrationBridge::ActivateVoiceInputImmediately(const FString& Tag, const FString& Token,
                                                               const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: ActivateVoiceInputImmediately, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		
		// Then we call the method, we the Java String parameter
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediately, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}

void UPlatformIntegrationBridge::ActivateVoiceInputImmediately(const FString& RequestOptions, const FString& Tag,
                                                               const FString& Token,
                                                               const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: ActivateVoiceInputImmediately with RequestOptions, Tag=%s"),
	       *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringRequestOptions = Env->NewStringUTF(TCHAR_TO_UTF8(*RequestOptions));
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		
		// Then we call the method, we the Java String parameter
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediatelyWithRequestOptions, JavaStringRequestOptions, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}

static void SendTranscription(const FString& Text, const FString& RequestOptions, const FString& Tag,
                              const FString& Token,
                              const FString& SDKVersion);

void UPlatformIntegrationBridge::DeactivateVoiceInput(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: DeactivateVoiceInput, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateVoiceInput, JavaStringTag);
	}
#endif
}

void UPlatformIntegrationBridge::DeactivateAndAbortRequest(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: DeactivateAndAbortRequest, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_DeactivateAndAbortRequest, JavaStringTag);
	}
#endif
}

void UPlatformIntegrationBridge::SendTranscription(const FString& Text, const FString& Tag, const FString& Token,
                                                   const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: SendTranscription, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringText = Env->NewStringUTF(TCHAR_TO_UTF8(*Text));
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscription, JavaStringText, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}

void UPlatformIntegrationBridge::SendTranscription(const FString& Text, const FString& RequestOptions,
                                                   const FString& Tag, const FString& Token,
                                                   const FString& SDKVersion)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: SendTranscription with RequestOptions, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringText = Env->NewStringUTF(TCHAR_TO_UTF8(*Text));
		jstring JavaStringRequestOptions = Env->NewStringUTF(TCHAR_TO_UTF8(*RequestOptions));
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jstring JavaStringToken = Env->NewStringUTF(TCHAR_TO_UTF8(*Token));
		jstring JavaStringSDKVersion = Env->NewStringUTF(TCHAR_TO_UTF8(*SDKVersion));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscriptionWithRequestOptions, JavaStringText, JavaStringRequestOptions, JavaStringTag, JavaStringToken, JavaStringSDKVersion);
	}
#endif
}

bool UPlatformIntegrationBridge::IsSupported(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: IsSupported, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jboolean JavaBoolean = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsSupported, JavaStringTag);
		return JavaBoolean == JNI_TRUE;
	}
#endif
	return true;
}

bool UPlatformIntegrationBridge::IsVoiceInputActive(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: IsVoiceInputActive, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jboolean JavaBoolean = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceInputActive, JavaStringTag);
		return JavaBoolean == JNI_TRUE;
	}
#endif
	return false;
}

bool UPlatformIntegrationBridge::IsVoiceStreamingActive(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: IsVoiceStreamingActive, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jboolean JavaBoolean = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsVoiceStreamingActive, JavaStringTag);
		return JavaBoolean == JNI_TRUE;
	}
#endif
	return false;
}

bool UPlatformIntegrationBridge::IsRequestInProgress(const FString& Tag)
{
	UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: IsRequestInProgress, Tag=%s"), *Tag);
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jstring JavaStringTag = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		jboolean JavaBoolean = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_Oculus_Assistant_VoiceSDK_IsRequestInProgress, JavaStringTag);
		return JavaBoolean == JNI_TRUE;
	}
#endif
	return false;
}

// setup callbacks
#if PLATFORM_ANDROID
extern "C"
{
	JNIEXPORT void JNICALL Java_com_oculus_assistant_api_voicesdk_immersivevoicecommands_ue_UEIVCEventsListener_nativeOnResponse(JNIEnv * jni, jclass clazz, jstring response)
	{
		const char* charsId = jni->GetStringUTFChars(response, 0);
		FString OurString = FString(UTF8_TO_TCHAR(charsId));
		jni->ReleaseStringUTFChars(response, charsId);
		
		UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: nativeOnResponse: %s"), *OurString);

		if (OurString.Len() < 1)
		{
			UE_LOG(LogPlatformIntegration, Warning, TEXT("Bridge: nativeOnResponse is empty will ignore and wait for full response."));
			return;
		}

		TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(OurString);
		
		//TODO below, similar code as wit, should extra them to a utilities class
		const bool bIsDeserializationError = !FJsonSerializer::Deserialize(Reader, Json);
		if (bIsDeserializationError)
		{
			UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
			VoiceSDKSubsystem->OnRequestError("Bridge: Response deserialization to JSON failed");
			return;
		}
		
		const bool bIsValidPartialTranscription = Json->HasField("text");
		if (!bIsValidPartialTranscription)
		{
			return;
		}
		// Then call Subsystem, which is inspired by the Unreal Building Facebook plugin.
		UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
		VoiceSDKSubsystem->OnRequestComplete(Json);
	}
	JNIEXPORT void JNICALL Java_com_oculus_assistant_api_voicesdk_immersivevoicecommands_ue_UEIVCEventsListener_nativeOnPartialResponse(JNIEnv * jni, jclass clazz, jstring response)
	{
		const char* charsId = jni->GetStringUTFChars(response, 0);
		FString OurString = FString(UTF8_TO_TCHAR(charsId));
		jni->ReleaseStringUTFChars(response, charsId);
		
		UE_LOG(LogPlatformIntegration, Display, TEXT("Bridge: nativeOnPartialResponse: %s"), *OurString);

		//TODO below, similar code as wit, should extra them to a utilities class
		TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(OurString);
		
		const bool bIsDeserializationError = !FJsonSerializer::Deserialize(Reader, Json);
		if (bIsDeserializationError)
		{
			return;
		}
		
		const bool bIsValidPartialTranscription = Json->HasField("text");
		if (!bIsValidPartialTranscription)
		{
			return;
		}
		
		UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
		VoiceSDKSubsystem->OnRequestProgress(Json);
	}
	JNIEXPORT void JNICALL Java_com_oculus_assistant_api_voicesdk_immersivevoicecommands_ue_UEIVCEventsListener_nativeOnError(JNIEnv * jni, jclass clazz, jstring s, jstring s1, jstring s2)
	{
		const char* charsId = jni->GetStringUTFChars(s, 0);
		FString string = FString(UTF8_TO_TCHAR(charsId));
		jni->ReleaseStringUTFChars(s, charsId);
		
		const char* charsId1 = jni->GetStringUTFChars(s1, 0);
		FString string1 = FString(UTF8_TO_TCHAR(charsId1));
		jni->ReleaseStringUTFChars(s1, charsId1);
		
		const char* charsId2 = jni->GetStringUTFChars(s2, 0);
		FString string2 = FString(UTF8_TO_TCHAR(charsId2));
		jni->ReleaseStringUTFChars(s2, charsId2);
		
		UE_LOG(LogPlatformIntegration, Error, TEXT("Bridge: nativeOnError: %s, %s, %s"), *string, *string1, *string2);
		
		UPlatformIntegrationSubsystem* VoiceSDKSubsystem = GEngine->GetEngineSubsystem<UPlatformIntegrationSubsystem>();
		VoiceSDKSubsystem->OnRequestError(FString::Printf(TEXT("%s, %s, %s"),  *string, *string1, *string2));//TODO error message might be a json.
	}
}
#endif
