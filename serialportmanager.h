#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H
#include <QtCore/QtGlobal>
#include <QObject>
#include <QtSerialPort/QSerialPort>
class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = 0);
    ~SerialPortManager();
    void writeData( QByteArray &data);
signals:
    void eventDataRecieved(QByteArray &data);
    void eventConnectionEstablished();
public slots:
    void openSerialPort(qint32 baudRate);
    void closeSerialPort();
    void readData();
private slots:
    void handleError(QSerialPort::SerialPortError error);
private:
    QSerialPort *serial;
};

#endif // SERIALPORTMANAGER_H
