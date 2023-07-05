#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <HCSR04.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <RTClib.h> 
#include "DTH_Turbidity.h"

#define SD_CS_PIN 53
#define TEMPERATURE_PIN 6
#define GPS_RX_PIN 12
#define GPS_TX_PIN 13
#define DEPTH_TRIG_PIN 22
#define DEPTH_ECHO_PIN 23
#define TURBIDITY_PIN A9
#define EPSILON 0.01

SoftwareSerial gps_ss(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;
File dataFile;
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temp_sensor(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2); 
UltraSonicDistanceSensor depth_sensor(DEPTH_TRIG_PIN, DEPTH_ECHO_PIN);
RTC_DS3231 rtc;
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

double randomGaussian() {
  double u = (double)random() / (double)RAND_MAX;
  double v = (double)random() / (double)RAND_MAX;
  double x = sqrt(-2.0 * log(u)) * cos(2.0 * PI * v);
  return x;
}

Coordinates getCoordinates() {
  Coordinates coordinates;
  while (gps_ss.available() > 0) {
    if (gps.encode(gps_ss.read())) {
      if (gps.location.isValid()) {
        coordinates.latitude = gps.location.lat();
        coordinates.longitude = gps.location.lng();
        return coordinates;
      }
    }
  }
}

Coordinates addNoiseToCoordinates(Coordinates original) {
  Coordinates noisy;
  
  noisy.latitude = original.latitude + randomGaussian() * EPSILON;
  noisy.longitude = original.longitude + randomGaussian() * EPSILON;
  
  return noisy;
}

void moveForward() {
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void moveBackward(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
}

void moveRight(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
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

void appendDataToSD(float latitude, float longitude, float noisyLatitude, float noisyLongitude, float temperature, float depth, float turbidity) {
  if (dataFile) {
    dataFile.print(getFormattedDateTime());
    dataFile.print(",");
    dataFile.print(latitude, 10);
    dataFile.print(",");
    dataFile.print(longitude, 10);
    dataFile.print(",");
    dataFile.print(noisyLatitude, 10);
    dataFile.print(",");
    dataFile.print(noisyLongitude, 10);
    dataFile.print(",");
    dataFile.print(temperature, 10);
    dataFile.print(",");
    dataFile.print(depth, 10);
    dataFile.print(",");
    dataFile.println(turbidity, 10);

    dataFile.flush(); // Ensure data is written to the SD card
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Data appended to SD card.");
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error writing data to SD card.");
  }
}

void setup() {
  // Initialize the random number generator with a somewhat random seed
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
  gps_ss.begin(9600);
  
  lcd.init();  // initialize the lcd 
  lcd.backlight(); // turn on the backlight

  lcd.print("Starting air boat");
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
  String filename = String(now.year(), DEC) +
		  formatDigits(now.month()) +
		  formatDigits(now.day()) + ".csv";
  SD.begin(SD_CS_PIN); // Initialize SD card
  // Open the data file in write mode
  // Check if the file already exists
  if (!SD.exists(filename)) {
    SD.begin(SD_CS_PIN);
    dataFile = SD.open(filename, FILE_WRITE);
    
    // Write the headers as the first row
    if (dataFile) {
      dataFile.println("Date Time, Latitude,Longitude,Noisy Latitude, Noisy Longitude,Temperature (C),Depth (cm),Turbidity (NTU)");
      dataFile.close();
      //Serial.println("File created with headers.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("File created with headers.");
    } else {
      //Serial.println("Error creating file.");
      lcd.clear();
      lcd.setCursor(0,0);
      //lcd.print("Error creating file.");
      lcd.print(filename);
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
  while (gps_ss.available() > 0) {
    if (gps.encode(gps_ss.read())) {
      if (gps.location.isValid()) {

        Coordinates original = getCoordinates();
        Coordinates noisy = addNoiseToCoordinates(original);

        float latitude = original.latitude;
        float longitude = original.longitude;

        float noisyLatitude =  noisy.latitude;
        float noisyLongitude = noisy.longitude;
        
        float temp = getTemperature();
        float turbidity = getTurbidity();
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
        lcd.print(latitude, 9);
        lcd.setCursor(0,1);
        lcd.print("Lon:");
        lcd.print(longitude, 8);
        
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
        Serial.print(depth, 6);
        Serial.print(",");
        Serial.print(latitude, 6);
        Serial.print(",");
        Serial.print(longitude, 6);
        
        appendDataToSD(latitude, longitude, noisyLatitude, noisyLongitude, temp, depth, turbidity);}
      }
    }
  }

 
  delay(100);
}
