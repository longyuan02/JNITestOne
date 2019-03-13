## 指南
|-flutter
|




借鉴博客(https://www.cnblogs.com/rocomp/p/4892866.html)

## JNI 概念
	JNI(java native interface:java) 本地开发接口
	JNI是一个协议,这个协议用来沟通java代码和外部的本地代码(c/c++),外部的c/c++也可以调用java代码
#### 优势
	代码效率上c/c++是本地语言,比Java更高效
	代码移植:c语言模块可以复用
	代码安全:相对c语言java更容易被反编译,一般加密算法都是用C语言编写，不容易被反编译


####  引用类型对应
	jobject 				(all java objects)
	|
	|-jclass     			(java.lang.Class objects)
	|-jstring 				(java.lang.String objects)
	|-jarray				(arrays)
	|       |-jobjectArray  (object arrays)
	|		|-jbooleanArray (boolean arrays)
	|		|-jbyteArray    (byte arrays)
	|		|-jchrArray 	(char arrays)
	|		|-jshortArray	(short arrays)
	|		|-jintArray		(int arrays)
	|		|-jlongArray	(long arrays)
	|		|-jfloatArray	(float arrays)
	|		|-jdoubleArray	(double arrays)
	|-jthrowable			(java.long.Throwable.object)

#### 堆内存和栈内存
	栈内存:系统自动分配和释放,保存全局、静态、局部变量,在栈上分配的内存叫做惊天分配,大小一般是固定的.
	堆内存:程序员手动分配(malloc/new)和释放(free/java不用手动释放,由GC回收),在堆上分配的内存叫做动态分配,一般硬件内存有多大堆内存就有多大.

## 交叉编译的概念
#### 1、交叉编译的概念
		在一个平台编译出另一个平台能执行的二进制代码
		主流平台又:windows、 mac os、 Linux
		主流处理器:x86、 arm、 mips
#### 2、交叉编译原理
	在一个平台上,模拟其他平台的特性
	便以流程:源代码-->编译-->链接-->可执行程序
#### 3、交叉编译工具链接
	多个工具的集合,一个工具使用完后接着调用下一个工具
#### 4、交叉编译编译工具
	NDK(Native Development kit)开发必备工具,模拟其他平台特性类编译代码的工具
	CDT(C/C++ Development Tools)是Eclipse开发C语言的一个插件，高亮显示C语言的语法
	Cygwin: 一个Windows平台的Unix模拟器
[可以参考这篇博客Cygwin简介及使用](http://www.cnblogs.com/rocomp/p/4805553.html)


### 环境配置 ndk 
cmakelists.txt 文件配置
<pre><code>
	cmake_minimum_required(VERSION 3.4.1)
#设置生成的so动态库最后输出的路径 配置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp)

#添加第二个
add_library(test-lib src/main/cpp/test-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries(native-lib ${log-lib})
target_link_libraries(test-lib ${log-lib})
</code></pre>


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
cpp文件中新建.cpp文件需要使用:"文件名"+-lib
<pre><code>
	ndk{
            moduleName "native-lib"//so文件自动生成lib+ moduleName +.so
            abiFilters "arm64-v8a","armeabi-v7a","x86","x86_64"//cup的类型
            
        }
</code></pre>

######  配置多个cpp文件生成so文件
	https://blog.csdn.net/qq13244843816/article/details/80783409

## JNIdemo
	开发环境mac androidstudio 3.0
	新建一个android工程 

## 引用os文件
	常用方法 目录 app/build/intermediates/cmake/debug/obj/
	copy所有so文件
	如果有修改,可以删掉重新make object


	在main同目录下新建jniLibs文件夹 复制os文件





































