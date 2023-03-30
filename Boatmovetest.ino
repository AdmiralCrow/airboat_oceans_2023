// C++ code
//

const int left_motor_a = 4;
const int left_motor_b = 5;
const int right_motor_a = 6;
const int right_motor_b = 7;
const int enable_a = 10;
const int enable_b = 11;

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
  digitalWrite(right_motor_a, LOW); // This was changed from HIGH to LOW do boat moving backwards. 
  digitalWrite(right_motor_b, HIGH);
  digitalWrite(left_motor_a, LOW); // same change as above
  digitalWrite(left_motor_b, HIGH);
  analogWrite(enable_a, 200);
  analogWrite(enable_b, 200);
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
  forward(6);
  stop();
  delay(seconds * 1000);
}
