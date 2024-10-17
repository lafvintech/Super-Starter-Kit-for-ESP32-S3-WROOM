#define PIN_BUZZER 14  // Define the pin number for the buzzer
#define PIN_BUTTON 21  // Define the pin number for the button

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);  // Set the buzzer pin as an output
  pinMode(PIN_BUTTON, INPUT);   // Set the button pin as an input
}

void loop() {
  // Check if the button is pressed (LOW when pressed assuming a pull-up resistor)
  if (digitalRead(PIN_BUTTON) == LOW) {
    digitalWrite(PIN_BUZZER, HIGH);  // Turn on the buzzer
  } else {
    digitalWrite(PIN_BUZZER, LOW);   // Turn off the buzzer
  }
}