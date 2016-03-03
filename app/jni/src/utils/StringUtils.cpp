//
// Created by Administrator on 2016/3/3.
//

#include "StringUtils.h"
char * StringUtils::Jstring2CStr(JNIEnv *env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)env->CallObjectMethod( jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = env->GetArrayLength( barr);
    jbyte* ba = env->GetByteArrayElements( barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}