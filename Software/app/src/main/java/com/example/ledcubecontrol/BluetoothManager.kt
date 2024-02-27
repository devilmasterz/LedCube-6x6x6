package com.example.ledcubecontrol

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.pm.PackageManager
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import java.io.IOException
import java.io.OutputStream
import java.util.UUID

class BluetoothManager (){


    private lateinit var bluetoothSocket: BluetoothSocket
    private val MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
    private var isConnected: Boolean = false
    @SuppressLint("MissingPermission")
    fun connect(device: BluetoothDevice):Boolean {
        try {
            bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID)
            bluetoothSocket.connect()
            isConnected = true
            return  true;

        } catch (e: IOException) {

            e.printStackTrace()

            try {
                bluetoothSocket.close()
                isConnected = false
                return false;
            } catch (closeException: IOException) {
                closeException.printStackTrace()
                isConnected = false
                return false;
            }
        }
    }

    fun disconnect() {
        try {
            bluetoothSocket.close()
        } catch (e: IOException) {

            e.printStackTrace()
        }
    }

    fun sendData(data: String) {
        try {
            bluetoothSocket.outputStream.write(data.toByteArray())
        } catch (e: IOException) {

            e.printStackTrace()
        }
    }

    fun isConnected(): Boolean {
        return isConnected
    }


}