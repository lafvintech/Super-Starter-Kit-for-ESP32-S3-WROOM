#include "driver/ledc.h"

#define PIN_BUZZER 14           // Define the pin number for the buzzer
#define PIN_BUTTON 21           // Define the pin number for the button
#define LEDC_CHANNEL LEDC_CHANNEL_0  // Define the LEDC channel
#define LEDC_TIMER LEDC_TIMER_0      // Define the LEDC timer
#define LEDC_MODE LEDC_LOW_SPEED_MODE  // Set LEDC mode to low speed
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // 13-bit duty resolution
#define LEDC_FREQUENCY 2000     // Initial frequency

void setup() {
  pinMode(PIN_BUTTON, INPUT);   // Set button pin as input

  // Configure LEDC timer
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_MODE,
    .duty_resolution = LEDC_DUTY_RES,
    .timer_num = LEDC_TIMER,
    .freq_hz = LEDC_FREQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&ledc_timer);

  // Configure LEDC channel
  ledc_channel_config_t ledc_channel = {
    .gpio_num = PIN_BUZZER,
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL,
    .timer_sel = LEDC_TIMER,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&ledc_channel);

  // Initial beep
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 4095); // 50% duty cycle
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
  delay(300);
  ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
  ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {  // If button is pressed (assuming active LOW)
    alert();  // Call alert function
  } else {
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);  // Turn off the buzzer
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
  }
}

// Function to create a siren-like alert sound
void alert() {
  float sinVal;  // Variable to store sine value
  int toneVal;   // Variable to store calculated frequency

  for (int x = 0; x < 360; x += 10) {  // Loop through 360 degrees
    sinVal = sin(x * (PI / 180));  // Calculate sine value
    toneVal = 2000 + sinVal * 500;  // Calculate frequency
    ledc_set_freq(LEDC_MODE, LEDC_TIMER, toneVal);  // Set new frequency
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 4095);   // 50% duty cycle
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    delay(10);  // Short delay for audible frequency change
  }
}