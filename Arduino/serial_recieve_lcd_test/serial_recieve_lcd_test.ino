#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();

  // Turn on the backlight
  lcd.backlight();
  lcd.clear();

  // Initialize Serial at 9600 baud rate
  Serial2.begin(9600);
}

void loop() {
  if (Serial2.available() > 0) {
    // Read the incoming data
    String message = Serial2.readStringUntil('\n');

    // Display the message on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    lcd.print(message);
  }
}
