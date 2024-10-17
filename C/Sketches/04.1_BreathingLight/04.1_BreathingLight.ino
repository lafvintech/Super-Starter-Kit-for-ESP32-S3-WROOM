// Define the LED pin number
#define PIN_LED   2

// Define the PWM channel number
#define CHN       0

// Define the PWM frequency in Hz
#define FRQ       1000

// Define the PWM resolution (8 bits = 256 levels)
#define PWM_BIT   8

void setup() {
  // Configure LED pin for PWM output
  // Parameters: pin, frequency, resolution, channel
  ledcAttachPin(PIN_LED, CHN);
  ledcSetup(CHN, FRQ, PWM_BIT);
}

void loop() {
  // Fade the LED in (gradually increase brightness)
  for (int i = 0; i < 255; i++) {
    ledcWrite(CHN, i);  // Set PWM duty cycle
    delay(10);          // Small delay for visible effect
  }

  // Fade the LED out (gradually decrease brightness)
  for (int i = 255; i > -1; i--) {
    ledcWrite(CHN, i);  // Set PWM duty cycle
    delay(10);          // Small delay for visible effect
  }
}