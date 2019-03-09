//
// Created by dragonfly on 2019/3/6.
//

#include "com_cn_kotlin_ndkbuild_JNI.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_cn_kotlin_ndkbuild_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
/**
 * jint 返回值
 * Java_全类名_方法名
 * JNIEnv *env  ---typedef const struct JNINativeInterface*  JNIEnv别名
 *
 *
 *
 */
extern "C" JNIEXPORT jint JNICALL
Java_com_cn_kotlin_ndkbuild_JNI_add
        (JNIEnv *env, jobject obj, jint ji, jint jj) {
    int result = ji + jj;
    return result;

}



