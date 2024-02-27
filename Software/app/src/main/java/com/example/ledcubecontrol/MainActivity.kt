package com.example.ledcubecontrol



import android.R
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.AdapterView.OnItemClickListener
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.core.content.ContextCompat
import com.example.ledcubecontrol.databinding.MainActivityBinding
import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity
import android.bluetooth.BluetoothSocket
import android.content.pm.PackageManager
import android.speech.RecognizerIntent
import android.speech.SpeechRecognizer
import android.util.Log
import androidx.core.app.ActivityCompat
import java.io.IOException
import java.util.Locale
import java.util.UUID

class MainActivity : ComponentActivity() {
    private  lateinit var  binding: MainActivityBinding
    private lateinit var bluetoothManager: BluetoothManager
    private lateinit var ledControl: LedControl

    private var RQ_SPEECH_REC = 102

    //private lateinit var bluetoothSocket: BluetoothSocket
    private lateinit var bluetoothAdapter: BluetoothAdapter
    private lateinit var deviceListView: ListView
    private lateinit var deviceAdapter: ArrayAdapter<String>
    private lateinit var deviceList: ArrayList<String>
    private lateinit var selectedDevice: BluetoothDevice
    private val REQUEST_BLUETOOTH_PERMISSIONS = 1
    private var checkBtnConnect : Boolean  = false

    private val permissions = arrayOf(
        Manifest.permission.BLUETOOTH,
        Manifest.permission.BLUETOOTH_ADMIN,
        Manifest.permission.ACCESS_FINE_LOCATION,
        Manifest.permission.ACCESS_COARSE_LOCATION,
        Manifest.permission.BLUETOOTH_CONNECT
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding =  MainActivityBinding.inflate(layoutInflater)
        setContentView(binding.root)

        bluetoothManager =  BluetoothManager();
        ledControl = LedControl(bluetoothManager)

        deviceListView = binding.deviceListView
        deviceList = ArrayList()
        deviceAdapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, deviceList)
        deviceListView.adapter = deviceAdapter



        binding.bgListDevice.visibility = View.GONE
        checkPermissions()
        setUpButtons()

