void setup() {
  // Initialize Serial2 with a baud rate of 9600
  Serial2.begin(9600);
}

void loop() {
  // Send a test message through Serial2
  Serial2.println("Test message from Arduino");

  // Wait for a second before sending the next message
  delay(1000);
}
