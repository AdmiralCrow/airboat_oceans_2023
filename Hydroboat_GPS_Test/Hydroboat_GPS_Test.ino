#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int RXPin = 4, TXPin = 3;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600


TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXPin, TXPin); // the seri

LiquidCrystal_I2C lcd(0x27,16,2); 
int getstr = 0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HydroBot");
  lcd.setCursor(0,1);
  lcd.print("Have patience...");
  delay(2000);  
}

void loop() {
    if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        float latitude=gps.location.lat();
        float longitude=gps.location.lng();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Lat:");
    lcd.print(latitude);
    lcd.setCursor(0,
    1);
    lcd.print("Lon:");
    lcd.print(longitude);
    delay(500);}}}
     
}