        binding.btnConnect.setOnClickListener{
            if (checkBtnConnect){
                binding.bgListDevice.visibility =  View.GONE
            }else{
                initializeBluetooth();

            }
            checkBtnConnect =!checkBtnConnect


        }
        binding.btnOnOff.setOnClickListener{
            if (bluetoothManager.isConnected()){
                ledControl.turnONOFF()
            }else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }

        }

        binding.btnMic.setOnClickListener{
            if (bluetoothManager.isConnected()){
                askSpeechInput()
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }
        binding.btnMode0.setOnClickListener{
            if (bluetoothManager.isConnected()){
                binding.textMode.text = "Chế độ thường"
                binding.textMode.visibility =  View.VISIBLE
                binding.layoutMode0.visibility =  View.VISIBLE
                binding.layoutMode1.visibility =  View.GONE
                ledControl.setMode(0)
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }

        binding.btnMode1.setOnClickListener{
            if (bluetoothManager.isConnected()){
                binding.textMode.text = "Chế độ âm thanh"
                binding.textMode.visibility =  View.VISIBLE
                binding.layoutMode1.visibility =  View.VISIBLE
                binding.layoutMode0.visibility =  View.GONE
                ledControl.setMode(1)
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }

        binding.btnShowText.setOnClickListener{
            if (bluetoothManager.isConnected()){
                ledControl.showText(converTextShow(binding.textShow.text.toString()))
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }

        binding.btnUp.setOnClickListener{
            if (bluetoothManager.isConnected()){
                    ledControl.adjustSensor(true)
                Toast.makeText(this,"Tăng mức cảm biến",Toast.LENGTH_SHORT).show()
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }
        binding.btnDown.setOnClickListener{
            if (bluetoothManager.isConnected()){
                ledControl.adjustSensor(false)
                Toast.makeText(this,"Giảm mức cảm biến",Toast.LENGTH_SHORT).show()
            }
            else{
                Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
            }
        }
        binding.btnReset.setOnClickListener{
            ledControl.reset();
        }


    }

    private fun checkPermissions() {
        val notGrantedPermissions = mutableListOf<String>()
        for (permission in permissions) {
            if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                notGrantedPermissions.add(permission)
            }
        }
        if (notGrantedPermissions.isNotEmpty()) {
            ActivityCompat.requestPermissions(this, notGrantedPermissions.toTypedArray(), REQUEST_BLUETOOTH_PERMISSIONS)
        } else {
            //initializeBluetooth()
        }
    }

    @SuppressLint("MissingPermission")
    private fun initializeBluetooth() {
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "Device doesn't support Bluetooth", Toast.LENGTH_SHORT).show()
            finish()
        } else {
            if (!bluetoothAdapter.isEnabled) {
                val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
                startActivityForResult(enableBtIntent, REQUEST_BLUETOOTH_PERMISSIONS)
            } else {
                showPairedDevices()
            }
        }

        deviceListView.setOnItemClickListener { _, _, position, _ ->
            val deviceInfo = deviceList[position]
            val deviceAddress = deviceInfo.substring(deviceInfo.length - 17)
            selectedDevice = bluetoothAdapter.getRemoteDevice(deviceAddress)
//
            if(bluetoothManager.isConnected()){
                bluetoothManager.disconnect()
                Thread.sleep(1000L)
            }

            if(bluetoothManager.connect(selectedDevice)){
                Toast.makeText(this,"Kết nối thành công",Toast.LENGTH_SHORT).show()
                binding.textConnect.text = "Đã kết nối"
                binding.textConnect.setTextColor(ContextCompat.getColor(this, R.color.holo_green_dark))
                binding.nameDevice.text = deviceInfo.substring(0, deviceInfo.length - 17)

                checkBtnConnect= false
                binding.bgListDevice.visibility = View.GONE


            }
            else{
                binding.textConnect.text = "Chưa kết nối"
                binding.textConnect.setTextColor(ContextCompat.getColor(this, R.color.holo_red_dark))
                Toast.makeText(this,"Kết nối thất bại",Toast.LENGTH_SHORT).show()
            }

        }
    }

    @SuppressLint("MissingPermission")
    private fun showPairedDevices() {
        val pairedDevices: Set<BluetoothDevice> = bluetoothAdapter.bondedDevices
        deviceList.clear()

        if (pairedDevices.isNotEmpty()) {
            for (device in pairedDevices) {
                deviceList.add("${device.name}\n${device.address}")
            }
            //deviceAdapter.clear()
            //deviceAdapter.addAll(deviceList)
            deviceAdapter.notifyDataSetChanged()
        binding.bgListDevice.visibility = View.VISIBLE
        } else {
            Toast.makeText(this, "No paired devices found", Toast.LENGTH_SHORT).show()
        }
    }



    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when (requestCode) {
            REQUEST_BLUETOOTH_PERMISSIONS -> {
                if (grantResults.isNotEmpty() && grantResults.all { it == PackageManager.PERMISSION_GRANTED }) {
                    //initializeBluetooth()
                } else {
                }
            }
        }
        //initializeBluetooth()
    }

    private fun  askSpeechInput(){
//        if(!SpeechRecognizer.isRecognitionAvailable(this)){
//            Toast.makeText(this,"Speech recoginition is not val",Toast.LENGTH_SHORT).show()
//
//        }else{
            val    i = Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH)
            i.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM)
            i.putExtra(RecognizerIntent.EXTRA_LANGUAGE,Locale.getDefault())
            i.putExtra(RecognizerIntent.EXTRA_PROMPT,"Say something")
            startActivityForResult(i,RQ_SPEECH_REC)
       // }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if(requestCode == RQ_SPEECH_REC && resultCode == Activity.RESULT_OK ){
                    val  result = data?.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS)
                    handelText(result?.get(0).toString().lowercase())
        }
    }

    private fun setUpButtons(){
        binding.btnMode0Type0.setOnClickListener{handelBtn(0,0)}
        binding.btnMode0Type1.setOnClickListener{handelBtn(0,1)}
        binding.btnMode0Type2.setOnClickListener{handelBtn(0,2)}
        binding.btnMode0Type3.setOnClickListener{handelBtn(0,3)}
        binding.btnMode0Type4.setOnClickListener{handelBtn(0,4)}
        binding.btnMode0Type5.setOnClickListener{handelBtn(0,5)}
        binding.btnMode0Type6.setOnClickListener{handelBtn(0,6)}
        binding.btnMode0Type7.setOnClickListener{handelBtn(0,7)}
        binding.btnMode0Type8.setOnClickListener{handelBtn(0,8)}
        binding.btnMode0Type9.setOnClickListener{handelBtn(0,9)}
        binding.btnMode0Type10.setOnClickListener{handelBtn(0,10)}
        binding.btnMode0Type11.setOnClickListener{handelBtn(0,11)}
        binding.btnMode0Type12.setOnClickListener{handelBtn(0,12)}
        binding.btnMode0Type13.setOnClickListener{handelBtn(0,13)}
        binding.btnMode0Type14.setOnClickListener{handelBtn(0,14)}
        binding.btnMode0Type15.setOnClickListener{handelBtn(0,15)}

        binding.btnMode1Type0.setOnClickListener{handelBtn(1,0)}
        binding.btnMode1Type1.setOnClickListener{handelBtn(1,1)}
        binding.btnMode1Type2.setOnClickListener{handelBtn(1,2)}
        binding.btnMode1Type3.setOnClickListener{handelBtn(1,3)}
        binding.btnMode1Type4.setOnClickListener{handelBtn(1,4)}
        binding.btnMode1Type5.setOnClickListener{handelBtn(1,5)}
        binding.btnMode1Type6.setOnClickListener{handelBtn(1,6)}
        binding.btnMode1Type7.setOnClickListener{handelBtn(1,7)}

    }

    private fun handelBtn(mode :Int, effect :Int){
        if (bluetoothManager.isConnected()){
            ledControl.setEffect(mode,effect)
        }else{
            Toast.makeText(this,"Chưa kết nối với LED",Toast.LENGTH_SHORT).show()
        }

    }

    private fun handelText(text : String){
        if (text.equals("bật", ignoreCase = true)){
            ledControl.turnON()
        }else  if (text.equals("tắt", ignoreCase = true)){
            ledControl.turnOFF()
        } else if (text.equals("chế độ thường", ignoreCase = true)){
            ledControl.setMode(0)
        } else if (text.equals("chế độ âm thanh", ignoreCase = true)){
            ledControl.setMode(1)
        } else if (text.equals("tăng mức cảm biến", ignoreCase = true)){
            ledControl.adjustSensor(true)
            Toast.makeText(this,"Tăng mức cảm biến",Toast.LENGTH_SHORT).show()
        } else if (text.equals("giảm mức cảm biến", ignoreCase = true)){
            ledControl.adjustSensor(true)
            Toast.makeText(this,"Giảm mức cảm biến",Toast.LENGTH_SHORT).show()
        } else if (text.equals("chế độ thường 0", ignoreCase = true) || text.equals("chế độ thường không", ignoreCase = true)){
            ledControl.setEffect(0,0)
        } else if (text.equals("chế độ thường 1", ignoreCase = true) || text.equals("chế độ thường một", ignoreCase = true)){
            ledControl.setEffect(0,1)
        } else if (text.equals("chế độ thường 2", ignoreCase = true) || text.equals("chế độ thường hai", ignoreCase = true)){
            ledControl.setEffect(0,2)
        } else if (text.equals("chế độ thường 3", ignoreCase = true) || text.equals("chế độ thường  ba", ignoreCase = true)){
            ledControl.setEffect(0,3)
        } else if (text.equals("chế độ thường 4", ignoreCase = true) || text.equals("chế độ thường bốn", ignoreCase = true)){
            ledControl.setEffect(0,4)
        } else if (text.equals("chế độ thường 5", ignoreCase = true) || text.equals("chế độ thường năm", ignoreCase = true)){
            ledControl.setEffect(0,5)
        } else if (text.equals("chế độ thường 6", ignoreCase = true) || text.equals("chế độ thường sáu", ignoreCase = true)){
            ledControl.setEffect(0,6)
        } else if (text.equals("chế độ thường 7", ignoreCase = true) || text.equals("chế độ thường bảy", ignoreCase = true)){
            ledControl.setEffect(0,7)
        } else if (text.equals("chế độ thường 8", ignoreCase = true) || text.equals("chế độ thường tám", ignoreCase = true)){
            ledControl.setEffect(0,8)
        } else if (text.equals("chế độ thường 9", ignoreCase = true) || text.equals("chế độ thường chín", ignoreCase = true)){
            ledControl.setEffect(0,9)
        } else if (text.equals("chế độ thường 10", ignoreCase = true) || text.equals("chế độ thường mười", ignoreCase = true)){
            ledControl.setEffect(0,10)
        } else if (text.equals("chế độ thường 11", ignoreCase = true) || text.equals("chế độ thường mười một", ignoreCase = true)){
            ledControl.setEffect(0,11)
        } else if (text.equals("chế độ thường 12", ignoreCase = true) || text.equals("chế độ thường mười hai", ignoreCase = true)){
            ledControl.setEffect(0,12)
        } else if (text.equals("chế độ thường 13", ignoreCase = true) || text.equals("chế độ thường mười ba", ignoreCase = true)){
            ledControl.setEffect(0,13)
        } else if (text.equals("chế độ thường 14", ignoreCase = true) || text.equals("chế độ thường mười bốn", ignoreCase = true)){
            ledControl.setEffect(0,14)
        } else if (text.equals("chế độ thường 15", ignoreCase = true) || text.equals("chế độ thường mười năm", ignoreCase = true)){
            ledControl.setEffect(0,15)
        } else if (text.equals("chế độ âm thanh 0", ignoreCase = true) || text.equals("chế độ âm thanh không", ignoreCase = true)){
            ledControl.setEffect(1,0)
        }  else if (text.equals("chế độ âm thanh 1", ignoreCase = true) || text.equals("chế độ âm thanh một", ignoreCase = true)){
            ledControl.setEffect(1,1)
        }  else if (text.equals("chế độ âm thanh 2", ignoreCase = true) || text.equals("chế độ âm thanh hai", ignoreCase = true)){
            ledControl.setEffect(1,2)
        } else if (text.equals("chế độ âm thanh 3", ignoreCase = true) || text.equals("chế độ âm thanh ba", ignoreCase = true)){
            ledControl.setEffect(1,3)
        } else if (text.equals("chế độ âm thanh 4", ignoreCase = true) || text.equals("chế độ âm thanh bốn", ignoreCase = true)){
            ledControl.setEffect(1,4)
        } else if (text.equals("chế độ âm thanh 5", ignoreCase = true) || text.equals("chế độ âm thanh năm", ignoreCase = true)){
            ledControl.setEffect(1,5)
        } else if (text.equals("chế độ âm thanh 6", ignoreCase = true) || text.equals("chế độ âm thanh sáu", ignoreCase = true)){
            ledControl.setEffect(1,6)
        } else if (text.equals("chế độ âm thanh 7", ignoreCase = true) || text.equals("chế độ âm thanh bảy", ignoreCase = true)){
            ledControl.setEffect(1,7)
        } else {
            val regexPattern = Regex("^hiện chữ (.*)")
            val matchResult = regexPattern.find(text)
            if (matchResult != null) {
                //show text
                var textShow = matchResult.groupValues[1]
                ledControl.showText(converTextShow(textShow))

            } else {
                Toast.makeText(this,"Câu lệnh không đúng!",Toast.LENGTH_SHORT).show()
            }

        }
    }

    override fun onDestroy() {
        super.onDestroy()
        bluetoothManager.disconnect()
    }

    fun converTextShow(input: String): String {
        var result = input.toLowerCase()
        result = result.replace("[@#]".toRegex(), "")
        val unaccentedString = java.text.Normalizer.normalize(result, java.text.Normalizer.Form.NFD)
            .replace("\\p{M}".toRegex(), "")
        return unaccentedString
    }

}

