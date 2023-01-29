#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Hello from C++";

    jclass fuck;
    fuck = env->FindClass("com/example/myapplication/MainActivity");
    jmethodID  mid = env->GetMethodID(fuck,"fuck", "()V");
    env->CallVoidMethod(obj,mid );


    jmethodID  mid2 = env->GetMethodID(fuck,"fuck", "(Ljava/lang/String;)V");
    env->CallVoidMethod(obj,mid2,env->NewStringUTF("gaga") );

    return env->NewStringUTF(hello.c_str());
}