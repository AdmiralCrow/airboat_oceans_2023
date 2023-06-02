// Download library from https://github.com/duyhuynh/Turbidity_Sensor
// Unzip and rename top folder to "Turbidity_Sensor"
// Place renamed folder in Arduino libraries folder on your computer. 
// Windows: Documents\Arduino\libraries
// Mac: ~/Documents/Arduino/libraries
#include "DTH_Turbidity.h"

#define TURBIDITY_SENSOR_PIN A9

DTH_Turbidity turbSensor(TURBIDITY_SENSOR_PIN);
float ntu_val = 0;
float volt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Test Turbidity sensor by Duy Huynh");  
}

void loop() { 
  // put your main code here, to run repeatedly:
  ntu_val = turbSensor.readTurbidity();
  Serial.print("Nephelometric Turbidity Units: ");
  Serial.println(ntu_val);
  volt = turbSensor.getVoltage();
  Serial.print("Turbidity voltage: ");
  Serial.println(volt);
  delay(2000);
}
