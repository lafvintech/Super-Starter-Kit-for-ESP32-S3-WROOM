#define PIN_ANALOG_IN   1   // Define the analog input pin
#define PIN_LED         14  // Define the LED pin (PWM output)
#define CHAN            0   // Define the PWM channel

void setup() {
  // Configure LED pin for PWM output
  // Parameters: pin, frequency (1000 Hz), resolution (12-bit), channel
  ledcAttachChannel(PIN_LED, 1000, 12, CHAN);
}

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN); //read adc
  int pwmVal = adcVal;        // adcVal re-map to pwmVal
  ledcWrite(PIN_LED, pwmVal);    // set the pulse width.
  delay(10);  // Short delay before next reading/update
}