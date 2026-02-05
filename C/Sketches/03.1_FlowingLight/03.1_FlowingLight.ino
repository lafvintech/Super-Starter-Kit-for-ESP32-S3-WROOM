// Define an array of byte to store the pin numbers for LEDs
byte ledPins[] = {21, 47, 48, 38, 39, 40, 41, 42, 2, 1};

// Declare a variable to store the number of LEDs
int ledCounts;

void setup() {
  // Calculate the number of LEDs using sizeof to get the total bytes of the array
  ledCounts = sizeof(ledPins);
  
  // Iterate through all LED pins and set them as OUTPUT
  for (int i = 0; i < ledCounts; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Forward iteration: from the first LED to the last
  for (int i = 0; i < ledCounts; i++) {
    digitalWrite(ledPins[i], HIGH);  // Turn on the current LED
    delay(100);                      // Wait for 100 milliseconds
    digitalWrite(ledPins[i], LOW);   // Turn off the current LED
  }
  
  // Backward iteration: from the last LED to the first
  for (int i = ledCounts - 1; i > -1; i--) {
    digitalWrite(ledPins[i], HIGH);  // Turn on the current LED
    delay(100);                      // Wait for 100 milliseconds
    digitalWrite(ledPins[i], LOW);   // Turn off the current LED
  }
}