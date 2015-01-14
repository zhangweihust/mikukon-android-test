/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.inject;


import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;



public class Demo extends Activity implements Callback, OnClickListener
{
	
	private static final int HANDLER_FLAG_LOAD = 0x128364;
	private static final int HANDLER_FLAG_REFRESH = 0x128365;
	
	private Handler handler;
	
	TextView  tv_jni;
	Button btn_load;
	Button btn_refresh;
	
	private int count;
	
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);
		
		handler = new Handler(this);
		
		
		
		tv_jni = (TextView)findViewById(R.id.tv_jni);
        btn_load = (Button) findViewById(R.id.btn_load);
        btn_refresh = (Button) findViewById(R.id.btn_refresh);

        btn_refresh.setEnabled(false);
        btn_load.setEnabled(true);
        
        btn_refresh.setOnClickListener(this);
        btn_load.setOnClickListener(this);
    }
    
    @Override
    public void onDestroy(){
    	super.onDestroy();
    	
        handler.removeMessages(HANDLER_FLAG_LOAD);
        handler.removeMessages(HANDLER_FLAG_REFRESH);
    }

    /* A native method that is implemented by the
     * 'hello-jni' native library, which is packaged
     * with this application.
     */
    public native String  stringFromJNI();

    /* This is another native method declaration that is *not*
     * implemented by 'hello-jni'. This is simply to show that
     * you can declare as many native methods in your Java code
     * as you want, their implementation is searched in the
     * currently loaded native libraries only the first time
     * you call them.
     *
     * Trying to call this function will result in a
     * java.lang.UnsatisfiedLinkError exception !
     */
    public native String  unimplementedStringFromJNI();

    /* this is used to load the 'hello-jni' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.hellojni/lib/libhello-jni.so at
     * installation time by the package manager.
     */
/*    static {
        System.loadLibrary("test");
    }*/

	@Override
	public boolean handleMessage(Message msg) {
		// TODO Auto-generated method stub
		switch(msg.what){
		case HANDLER_FLAG_LOAD:
			handler.sendEmptyMessageDelayed(HANDLER_FLAG_REFRESH, 3000);
			break;
		case HANDLER_FLAG_REFRESH:
			count++;
			tv_jni.setText( stringFromJNI() + ": " + count);
			handler.sendEmptyMessageDelayed(HANDLER_FLAG_REFRESH, 3000);
			break;
		}
		return false;
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch(v.getId()){
		case R.id.btn_load:
			System.loadLibrary("test");
			count = 0;
			handler.sendEmptyMessageDelayed(HANDLER_FLAG_LOAD, 3000);
			btn_load.setEnabled(false);
			btn_refresh.setEnabled(true);
			break;
		case R.id.btn_refresh:
			handler.removeMessages(HANDLER_FLAG_REFRESH);
			handler.sendEmptyMessageDelayed(HANDLER_FLAG_REFRESH, 3000);
			break;
		}
		
	}
}
