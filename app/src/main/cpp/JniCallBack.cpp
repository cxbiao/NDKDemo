#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "com_bryan_ndk_JniCallBack.h"
#include <android/log.h>
#define LOG_TAG "nativeProcess"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)



JavaVM * gJavaVM;
jobject  gJavaObj;
static volatile int gIsThreadExit = 0;

static void* native_thread_exec(void *arg) {

	JNIEnv *env;

	//从全局的JavaVM中获取到环境变量
	gJavaVM->AttachCurrentThread(&env, NULL);

	//获取Java层对应的类
	jclass javaClass = env->GetObjectClass(gJavaObj);
	if( javaClass == NULL ) {
		LOG("Fail to find javaClass");
		return 0;
	}

	//获取Java层被回调的函数
	jmethodID javaCallback = env->GetMethodID(javaClass,"onNativeCallback","(I)V");
	if( javaCallback == NULL) {
		LOG("Fail to find method onNativeCallback");
		return 0;
	}

	LOG("native_thread_exec loop enter");

	int count = 0;

	//线程循环
	while(!gIsThreadExit) {

		//回调Java层的函数
		env->CallVoidMethod(gJavaObj,javaCallback,count++);

		//休眠1秒
		sleep(1);
	}

	gJavaVM->DetachCurrentThread();

	LOG("native_thread_exec loop leave");
}


/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeInitilize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_JniCallBack_nativeInitilize(JNIEnv *env, jobject obj){
	//注意，直接通过定义全局的JNIEnv和jobject变量，在此保存env和thiz的值是不可以在线程中使用的

	//线程不允许共用env环境变量，但是JavaVM指针是整个jvm共用的，所以可以通过下面的方法保存JavaVM指针，在线程中使用
	env->GetJavaVM(&gJavaVM);

	//同理，jobject变量也不允许在线程中共用，因此需要创建全局的jobject对象在线程中访问该对象
	gJavaObj = env->NewGlobalRef(obj);
}

/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeThreadStart
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_JniCallBack_nativeThreadStart(JNIEnv *env, jobject obj){
	gIsThreadExit = 0;

	//通过pthread库创建线程
	pthread_t threadId;
	if( pthread_create(&threadId,NULL,native_thread_exec,NULL) != 0 ) {
	   LOG("native_thread_start pthread_create fail !");
	   return;
	}

	LOG("native_thread_start success");
}

/*
 * Class:     com_bryan_ndk_JniCallBack
 * Method:    nativeThreadStop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_JniCallBack_nativeThreadStop(JNIEnv *env, jobject obj){
	gIsThreadExit = 1;
	LOG("native_thread_stop success");
}


