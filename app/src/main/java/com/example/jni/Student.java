package com.example.jni;

import android.util.Log;

/**
 * 描述:
 * <p>
 * author zys
 * create by 2021/4/20
 */
public class Student {

    private final static String TAG = "测试TAG_Java";

    private String name;
    private int age;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        Log.d(TAG, "setName : " + name);
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        Log.d(TAG, "setAge : " + age);
        this.age = age;
    }

    public static void showInfo(String info) {
        Log.d(TAG, "showInfo :" + info);
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
