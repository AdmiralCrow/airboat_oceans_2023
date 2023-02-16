#include "DeviceDriverSet_xxx0.h"

extern DeviceDriverSet_Motor AppMotor;

enum SmartRobotCarMotionControl
{
  Forward, //(1)
  Backward, //(2)
  Left, //(3)
  Right, //(4)
  stop_it //(5)
}; 

struct Application_xxx
{
  SmartRobotCarMotionControl Motion_Control;
};

extern Application_xxx Application_SmartRobotCarxxx0;

static void ApplicationFunctionSet_SmartRobotCarMotionControl(SmartRobotCarMotionControl direction, uint8_t is_speed)
{
  static uint8_t directionRecord = 0;
  uint8_t Kp, UpperLimit;
  uint8_t speed = is_speed;
  
  switch (direction)
  {
    case Forward:
      AppMotor.DeviceDriverSet_Motor_control(direction_just, speed, direction_just, speed, control_enable); 
      break;
    case Backward:
      AppMotor.DeviceDriverSet_Motor_control(direction_back, speed, direction_back, speed, control_enable); 
      break;
    case Left:
      AppMotor.DeviceDriverSet_Motor_control(direction_back, speed, direction_just, speed, control_enable); 
      break;
    case Right:
      AppMotor.DeviceDriverSet_Motor_control(direction_just, speed, direction_back, speed, control_enable); 
      break;
    case stop_it:
      AppMotor.DeviceDriverSet_Motor_control(direction_void, 0, direction_void, 0, control_enable); 
      break;
    default:
      break;
  }
}
