#include <OneWire.h>
#include <DallasTemperature.h>

String command;

// Data wire is connected to pin 2
#define ONE_WIRE_BUS 6

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);


// C++ code
//

const int left_motor_a = 2;
const int left_motor_b = 3;
const int right_motor_a = 5;
const int right_motor_b = 4;
const int enable_a = A13;
const int enable_b = A5;

void forward(int second) {
  //Serial.println("Forward Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  delay(second * 1000);
  
}

void backward(int second) {
  //Serial.println("backward Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, HIGH);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  delay(second * 1000);
  
}

void right(int second) {
  //Serial.println("right Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  delay(second * 1000);
  
}

void left(int second) {
  //Serial.println("left Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
  delay(second * 1000);
  
}



void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(left_motor_a, OUTPUT); // left motor: CCW
  pinMode(left_motor_b, OUTPUT); // left motor: CW
  pinMode(right_motor_a, OUTPUT); // right motor: CCW
  pinMode(right_motor_b, OUTPUT); // right motor: CW
  pinMode(enable_a, OUTPUT);
  pinMode(enable_b, OUTPUT);
  
}

const int seconds = 2;

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.println(temperature);
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
    }
  
  delay(1000); // Wait for a second  
}
