#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <stdio.h>
#include <QtSerialPort/QSerialPortInfo>
#include <easytransferpi.h>
#include <actionhandler.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ActionHandler *easypi=new ActionHandler(9600);
    easypi->startConnection();
    return a.exec();
}
