#include "esp_camera.h"
#define CAMERA_MODEL_ESP32S3_EYE
#include "camera_pins.h"
#include "ws2812.h"
#include "sd_read_write.h"

#define BUTTON_PIN  0  // Define the pin for the button

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ws2812Init();  // Initialize WS2812 LED
  
  // Initialize SD card
  sdmmcInit();
  if (!SD_MMC.begin()) {  // Check if SD card is successfully mounted
    ws2812SetColor(1);  // SD card initialization failed, set red light
    Serial.println("SD card initialization failed");
    return;  // If SD card is necessary, you can return here
  }
  
  createDir(SD_MMC, "/camera");
  listDir(SD_MMC, "/camera", 0);
  
  if (cameraSetup() == 1) {
    ws2812SetColor(2);  // Camera setup successful, set green light
  } else {
    ws2812SetColor(1);  // Camera setup failed, set red light
    Serial.println("Camera setup failed");
    return;
  }
}

void loop() {
  if(digitalRead(BUTTON_PIN)==LOW){  // Check if button is pressed
    delay(20);  // Debounce delay
    if(digitalRead(BUTTON_PIN)==LOW){
	  	ws2812SetColor(3);  // Set LED color to indicate photo capture in progress
      while(digitalRead(BUTTON_PIN)==LOW);  // Wait for button release
      camera_fb_t * fb = NULL;
      fb = esp_camera_fb_get();  // Capture a photo
      if (fb != NULL) {
        int photo_index = readFileNum(SD_MMC, "/camera");  // Get the next file number
        if(photo_index!=-1)
        {
          String path = "/camera/" + String(photo_index) +".jpg";
          writejpg(SD_MMC, path.c_str(), fb->buf, fb->len);  // Save the photo to SD card
        }
        esp_camera_fb_return(fb);  // Return the frame buffer to be reused
      }
      else {
        Serial.println("Camera capture failed.");
      }
      ws2812SetColor(2);  // Set LED color back to indicate ready state
    }
  }
}

int cameraSetup(void) {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  // for larger pre-allocated frame buffer.
  if(psramFound()){
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    // Limit the frame size when PSRAM is not available
    config.frame_size = FRAMESIZE_SVGA;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return 0;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  s->set_vflip(s, 1); // flip it back
  s->set_brightness(s, 1); // up the brightness just a bit
  s->set_saturation(s, 0); // lower the saturation

  Serial.println("Camera configuration complete!");
  return 1;
}