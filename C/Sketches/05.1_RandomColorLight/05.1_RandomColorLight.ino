// Array to store pin numbers for red, green, and blue LED channels
const byte ledPins[] = {38, 39, 40};    //define red, green, blue led pins

// Array to store PWM channel numbers
const byte chns[] = {0, 1, 2};          //define the pwm channels

// Variables to store RGB color values
int red, green, blue;

void setup() {
  // Configure PWM for each LED channel (Red, Green, Blue)
  for (int i = 0; i < 3; i++) {   //setup the pwm channels,1KHz,8bit
    ledcAttachChannel(ledPins[i], 1000, 8, chns[i]);
  }
}

void loop() {
  // Generate random values (0-255) for red, green, and blue
  red = random(0, 256);
  green = random(0, 256);
  blue = random(0, 256);
  
  // Set the LED color using the random RGB values
  setColor(red, green, blue);
  
  // Wait for 200 milliseconds before changing color again
  delay(200);
}

// Function to set the RGB LED color
void setColor(byte r, byte g, byte b) {
  // For common anode LED, low level turns on the LED
  // So we invert the values (255 - value)
  ledcWrite(ledPins[0], 255 - r); //Common anode LED, low level to turn on the led.
  ledcWrite(ledPins[1], 255 - g);
  ledcWrite(ledPins[2], 255 - b);
}