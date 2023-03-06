const int right_motor_a = 24;
const int right_motor_b = 23;
const int right_motor_en = 25;

const int left_motor_a = 15;
const int left_motor_b = 14;
const int left_motor_en = 4;

void setup() {
  pinMode(right_motor_a, OUTPUT);
  pinMode(right_motor_b, OUTPUT);
  pinMode(right_motor_en, OUTPUT);
  
  pinMode(left_motor_a, OUTPUT);
  pinMode(left_motor_b, OUTPUT);
  pinMode(left_motor_en, OUTPUT);
  
  // set PWM frequency to 1000 Hz
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  
  analogWrite(right_motor_en, 191);
  analogWrite(left_motor_en, 191);
}

void forward(int second) {
  Serial.println("Forward Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  delay(second * 1000);
}

void reverse(int second) {
  Serial.println("Reverse Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, HIGH);
  delay(second * 1000);
}

void right(int second) {
  Serial.println("Right Moving");
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
  delay(second * 1000);
}

void left(int second) {
  Serial.println("Left Moving");
  digitalWrite(right_motor_a, HIGH);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, HIGH);
  delay(second * 1000);
}

void stop() {
  Serial.println("Stopping Motors");
  analogWrite(right_motor_en, 0);
  analogWrite(left_motor_en, 0);
}

void exit_() {
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
}

void loop() {
  forward(2);
  reverse(2);
  left(2);
  right(2);
  stop();
  exit_();
}
