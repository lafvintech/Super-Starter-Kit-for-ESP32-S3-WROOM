const byte ledPins[] = {38, 39, 40};  //define led pins
const byte chns[] = {0, 1, 2};        //define the pwm channels

void setup() {
  for (int i = 0; i < 3; i++) {       //setup the pwm channels
    ledcAttachChannel(ledPins[i], 1000, 8, chns[i]);
  }
}

void loop() {
  // Cycle through all 256 color positions
  for (int i = 0; i < 256; i++) {
    setColor(wheel(i));
    delay(20);  // Small delay for visible color transition
  }
}

// Function to set RGB LED color based on a single long value
void setColor(long rgb) {
  // Extract individual color components and set PWM values
  // Note: 255 - value is used for common anode LEDs
  ledcWrite(ledPins[0], 255 - (rgb >> 16) & 0xFF);  // Red
  ledcWrite(ledPins[1], 255 - (rgb >> 8) & 0xFF);   // Green
  ledcWrite(ledPins[2], 255 - (rgb >> 0) & 0xFF);   // Blue
}

// Function to generate a color wheel effect
long wheel(int pos) {
  long WheelPos = pos % 0xff;
  
  // Generate RGB color based on the position in the wheel
  if (WheelPos < 85) {
    // Red to Green transition
    return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
  } else if (WheelPos < 170) {
    // Green to Blue transition
    WheelPos -= 85;
    return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
  } else {
    // Blue to Red transition
    WheelPos -= 170;
    return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
  }
}