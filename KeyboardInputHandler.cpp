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

JNIEXPORT void JNICALL Java_de_lojaw_jni_KeyboardInputHandler_moveMouse(JNIEnv* env, jobject obj, jint x, jint y, jboolean isAbsolute) {
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    if (isAbsolute) {
        input.mi.dwFlags |= MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = (x * 65535) / GetSystemMetrics(SM_CXSCREEN); // Normalisieren der X-Koordinate
        input.mi.dy = (y * 65535) / GetSystemMetrics(SM_CYSCREEN); // Normalisieren der Y-Koordinate
    }
    SendInput(1, &input, sizeof(INPUT));
}

JNIEXPORT jintArray JNICALL Java_de_lojaw_jni_KeyboardInputHandler_getMousePosition(JNIEnv* env, jobject obj) {
    POINT p;
    if (GetCursorPos(&p)) {
        jintArray mousePos = env->NewIntArray(2);
        jint pos[2] = { p.x, p.y };
        env->SetIntArrayRegion(mousePos, 0, 2, pos);
        return mousePos;
    }
    else {
        // Handle error, zum Beispiel Rückgabe eines leeren Arrays
        return env->NewIntArray(0);
    }
}

JNIEXPORT void JNICALL Java_de_lojaw_jni_KeyboardInputHandler_mouseClick(JNIEnv* env, jobject obj, jint button, jint delay) {
    INPUT input[2] = {}; // Array für Drücken und Loslassen
    ZeroMemory(&input, sizeof(input));

    // Maustaste drücken
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = (button == 0 ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);

    // Maustaste loslassen
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = (button == 0 ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);

    SendInput(1, &input[0], sizeof(INPUT)); // Maustaste drücken
    Sleep(delay); // Verzögerung zwischen Drücken und Loslassen
    SendInput(1, &input[1], sizeof(INPUT)); // Maustaste loslassen
}




