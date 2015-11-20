#include <EasyTransfer.h>
struct SensorsFeedback
{
    float solarVoltage;
    float solarCurrent;
    float batteryVoltage;
    float batteryCurrent;
    float leftMotorCurrent;
    float rightMotorCurrent;
};
struct NavigationCommand{
    int leftMotorPower;
    int rightMotorPower;
};
SensorsFeedback sensorData;
NavigationCommand navCommand;
EasyTransfer etIn;
EasyTransfer etOut;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  etIn.begin(details(navCommand), &Serial);
  etOut.begin(details(sensorData), &Serial);

}

void loop() {
  // put your main code here, to run repeatedly:
    sensorData.solarVoltage=7.9;
    sensorData.solarCurrent=7.9;
    sensorData.batteryVoltage=7.8;
    sensorData.batteryCurrent=7.1;
    sensorData.rightMotorCurrent=12.1;
    sensorData.leftMotorCurrent=11.2;
    etOut.sendData();
    if(etIn.receiveData())
    {
        if(navCommand.rightMotorPower==1601)
        {
            //data recieved.
        }
    }
    delay(50);

}
