package com.cn.kotlin.ndkbuild

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    var jni = JNI();
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

//    companion object {
//
//        // Used to load the 'native-lib' library on application startup.
//        init {
//            System.loadLibrary("test")
//        }
//    }

    public fun add(v: View) {
//        Log.w("输出add方法:", jni.add(11, 99).toString());
//        sample_text.text = jni.sayHello("你好开始");
        jni.callbackadd();
    }

    public fun increaseArrayElse(v: View) {
        var int_array: IntArray = intArrayOf(1, 2, 3, 4, 5)
        Log.e("打印======", "11111");
        jni.increaseArrayElse(int_array);
        var sizes = int_array.size;
        for (item in int_array) {
            Log.w("打印======", item.toString());
        }
        Log.w("打印======", jni.checkPw("123456").toString());
    }

    public fun callbacked(v: View) {
        jni.callBacked()
    }

    public fun backString(v: View) {
        jni.backCString()
    }

    public fun backStatic(v: View) {
        jni.bakcStaticString()
    }

}
