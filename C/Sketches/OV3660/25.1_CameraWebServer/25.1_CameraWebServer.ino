#include "esp_camera.h"
#include <WiFi.h>

// ===================
// Select camera model
// ===================
//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
//#define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
//#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
// ** Espressif Internal Boards **
//#define CAMERA_MODEL_ESP32_CAM_BOARD
//#define CAMERA_MODEL_ESP32S2_CAM_BOARD
//#define CAMERA_MODEL_ESP32S3_CAM_LCD

#include "camera_pins.h"

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid     = "********";
const char* password = "********";

void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

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
  
  // OV3660 optimized configuration - focus on quality and smoothness
  config.frame_size = FRAMESIZE_VGA;  // SVGA 640x480 - OV3660 optimal quality resolution
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  config.grab_mode = CAMERA_GRAB_LATEST;  // Get latest frame, reduce latency
  config.fb_location = CAMERA_FB_IN_DRAM;  // No PSRAM dependency, use DRAM
  config.jpeg_quality = 8;  // High quality setting (lower number = higher quality)
  config.fb_count = 1;  // Single buffer, reduce memory usage
  
  Serial.println("=== OV3660 Optimized Configuration ===");
  Serial.printf("Target resolution: SVGA (800x600)\n");
  Serial.printf("JPEG quality: %d (high quality)\n", config.jpeg_quality);
  Serial.printf("Frame buffer: DRAM (no PSRAM dependency)\n");

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  if (s == NULL) {
    Serial.println("Failed to get camera sensor");
    return;
  }
  
  Serial.printf("Camera sensor detected: PID=0x%02X\n", s->id.PID);
  
  // OV3660 specific image quality optimization settings
  s->set_vflip(s, 1); // flip it back
  s->set_brightness(s, 1); // moderate brightness increase
  s->set_saturation(s, 1); // slightly increase saturation for enhanced colors
  s->set_contrast(s, 1); // increase contrast for enhanced details
  
  // OV3660 image quality enhancement settings
  s->set_gainceiling(s, (gainceiling_t)2);  // gain ceiling, balance noise
  s->set_colorbar(s, 0);  // disable color bar
  s->set_whitebal(s, 1);  // enable auto white balance
  s->set_gain_ctrl(s, 1);  // enable auto gain
  s->set_exposure_ctrl(s, 1);  // enable auto exposure
  s->set_hmirror(s, 0);  // no horizontal mirror
  s->set_dcw(s, 1);  // enable downsampling
  s->set_bpc(s, 1);  // enable bad pixel correction, improve quality
  s->set_wpc(s, 1);  // enable white pixel correction
  s->set_raw_gma(s, 1);  // enable raw gamma correction
  s->set_lenc(s, 1);  // enable lens correction, reduce distortion
  
  // Set effect to normal mode (no effect)
  s->set_special_effect(s, 0);  // 0 = no effect
  
  Serial.println("OV3660 optimized for high image quality");
  
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);  // Disable WiFi power saving mode, improve performance
  
  // Set WiFi power to maximum
  WiFi.setTxPower(WIFI_POWER_19_5dBm);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.printf("WiFi signal strength: %d dBm\n", WiFi.RSSI());
  Serial.printf("WiFi channel: %d\n", WiFi.channel());

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop() {
  // Monitor system status
  static unsigned long last_report = 0;
  unsigned long now = millis();
  
  if (now - last_report > 30000) {  // Report status every 30 seconds
    last_report = now;
    Serial.printf("System Status - Free heap: %d bytes, Min free heap: %d bytes\n", 
                 ESP.getFreeHeap(), ESP.getMinFreeHeap());
    Serial.printf("WiFi status: %s, RSSI: %d dBm\n", 
                 WiFi.isConnected() ? "Connected" : "Disconnected", WiFi.RSSI());
  }
  
  // Lightweight delay, reduce CPU usage
  delay(1000);
}
