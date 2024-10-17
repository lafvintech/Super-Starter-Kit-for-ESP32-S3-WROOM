#define PIN_LED     21         // Define the LED pin
#define TOUCH_PIN   14          // Use a valid touch pin on ESP32-S3
#define PRESS_VAL   50000      // This threshold may need adjustment
#define RELEASE_VAL 65000      // This threshold may need adjustment

bool isProcessed = false;      // Flag to track if touch event has been processed

void setup() {
  Serial.begin(115200);        // Initialize serial communication
  pinMode(PIN_LED, OUTPUT);    // Set LED pin as output
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);  // Read touch sensor value
  //Serial.println(touchValue);  // Print touch value for debugging

  if (touchValue < PRESS_VAL) {  // Note: Lower value indicates touch
    if (!isProcessed) {          // If touch hasn't been processed yet
      isProcessed = true;        // Mark as processed
      Serial.println("Released!");
      reverseGPIO(PIN_LED);      // Toggle LED state
    }
  }
  if (touchValue > RELEASE_VAL) {  // Touch released
    if (isProcessed) {             // If a touch was previously processed
      isProcessed = false;         // Reset processed flag
      Serial.println("Touch detected!");
    }
  }
  
  delay(50);  // Short delay to prevent too frequent readings
}

void reverseGPIO(int pin) {
  digitalWrite(pin, !digitalRead(pin));  // Toggle the state of the given pin
}