#include <SD.h>

#define SD_CS_PIN 4
File dataFile;

void setup() {
  Serial.begin(9600);
  
  pinMode(SD_CS_PIN, OUTPUT);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD initialization failed.");
    return;
  }

  dataFile = SD.open("data1.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Hello World22");
    dataFile.close();
    Serial.println("Hello World written to file.");
  } else {
    Serial.println("Error opening file for write.");
  }
}

void loop() {
  // nothing here for this simple script
}
