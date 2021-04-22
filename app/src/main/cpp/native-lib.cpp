

#include "jni_common.h"

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
    const char *textInfo = env->GetStringUTFChars(text_info, nullptr);
    Log_D("参数二：textInfo = %s\n", textInfo);

    //三、基本类型数组
    int *int_arr = env->GetIntArrayElements(ints, nullptr);
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
        const char *strElement = env->GetStringUTFChars(jStr, nullptr);
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

    const char *strValue = env->GetStringUTFChars(str, nullptr);

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
    const char *getNameValue = env->GetStringUTFChars(getNameResult, nullptr);
    Log_D("调用getName方法，结果是 : %s\n", getNameValue);

    //调用静态方法
    jstring infoValue = env->NewStringUTF("在Jni中 调用静态方法");
    env->CallStaticVoidMethod(studentClass, showInfo, infoValue);


}

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *javaVm, void *) {


    return JNI_VERSION_1_6;
}