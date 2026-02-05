void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  Serial.println("ESP32S3 initialization completed!");  // Print initialization message
}

void loop() {
  // Print the running time in seconds, formatted to one decimal place
  Serial.printf("Running time : %.1f s\r\n", millis() / 1000.0f);
  delay(1000);  // Wait for 1 second (1000 milliseconds)
}