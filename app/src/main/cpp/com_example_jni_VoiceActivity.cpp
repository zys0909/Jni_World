//
// Created by admin on 2021/4/22.
//

#include "com_example_jni_VoiceActivity.h"

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
            channel->addDSP(1, dsp); // 第二个音轨

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
            channel->addDSP(0, dsp);
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
