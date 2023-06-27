#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <HCSR04.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <RTClib.h>  // Include the RTC library
#include "DTH_Turbidity.h"

#define SD_CS_PIN 53 // Define the chip select pin for the SD card
#define TEMPERATURE_PIN 6
#define GPS_RX_PIN 12 // Define the RX and TX pins
#define GPS_TX_PIN 13 // for the software serial.
#define DEPTH_TRIG_PIN 22
#define DEPTH_ECHO_PIN 23
#define TURBIDITY_PIN A9

SoftwareSerial gps_ss(GPS_RX_PIN, GPS_TX_PIN);
File dataFile;
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temp_sensor(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2); 
UltraSonicDistanceSensor depth_sensor(DEPTH_TRIG_PIN, DEPTH_ECHO_PIN);
RTC_DS3231 rtc;  // Create an instance of the RTC class
TinyGPSPlus gps;
DTH_Turbidity turb_sensor(TURBIDITY_PIN);

int getstr = 0;
float temp_measured;
int enA = A1;
int in1 = 2;
int in2 = 3;
int enB = A0;
int in3 = 4;
int in4 = 5;
float volt;
float ntu;

struct Coordinates {
  float latitude;
  float longitude;
};

Coordinates getCoordinates() {
  Coordinates coordinates;
  while (gps_ss.available() > 0) {
    if (gps.encode(gps_ss.read())) {
      if (gps.location.isValid()) {
        //delay(500);
        coordinates.latitude = gps.location.lat();
        coordinates.longitude = gps.location.lng();
        return coordinates;
      }
    }
  }
}

void moveForward() {
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
//  Serial.println("MForward");
}

void moveBackward(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
//  Serial.println("MBackward");
}

void moveRight(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
//  Serial.println("MRight");
}

void moveLeft(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
//  Serial.println("MLeft");
}

void stopMotion(){
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);  
//  Serial.println("STOP");
}

float round_to_dp( float in_value, int decimal_place ){
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float getTurbidity(){
  return turb_sensor.readTurbidity();
}

float getDepth() {
  return depth_sensor.measureDistanceCm();
}

float getTemperature(){
  temp_sensor.requestTemperatures();
  temp_measured = (temp_sensor.getTempCByIndex(0) * 9.0) / 5.0 + 32.0;
  return temp_measured;
}

// Helper function to format a number as two digits with leading zeros if necessary
String formatDigits(int digits) {
  if (digits < 10) {
    return "0" + String(digits);
  } else {
    return String(digits);
  }
}

String getFormattedDateTime() {
  DateTime now = rtc.now();
  String formattedDateTime = String(now.year()) + "-" +
                             formatDigits(now.month()) + "-" +
                             formatDigits(now.day()) + " " +
                             formatDigits(now.hour()) + ":" +
                             formatDigits(now.minute()) + ":" +
                             formatDigits(now.second());
  return formattedDateTime;
}

void appendDataToSD(float latitude, float longitude, float temperature, float depth, float turbidity) {
  if (dataFile) {
    dataFile.print(getFormattedDateTime());
    dataFile.print(",");
    dataFile.print(latitude, 6);
    dataFile.print(",");
    dataFile.print(longitude, 6);
    dataFile.print(",");
    dataFile.print(temperature, 6);
    dataFile.print(",");
    dataFile.print(depth, 6);
    dataFile.print(",");
    dataFile.println(turbidity, 6);

    dataFile.flush(); // Ensure data is written to the SD card
    //Serial.println("Data appended to SD card.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Data appended to SD card.");
  } else {
    //Serial.println("Error writing data to SD card.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error writing data to SD card.");
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();  // initialize the lcd 
  lcd.backlight(); // turn on the backlight

  lcd.print("Starting hover boat...");
  delay(1000);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  temp_sensor.begin();

  //String filename = "data.csv";
  rtc.begin();
  // Get the current date and time from the RTC
  DateTime now = rtc.now();
  // Create the filename using the current date and time
  String filename = String(now.year(), DEC) + "-" +
		  formatDigits(now.month()) + "-" +
		  formatDigits(now.day()) + "_" +
		  formatDigits(now.hour()) + "_" +
		  formatDigits(now.minute()) + "_" +
		  formatDigits(now.second()) + ".csv";
  SD.begin(SD_CS_PIN); // Initialize SD card
  // Open the data file in write mode
  // Check if the file already exists
  if (!SD.exists(filename)) {
    SD.begin(SD_CS_PIN);
    dataFile = SD.open(filename, FILE_WRITE);
    
    // Write the headers as the first row
    if (dataFile) {
      dataFile.println("Date Time, Latitude,Longitude,Temperature (C),Depth (cm),Turbidity (NTU)");
      dataFile.close();
      //Serial.println("File created with headers.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("File created with headers.");
    } else {
      //Serial.println("Error creating file.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error creating file.");
    }
  } else {
    // File already exists
    SD.begin(SD_CS_PIN);
    dataFile = SD.open(filename, FILE_WRITE);
    
    if (dataFile) {
      //Serial.println("File opened.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("File opened.");
    } else {
      //Serial.println("Error opening file.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error opening file.");
    }
  }
}

void loop() {
	float temp = getTemperature();
	float turbidity = getTurbidity();
	Coordinates coords = getCoordinates();
	float latitude = coords.latitude;
	float longitude = coords.longitude;
	float depth = getDepth();

	lcd.clear();
	//lcd.setCursor(0,0);
	//lcd.print("Temp: ");
	//lcd.print(temp);
	//lcd.setCursor(0,1);
	//lcd.print("Turb: ");
	//lcd.print(turbidity);
	//lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Lat:");
	lcd.print(latitude);
	lcd.setCursor(0,1);
	lcd.print("Lon:");
	lcd.print(longitude);

	getstr=Serial.read();

	if(getstr=='f'){
	moveForward();}
	else if(getstr=='b'){
	moveBackward();}
	else if(getstr=='l'){
	moveLeft();}
	else if(getstr=='r'){
	moveRight();}
	else if(getstr=='s'){
	stopMotion();}
	else if (getstr == '2') {
	Serial.print(temp);
	Serial.print(",");
	Serial.print(turbidity);
	Serial.print(",");
	//Serial.print("deep");
	Serial.print(depth, 6);
	Serial.print(",");
	Serial.print(latitude, 6);
	//Serial.print("far");
	Serial.print(",");
	Serial.print(longitude, 6);
	//Serial.print("too far");
	//Serial.print(",");

	appendDataToSD(latitude, longitude, temp, depth, turbidity);}
 
  delay(100);
}
