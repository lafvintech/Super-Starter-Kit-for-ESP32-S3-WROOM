#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>

#define CAMERA_MODEL_ESP32S3_EYE
#include "camera_pins.h"
#define LED_BUILT_IN  2  // Built-in LED pin

// WiFi configuration
const char* ssid_Router     = "*********"; // Router SSID
const char* password_Router = "*********"; // Router password

WiFiServer server_Cmd(5000);     // Command server port 5000
WiFiServer server_Camera(8000);  // Camera server port 8000
TaskHandle_t cmdTaskHandle = NULL;
TaskHandle_t blinkTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  
  // Ultimate performance settings - for 8MB PSRAM hardware
  setCpuFrequencyMhz(240);           // Maximum CPU frequency
  
  // WiFi performance optimization
  WiFi.setTxPower(WIFI_POWER_19_5dBm); // Maximum WiFi transmission power
  
  // TCP/IP stack optimization
  WiFi.setSleep(false);              // Disable WiFi sleep to improve response speed
  
  // Initialize LED
  pinMode(LED_BUILT_IN, OUTPUT);
  digitalWrite(LED_BUILT_IN, LOW);
  
  // Initialize camera
  cameraSetup();

  // Connect to WiFi router
  Serial.printf("Connecting to %s ", ssid_Router);
  WiFi.begin(ssid_Router, password_Router);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  // Wait for WiFi connection
  uint8_t retries = 30;
  while (WiFi.status() != WL_CONNECTED && retries--) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println(":8000' to connect in app.");
    
    // Start servers
    server_Camera.begin(8000);
    server_Cmd.begin(5000);
  } else {
    Serial.println("WiFi connection failed!");
  }

  // Disable core 0 watchdog timer
  disableCore0WDT();
  
  // Memory optimization - fully utilize 8MB PSRAM
  heap_caps_malloc_extmem_enable(1024); // Enable external memory allocation
  
  // Create command processing and LED blinking tasks on core 0 - using larger stack space
  xTaskCreateUniversal(loopTask_Cmd, "loopTask_Cmd", 8192, NULL, 2, &cmdTaskHandle, 0);  // Increase stack size and priority
  xTaskCreateUniversal(loopTask_Blink, "loopTask_Blink", 4096, NULL, 1, &blinkTaskHandle, 0);
}

// Main loop (running on core 1)
void loop() {
  // Check WiFi connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost, reconnecting...");
    WiFi.reconnect();
    // Wait for reconnection, maximum 10 seconds
    uint8_t retries = 20;
    while (WiFi.status() != WL_CONNECTED && retries--) {
      delay(500);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nReconnected to WiFi");
    }
  }

  // Accept camera client connection
  WiFiClient client = server_Camera.accept();
  if (client) {
    Serial.println("Camera Server connected to a client.");
    
    // Ultimate TCP connection optimization
    client.setNoDelay(true);           // Disable Nagle algorithm
    client.setTimeout(100);            // Reduce timeout duration
    
    uint32_t frameCount = 0;
    uint32_t startTime = millis();
    
    while (client.connected()) {
      camera_fb_t *fb = esp_camera_fb_get();
      if (fb != NULL) {
        // Send frame size
        uint32_t frameSize = fb->len;
        client.write((uint8_t*)&frameSize, 4);
        
        // OV3660 optimized transmission - DRAM configuration using moderate transmission blocks
        size_t sentBytes = 0;
        while (sentBytes < fb->len) {
          size_t chunkSize = min(8192, (int)(fb->len - sentBytes)); // 8KB transmission block (DRAM optimized)
          size_t sent = client.write(fb->buf + sentBytes, chunkSize);
          if (sent == 0) {
            Serial.println("Send failed");
            break;
          }
          sentBytes += sent;
        }
        
        esp_camera_fb_return(fb);
        
        // Calculate and display frame rate
        frameCount++;
        if (frameCount % 30 == 0) {
          float fps = frameCount * 1000.0 / (millis() - startTime);
          Serial.printf("Stream FPS: %.2f\n", fps);
        }
      } else {
        Serial.println("Camera capture failed");
        delay(50); // Reduce delay on failure
      }
    }
    
    // Display final frame rate
    float fps = frameCount * 1000.0 / (millis() - startTime);
    Serial.printf("Stream ended. Average FPS: %.2f\n", fps);
    
    client.stop();
    Serial.println("Camera Client Disconnected.");
  }
  
  // Minimum delay to give video service more CPU time
  delay(1);
}

