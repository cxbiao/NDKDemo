package com.bryan;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.bryan.ndk.NativeProcess;

public class MainActivity extends AppCompatActivity {

    private NativeProcess nativeProcess=new NativeProcess();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void hello() {
        Log.d("NativeProcess", "MainActivity:hello()  我被调用了");
    }

    public void easyHello(View v){
        Toast.makeText(this, NativeProcess.sayHello(),Toast.LENGTH_SHORT).show();
    }

    public void add(View v){
        Toast.makeText(this,NativeProcess.add(1,2)+"",Toast.LENGTH_SHORT).show();
    }

    public void handleStr(View v){
        Toast.makeText(this,NativeProcess.sayHelloInC("this is perfect"),Toast.LENGTH_SHORT).show();
    }

    public void handleArr(View v){
        int[] src={0,1,2,3,4,5};
        int[] dest=NativeProcess.intMethod(src);
        for (int param:dest){
            Log.d("NativeProcess", param+"");
        }

    }


    public void callHello1(View v){
        nativeProcess.callhelloFromNativeProcess();
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
}
