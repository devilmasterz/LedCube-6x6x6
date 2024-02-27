package com.example.ledcubecontrol

class LedControl(private  val bluetoothManager: BluetoothManager) {

    fun turnONOFF() {
        bluetoothManager.sendData("on_off@")
    }

    fun turnON(){
        bluetoothManager.sendData("on@")
    }
    fun turnOFF(){
        bluetoothManager.sendData("off@")
    }




    fun setMode(mode: Int) {
        bluetoothManager.sendData("mode$mode@")
    }

    fun setEffect(mode: Int, effect : Int){

        bluetoothManager.sendData("mode${mode}_${effect}@")
    }

    fun showText(text : String){
        bluetoothManager.sendData("#$text@")
    }

    fun adjustSensor(up :Boolean){
        if (up){
            bluetoothManager.sendData("up@")
        }else{
            bluetoothManager.sendData("down@")
        }

    }

    fun reset(){
        bluetoothManager.sendData("reset@")
    }


}