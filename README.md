## NDK集成
    AS环境下
    a.设置中心->plugin->android NDK support(勾上)
    b.下载完成以后再sdk目录下多一个ndk-bundle目录文件
    c.或者下载ndkzip文件 直接拷贝到sdk目录下

### 步骤一
    先在java中 先声明native方法 然后执行'生成.h文件'
### 生成.h头文件
    src/main目录下
    定位到java文件夹 javah 类全名
    bogon:java dragonfly$ : javah com.cn.kotlin.ndkbuild.JNI
### java函数签名 
    1.androidstudio 3.2
    查看方法签名     在app-> build ->intermediats->javac ->classes-> 目标文件(类)所在根目录
    /Users/dragonfly/Documents/workspace/NDKUse/NDKTest/app/build/intermediates/javac/debug/compileDebugJavaWithJavac/classes/com/cn/kotlin/ndkbuild 
    执行 javap -s '类名'
    2. 其他版本 在app-> build ->intermediats-class- debug
    执行 javap -s '类名'

### 更改java文件后 rebuildproject

### 引入jni.h文件 使用相应方法    

## gradle 配置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
cpp文件中新建.cpp文件需要使用:"文件名"+-lib
<pre><code>
	ndk{
            moduleName "native-lib"//so文件自动生成lib+ moduleName +.so
            abiFilters "arm64-v8a","armeabi-v7a","x86","x86_64"//cup的类型
            ldLibs "log"//输出log
        }
        //对应ndk库里 liblog.so文件调用使用
        //mac对应路径 /Users/dragonfly/Library/Android/sdk/ndk-bundle/platforms/android-24///arch-arm/usr/lib/liblog.so
</code></pre>
#### c打印log
<pre><code>
#include <stdio.h>
#include <stdbool.h>
#include <android/log.h>
#define LOG_TAG "BT"  //输出
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) // 定义LOGI类型 
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__) // 定义LOGW类型 
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__) // 定义LOGE类型 
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__) // 定义LOGF类

LOGI("result=====");
//输出结果 BT: result=====
</code></pre>
[Android中C/C++的日志打印 博客](https://blog.csdn.net/u013357557/article/details/81411686)

