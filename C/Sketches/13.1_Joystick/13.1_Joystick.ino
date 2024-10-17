int xyzPins[] = {14, 13};   //x,y pins

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
}

void loop() {
  int xVal = analogRead(xyzPins[0]);  // Read X-axis value
  int yVal = analogRead(xyzPins[1]);  // Read Y-axis value
  Serial.printf("X,Y: %d,\t%d\n", xVal, yVal);  // Print X and Y values
  delay(500);  // Wait for 500 milliseconds before next reading
}