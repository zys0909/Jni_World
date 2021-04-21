package com.example.jni;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import org.fmod.FMOD;

/**
 * 描述:
 * <p>
 * author zys
 * create by 2021/4/21
 */
public class VoiceActivity extends AppCompatActivity {

    private static final int MODE_NORMAL = 0; // 正常
    private static final int MODE_LUOLI = 1; //
    private static final int MODE_DASHU = 2; //
    private static final int MODE_JINGSONG = 3; //
    private static final int MODE_GAOGUAI = 4; //
    private static final int MODE_KONGLING = 5; //

    static {
        System.loadLibrary("native-lib");
    }

    private String path;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice);
        FMOD.init(this);
        path = "file:///android_asset/derry.mp3";
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    // 六个 点击事件
    public void onFix(View view) {
        switch (view.getId()) {
            case R.id.btn_normal:
                voiceChangeNative(MODE_NORMAL, path); // 真实开发中，必须子线程  JNI线程（很多坑）
                break;
            case R.id.btn_luoli:
                voiceChangeNative(MODE_LUOLI, path);
                break;
            case R.id.btn_dashu:
                voiceChangeNative(MODE_DASHU, path);
                break;
            case R.id.btn_jingsong:
                voiceChangeNative(MODE_JINGSONG, path);
                break;
            case R.id.btn_gaoguai:
                voiceChangeNative(MODE_GAOGUAI, path);
                break;
            case R.id.btn_kongling:
                voiceChangeNative(MODE_KONGLING, path);
                break;
        }
    }

    private void playerEnd(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    private native void voiceChangeNative(int modeNormal, String path);
}
