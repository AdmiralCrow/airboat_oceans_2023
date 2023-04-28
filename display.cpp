#include "display.h"

// Constructor for the Display class
Display::Display() : lcd(0x27, 16, 2) {}

// Initialize the LCD display
void Display::init() {
  lcd.init();
  lcd.backlight();
}

// Update the LCD display with temperature and GPS location data
void Display::update(float temperature, double latitude, double longitude) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 2);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Lat: ");
  lcd.print(latitude, 6);
  lcd.print(", Long: ");
  lcd.print(longitude, 6);
}

// Scroll the contents of the LCD display left
void Display::scrollDisplayLeft() {
  lcd.scrollDisplayLeft();
}
