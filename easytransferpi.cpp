#include "easytransferpi.h"
#include <QDebug>
EasyTransferPi::EasyTransferPi(QObject *parent) :
    QObject(parent)
{
}
void EasyTransferPi::begin(uint8_t *ptr, uint8_t lenght, qint32 baudRate)
{
    address=ptr;
    size=lenght;
    isDataRecieved=FALSE;
    baud=baudRate;
    rx_array_inx=0;
    rx_buffer=(uint8_t*)malloc(size+1);
    portManager=new SerialPortManager();
    connect(portManager, SIGNAL(eventDataRecieved(QByteArray&)), this, SLOT(onDataIncoming(QByteArray&)));
    connect(portManager,SIGNAL(eventConnectionEstablished()),this,SLOT(onConnected()));

    openSerialPort();
}
void EasyTransferPi::onConnected()
{
    emit eventReadyToSend();
}
void EasyTransferPi::openSerialPort()
{
    portManager->openSerialPort(baud);
}
bool EasyTransferPi::receiveData()
{
    if(isDataRecieved)
    {
        isDataRecieved=FALSE;
        return TRUE;
    }
    return isDataRecieved;
}
void EasyTransferPi::onDataIncoming(QByteArray &data)
{
    if(data.length()>3)
    {
        rx_array_inx=0;
        while(data[rx_array_inx]!=0x06)
        {
            rx_array_inx++;
        }
        data.remove(0,rx_array_inx+1);
        if(data[0]==0x85)
        {
            rx_len=(int)data[1];
            if(rx_len!=size)
            {
                rx_len=0;
                return;
            }
        }
        if(rx_len!=0)
        {
            data.remove(0,2);
            calc_CS=rx_len;
            for (int i = 0; i < rx_len; ++i) {
                calc_CS^=data[i];
            }
            if(calc_CS==data[data.length()-1])//cs good
            {
                memcpy(address,data,size);
                rx_len=0;
                rx_array_inx=0;
                isDataRecieved=TRUE;
                emit eventDataArrived();
                return;
            }
        }
    }
}
void EasyTransferPi::sendData(uint8_t *dataPtr, uint8_t lenght)
{
    uint8_t CS=lenght;
    QByteArray dataArray;
    dataArray.push_back(0x06);
    dataArray.push_back(0x85);
    dataArray.push_back(lenght);
    for (int i = 0; i < lenght; ++i) {
        dataArray.push_back(dataPtr[i]);
        CS^=*(dataPtr+i);
    }
    dataArray.push_back(CS);
    portManager->writeData(dataArray);
}
