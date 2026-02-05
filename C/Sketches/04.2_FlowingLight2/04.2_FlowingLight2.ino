// Array to store LED pin numbers
const byte ledPins[] = {21, 47, 38, 39, 40, 41, 42, 2};  //define led pins

// Array to store PWM channel numbers
const byte chns[] = {0, 1, 2, 3, 4, 5, 6, 7};  //define the pwm channels

// Array to define PWM duty cycles for the flowing effect
const int dutys[] = {0, 0, 0, 0, 0, 0, 0, 0,
                     1023, 512, 256, 128, 64, 32, 16, 8,
                     0, 0, 0, 0, 0, 0, 0, 0
                    };  //define the pwm dutys

// Variable to store the number of LEDs
int ledCounts;

// Delay time between each step of the flowing effect (in milliseconds)
int delayTimes = 50;  //flowing speed ,the smaller, the faster

void setup() {
  ledCounts = sizeof(ledPins);  //get the led counts
  
  // Configure PWM for each LED
  for (int i = 0; i < ledCounts; i++) {  //setup the pwm channels
    ledcAttachChannel(ledPins[i], 1000, 10, chns[i]);
  }
}

void loop() {
  // Flow light from one side to the other
  for (int i = 0; i < 16; i++) {        //flowing one side to other side
    for (int j = 0; j < ledCounts; j++) {
      ledcWrite(ledPins[j], dutys[i + j]);
    }
    delay(delayTimes);
  }
  
  // Flow light back from the other side
  for (int i = 0; i < 16; i++) {      //flowing one side to other side
    for (int j = ledCounts - 1; j > -1; j--) {
      ledcWrite(ledPins[j], dutys[i + (ledCounts - 1 - j)]);
    }
    delay(delayTimes);
  }
}