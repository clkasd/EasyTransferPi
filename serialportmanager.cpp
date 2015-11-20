#include "serialportmanager.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent) :
    QObject(parent)
{
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}
SerialPortManager::~SerialPortManager()
{
}
void SerialPortManager::openSerialPort(qint32 baudRate)
{
    QSerialPortInfo portToUse;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(!info.isBusy() && (info.description().contains("Arduino") || info.manufacturer().contains("Arduino")))
            portToUse = info;
    }

    if(portToUse.isNull() || !portToUse.isValid())
    {
        qDebug() << "port is not valid:" << portToUse.portName();
        return;
    }

    serial->setPortName(portToUse.portName());
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {

        emit eventConnectionEstablished();
        qDebug() << "Connected to" << portToUse.description() << "on" << portToUse.portName();
    } else {
        qCritical() << "Serial Port error:" << serial->errorString();

        qDebug() << tr("Open error");
    }
}



void SerialPortManager::closeSerialPort()
{
    serial->close();
    qDebug() << tr("Disconnected");
}
void SerialPortManager::writeData(QByteArray &data)
{

    serial->write(data);
    if(serial->waitForBytesWritten(10))
    {
        qDebug()<<data.toHex();
    }
}
void SerialPortManager::readData()
{
    QByteArray array=serial->readAll();
    while(serial->waitForReadyRead(10))
        array+=serial->readAll();
    emit eventDataRecieved(array);
}
void SerialPortManager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        // QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        qCritical() << "Serial Port error:" << serial->errorString();
        closeSerialPort();
    }
}
