
#include <string>
#include <android/log.h>
#include <unistd.h>
#include "com_example_jni_VoiceActivity.h"

#define TAG "测试TAG_jni"
#define Log_D(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_JniTest_stringFromJNI(JNIEnv *env, jobject thiz) {
    string hello = "欢迎来Jni的世界";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniTest_testArrayAction(JNIEnv *env,
                                             jobject thiz,
                                             jint count,
                                             jstring text_info,
                                             jintArray ints,
                                             jobjectArray str_arr) {
    //一、基本数据类型
    int countInt = count;
    Log_D("参数一：count = %d\n", countInt);

    //二、引用类型
    const char *textInfo = env->GetStringUTFChars(text_info, NULL);
    Log_D("参数二：textInfo = %s\n", textInfo);

    //三、基本类型数组
    int *int_arr = env->GetIntArrayElements(ints, NULL);
    //数组长度
    int intSize = env->GetArrayLength(ints);

    for (int i = 0; i < intSize; ++i) {
        *(int_arr + i) += 100;
        Log_D("参数三：arr[%d] = %d\n", i, *(int_arr + i));
    }
    /**
     * 0:           刷新Java层数组，并释放C++层数组；
     * JNI_COMMIT   :只提交，只刷新Java层属猪，不释放C++数组
     * JNI_ABORT    ：只是放C++层数组
     */
    env->ReleaseIntArrayElements(ints, int_arr, 0);

    //四、引用类型数组
    int strSize = env->GetArrayLength(str_arr);
    for (int i = 0; i < strSize; ++i) {
        auto jStr = static_cast<jstring>(env->GetObjectArrayElement(str_arr, i));
        const char *strElement = env->GetStringUTFChars(jStr, NULL);
        Log_D("参数四：String数组 %d  --》 %s\n", i, strElement);
        env->ReleaseStringUTFChars(jStr, strElement);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniTest_putObject(JNIEnv *env,
                                       jobject thiz,
                                       jobject student,
                                       jstring str) {

    const char *strValue = env->GetStringUTFChars(str, NULL);

    Log_D("str = %s\n", strValue);
    //1. 寻找类
    //jclass studentClass = env->FindClass("com/example/jni/JniTest");
    jclass studentClass = env->GetObjectClass(student);

    //2.获取Student中的函数
    jmethodID setName = env->GetMethodID(studentClass, "setName", "(Ljava/lang/String;)V");
    jmethodID getName = env->GetMethodID(studentClass, "getName", "()Ljava/lang/String;");
    jmethodID showInfo = env->GetStaticMethodID(studentClass, "showInfo", "(Ljava/lang/String;)V");

    //3调用SetName
    jstring nameValue = env->NewStringUTF("张无忌");
    env->CallVoidMethod(student, setName, nameValue);

    //调用getName
    jstring getNameResult = static_cast<jstring>(env->CallObjectMethod(student, getName));
    const char *getNameValue = env->GetStringUTFChars(getNameResult, NULL);
    Log_D("调用getName方法，结果是 : %s\n", getNameValue);

    //调用静态方法
    jstring infoValue = env->NewStringUTF("在Jni中 调用静态方法");
    env->CallStaticVoidMethod(studentClass, showInfo, infoValue);


}

using namespace FMOD;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_VoiceActivity_voiceChangeNative(JNIEnv *env,
                                                     jobject thiz,
                                                     jint mode_normal,
                                                     jstring path) {

    char *content_ = "默认 播放完毕";
    const char *path_ = env->GetStringUTFChars(path, NULL);

    //音效引擎系统 指针
    System *system = 0;
    //声音
    Sound *sound = 0;

    //音轨
    Channel *channel = 0;

    //数字信号
    DSP *dsp = 0;

    //创建系统
    System_Create(&system);
    //初始化系统
    system->init(32, FMOD_INIT_NORMAL, 0);

    //创建声音
    system->createSound(path_, FMOD_DEFAULT, 0, &sound);

    //播放声音
    system->playSound(sound, 0, false, &channel);


    switch (mode_normal) {
        case com_example_jni_VoiceActivity_MODE_NORMAL:
            content_ = "原声 播放完毕";
            break;
        case com_example_jni_VoiceActivity_MODE_LUOLI:
            content_ = "萝莉音 播放完毕";
            // 音调高 -- 萝莉 2.0
            // 1.创建DSP类型的Pitch 音调条件
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            // 2.设置Pitch音调调节2.0
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0f);
            // 3.添加音效进去 音轨
            channel->addDSP(0, dsp);
            break;
        case com_example_jni_VoiceActivity_MODE_DASHU:
            content_ = "大叔音 播放完毕";
            // 音调低 -- 大叔 0.7
            // 1.创建DSP类型的Pitch 音调条件
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            // 2.设置Pitch音调调节2.0
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);
            // 3.添加音效进去 音轨
            channel->addDSP(0, dsp);
            break;
        case com_example_jni_VoiceActivity_MODE_JINGSONG:
            content_ = "惊悚音 播放完毕";

            // 从音轨拿 当前 频率
            float mFrequency;
            channel->getFrequency(&mFrequency);

            // 修改频率
            channel->setFrequency(mFrequency * 1.5f); // 频率加快  小黄人的声音
            break;
        case com_example_jni_VoiceActivity_MODE_GAOGUAI:
            content_ = "搞怪音 播放完毕";

            // 惊悚音效：特点： 很多声音的拼接

            // TODO 音调低
            // 音调低 -- 大叔 0.7
            // 1.创建DSP类型的Pitch 音调条件
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            // 2.设置Pitch音调调节2.0
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7f);
            // 3.添加音效进去 音轨
            channel->addDSP(0, dsp); // 第一个音轨

            // TODO 搞点回声
            // 回音 ECHO
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音 延时    to 5000.  Default = 500.
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); // 回音 衰减度 Default = 50   0 完全衰减了
            channel->addDSP(1,dsp); // 第二个音轨

            // TODO 颤抖
            // Tremolo 颤抖音 正常5    非常颤抖  20
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 20); // 非常颤抖
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8f); // ？？？
            channel->addDSP(2, dsp); // 第三个音轨
            break;
        case com_example_jni_VoiceActivity_MODE_KONGLING:
            content_ = "空灵音 播放完毕";
            // 回音 ECHO
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音 延时    to 5000.  Default = 500.
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); // 回音 衰减度 Default = 50   0 完全衰减了
            channel->addDSP(0,dsp);
            break;
    }

    //等待播放完毕，回收资源

    bool isPlayer = true;

    while (isPlayer) {
        channel->isPlaying(&isPlayer);
        usleep(1000 * 1000);
    }
    //释放
    sound->release();
    system->release();
    system->close();
    env->ReleaseStringUTFChars(path, path_);

    // 告知Java播放完毕
    jclass mainCls = env->GetObjectClass(thiz);
    jmethodID endMethod = env->GetMethodID(mainCls, "playerEnd", "(Ljava/lang/String;)V");
    jstring value = env->NewStringUTF(content_);
    env->CallVoidMethod(thiz, endMethod, value);

}