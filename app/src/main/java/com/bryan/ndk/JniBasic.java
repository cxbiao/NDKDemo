package com.bryan.ndk;

import android.util.Log;

/**
 * Author：Cxb on 2016/3/2 17:33
 */
public class JniBasic {



    //C调用java空方法
    public void hello(){
        Log.i("nativeProcess", "JniBasic:hello()  我被调用了");
    }
    //C调用java中的带两个int参数的方法
    public int Add(int x,int y){
        int result=x+y;
        Log.i("nativeProcess",result+"");
        return result;
    }
    //C调用java中参数为string的方法
    public void printStr(String str){
        Log.i("nativeProcess",str);
    }

    public static void demo(){
        Log.i("nativeProcess", "哈哈哈,我是静态方法");
    }


    public static native String sayHello();


    public static native int add(int x ,int y);
    /**
     * 给字符串后面拼装字符  加密运算   web   url
     * @param s
     * @return
     */
    public static native String sayHelloInC(String s);
    //
    /**
     * 给c代码传递int数组   让c代码给这个数组进行操作
     * 图形 声音的处理
     * @param iNum
     * @return
     */
    public static native int[] intMethod(int[] iNum);



    public native void callhelloFromBasic();
    public native void callAdd();
    public native void callprintStr();
    public native void callhelloFromMainActivity();
    public native void callStaticMethod();
}
