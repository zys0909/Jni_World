/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_derry_derry_voicechange_MainActivity */

// xxx.h ---- xxx.c     早期
// xxx.hpp ---- xxx.cpp
// xxx.h ----  xxx.cpp  兼容的，可以的

// xxx.hpp 是头文件而已

#include <fmod.hpp> // TODO 最后一步 FMOD的头文件，必须导入，才能使用功能

#include <string>

#ifndef _Included_com_derry_derry_voicechange_MainActivity
#define _Included_com_derry_derry_voicechange_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
#undef com_example_jni_VoiceActivity_MODE_NORMAL
#define com_example_jni_VoiceActivity_MODE_NORMAL 0L
#undef com_example_jni_VoiceActivity_MODE_LUOLI
#define com_example_jni_VoiceActivity_MODE_LUOLI 1L
#undef com_example_jni_VoiceActivity_MODE_DASHU
#define com_example_jni_VoiceActivity_MODE_DASHU 2L
#undef com_example_jni_VoiceActivity_MODE_JINGSONG
#define com_example_jni_VoiceActivity_MODE_JINGSONG 3L
#undef com_example_jni_VoiceActivity_MODE_GAOGUAI
#define com_example_jni_VoiceActivity_MODE_GAOGUAI 4L
#undef com_example_jni_VoiceActivity_MODE_KONGLING
#define com_example_jni_VoiceActivity_MODE_KONGLING 5L
/*
 * Class:     com_example_jni_VoiceActivity
 * Method:    voiceChangeNative
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_jni_VoiceActivity_voiceChangeNative
  (JNIEnv *, jobject, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
