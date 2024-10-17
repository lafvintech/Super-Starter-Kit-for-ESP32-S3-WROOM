#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define CAMERA_MODEL_ESP32S3_EYE
#include "camera_pins.h"
#define LED_BUILT_IN  2  // Define the built-in LED pin

// WiFi credentials
const char* ssid_Router     =   "********"; // Your router's SSID
const char* password_Router =   "********";; // Your router's password
const char *ssid_AP         =   "ESP32S3"; // Set your AP name
const char *password_AP     =   "12345678"; // Set your AP password

WiFiServer server_Cmd(5000);     // Command server on port 5000
WiFiServer server_Camera(8000);  // Camera server on port 8000
extern TaskHandle_t loopTaskHandle;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  pinMode(LED_BUILT_IN, OUTPUT);
  cameraSetup();  // Initialize the camera

  // Set up WiFi Access Point
  WiFi.softAP(ssid_AP, password_AP);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server_Camera.begin(8000);
  server_Cmd.begin(5000);
  /////////////////////////////////////////////////////
  // Connect to WiFi router
  WiFi.begin(ssid_Router, password_Router);
  Serial.print("Connecting ");
  Serial.print(ssid_Router);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  while (WiFi.STA.hasIP() != true) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  /////////////////////////////////////////////////////
  Serial.print("Camera Ready! Use '");
  Serial.print(WiFi.softAPIP());
  Serial.print(" or ");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect in RaspPICar app.");

  disableCore0WDT();  // Disable watchdog timer on core 0
  // Create tasks for command handling and LED blinking on core 0
  xTaskCreateUniversal(loopTask_Cmd, "loopTask_Cmd", 8192, NULL, 1, &loopTaskHandle, 0);
  xTaskCreateUniversal(loopTask_Blink, "loopTask_Blink", 8192, NULL, 1, &loopTaskHandle, 0);
}

// Main loop (runs on core 1)
void loop() {
  WiFiClient client = server_Camera.accept();  // Listen for incoming clients
  if (client) {
    Serial.println("Camera Server connected to a client.");
    String currentLine = "";
    while (client.connected()) {
      camera_fb_t * fb = NULL;
      while (client.connected()) {
        fb = esp_camera_fb_get();  // Get a frame from the camera
        if (fb != NULL) {
          // Send frame size
          uint8_t slen[4];
          slen[0] = fb->len >> 0;
          slen[1] = fb->len >> 8;
          slen[2] = fb->len >> 16;
          slen[3] = fb->len >> 24;
          client.write(slen, 4);
          // Send frame data
          client.write(fb->buf, fb->len);
          esp_camera_fb_return(fb);
        }
        else {
          Serial.println("Camera Error");
        }
      }
    }
    client.stop();
    Serial.println("Camera Client Disconnected.");
  }
}

// Task for handling commands (runs on core 0)
void loopTask_Cmd(void *pvParameters) {
  Serial.println("Task Cmd_Server is starting ... ");
  while (1) {
    WiFiClient client = server_Cmd.accept();
    if (client) {
      Serial.println("Command Server connected to a client.");
      String currentLine = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          client.write(c);
          Serial.write(c);
          if (c == '\n') {
            currentLine = "";
          }
          else {
            currentLine += c;
          }
        }
      }
      client.stop();
      Serial.println("Command Client Disconnected.");
    }
  }
}

// Task for blinking LED (runs on core 0)
void loopTask_Blink(void *pvParameters) {
  Serial.println("Task Blink is starting ... ");
  while (1) {
    digitalWrite(LED_BUILT_IN, !digitalRead(LED_BUILT_IN));  // Toggle LED state
    delay(1000);
  }
}

// Function to set up the camera
void cameraSetup() {
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
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  s->set_vflip(s, 1); // flip it back
  s->set_brightness(s, 1); // up the brightness just a bit
  s->set_saturation(s, 0); // lower the saturation

  Serial.println("Camera configuration complete!");
}