/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.oculus.assistant.api.voicesdk.immersivevoicecommands.ue;

import android.util.Log;

import com.oculus.assistant.api.voicesdk.immersivevoicecommands.IVCEventsListener;

public class UEIVCEventsListener implements IVCEventsListener {
    private static final String TAG = UEIVCEventsListener.class.getSimpleName();

    public native void nativeOnPartialResponse(String s);

    public native void nativeOnResponse(String s);

    public native void nativeOnError(String s, String s1, String s2);

    @Override
    public void onPartialResponse(String s) {
        Log.d(TAG, "onPartialResponse=" + s);
        nativeOnPartialResponse(s);
    }

    @Override
    public void onResponse(String s) {
        Log.d(TAG, "onResponse=" + s);
        nativeOnResponse(s);
    }

    @Override
    public void onError(String s, String s1, String s2) {
        Log.d(TAG, "onError=" + s + ", " + s1 + ", " + s2);

        nativeOnError(s, s1, s2);
    }

    @Override
    public void onAborted() {
        Log.d(TAG, "onAborted");

    }

    @Override
    public void onRequestCompleted() {
        Log.d(TAG, "onRequestCompleted");

    }

    @Override
    public void onMicLevelChanged(float v) {
        Log.d(TAG, "onMicLevelChanged=" + v);

    }

    @Override
    public void onRequestCreated() {
        Log.d(TAG, "onRequestCreated");

    }

    @Override
    public void onStartListening() {
        Log.d(TAG, "onStartListening");

    }

    @Override
    public void onStoppedListening(int i) {
        Log.d(TAG, "onStoppedListening=" + i);

    }

    @Override
    public void onMicDataSent() {
        Log.d(TAG, "onMicDataSent");

    }

    @Override
    public void onMinimumWakeThresholdHit() {
        Log.d(TAG, "onMinimumWakeThresholdHit");

    }

    @Override
    public void onPartialTranscription(String s) {
        Log.d(TAG, "onPartialTranscription=" + s);

    }

    @Override
    public void onFullTranscription(String s) {
        Log.d(TAG, "onFullTranscription=" + s);

    }

    @Override
    public void onServiceNotAvailable(String s, String s1) {
        Log.d(TAG, "onServiceNotAvailable=" + s + ", " + s1);

    }
}
