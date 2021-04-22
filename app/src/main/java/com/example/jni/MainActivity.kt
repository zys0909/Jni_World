package com.example.jni

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

    }

    fun onClick(view: View) {
        when (view.id) {
            R.id.btn_01 -> startActivity(Intent(this, TypeChangeActivity::class.java))
            R.id.btn_02 -> startActivity(Intent(this, VoiceActivity::class.java))
            R.id.btn_03 -> {
            }
            R.id.btn_04 -> {
            }
            R.id.btn_05 -> {
            }
            R.id.btn_06 -> {
            }

        }
    }
}