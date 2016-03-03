#include <stdio.h>
#include <stdlib.h>
#include "com_bryan_ndk_NativeProcess.h"
#include <android/log.h>
#define LOG_TAG "NativeProcess"
#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

char* Jstring2CStr(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}

JNIEXPORT jstring JNICALL Java_com_bryan_ndk_NativeProcess_sayHello(JNIEnv *env, jclass jcls){
    LOG("hello world from c中文");
    return (*env)->NewStringUTF(env,"hello world from c中文");

}

JNIEXPORT jint JNICALL Java_com_bryan_ndk_NativeProcess_add(JNIEnv *env, jclass jcls, jint x, jint y){
    LOG("x=%d\n", x);
    LOG("y=%d\n", y);
    return x + y;
}


JNIEXPORT jstring JNICALL Java_com_bryan_ndk_NativeProcess_sayHelloInC(JNIEnv *env, jclass jcls, jstring jstr){
    char *cstr = Jstring2CStr(env, jstr);
    strcat(cstr, " hello");
    LOG("%s", cstr);
    return (*env)->NewStringUTF(env, cstr);
}


JNIEXPORT jintArray JNICALL Java_com_bryan_ndk_NativeProcess_intMethod(JNIEnv *env, jclass jcls, jintArray jintArr){
    // jArray  遍历数组   jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    // 数组的长度    jsize       (*GetArrayLength)(JNIEnv*, jarray);
    // 对数组中每个元素 +5
    int length =(*env)->GetArrayLength(env, jintArr);
    int* array =(*env)->GetIntArrayElements(env, jintArr, 0);
    int i=0;
    for(;i<length;i++){
        *(array+i)+=5;
    }
    return jintArr;
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callhelloFromNativeProcess(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =(*env)->FindClass(env,"com/bryan/ndk/NativeProcess");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=(*env)->GetMethodID(env,clazz,"hello","()V");
	// void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
	(*env)->CallVoidMethod(env,obj,method);
}

JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callAdd(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =(*env)->FindClass(env,"com/bryan/ndk/NativeProcess");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=(*env)->GetMethodID(env,clazz,"Add","(II)I");
	// void        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
	(*env)->CallIntMethod(env,obj,method,3,4);
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callprintStr(JNIEnv *env, jobject obj){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	jclass clazz =(*env)->FindClass(env,"com/bryan/ndk/NativeProcess");
	// jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	//javap -s获得方法签名
	jmethodID method=(*env)->GetMethodID(env,clazz,"printStr","(Ljava/lang/String;)V");
	jstring str=(*env)->NewStringUTF(env,"hello");
	(*env)->CallVoidMethod(env,obj,method,str);
}

//obj是native方法所在的类
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callhelloFromMainActivity(JNIEnv *env, jobject obj){
	jclass clazz =(*env)->FindClass(env,"com/bryan/MainActivity");

	jmethodID method=(*env)->GetMethodID(env,clazz,"hello","()V");
	jobject objmain=(*env)->AllocObject(env,clazz);// new MainActivity();
	(*env)->CallVoidMethod(env,objmain,method);
}


JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callStaticMethod(JNIEnv *env, jobject obj){
	jclass clazz =(*env)->FindClass(env,"com/bryan/ndk/NativeProcess");
	//  jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
	jmethodID method=(*env)->GetStaticMethodID(env,clazz,"demo","()V");
	//void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
	(*env)->CallStaticVoidMethod(env,clazz,method);
}