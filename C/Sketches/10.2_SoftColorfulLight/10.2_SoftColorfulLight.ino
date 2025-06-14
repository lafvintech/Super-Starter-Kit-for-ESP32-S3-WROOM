const byte adcChns[] = {14, 13, 12};    // define the adc channels
const byte ledPins[] = {38, 39, 40};    // define led pins
const byte pwmChns[] = { 0,  1,  2};    // define the pwm channels
int colors[] = {0, 0, 0};               // red, green ,blue values of color.

void setup() {
  for (int i = 0; i < 3; i++) {         //setup the pwm channels
    ledcAttachChannel(ledPins[i], 1000, 8, pwmChns[i]);//1KHz, 8bit(0-255).
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    colors[i] = map(analogRead(adcChns[i]), 0, 4096, 0, 255); //calculate color value.
    ledcWrite(ledPins[i], 256 - colors[i]);                   //set color
  }
  delay(10);
}