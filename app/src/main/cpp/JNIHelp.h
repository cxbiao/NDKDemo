#ifndef JNIHELP_H
#define JNIHELP_H

#include <jni.h>


# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))


#define ATTACH_HELPER(vm,env) AttachHelper attachHelper((vm),(env))
class AttachHelper
{
public:
    AttachHelper(JavaVM *vm,JNIEnv **env){
        mVm = vm;
        bAttachedCurrentThread = false;
        vm->GetEnv((void**) env,JNI_VERSION_1_4);
        if(!(*env)){
            vm->AttachCurrentThread(env, NULL);
            bAttachedCurrentThread = true;
        }
    }

    ~AttachHelper(){
        if(bAttachedCurrentThread)
            mVm->DetachCurrentThread();
    }

private:
    bool bAttachedCurrentThread;
    JavaVM *mVm;
};


#define FIND_CLASS(env, clazz, className, b_global) do { \
    (clazz) = env->FindClass((className)); \
    if (!(clazz)) { \
        LOGE("FindClass(%s) failed", (className)); \
        return JNI_ERR; \
    } \
    if (b_global) { \
        (clazz) = (jclass) env->NewGlobalRef((clazz)); \
        if (!(clazz)) { \
            LOGE("NewGlobalRef(%s) failed", (className)); \
            return JNI_ERR; \
        } \
    } \
} while (0)

#define GET_METHOD_ID(env,var, clazz, methodName, methodDescriptor) do { \
    (var) = env->GetMethodID((clazz), (methodName), (methodDescriptor)); \
    if (!(var)) { \
        LOGE("GetMethodID(%s) failed", (methodName)); \
        return JNI_ERR; \
    } \
} while (0)


#define GET_STATIC_METHOD_ID(env,var, clazz, methodName, methodDescriptor) do { \
    (var) = env->GetStaticMethodID((clazz), (methodName), (methodDescriptor)); \
    if (!(var)) { \
        LOGE("GetStaticMethodID(%s) failed", (methodName)); \
        return JNI_ERR; \
    } \
} while (0)


#define GET_FIELD_ID(env,var, clazz, fieldName, fieldDescriptor) do { \
    (var) = env->GetFieldID((clazz), (fieldName), (fieldDescriptor)); \
    if (!(var)) { \
        LOGE("GetFieldID(%s) failed", (fieldName)); \
        return JNI_ERR; \
    } \
} while (0)




#endif//JNIHELP_H