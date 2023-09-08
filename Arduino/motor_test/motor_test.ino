// C++ code
//

const int left_motor_a = 2;
const int left_motor_b = 3;
const int right_motor_a = 5;
const int right_motor_b = 4;
const int enable_a = A1 ;
const int enable_b = A0;

void setup()
{
  pinMode(left_motor_a, OUTPUT); // left motor: CCW
  pinMode(left_motor_b, OUTPUT); // left motor: CW
  pinMode(right_motor_a, OUTPUT); // right motor: CCW
  pinMode(right_motor_b, OUTPUT); // right motor: CW
  pinMode(enable_a, OUTPUT);
  pinMode(enable_b, OUTPUT);
  Serial.begin(9600);
 
}

void forward(int second) {
  Serial.println("Forward Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 255);
  analogWrite(enable_b, 255);
  delay(second * 1000);
  
}

void backward(int second) {
  Serial.println("backward Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, HIGH);
  analogWrite(enable_a, 255);
  analogWrite(enable_b, 255);
  delay(second * 1000);
  
}

void right(int second) {
  Serial.println("right Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 255);
  analogWrite(enable_b, 255);
  delay(second * 1000);
  
}

void left(int second) {
  Serial.println("left Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 255);
  analogWrite(enable_b, 255);
  delay(second * 1000);
  
}

void stop() {
  Serial.println("Stopping Motors");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
  analogWrite(enable_a, 0);
  analogWrite(enable_b, 0);
}

const int seconds = 2;

void loop()
{
  forward(10);
  stop();
  backward(2);
  stop();
  right(2);
  stop();
  left(2);
  stop();
  delay(seconds * 1000);
}
