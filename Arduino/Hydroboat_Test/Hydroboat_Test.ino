#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial ss(15, 14); //rx, tx

File myFile;
OneWire oneWire(6);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2); 
int getstr = 0;
float temp_measured;
int enA = A1;
int in1 = 2;
int in2 = 3;
int enB = A0;
int in3 = 4;
int in4 = 5;
float volt;
float ntu;

void moveForward() {
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
//  Serial.println("MForward");
}

void moveBackward(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
//  Serial.println("MBackward");
}

void moveRight(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
//  Serial.println("MRight");
}

void moveLeft(){
  analogWrite(enA, 140);
  analogWrite(enB, 140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
//  Serial.println("MLeft");
}

void stopMotion(){
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);  
//  Serial.println("STOP");
}

float round_to_dp( float in_value, int decimal_place ){
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float getTurbidity(){
  volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(A9)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
//    Serial.print(volt);
//    Serial.println(" V");
//    Serial.print(ntu);
//    Serial.print(" NTU");
    delay(10);
    return ntu;
  }

float getTemperature(){
  sensors.requestTemperatures();
//  Serial.print(sensors.getTempCByIndex(0));
//  Serial.print(",");
//  Serial.println((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  temp_measured = (sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0;
  return temp_measured;
  
  delay(1000);
  }

float getLat(){
    while (ss.available() > 0){
      if (gps.encode(ss.read())){
        if (gps.location.isValid()){
            delay(500);
            float latitude = gps.location.lat();
            return latitude;}}}
}

float getLong(){
    while (ss.available() > 0){
      if (gps.encode(ss.read())){
        if (gps.location.isValid()){
            delay(500);
             float longitude = gps.location.lng();
             return longitude;}}}
}

//void cardReader(){
//  while (!Serial) {
//    ; // wait for serial port to connect.
//  }
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Init SD card...");
//
//  if (!SD.begin(53)) {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("init failed!");
//  }
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("init done.");
//
//  myFile = SD.open("test.txt");
//  if (myFile) {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("test.txt:");
//    while (myFile.available()) {
//      lcd.clear();
////      Serial.println("This is what is in the file!");
////      Serial.write(myFile.read());
//      lcd.setCursor(0,1);
//      lcd.print(myFile.read());
//    }
//
//    myFile.close();
//  } else {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("error opening test.txt");
//  }
//  }

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HydroBot");
  lcd.setCursor(0,1);
  lcd.print("Have patience...");
  delay(1000);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  sensors.begin();
  
}

void loop() {
  float temp = getTemperature();
  float turbidity = getTurbidity();
//  float latitude = getLat();
//  float longitude = getLong();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Turb: ");
  lcd.print(turbidity);
//  delay(500);
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Lat:");
//    lcd.print(latitude);
//    lcd.setCursor(0,1);
//    lcd.print("Lon:");
//    lcd.print(longitude);

     getstr=Serial.read();
     
     if(getstr=='f'){
      moveForward();
      delay(100);}
     else if(getstr=='b'){
      moveBackward();
      delay(100);}
     else if(getstr=='l'){
      moveLeft();
      delay(100);}
     else if(getstr=='r'){
      moveRight();
      delay(100);}
     else if(getstr=='s'){
      stopMotion();
      delay(100);}
     else if (getstr == '2') {
        delay(100);
        Serial.print(temp);
        Serial.print(",");
        Serial.print(turbidity);
        Serial.print(",");
        Serial.print("deep");
        Serial.print(",");
//        Serial.print(latitude, 6);
        Serial.print("far");
        Serial.print(",");
//        Serial.print(longitude, 6);
        Serial.print("too far");
        Serial.print(",");
        getstr = 0;
        delay(100);}
    
}
