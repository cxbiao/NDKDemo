#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define LOG_TAG "nativeProcess"

#include "log.h"
#include "JNIHelp.h"
#include "utils.h"




JavaVM * gJavaVM;
jobject  gJavaObj;
static volatile int gIsThreadExit = 0;


static void* native_thread_exec(void *arg) {

	JNIEnv *env;

	//从全局的JavaVM中获取到环境变量
	//gFields.vm->AttachCurrentThread(&env, NULL);

    ATTACH_HELPER(gFields.vm,&env);



    LOGI("native_thread_exec loop enter");

	int count = 0;

	//线程循环
	while(!gIsThreadExit) {

		//回调Java层的函数
		env->CallVoidMethod(gFields.JniCallBack.instance,gFields.JniCallBack.onNativeCallback,count++);

		//休眠1秒
		sleep(1);
        //usleep(1000000); //微秒
	}

	//gFields.vm->DetachCurrentThread();

    LOGI("native_thread_exec loop leave");
    return  NULL;
}




/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeInitilize
 * Signature: ()V
 */
static void  init(JNIEnv *env, jobject obj){
	//注意，直接通过定义全局的JNIEnv和jobject变量，在此保存env和thiz的值是不可以在线程中使用的

	//线程不允许共用env环境变量，但是JavaVM指针是整个jvm共用的，所以可以通过下面的方法保存JavaVM指针，在线程中使用
	//env->GetJavaVM(&gJavaVM);

	//同理，jobject变量也不允许在线程中共用，因此需要创建全局的jobject对象在线程中访问该对象
	gFields.JniCallBack.instance = env->NewGlobalRef(obj);
}

/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeThreadStart
 * Signature: ()V
 */
static void  start(JNIEnv *env, jobject obj){
	gIsThreadExit = 0;

	//通过pthread库创建线程
	pthread_t threadId;
	if( pthread_create(&threadId,NULL,native_thread_exec,NULL) != 0 ) {
        LOGI("native_thread_start pthread_create fail !");
	   return;
	}

    LOGI("native_thread_start success");
}

/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeThreadStop
 * Signature: ()V
 */
static void  stop(JNIEnv *env, jobject obj){
	gIsThreadExit = 1;
    LOGI("native_thread_stop success");
}

static const JNINativeMethod gMethods[] = {
		{"nativeInitilize", "()V", (void *)init},
		{"nativeThreadStart", "()V", (void *)start},
		{"nativeThreadStop", "()V", (void*)stop}


};

int regiser_JNICallBack(JavaVM* vm ,JNIEnv* env){
	if (gFields.JniCallBack.clazz == NULL) {
		LOGE("Can't find com/bryan/ndk/JniCallBack");
		return -1;
	}
	if (env->RegisterNatives(gFields.JniCallBack.clazz,gMethods,NELEM(gMethods)) !=JNI_OK) {
		LOGE("RegisterNatives failed for  %s\n","JniCallBack");
		return JNI_ERR;
	}
	LOGI("Register JniCallBack success");
	return JNI_OK;
}