// Command processing task (running on core 0)
void loopTask_Cmd(void *pvParameters) {
  Serial.println("Command handler task started on Core 0");
  
  while (1) {
    WiFiClient client = server_Cmd.accept();
    if (client) {
      Serial.println("Command Server connected to a client.");
      client.setNoDelay(true);
      
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          client.write(c); // Echo received character
          Serial.write(c);
          
          // Command processing logic can be added here
        }
      }
      
      client.stop();
      Serial.println("Command Client Disconnected.");
    }
    
    // Small delay to prevent excessive CPU resource consumption
    delay(10);
  }
}

// LED blinking task (running on core 0)
void loopTask_Blink(void *pvParameters) {
  Serial.println("LED blink task started on Core 0");
  
  while (1) {
    digitalWrite(LED_BUILT_IN, !digitalRead(LED_BUILT_IN)); // Toggle LED state
    delay(500); // Increase blinking frequency
  }
}

// Camera setup function
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
  
  // OV3660 optimized configuration - solve stripe and anomaly issues
  config.xclk_freq_hz = 20000000;        // 20MHz XCLK (OV3660 recommended frequency)
  config.frame_size = FRAMESIZE_VGA;     // 800x600 resolution (OV3660 optimal resolution)
  config.pixel_format = PIXFORMAT_JPEG;  // JPEG format
  config.grab_mode = CAMERA_GRAB_LATEST; // Get latest frame to reduce latency
  config.fb_location = CAMERA_FB_IN_DRAM; // Use DRAM to avoid OV3660 PSRAM compatibility issues
  config.jpeg_quality = 20;              // Quality setting 20
  config.fb_count = 3;                   // 3 frame buffers (maximum allowed by DRAM)
  
  // Initialize camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  // OV3660 sensor specific optimization settings - solve stripe and anomaly issues
  sensor_t * s = esp_camera_sensor_get();
  
  if (s == NULL) {
    Serial.println("Failed to get camera sensor");
    return;
  }
  
  Serial.printf("Camera sensor detected: PID=0x%02X\n", s->id.PID);
  
  // OV3660 basic settings
  s->set_vflip(s, 1);         // Flip image (solve upside down issue)
  s->set_hmirror(s, 0);       // No horizontal mirror
  s->set_brightness(s, 1);    // Moderately increase brightness
  s->set_saturation(s, 1);    // Slightly increase saturation to enhance colors
  s->set_contrast(s, 1);      // Increase contrast to enhance details
  
  // OV3660 image quality enhancement settings
  s->set_gainceiling(s, (gainceiling_t)2);  // Gain ceiling, balance noise
  s->set_colorbar(s, 0);      // Disable color bar
  s->set_whitebal(s, 1);      // Enable auto white balance
  s->set_gain_ctrl(s, 1);     // Enable auto gain control
  s->set_exposure_ctrl(s, 1); // Enable auto exposure control
  s->set_dcw(s, 1);           // Enable downsampling
  s->set_quality(s, 20);      // Set sensor JPEG quality
  
  Serial.println("=== OV3660 Camera Configuration Complete ===");
  Serial.printf("Resolution: VGA (800x600)\\n");
  Serial.printf("JPEG quality: %d\\n", 12);
  Serial.printf("Frame buffer: DRAM (2 buffers)\\n");
  Serial.printf("XCLK frequency: 20MHz\\n");
  Serial.println("OV3660 optimized for stability and quality!");
}
