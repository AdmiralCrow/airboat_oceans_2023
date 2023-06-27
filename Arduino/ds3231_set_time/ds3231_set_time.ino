#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  rtc.begin();

  // Set the time to a specific date
  DateTime dt(2023, 6, 26, 12, 30, 0); // Format: DateTime(year, month, day, hour, minute, second)
  rtc.adjust(dt);
}

void loop() {
  // Your code here
}
