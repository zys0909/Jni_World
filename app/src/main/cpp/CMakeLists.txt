
# 最低支持的 cmake版本
cmake_minimum_required(VERSION 3.10.2)

# set() 相当于设置别名，即 JNI_SDK = ${CMAKE_SOURCE_DIR}/
set(JNI_SDK ${CMAKE_SOURCE_DIR}/)

# TODO 导入头文件
include_directories(inc)

file(GLOB ALL_CPP *.c *.h *.cpp)

#list(APPEND cpp_srcs ${c_srcs})


add_library( # 设置生成的libary 的名字.
        native-lib

        # 动态库 .so   //STATIC 是静态库 .a
        SHARED

        # Provides a relative path to your source file(s).
        ${ALL_CPP})

#   CMAKE_SOURCE_DIR  -》 CMakeLists.txt 所在目录
#   CMAKE_ANDROID_ARCH_ABI  当前CPU架构的 库文件目录
#   TODO 导入库文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

#自动寻找log 库
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)


# 将log-lib动态链接native-lib
target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        fmod    #链接fmod.so到native-lib
        fmodL   #链接fmodL.so到native-lib
        )