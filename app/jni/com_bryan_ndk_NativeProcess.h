/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_bryan_ndk_NativeProcess */

#ifndef _Included_com_bryan_ndk_NativeProcess
#define _Included_com_bryan_ndk_NativeProcess
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    sayHello
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_bryan_ndk_NativeProcess_sayHello
  (JNIEnv *, jclass);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_bryan_ndk_NativeProcess_add
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    sayHelloInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_bryan_ndk_NativeProcess_sayHelloInC
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    intMethod
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_bryan_ndk_NativeProcess_intMethod
  (JNIEnv *, jclass, jintArray);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    callhelloFromNativeProcess
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callhelloFromNativeProcess
  (JNIEnv *, jobject);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    callAdd
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callAdd
  (JNIEnv *, jobject);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    callprintStr
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callprintStr
  (JNIEnv *, jobject);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    callhelloFromMainActivity
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callhelloFromMainActivity
  (JNIEnv *, jobject);

/*
 * Class:     com_bryan_ndk_NativeProcess
 * Method:    callStaticMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_bryan_ndk_NativeProcess_callStaticMethod
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
