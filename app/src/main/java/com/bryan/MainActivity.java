package com.bryan;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.bryan.ndk.JniBasic;
import com.bryan.ndk.JniCallBack;

public class MainActivity extends AppCompatActivity {

    private JniBasic nativeProcess=new JniBasic();
    private JniCallBack jniCallBack=new JniCallBack();

    static {
        System.loadLibrary("nativeProcess");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniCallBack.nativeInitilize();
        jniCallBack.nativeThreadStart();
    }

    public void hello() {
        Log.i("nativeProcess", "MainActivity:hello()  我被调用了");
    }

    public void easyHello(View v){
        Toast.makeText(this, JniBasic.sayHello(),Toast.LENGTH_SHORT).show();
    }

    public void add(View v){
        Toast.makeText(this, JniBasic.add(1, 2)+"",Toast.LENGTH_SHORT).show();
    }

    public void handleStr(View v){
        Toast.makeText(this, JniBasic.sayHelloInC("this is perfect--中国"),Toast.LENGTH_SHORT).show();
    }

    public void handleArr(View v){
        int[] src={0,1,2,3,4,5};
        int[] dest= JniBasic.intMethod(src);
        for (int param:dest){
            Log.i("nativeProcess", param+"");
        }

    }


    public void callHello1(View v){
        nativeProcess.callhelloFromBasic();
    }

    public void callAdd(View v){
        nativeProcess.callAdd();
    }

    public void callprintStr(View v){
        nativeProcess.callprintStr();
    }

    public void callhello2(View v){
        nativeProcess.callhelloFromMainActivity();
    }

    public void callStatic(View v){
        nativeProcess.callStaticMethod();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        jniCallBack.nativeThreadStop();
    }
}
