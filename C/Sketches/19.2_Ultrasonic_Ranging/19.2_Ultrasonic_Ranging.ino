#include <UltrasonicSensor.h>

UltrasonicSensor ultrasonic(13, 14);  // Create ultrasonic sensor object, using pins 13 and 14

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud
  
  int temperature = 22;  // Set ambient temperature (in Celsius)
  ultrasonic.setTemperature(temperature);  // Calibrate sensor for the set temperature
}

void loop() {
  int distance = ultrasonic.distanceInCentimeters();  // Measure distance in centimeters
  Serial.printf("Distance: %dcm\n",distance);  // Print the measured distance
  delay(300);  // Wait for 300 milliseconds before next measurement
}