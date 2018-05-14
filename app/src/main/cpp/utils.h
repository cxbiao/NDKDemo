//
// Created by Bryan on 2018/5/14.
//

#ifndef NDKDEMO_UTILS_H
#define NDKDEMO_UTILS_H

#include <jni.h>

struct fields{
    JavaVM* vm;
    struct {
        jclass clazz;
        jmethodID hello;
        jmethodID Add;
        jmethodID printStr;
        jmethodID demo;

    } JniBasic;
    struct {
        jclass clazz;
        jobject instance;
        jmethodID onNativeCallback;
    } JniCallBack;
    struct {
        jclass clazz;
        jmethodID hello;

    }MainActivity;

} ;

extern fields gFields;


#endif //NDKDEMO_UTILS_H
