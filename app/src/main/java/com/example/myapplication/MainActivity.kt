package com.example.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.example.myapplication.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        stringFromJNI()
        // Example of a call to a native method
       // binding.sampleText.text = stringFromJNI()
        fuck()
    }

    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'myapplication' library on application startup.
        init {
            System.loadLibrary("myapplication")
        }

    }


    public fun fuck(){
        Log.e("fuck","fuckyou")
    }

    public fun fuck(s:String){
        runOnUiThread {
            Log.e("fuck","fuckyou223")
            binding.sampleText.text=s
        }

    }

}