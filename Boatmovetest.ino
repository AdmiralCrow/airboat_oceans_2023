// Define the pins for controlling the DC motors
const int motor_a = 9;// output2
const int motor_b = 11;//output1
const int enable = 6;

void setup()
{
  // Set the motor control pins to output mode
  pinMode(motor_a, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(enable, OUTPUT);
  
  // Initialize Serial communication at a baud rate of 9600
  Serial.begin(9600);
}

// Function for moving the robot forward for a specified duration
void forward(int seconds) {
  // Print a message to Serial to indicate the robot is moving forward
  Serial.println("Moving forward");

  // Set the direction signals for the motors to rotate them in the forward direction
  digitalWrite(motor_a, HIGH);
  digitalWrite(motor_b, LOW);

  // Set the speed control signals for the motors using analogWrite function
  analogWrite(enable, 200);

  // Wait for the specified duration of time using the delay function
  delay(seconds * 1000);
}

// Function for stopping the robot
void stop() {
  // Print a message to Serial to indicate the robot is stopping
  Serial.println("Stopping");

  // Set the direction signals for the motors to stop
  digitalWrite(motor_a, LOW);
  digitalWrite(motor_b, LOW);

  // Set the speed control signals for the motors to 0
  analogWrite(enable, 0);
}

// Function for moving the robot backward for a specified duration
void backward(int seconds) {
  // Print a message to Serial to indicate the robot is moving backward
  Serial.println("Moving backward");

  // Set the direction signals for the motors to rotate them in the backward direction
  digitalWrite(motor_a, LOW);
  digitalWrite(motor_b, HIGH);

  // Set the speed control signals for the motors using analogWrite function
  analogWrite(enable, 200);

  // Wait for the specified duration of time using the delay function
  delay(seconds * 1000);
}

// Function for turning the robot left for a specified duration
void turn_left(int seconds) {
  // Print a message to Serial to indicate the robot is turning left
  Serial.println("Turning left");

  // Set the direction signals for the motors to turn left
  digitalWrite(motor_a, LOW);
  digitalWrite(motor_b, HIGH);

  // Set the speed control signals for the motors using analogWrite function
  analogWrite(enable, 200);

  // Wait for the specified duration of time using the delay function
  delay(seconds * 1000);
}

// Function for turning the robot right for a specified duration
void turn_right(int seconds) {
  // Print a message to Serial to indicate the robot is turning right
  Serial.println("Turning right");

  // Set the direction signals for the motors to turn right
  digitalWrite(motor_a, HIGH);
  digitalWrite(motor_b, LOW);

  // Set the speed control signals for the motors using analogWrite function
  analogWrite(enable, 200);

  // Wait for the specified duration of time using the delay function
  delay(seconds * 1000);
}

void loop()
{
  // Move forward for 6 seconds
  forward(6);

  // Stop the robot
  stop();

  // Wait for 2 seconds before starting the next movement
  delay(2000);

  // Turn left for 2 seconds
  turn_left(2);

  // Stop the robot
  stop();

  // Wait for 2 seconds before starting the next movement
  delay(2000);

  // Turn right for 2 seconds
  turn_right(2);

 // Stop the robot
  stop();

  // Wait for 2 seconds before starting the next movement
  delay(2000);
}
