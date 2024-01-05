#include "pch.h"
#include <jni.h>
#include "de_lojaw_jni_KeyboardInputHandler.h"
#include <Windows.h>

JNIEXPORT void JNICALL Java_de_lojaw_jni_KeyboardInputHandler_sendSignal(JNIEnv* env, jobject obj) {
    // Implementieren Sie hier den Code für die sendSignal-Methode
    // Dies ist nur ein einfaches Beispiel:
    MessageBoxA(NULL, "Signal wurde gesendet!", "SignalHandler", MB_OK);
}

JNIEXPORT void JNICALL Java_de_lojaw_jni_KeyboardInputHandler_pressKey(JNIEnv* env, jobject obj, jchar key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScan(key);
    SendInput(1, &input, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_de_lojaw_jni_KeyboardInputHandler_releaseKey(JNIEnv* env, jobject obj, jchar key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScan(key);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

