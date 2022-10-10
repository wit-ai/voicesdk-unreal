/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.oculus.assistant.api.voicesdk.immersivevoicecommands.ue;

import android.app.Activity;
import android.app.FragmentManager;
import android.util.Log;

import com.oculus.assistant.api.unity.immersivevoicecommands.UnityIVCServiceFragment;
import com.oculus.assistant.api.voicesdk.immersivevoicecommands.IVCSDK;
import com.oculus.assistant.api.voicesdk.immersivevoicecommands.WitRuntimeConfiguration;

public class UEIVCHelper {
    private static final String TAG = UEIVCHelper.class.getSimpleName();

    public static void activateVoiceInput(final Activity activity, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "Activate: Current activity == " + activity + ", tag == " + tag);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activate();
                    Log.d(TAG, "8. Activated.");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInput failed with exception " + e.getMessage());
        }
    }

    public static void activateVoiceInput(final Activity activity, final String requestOptions, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "Activate with requestOptions: Current activity == " + activity + ", tag == " + tag + ", requestOptions == " + requestOptions);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activate(requestOptions);
                    Log.d(TAG, "8. Activated with requestOptions.");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInput failed with exception " + e.getMessage());
        }
    }

    public static void activateVoiceInputImmediately(final Activity activity, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "activateVoiceInputImmediately: Current activity == " + activity + ", tag == " + tag);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activateImmediately();
                    Log.d(TAG, "8. Activated Immediately");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediately failed with exception " + e.getMessage());
        }
    }

    public static void activateVoiceInputImmediately(final Activity activity, final String requestOptions, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "activateVoiceInputImmediately with requestOptions : Current activity == " + activity + ", tag == " + tag + ", requestOptions == " + requestOptions);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activateImmediately(requestOptions);
                    Log.d(TAG, "8. Activated Immediately with requestOptions.");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_ActivateVoiceInputImmediately failed with exception " + e.getMessage());
        }
    }

    public static void deactivateVoiceInput(Activity activity, String tag) {
        Log.d(TAG, "deactivateVoiceInput: Current activity == " + activity + ", tag == " + tag);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will deactivateVoiceInput.");
            IVCSDK sdk = fragment.getService();
            sdk.deactivate();
            return;
        }
        Log.d(TAG, "0. No existing Fragment. So No need to deactivateVoiceInput.");
    }

    public static void deactivateAndAbortRequest(Activity activity, String tag) {
        Log.d(TAG, "deactivateAndAbortRequest: Current activity == " + activity + ", tag == " + tag);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will deactivateAndAbortRequest.");
            IVCSDK sdk = fragment.getService();
            sdk.deactivateAndAbortRequest();
            return;
        }
        Log.d(TAG, "0. No existing Fragment. So No need to deactivateAndAbortRequest.");
    }

    public static void sendTranscription(final Activity activity, final String text, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "sendTranscription: Current activity == " + activity + "text == " + text + ", tag == " + tag);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activate(text, "");
                    Log.d(TAG, "8. sendTranscription");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscription failed with exception " + e.getMessage());
        }
    }

    public static void sendTranscription(final Activity activity, final String text, final String requestOptions, final String tag, final String token, final String clientSDKVersion) {
        Log.d(TAG, "sendTranscription with requestOptions: Current activity == " + activity + "text == " + text + ", tag == " + tag + ", requestOptions == " + requestOptions);
        try {
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    UnityIVCServiceFragment serviceFragment = UEIVCHelper.getIVCServiceFragment(activity, tag, token, clientSDKVersion);

                    IVCSDK sdk = serviceFragment.getService();
                    sdk.activate(text, requestOptions);
                    Log.d(TAG, "8. sendTranscription with requestOptions.");
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "AndroidThunkJava_Oculus_Assistant_VoiceSDK_SendTranscription failed with exception " + e.getMessage());
        }
    }

    public static boolean IsSupported(Activity activity, String tag) {
        Log.d(TAG, "IsSupported: Current activity == " + activity);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will check if the service is active.");
            IVCSDK sdk = fragment.getService();
            return sdk.isSupported();
        }
        Log.d(TAG, "0. No existing Fragment. So just return the default value -- True.");
        return true;
    }


    public static boolean IsVoiceInputActive(Activity activity, String tag) {
        Log.d(TAG, "IsVoiceInputActive: Current activity == " + activity + ", tag == " + tag);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will check if the service is active.");
            IVCSDK sdk = fragment.getService();
            return sdk.isActive();//TODO IsVoiceInputActive=> isActive This may wrong. will double check to make sure UE and Unity aligned.
        }
        Log.d(TAG, "0. No existing Fragment. So NO active Voice Input.");
        return false;
    }

    public static boolean IsRequestInProgress(Activity activity, String tag) {
        Log.d(TAG, "IsRequestInProgress: Current activity == " + activity);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will check if the service's request active.");
            IVCSDK sdk = fragment.getService();
            return sdk.isRequestActive();//TODO IsRequestInProgress => isRequestActive This may wrong. will double check to make sure UE and Unity aligned.
        }
        Log.d(TAG, "0. No existing Fragment. So NO request is active");
        return false;
    }

    public static boolean IsVoiceStreamingActive(Activity activity, String tag) {
        Log.d(TAG, "IsVoiceStreamingActive: Current activity == " + activity);
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will check if the service's Mic is active.");
            IVCSDK sdk = fragment.getService();
            return sdk.isMicActive();//TODO IsVoiceStreamingActive => isMicActive This may wrong. will double check to make sure UE and Unity aligned.
        }
        Log.d(TAG, "0. No existing Fragment. So Mic is NOT active.");
        return false;
    }

    public static UnityIVCServiceFragment getIVCServiceFragment(Activity activity, String tag, String token, String clientSDKVersion) {
        final FragmentManager fragmentManager = activity.getFragmentManager();
        UnityIVCServiceFragment fragment =
                (UnityIVCServiceFragment) fragmentManager.findFragmentByTag(tag);
        if (null != fragment) {
            Log.d(TAG, "0. Found an existing Fragment, will reuse it.");
            return fragment;
        }
        fragment = UnityIVCServiceFragment.createAndAttach(activity, tag, clientSDKVersion);
        Log.d(TAG, "1. Created and attached Activity-");
        IVCSDK sdk = fragment.getService();
        Log.d(TAG, "2. Got the IVC Service");
        sdk.connect();
        Log.d(TAG, "3. Connected to Message Receiver");
        WitRuntimeConfiguration config = new WitRuntimeConfiguration();
        Log.d(TAG, "4. Construct RuntimeConfig");
        config.witConfiguration.clientAccessToken = token;
        Log.d(TAG, "5. Setup AccessToken");
        sdk.setRuntimeConfig(config);
        Log.d(TAG, "6. Set RumtimeConfig");
        sdk.setListener(new UEIVCEventsListener());
        Log.d(TAG, "7. Add IVC Event Listener");
        return fragment;
    }
}
