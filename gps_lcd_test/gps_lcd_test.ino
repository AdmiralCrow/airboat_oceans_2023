#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h> 

#define RX_PIN 19 // Define the RX and TX pins
#define TX_PIN 18 // for the software serial.

// Initialize the LCD display
// LiquidCrystal_I2C lcd(address, columns, rows);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

SoftwareSerial ss(RX_PIN, TX_PIN);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);

  lcd.init();  // initialize the lcd 
  lcd.backlight(); // turn on the backlight

  lcd.print("Waiting for GPS ...");
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Lat: ");
        lcd.print(gps.location.lat(), 6);
  
        lcd.setCursor(0,1);
        lcd.print("Lon: ");
        lcd.print(gps.location.lng(), 6);
      }
    }
  }
}
