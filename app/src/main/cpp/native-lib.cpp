#include <jni.h>
#include <string>
#include <unistd.h>

JavaVM *g_VM;
jobject g_obj;

void fuck2(){
    sleep(5);
    JNIEnv *env;

    bool mNeedDetach;
    //获取当前native线程是否有没有被附加到jvm环境中
    int getEnvStat = (*g_VM).GetEnv( (void **) &env,JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        //如果没有， 主动附加到jvm环境中，获取到env
        if ((*g_VM).AttachCurrentThread( &env, NULL) != 0) {
            return;
        }
        mNeedDetach = JNI_TRUE;
    }

    //通过全局变量g_obj 获取到要回调的类
    jclass javaClass = (*env).GetObjectClass( g_obj);
    if (javaClass == nullptr) {
        (*g_VM).DetachCurrentThread();
        return;
    }
    //获取要回调的方法ID
    jmethodID javaCallbackId = (*env).GetMethodID( javaClass,
                                                   "fuck", "(Ljava/lang/String;)V");
    if (javaCallbackId == nullptr) {
        return;
    }
    //执行回调
    (*env).CallVoidMethod(g_obj, javaCallbackId,env->NewStringUTF("gatrgfhga") );

    //释放当.程
    if(mNeedDetach) {
        (*g_VM).DetachCurrentThread();
    }
    env = nullptr;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Hello from C++";
//JavaVM是虚拟机在JNI中的表示，等下再其他线程回调java层需要用到
    (*env).GetJavaVM( &g_VM);
    // 生成一个全局引用保留下来，以便回调
    g_obj = (*env).NewGlobalRef( obj);

    pthread_t thread1;
    char *message1 = "Thread 1";
    pthread_create(&thread1, NULL, reinterpret_cast<void *(*)(void *)>(fuck2), (void *) message1);

    jclass fuck;
    fuck = env->FindClass("com/example/myapplication/MainActivity");
    jmethodID  mid = env->GetMethodID(fuck,"fuck", "()V");
    env->CallVoidMethod(obj,mid );


    jmethodID  mid2 = env->GetMethodID(fuck,"fuck", "(Ljava/lang/String;)V");
    env->CallVoidMethod(obj,mid2,env->NewStringUTF("gaga") );

    return env->NewStringUTF(hello.c_str());
}