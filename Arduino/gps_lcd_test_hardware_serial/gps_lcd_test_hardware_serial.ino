#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

// Initialize the LCD display
// LiquidCrystal_I2C lcd(address, columns, rows);
LiquidCrystal_I2C lcd(0x27, 16, 2);

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // Use Serial1 for GPS communication

  lcd.init();  // initialize the lcd
  lcd.backlight(); // turn on the backlight

  lcd.print("Connecting to GPS");
}    

void loop() {
  while (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
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
