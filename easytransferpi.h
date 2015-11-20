#ifndef EASYTRANSFERPI_H
#define EASYTRANSFERPI_H

#include <QObject>
#include <stdlib.h>
#include <QtSerialPort/QSerialPort>
#include <stdint.h>
#include <serialportmanager.h>
typedef uint8_t byte;
#define details(name) (byte*)&name,sizeof(name)
class EasyTransferPi : public QObject
{
    Q_OBJECT
public:
    explicit EasyTransferPi(QObject *parent = 0);
    void begin(uint8_t* ,uint8_t,qint32 baudRate);
    void sendData(uint8_t* ,uint8_t);
    bool receiveData();
    SerialPortManager* portManager;
signals:
    void eventDataArrived();
    void eventReadyToSend();
public slots:
    void onDataIncoming(QByteArray &data);
    void onConnected();
private:
    uint8_t *address;
    uint8_t size;
    uint8_t *rx_buffer;
    uint8_t rx_array_inx;
    uint8_t rx_len;
    uint8_t calc_CS;
    qint32 baud;
    void openSerialPort();
    bool isDataRecieved;
private slots:

};

#endif // EASYTRANSFERPI_H
