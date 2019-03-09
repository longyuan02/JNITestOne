package com.cn.kotlin.ndkbuild;

import android.util.Log;

public class JNI {
    {
        System.loadLibrary("native-lib");
    }

    public native String stringFromJNI();

    //实现加法
    public native int add(int x, int y);

    //从java中串字符串到c c进行拼接
    public native String sayHello(String s);

    //C代码给每个数字加10
    public native int[] increaseArrayElse(int[] intArray);

    //检查密码是否正确
    public native int checkPw(String pw);

    //声明c代码调用java
    public native void callbackadd();

    //被调用java方法
    public int addCallBack(int x, int y) {
        Log.w("addCallBack======", String.valueOf(x + y));
        return x + y;
    }


    //被调用无返回值
    public native void callBacked();

    public void callBackNull() {
        Log.w("print====callBackNull:", "callBackNull");
    }

    //返回C字符串
    public native void backCString();

    public void getString(String str) {
        Log.w("getString======", str);
    }

    //返回静态static方法
    public native void bakcStaticString();

    public static void getStaticString(String str) {
        Log.w("返回static======", str);
    }

}
