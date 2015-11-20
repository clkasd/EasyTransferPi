#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H
#include <easytransferpi.h>
#include <QObject>

//stuct to read
struct SensorFeedback
{
    float solarVoltage;
    float solarCurrent;
    float batteryVoltage;
    float batteryCurrent;
    float leftMotorCurrent;
    float rightMotorCurrent;
};
struct NavigationCommand
{
    int leftMotorPower;
    int rightMotorPower;
};
class ActionHandler : public QObject
{
    Q_OBJECT
public:
    ActionHandler(int baudRate);
    SensorFeedback sensorData;
    NavigationCommand navCommand;
    void startConnection();
signals:

public slots:
    void onDataArrived();
    void onReadyToSend();
private:
    EasyTransferPi* transferManager;
    int baud;
};

#endif // ACTIONHANDLER_H
