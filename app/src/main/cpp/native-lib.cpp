#include <jni.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#define LOG_TAG "BT"
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__) // 定义LOGD类型
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)  // 定义LOGI类型
#define LOGW(...)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)  // 定义LOGW类型
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__) // 定义LOGE类型
#define LOGF(...)__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__) // 定义LOGF类

/**
 * 引入jni.h文件 使用相应方法
 * 
 * 生成头文件
 * 
 * 目标文件java层级
 * 执行javah 文件全名
 * 查看方法签名     在app-> build ->intermediats->javac ->classes-> 目标文件
 * /Users/dragonfly/Documents/workspace/NDKUse/NDKTest/app/build/intermediates/javac/debug/compileDebugJavaWithJavac/classes/com/cn/kotlin/ndkbuild 
 * 执行 javap -s '类名'
*/

extern "C" JNIEXPORT jstring JNICALL
Java_com_cn_kotlin_ndkbuild_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject /* this */)
{
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
/**
 * jint 返回值
 * Java_全类名_方法名
 * JNIEnv *env  ---typedef const struct JNINativeInterface*  JNIEnv别名
 */
extern "C" JNIEXPORT jint JNICALL
Java_com_cn_kotlin_ndkbuild_JNI_add(JNIEnv *env, jobject obj, jint ji, jint jj)
{
    int result = ji + jj;
    return result;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_cn_kotlin_ndkbuild_JNI_sayHello(JNIEnv *env, jobject obj, jstring sl)
{
    std::string hello = "Hello from C+++++++++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jarray JNICALL
Java_com_cn_kotlin_ndkbuild_JNI_increaseArrayElse(JNIEnv *env, jobject obj, jintArray arr)
{
    //拿到整型数组的长度以及第0个元素的地址
    //   jsize GetArrayLength(jarray array)
    int length = (*env).GetArrayLength(arr);
    //  jint* GetIntArrayElements(jintArray array, jboolean* isCopy)
    int *arrp = (*env).GetIntArrayElements(arr, JNI_FALSE);
    int i;
    for (i = 0; i < length; i++)
    {
        *(arrp + i) += 10; //将数组中的每个元素加10
    }
    return arr;
}
/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char *JString2CStr(JNIEnv *env, jstring jstr)
{
    char *rtn = NULL;
    jclass clsstring = (*env).FindClass("java/lang/String");
    jstring strencode = (*env).NewStringUTF("GB2312");
    jmethodID mid = (*env).GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env).CallObjectMethod(jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env).GetArrayLength(barr);
    jbyte *ba = (*env).GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char *)malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env).ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}
extern "C" JNIEXPORT jint JNICALL
Java_com_cn_kotlin_ndkbuild_JNI_checkPw(JNIEnv *env, jobject job, jstring jstr)
{
    //服务器返回密码123456  定义一个c char指针字符
    jstring jss=(*env).NewStringUTF("123456");
    char* chars=JString2CStr(env,jss);
    // char *chars = JString2CStr(env, origin);
    char *forUser = JString2CStr(env, jstr);
    //函数比较字符串是否相同
    int code = strcmp(chars, forUser);
    if (code == 0)
    {
        return 200;
    }
    else
    {
        return 400;
    }
}
//c调用java方法
extern "C" JNIEXPORT void JNICALL Java_com_cn_kotlin_ndkbuild_JNI_callbackadd(JNIEnv *env, jobject job)
{
    //1.得到字符串 com.cn.kotlin.ndkbuild.JNI
    //jclass FindClass(const char *name)
    jclass jclass = (*env).FindClass("com/cn/kotlin/ndkbuild/JNI"); //linux下使用'/'标识目录路径
    //2.得到方法 (II)I
    //jmethodID GetMethodID(jclass clazz, const char *name,const char *sig)
    jmethodID jmethodIDs = (*env).GetMethodID(jclass, "addCallBack", "(II)I");
    //3.实例化类
    //jobject AllocObject(jclass clazz)
    jobject jobjects = (*env).AllocObject(jclass);
    //4.调用方法
    //jint CallIntMethod(jobject obj, jmethodID methodID, ...)
    jint jints = (*env).CallIntMethod(jobjects, jmethodIDs, 99, 101);
    LOGI("result=====");
}
//调用无返回值
extern "C" JNIEXPORT void JNICALL Java_com_cn_kotlin_ndkbuild_JNI_callBacked(JNIEnv *env, jobject job)
{
    jclass jclass = (*env).FindClass("com/cn/kotlin/ndkbuild/JNI");
    jmethodID jmethodIDs = (*env).GetMethodID(jclass, "callBackNull", "()V");
    jobject jobjects = (*env).AllocObject(jclass);
    //void CallVoidMethod(jobject obj, jmethodID methodID, ...)
    (*env).CallVoidMethod(jobjects, jmethodIDs);
}

//调用返回值
extern "C" JNIEXPORT void JNICALL Java_com_cn_kotlin_ndkbuild_JNI_backCString(JNIEnv *env, jobject job)
{
    jclass jclass = (*env).FindClass("com/cn/kotlin/ndkbuild/JNI");
    jmethodID jmethodIDs = (*env).GetMethodID(jclass, "getString", "(Ljava/lang/String;)V");
    jobject jobjects = (*env).AllocObject(jclass);
    //jstring NewStringUTF(const char *utf)
    jstring jst = (*env).NewStringUTF("I input str:(*env)");
    //void CallVoidMethod(jobject obj, jmethodID methodID, ...)
    (*env).CallVoidMethod(jobjects, jmethodIDs, jst);
}
//调用静态方法返回值
extern "C" JNIEXPORT void JNICALL Java_com_cn_kotlin_ndkbuild_JNI_bakcStaticString(JNIEnv *env, jobject job)
{
    jclass jclass = (*env).FindClass("com/cn/kotlin/ndkbuild/JNI");
    jmethodID jmethodIDs = (*env).GetStaticMethodID(jclass, "getStaticString", "(Ljava/lang/String;)V");
    //jstring NewStringUTF(const char *utf)
    jstring jst = (*env).NewStringUTF("I input static:(*env)");
    //void CallVoidMethod(jobject obj, jmethodID methodID, ...)
    (*env).CallStaticVoidMethod(jclass, jmethodIDs, jst);
}
