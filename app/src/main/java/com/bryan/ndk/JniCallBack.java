package com.bryan.ndk;

import android.util.Log;

/**
 * Author：Cxb on 2016/3/3 14:45
 */
public class JniCallBack {

    public native void nativeInitilize();

    public native void nativeThreadStart();
    public native void nativeThreadStop();

    //jni子线程的回调函数
    public void onNativeCallback( int count ) {
        //子线程
        //Log.d("nativeProcess", Thread.currentThread().getName());
        Log.d("nativeProcess", "onNativeCallback count=" + count);
    }


}
