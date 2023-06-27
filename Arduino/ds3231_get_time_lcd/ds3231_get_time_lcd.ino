#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

String formatDigits(int digits) {
  if (digits < 10) {
    return "0" + String(digits);
  } else {
    return String(digits);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup");
  rtc.begin();
  // Initialize the LCD
  lcd.init();
}

void loop() {
  // Get the current date and time from the RTC
  DateTime now = rtc.now();
  // Create the filename using the current date and time
  String theDate = String(now.year(), DEC) + "-" +
  formatDigits(now.month()) + "-" +
  formatDigits(now.day());

  String theTime = formatDigits(now.hour()) + "_" +
  formatDigits(now.minute()) + "_" +
  formatDigits(now.second());

  Serial.println(theDate);

    // Turn on the backlight and print a message
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Date: " + theDate);
  lcd.setCursor(0,1);
  lcd.print("Time: " + theTime);

  delay(1000);
}
