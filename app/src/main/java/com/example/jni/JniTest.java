package com.example.jni;

/**
 * 描述:
 * <p>
 * author zys
 * create by 2021/4/19
 */
public class JniTest {
    // Used to load the 'native-lib' library on application startup.
    static {
        //System.load("lib");//以绝对路径 加载动态链接库文件
        System.loadLibrary("native-lib");//以库目录遍历，自动寻找
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void testArrayAction(int count,String textInfo,int[] ints,String [] strArr);

    public native void putObject(Student student,String info);
}
