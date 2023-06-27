#include <RTClib.h>

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
}

void loop() {
  // Get the current date and time from the RTC
  DateTime now = rtc.now();
  // Create the filename using the current date and time
  String theDateTime = String(now.year(), DEC) + "-" +
  formatDigits(now.month()) + "-" +
  formatDigits(now.day()) + "_" +
  formatDigits(now.hour()) + "_" +
  formatDigits(now.minute()) + "_" +
  formatDigits(now.second());

  Serial.print("Current Formatted Datetime: ");
  Serial.println(theDateTime);

  delay(1000);
}
