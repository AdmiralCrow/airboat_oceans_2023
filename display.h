#ifndef DISPLAY_H // if DISPLAY_H is not defined, then define it
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

class Display {
public:
  // Constructor for the Display class
  Display();
  
  // Initialize the LCD display
  void init();
  
  // Update the LCD display with temperature and GPS location data
  void update(float temperature, double latitude, double longitude);
  
  // Scroll the contents of the LCD display left
  void scrollDisplayLeft();
  
private:
  LiquidCrystal_I2C lcd; // create a private instance of the LiquidCrystal_I2C class
};

#endif // end the #ifndef-#define block
