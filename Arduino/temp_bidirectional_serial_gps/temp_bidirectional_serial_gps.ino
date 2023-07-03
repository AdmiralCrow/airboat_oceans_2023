#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

#define RX_PIN 12 // Define the RX and TX pins
#define TX_PIN 13 // for the software serial.
// Data wire is connected to pin 2
#define ONE_WIRE_BUS 6

// The serial connection to the GPS module
SoftwareSerial ss(RX_PIN, TX_PIN);

TinyGPSPlus gps; // This is the GPS object that will interact with the U-Blox GPS module

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// LiquidCrystal_I2C lcd(address, columns, rows);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

String command;
const int left_motor_a = 2;
const int left_motor_b = 3;
const int right_motor_a = 5;
const int right_motor_b = 4;
const int enable_a = A1;
const int enable_b = A0;

void forward(int second) {
  //Serial.println("Forward Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  //delay(second * 1000);
}

void backward(int second) {
  //Serial.println("backward Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, HIGH);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  //delay(second * 1000);
}

void right(int second) {
  //Serial.println("right Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  //delay(second * 1000);
}

void left(int second) {
  //Serial.println("left Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  //delay(second * 1000);
}

void stay(int second) {
  //Serial.println("stop Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  //delay(second * 1000);
}


void setup() {
  Serial.begin(9600);
  sensors.begin();
  ss.begin(9600);
  
  lcd.init();  // initialize the lcd 
  lcd.backlight(); // turn on the backlight

  lcd.print("Waiting for GPS ...");
  
  pinMode(left_motor_a, OUTPUT); // left motor: CCW
  pinMode(left_motor_b, OUTPUT); // left motor: CW
  pinMode(right_motor_a, OUTPUT); // right motor: CCW
  pinMode(right_motor_b, OUTPUT); // right motor: CW
  pinMode(enable_a, OUTPUT);
  pinMode(enable_b, OUTPUT);
}

const int seconds = 1;

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()){
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        sensors.requestTemperatures();
        float temperature = sensors.getTempCByIndex(0);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Lat: ");
        lcd.print(latitude, 9);
  
        lcd.setCursor(0,1);
        lcd.print("Lon: ");
        lcd.print(longitude, 8);
        
        Serial.println(String(temperature, 4) + "," + String(latitude, 10) + "," + String(longitude, 10));


        if (Serial.available()) {
          command = Serial.readStringUntil('\n');
          command.trim();
        
          if(command.equals("forward")) {
              forward(seconds);
            }
          else if(command.equals("backward")) {
              backward(seconds);
            }
          else if(command.equals("left")) {
              left(seconds);
            }
          else if(command.equals("right")) {
              right(seconds);
            }
          else if(command.equals("stop")) {
              stay(seconds);
            }
          }
        
        delay(1000); // Wait for a second
      }
    }
  }
}
