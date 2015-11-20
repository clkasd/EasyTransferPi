# EasyTransferPi
Raspberrypi &amp; Arduino serial communication library(Available to use with Qt)

A library called EasyTransfer for arduino made serial communication dead simple between two arduinos.
But if you want to communicate with an arduino from your raspberrypi using EasyTransfer, use EasyTransferPi.

The protocol is designed to be used with EasyTransfer on Arduino.This is an example also.Arduino .ino file is included in Arduino folder.

# Installation:
Add these three classes on your Qt project :
<br />-EasyTransferPi
<br />-SerialPortManager
<br />-ActionHandler(to handle data processing)

# Usage:
ActionHandler class is an example about how to use this library.
You must create EasyTransferPi object and connect the eventReadyToSend() SIGNAL to some SLOT.
This operation indicates that the connection between RaspberryPi and Arduino is established.
```
EasyTransferPi *transferManager=new EasyTransferPi();
connect(transferManager,SIGNAL(eventReadToSend()),this,SLOT(onReadyToSend()));
```
Slot example:
```
void ActionHandler::onReadyToSend()
{
  while(1)
  {
    usleep(1000000);
    navCommand.leftMotorPower=1500;
    navCommand.rightMotorPower=1601;
    transferManager->sendData(details(navCommand));
  }
}
```
To start connection just call:
```
transferManager->begin(details(sensorData),baud);//sensorData=data to recieve.
```
To send data:
```
transferManager->sendData(details(navCommand));//navCommand=data to send.
```
ActionHandler class is where you take actions according to data communications.
So main.cpp is just for starting the task.
```
//main.cpp
ActionHandler *easypi=new ActionHandler(9600);
easypi->startConnection();//starts the connection.
```

Checkout blog post: http://developwear.com/blog/2015/11/20/easytransferpi-easytransfer-raspberrypi/
