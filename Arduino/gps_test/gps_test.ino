#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define RX_PIN 19  // Define the RX and TX pins
#define TX_PIN 18  // for the software serial.

// The serial connection to the GPS module
SoftwareSerial ss(RX_PIN, TX_PIN);

TinyGPSPlus gps; // This is the GPS object that will interact with the U-Blox GPS module

void setup() {
  Serial.begin(9600);
  ss.begin(9600);

  Serial.println("Waiting for GPS ...");
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0) {
    // get the byte data from the GPS
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      // if a new set of coordinates has been received
      Serial.print("Latitude: "); 
      Serial.print(gps.location.lat(), 6); // print the latitude with 6 decimal places
      Serial.print(", Longitude: "); 
      Serial.println(gps.location.lng(), 6); // print the longitude with 6 decimal places
    }
  }
}
