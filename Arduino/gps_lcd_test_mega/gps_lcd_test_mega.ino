#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

// Initialize the LCD display
// LiquidCrystal_I2C lcd(address, columns, rows);
LiquidCrystal_I2C lcd(0x27, 16, 2);

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Use Serial1 for GPS communication

  lcd.init();  // initialize the lcd
  lcd.backlight(); // turn on the backlight

  lcd.print("Waiting for GPS ...");
}

void loop() {
  while (Serial1.available() > 0) {
    if (gps.encode(Serial1.read())) {
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
