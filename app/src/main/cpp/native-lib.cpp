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

    return env->NewStringUTF(hello.c_str());
}