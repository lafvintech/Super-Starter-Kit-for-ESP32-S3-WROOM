#define PIN_ANALOG_IN  1  // Define the analog input pin number

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
}

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN);  // Read the analog value from the defined pin
  double voltage = adcVal / 4095.0 * 3.3;  // Convert ADC value to voltage

  // Print the ADC value and calculated voltage
  Serial.printf("ADC Val: %d, \t Voltage: %.2fV\r\n", adcVal, voltage);
  
  delay(200);  // Wait for 200 milliseconds before the next reading
}