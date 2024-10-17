#define PIN_ANALOG_IN   1     // Define the analog input pin
#define PIN_LED         14    // Define the LED pin (PWM output)
#define CHAN            0     // Define the PWM channel
#define LIGHT_MIN       372   // Minimum light sensor value
#define LIGHT_MAX       2048  // Maximum light sensor value

void setup() {
  // Configure LED pin for PWM output
  // Parameters: pin, frequency (1000 Hz), resolution (12-bit), channel
  ledcAttachChannel(PIN_LED, 1000, 12, CHAN);
}

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN); //read adc

  // Constrain ADC value between LIGHT_MIN and LIGHT_MAX, then map to PWM range
  int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  // adcVal re-map to pwmVal

  ledcWrite(PIN_LED, pwmVal);    // set the pulse width.
  delay(10);  // Short delay before next reading/update
}