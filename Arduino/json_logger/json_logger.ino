#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include "display.h"

//pins
#define ONE_WIRE_BUS 2
#define GPS_RX_PIN 4
#define GPS_TX_PIN 3
#define SD_CS_PIN 10

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;
File dataFile;
float temperatureA_c;
Display display; // create an instance of the Display class

void setup() {
  Serial.begin(9600);
  sensors.begin();
  gpsSerial.begin(9600);

  pinMode(SD_CS_PIN, OUTPUT);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD initialization failed.");
    return;
  }
//creates or edits existing file, then closes file
  if (!SD.exists("data1.txt")) {
    dataFile = SD.open("data1.txt", O_CREAT | O_WRITE);
    if (dataFile) {
      Serial.println("New file created.");
      dataFile.close();
    } else {
      Serial.println("Error creating file.");
    }
  }

  display.init(); // initialize the display
}

void printUTC(const TinyGPSTime &gpsTime) {
  char buffer[30];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
          gps.date.year(), gps.date.month(), gps.date.day(),
          gpsTime.hour(), gpsTime.minute(), gpsTime.second(), gpsTime.centisecond());

  Serial.print(buffer);
}

void logData() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  Serial.println("Logging Data.");
  sensors.requestTemperatures();
  float temperatureA_c = sensors.getTempCByIndex(0);

  char dataTxt[100];
  sprintf(dataTxt, "%04d-%02d-%02d,%02d:%02d:%02d,%.2f,%.6f,%.6f\n",
          gps.date.year(), gps.date.month(), gps.date.day(),
          gps.time.hour(), gps.time.minute(), gps.time.second(),
          temperatureA_c, gps.location.lat(), gps.location.lng());

  display.update(temperatureA_c, gps.location.lat(), gps.location.lng()); // update the display using the instance of the Display class

  Serial.print("\nTemperature:\n");
  Serial.print(temperatureA_c, 2);
  Serial.print(" C\n");
  Serial.print("GPS:\n");
  printUTC(gps.time);
  Serial.print("\nLatitude: ");
  Serial.print(gps.location.lat(), 6);
  Serial.print(", Longitude: ");
  Serial.print(gps.location.lng(), 6);
  Serial.print("\n");
  //opens file to then fill file with data and then closes
  dataFile = SD.open("data1.txt", FILE_WRITE);    
  if (dataFile) {
    dataFile.println(dataTxt);
    dataFile.close();
  } else {
    Serial.println("Error writing to file.");
  }
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) { // Only print data when there is an updated location
    sensors.requestTemperatures();
    float temperatureA_c = sensors.getTempCByIndex(0);

    logData();
    display.update(temperatureA_c, gps.location.lat(), gps.location.lng()); // update the display using the instance of the Display class
    delay(1000);
  }

  // Scroll contents of LCD display left every 5 seconds
  static unsigned long lastScrollTime = 0;
  if (millis() - lastScrollTime >= 5000) {
    display.scrollDisplayLeft(); // use the instance of the Display class to scroll the display
    lastScrollTime = millis();
  }
}
