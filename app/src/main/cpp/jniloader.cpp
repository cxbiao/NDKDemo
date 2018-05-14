#include <jni.h>
#define LOG_TAG "JNI_OnLoad"
#include "log.h"
#include "utils.h"
#include "JNIHelp.h"

fields gFields;

int register_JNIBasic(JavaVM* vm ,JNIEnv* env);
int regiser_JNICallBack(JavaVM* vm ,JNIEnv* env);
jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!");
        return result;
    }
    LOGD("JNI_OnLoad!");
    gFields.vm=vm;
    FIND_CLASS(env,gFields.JniBasic.clazz,"com/bryan/ndk/JniBasic", true);
    GET_METHOD_ID(env,gFields.JniBasic.hello,gFields.JniBasic.clazz,"hello","()V");
    GET_METHOD_ID(env,gFields.JniBasic.Add,gFields.JniBasic.clazz,"Add","(II)I");
    GET_METHOD_ID(env,gFields.JniBasic.printStr,gFields.JniBasic.clazz,"printStr","(Ljava/lang/String;)V");
    GET_STATIC_METHOD_ID(env,gFields.JniBasic.demo,gFields.JniBasic.clazz,"demo","()V");

    FIND_CLASS(env,gFields.JniCallBack.clazz,"com/bryan/ndk/JniCallBack", true);
    GET_METHOD_ID(env,gFields.JniCallBack.onNativeCallback,gFields.JniCallBack.clazz,"onNativeCallback","(I)V");

    FIND_CLASS(env,gFields.MainActivity.clazz,"com/bryan/MainActivity", true);
    GET_METHOD_ID(env,gFields.MainActivity.hello,gFields.MainActivity.clazz,"hello","()V");


    register_JNIBasic(vm,env);
    regiser_JNICallBack(vm,env);
    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!");
        return;
    }
    LOGD("JNI_OnUnload!");

    env->DeleteGlobalRef(gFields.JniBasic.clazz);
    env->DeleteGlobalRef(gFields.JniCallBack.clazz);
    env->DeleteGlobalRef(gFields.MainActivity.clazz);

}

