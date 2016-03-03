#include <stdio.h>
#include <stdlib.h>
#include "com_bryan_ndk_JniBasic.h"
#include "StringUtils.h"
#include <android/log.h>
#include <vector>
#define LOG_TAG "nativeProcess"
#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
using namespace std;

/**
 * C 语言 (*env)->
 * C++ env->
 */


JNIEXPORT jstring JNICALL Java_com_bryan_ndk_JniBasic_sayHello(JNIEnv *env, jclass jcls){
    LOG("hello world from c中文");
    return env->NewStringUTF("hello world from c中文");

}

JNIEXPORT jint JNICALL Java_com_bryan_ndk_JniBasic_add(JNIEnv *env, jclass jcls, jint x, jint y){
    LOG("x=%d\n", x);
    LOG("y=%d\n", y);

	vector<int> ves;
	ves.push_back(1);
	ves.push_back(2);
	ves.push_back(4);
	LOG("vector:first=%d",*(ves.begin()));
	LOG("vector:size=%d",ves.size());
    return x + y;
}


JNIEXPORT jstring JNICALL Java_com_bryan_ndk_JniBasic_sayHelloInC(JNIEnv *env, jclass jcls, jstring jstr){
    char *cstr = StringUtils::Jstring2CStr(env, jstr);
    strcat(cstr, " hello");
    LOG("%s", cstr);
    return env->NewStringUTF(cstr);
}


JNIEXPORT jintArray JNICALL Java_com_bryan_ndk_JniBasic_intMethod(JNIEnv *env, jclass jcls, jintArray jintArr){
    // jArray  遍历数组   jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    // 数组的长度    jsize       (*GetArrayLength)(JNIEnv*, jarray);
    // 对数组中每个元素 +5
    int length =env->GetArrayLength( jintArr);
    int* array =env->GetIntArrayElements(jintArr, 0);
    int i=0;
    for(;i<length;i++){
        *(array+i)+=5;
    }
    return jintArr;
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_JniBasic_callhelloFromBasic(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =env->FindClass("com/bryan/ndk/JniBasic");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=env->GetMethodID(clazz,"hello","()V");
	// void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
	env->CallVoidMethod(obj,method);
}

JNIEXPORT void JNICALL Java_com_bryan_ndk_JniBasic_callAdd(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =env->FindClass("com/bryan/ndk/JniBasic");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=env->GetMethodID(clazz,"Add","(II)I");
	// void        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
	env->CallIntMethod(obj,method,3,4);
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_JniBasic_callprintStr(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =env->FindClass("com/bryan/ndk/JniBasic");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=env->GetMethodID(clazz,"printStr","(Ljava/lang/String;)V");
	jstring str=env->NewStringUTF("hello");
	env->CallVoidMethod(obj,method,str);
}

//obj是native方法所在的类
JNIEXPORT void JNICALL Java_com_bryan_ndk_JniBasic_callhelloFromMainActivity(JNIEnv *env, jobject obj){
	jclass clazz =env->FindClass("com/bryan/MainActivity");

	jmethodID method=env->GetMethodID(clazz,"hello","()V");
	jobject objmain=env->AllocObject(clazz);// new MainActivity();
	env->CallVoidMethod(objmain,method);
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_JniBasic_callStaticMethod(JNIEnv *env, jobject obj){
	jclass clazz =env->FindClass("com/bryan/ndk/JniBasic");
	//  jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
	jmethodID method=env->GetStaticMethodID(clazz,"demo","()V");
	//void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
	env->CallStaticVoidMethod(clazz,method);
}