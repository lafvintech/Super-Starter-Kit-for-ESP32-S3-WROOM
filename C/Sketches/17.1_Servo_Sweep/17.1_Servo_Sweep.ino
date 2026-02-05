#define SERVO_PIN 21  //define the pwm pin
#define SERVO_CHN 0   //define the pwm channel
#define SERVO_FRQ 50  //define the pwm frequency
#define SERVO_BIT 12  //define the pwm precision

// Function prototypes
void servo_set_pin(int pin);
void servo_set_angle(int angle);

void setup() {
  servo_set_pin(SERVO_PIN);  // Initialize the servo pin
}

void loop() {
  for (int i = 0; i < 180; i++) {  //make light fade in
    servo_set_angle(i);  // Set servo angle from 0 to 179 degrees
    delay(10);  // Short delay for smooth movement
  }
  for (int i = 180; i > 0; i--) {  //make light fade out
    servo_set_angle(i);  // Set servo angle from 180 to 1 degrees
    delay(10);  // Short delay for smooth movement
  }
}

void servo_set_pin(int pin) {
  // Configure PWM for servo control
  ledcAttachChannel(pin, SERVO_FRQ, SERVO_BIT, SERVO_CHN);
}

void servo_set_angle(int angle) {
  if (angle > 180 || angle < 0)
    return;  // Ensure angle is within valid range
  long pwm_value = map(angle, 0, 180, 103, 512);  // Map angle to PWM value
  ledcWrite(SERVO_PIN, pwm_value);  // Set PWM duty cycle
}