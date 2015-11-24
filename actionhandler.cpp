#include "actionhandler.h"
#include <QDebug>

ActionHandler::ActionHandler(int baudRate)
{
    transferManager=new EasyTransferPi();
    connect(transferManager,SIGNAL(eventReadyToSend()),this,SLOT(onReadyToSend()));
    connect(transferManager,SIGNAL(eventDataArrived()),this,SLOT(onDataArrived()));
    baud=baudRate;
}

void ActionHandler::onDataArrived()
{
    qDebug()<<sensorData.batteryCurrent;
}
void ActionHandler::startConnection()
{
    transferManager->begin(details(sensorData),baud);
}

//awares that conection is established
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
