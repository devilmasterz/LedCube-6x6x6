package com.example.ledcubecontrol

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import com.example.ledcubecontrol.databinding.MainActivityBinding

class temp {




//    private  lateinit var binding: MainActivityBinding;
//    private lateinit var bluetoothAdapter: BluetoothAdapter
//    private lateinit var pairedDevicesListView: ListView
//    private lateinit var bluetoothManager: BluetoothManager
//    private lateinit var ledControl: LedControl
//    private var selectedDeviceAddress: String? = null
//    private lateinit var pairedDevices: ArrayList<BluetoothDevice>
//
//
//    override fun onCreate(savedInstanceState: Bundle?) {
//        super.onCreate(savedInstanceState)
//        binding = MainActivityBinding.inflate(layoutInflater);
//        val view = binding.root;
//        setContentView(view);
//
//        requestPermissions()
//
//
//        pairedDevices = ArrayList()
//
//
//        pairedDevicesListView = view.findViewById(R.id.listDevice)
//        pairedDevicesListView.onItemClickListener =
//            AdapterView.OnItemClickListener { _, _, position, _ ->
//                val deviceAddress = pairedDevices[position].address
//                selectedDeviceAddress = deviceAddress
//                bluetoothManager.connectToDevice(deviceAddress)
//            }
//
//
//        binding.btnConnect.setOnClickListener {
//            Toast.makeText(this, "Nội dung thông báo", Toast.LENGTH_SHORT).show()
//            showPairedDevices()
//        }
//
//
//        binding.btnOnoff.setOnClickListener {
//            ledControl.turnOn();
//        }
//
//
//    }
//
//
//    private fun requestPermissions() {
//        val permissions = arrayOf(
//            Manifest.permission.BLUETOOTH,
//            Manifest.permission.BLUETOOTH_ADMIN,
//            Manifest.permission.ACCESS_FINE_LOCATION,
//            Manifest.permission.ACCESS_COARSE_LOCATION,
//            Manifest.permission.BLUETOOTH_CONNECT
//        )
//
////        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
////            permissions.plus(Manifest.permission.BLUETOOTH_CONNECT)
////        }
//        ActivityCompat.requestPermissions(this, permissions, REQUEST_PERMISSIONS)
//    }
//    override fun onRequestPermissionsResult(
//        requestCode: Int,
//        permissions: Array<out String>,
//        grantResults: IntArray
//    ) {
//        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
//        if (requestCode == REQUEST_PERMISSIONS) {
//            if (grantResults.isNotEmpty() && grantResults.all { it == PackageManager.PERMISSION_GRANTED }) {
//                Log.e("az","loi1")
//                initializeBluetooth()
//
//            } else {
//                // Handle if the user denies any permission
//            }
//        }
//    }
//
//
//
//    @SuppressLint("MissingPermission")
//    private fun initializeBluetooth() {
//        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
//        bluetoothManager = BluetoothManager(bluetoothAdapter)
//        ledControl = LedControl(bluetoothManager)
//        pairedDevices = ArrayList()
//
//        if (!bluetoothAdapter.isEnabled) {
//            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
//
//            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
//        } else {
//            showPairedDevices()
//        }
//    }
//
//
//    @SuppressLint("MissingPermission")
//    private fun showPairedDevices() {
//        pairedDevices.clear() // Clear the old list
//
//
//        val devices: Set<BluetoothDevice>? =  bluetoothAdapter.bondedDevices
//
//        devices?.forEach { device ->
//            pairedDevices.add(device)
//        }
//        Log.e("d","zzzz");
//        val deviceNames = pairedDevices.map { "${it.name} - ${it.address}" }
//        val adapter =
//            ArrayAdapter(this, android.R.layout.simple_list_item_1, deviceNames)
//        pairedDevicesListView.adapter = adapter
//    }
//
//
//
//    companion object {
//        private const val REQUEST_PERMISSIONS = 1
//        private const val REQUEST_ENABLE_BT = 2
//    }

}