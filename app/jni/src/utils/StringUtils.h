//
// Created by Administrator on 2016/3/3.
//

#ifndef NDKDEMO_STRINGUTILS_H
#define NDKDEMO_STRINGUTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

class StringUtils {

public:
    static char * Jstring2CStr(JNIEnv* env, jstring jstr);

};


#endif //NDKDEMO_STRINGUTILS_H
