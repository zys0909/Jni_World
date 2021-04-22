package com.example.jni;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class TypeChangeActivity extends AppCompatActivity {

    private final JniTest jni = new JniTest();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_type_change);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(jni.stringFromJNI());
    }

    public void test01(View view) {
        int[] ints = new int[]{1, 2, 3, 4, 5, 6};
        String[] strArr = new String[]{"李小龙", "李连杰", "李元霸"};
        jni.testArrayAction(99, "", ints, strArr);


    }

    public void test02(View view) {
    }

    public void test03(View view) {
    }

    public void test04(View view) {
    }

    public void test05(View view) {
    }

    public void test06(View view) {

        startActivity(new Intent(this, VoiceActivity.class));
    }
}