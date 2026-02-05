void setup()
{
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
}

void loop()
{
  Serial.printf("Touch value: %d \r\n", touchRead(T14));  // get value using T14（GPIO14）
  delay(1000);  // Wait for 1 second before next reading
}