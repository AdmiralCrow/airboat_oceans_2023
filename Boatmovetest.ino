#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;

Application_xxx Application_SmartRobotCarxxx0;

void setup() {
  AppMotor.DeviceDriverSet_Motor_Init();
  delay(2000);
  Application_SmartRobotCarxxx0.Motion_Control = 0;

  DeviceDriverSet_Motor_CircularTrajectory(200 /*speed*/, 0 /*startAngle*/, 360 /*endAngle*/, -1 /*direction*/);

}

void loop() {

}

void DeviceDriverSet_Motor_CircularTrajectory(uint8_t speed, int startAngle, int endAngle, int direction) {
  for (int i = startAngle; i < endAngle; i++) {
    float radian = i * PI / 180;
    int speed_A = speed * cos(radian);
    int speed_B = speed * sin(radian);
    AppMotor.DeviceDriverSet_Motor_control(direction, speed_A, direction, speed_B, control_enable);
    delay(10);
  }
}
