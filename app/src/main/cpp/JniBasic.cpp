#include <stdlib.h>
#include <string.h>
#define LOG_TAG "nativeProcess"
#include "log.h"
#include "JNIHelp.h"
#include <vector>
#include "utils.h"

using namespace std;

/**
 * C 语言 (*env)->
 * C++ env->
 */



static jstring sayHello(JNIEnv *env, jclass jcls){
	LOGI("hello world from c中文");
    return env->NewStringUTF("hello world from c中文");

}

static jint  add(JNIEnv *env, jclass jcls, jint x, jint y){
	LOGI("x=%d\n", x);
	LOGI("y=%d\n", y);

	vector<int> ves;
	ves.push_back(1);
	ves.push_back(2);
	ves.push_back(4);
	LOGI("vector:first=%d",*(ves.begin()));
	LOGI("vector:size=%d",ves.size());
    return x + y;
}


static jstring  sayHelloInC(JNIEnv *env, jclass jcls, jstring jstr){
	//jstring 转char *
    const char *cstr = env->GetStringUTFChars(jstr,JNI_FALSE);
	char copy[100];
	strcpy(copy,cstr);
    strcat(copy,"_concat");

	env->ReleaseStringUTFChars(jstr,cstr);
	LOGI("%s", copy);
    return env->NewStringUTF(copy);
}


static jintArray  intMethod(JNIEnv *env, jclass jcls, jintArray jintArr){
    // jArray  遍历数组   jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    // 数组的长度    jsize       (*GetArrayLength)(JNIEnv*, jarray);
    // 对数组中每个元素 +5
    int length =env->GetArrayLength( jintArr);
    int* array =env->GetIntArrayElements(jintArr, 0);
    for(int i=0;i<length;i++){
        *(array+i)+=5;
    }
    return jintArr;
}


static void  callhelloFromBasic(JNIEnv *env, jobject obj){

	env->CallVoidMethod(obj,gFields.JniBasic.hello);
}

static void  callAdd(JNIEnv *env, jobject obj){

	env->CallIntMethod(obj,gFields.JniBasic.Add,3,4);
}


static void  callprintStr(JNIEnv *env, jobject obj){

	jstring str=env->NewStringUTF("hello");
	env->CallVoidMethod(obj,gFields.JniBasic.printStr,str);
}

//obj是native方法所在的类
static void  callhelloFromMainActivity(JNIEnv *env, jobject obj){

	jobject objmain=env->AllocObject(gFields.MainActivity.clazz);// new MainActivity();
	env->CallVoidMethod(objmain,gFields.MainActivity.hello);
    env->DeleteLocalRef(objmain);
}


static void  callStaticMethod(JNIEnv *env, jobject obj){

	env->CallStaticVoidMethod(gFields.JniBasic.clazz,gFields.JniBasic.demo);
}


static const JNINativeMethod gMethods[] = {
		{"sayHello", "()Ljava/lang/String;", (void *)sayHello},
		{"add", "(II)I", (void *)add},
		{"sayHelloInC", "(Ljava/lang/String;)Ljava/lang/String;", (void*)sayHelloInC},
		{"intMethod","([I)[I",(void*)intMethod},
		{"callhelloFromBasic","()V",(void*)callhelloFromBasic},
		{"callAdd","()V",(void*)callAdd},
		{"callprintStr","()V",(void*)callprintStr},
		{"callhelloFromMainActivity","()V",(void*)callhelloFromMainActivity},
		{"callStaticMethod","()V",(void*)callStaticMethod},

};

int register_JNIBasic(JavaVM* vm ,JNIEnv* env){

	if (gFields.JniBasic.clazz == NULL) {
		LOGE("Can't find com/bryan/ndk/JniBasic");
		return -1;
	}
	if (env->RegisterNatives(gFields.JniBasic.clazz,gMethods,NELEM(gMethods)) !=JNI_OK) {
		LOGE("RegisterNatives failed for  %s\n","JniBasic");
		return JNI_ERR;
	}
	LOGI("Register JniBasic success");
	return JNI_OK;
}