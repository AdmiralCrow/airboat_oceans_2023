#include <Wire.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HCSR04.h>
#include <TinyGPS++.h>
#include <SD.h>
#include "DTH_Turbidity.h"

#define GPS_RX_PIN 12 // Define the RX and TX pins
#define GPS_TX_PIN 13 // for the software serial.
#define SD_CS_PIN 53 // Define the chip select pin for the SD card
#define TEMPERATURE_PIN 6
#define TURBIDITY_PIN A9
#define DEPTH_TRIG_PIN 22
#define DEPTH_ECHO_PIN 23

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(TEMPERATURE_PIN);

// Pass our oneWire reference to DallasTemperature library
DallasTemperature temp_sensor(&oneWire);

DTH_Turbidity turb_sensor(TURBIDITY_PIN);

UltraSonicDistanceSensor depth_sensor(DEPTH_TRIG_PIN, DEPTH_ECHO_PIN);

SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;
File dataFile;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  SD.begin(SD_CS_PIN); // Initialize SD card

  // Open the data file in write mode, append if the file exists
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    // Check if the file is empty
    if (dataFile.size() == 0) {
      dataFile.println("Latitude,Longitude,Temperature (C),Turbidity,Depth");
    }
    dataFile.close();
    Serial.println("SD card initialized.");
  } else {
    Serial.println("Error opening data file.");
  }
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()){
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Append data to the data file
        appendDataToSD(latitude, longitude);
      }
    }
  }
}

void appendDataToSD(float latitude, float longitude) {
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(latitude, 6);
    dataFile.print(",");
    dataFile.print(longitude, 6);
    dataFile.print(",");
    dataFile.print(readTemperatureSensor(), 2);
    dataFile.print(",");
    dataFile.print(readTurbiditySensor(), 2);
    dataFile.print(",");
    dataFile.println(readDepthSensor(), 2);
    
    dataFile.flush(); // Ensure data is written to the SD card
    dataFile.close();
    Serial.println("Data appended to SD card.");
  } else {
    Serial.println("Error writing data to SD card.");
  }
}

float readTemperatureSensor() {
  // Replace with your code to read temperature
  // For example:
  // float temperature = analogRead(TEMPERATURE_PIN); // Read analog value
  // temperature = map(temperature, 0, 1023, -40, 125); // Map to temperature range
  // return temperature;
  // return 25.5; // Placeholder value
  return temp_sensor.getTempCByIndex(0);
}

float readTurbiditySensor() {
  // Replace with your code to read turbidity
  // For example:
  // float turbidity = analogRead(TURBIDITY_PIN); // Read analog value
  // turbidity = map(turbidity, 0, 1023, 0, 100); // Map to turbidity range
  // return turbidity;
  // return 50.0; // Placeholder value
  return turb_sensor.readTurbidity();
}

float readDepthSensor() {
  // Replace with your code to read depth
  // For example:
  // float depth = analogRead(DEPTH_PIN); // Read analog value
  // depth = map(depth, 0, 1023, 0, 100); // Map to depth range
  // return depth;
  // return 10.0; // Placeholder value
  return depth_sensor.measureDistanceCm();
}
