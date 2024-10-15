Chapter 25 Camera Web Server
===============================
Project 25.1 Camera Web Server
---------------------------------

Connect ESP32-S3 using USB and check its IP address through serial monitor. Use 
web page to access IP address to obtain video and image data.

Connect
^^^^^^^
Connect ESP32-S3 to the computer using the USB cable.
.. image:: img/0/connect1.png

Sketch
^^^^^^^
**Sketch_25.1_As_CameraWebServer**

.. image:: img/software/25.1.png

Before running the program, please modify your router’s name and password in the 
box shown in the illustration above to make sure that your Sketch can compile and 
work successfully.

Compile and upload codes to ESP32-S3, open the serial monitor and set the baud 
rate to 115200, and the serial monitor will print out a network link address.

.. image:: img/phenomenon/25.1.png

If your ESP32-S3 has been in the process of connecting to router, but the inform
ation above has not been printed out, please re-check whether the router name and 
password have been entered correctly and press the reset key on ESP32-S3 WROOM to 
wait for a successful connection prompt.

Open a web browser, enter the IP address printed by the serial monitor in the 
address bar, and access it. Taking the Google browser as an example, here's what 
the browser prints out after successful access to ESP32S3's IP.

.. image:: img/phenomenon/25.1-1.png

Click on Start Stream. The effect is shown in the image below.

.. image:: img/phenomenon/25.1-2.png

.. note:: 
    If sketch compilation fails due to ESP32-S3 support package, follow the steps of the image to open the CameraWebServer. This sketch is the same as described in the tutorial above.

.. image:: img/phenomenon/25.1-3.png

Code
^^^^^^
The following is the program code.You need include other code files in the same 
folder when write your own code.

.. code-block:: C

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
    
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

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

    startCameraServer();

    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
    }

    void loop() {
    // Do nothing. Everything is done in another task by the web server
    delay(10000);
    }


Project 25.2 Video Web Server
----------------------------------
Connect to ESP32-S3 using USB and view its IP address through a serial monitor. 
Access IP addresses through web pages to obtain real-time video data.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- Type C USB Cable x1
- Memory Card x1

Connect
^^^^^^^
Connect ESP32-S3 to the computer using the USB cable.

.. image:: img/0/connect1.png

Sketch
^^^^^^^
**Sketch_25.2_As_VideoWebServer**

.. image:: img/software/25.2.png

Before running the program, please modify your router’s name and password in the 
box shown in the illustration above to make sure that your Sketch can compile and 
work successfully.

Compile and upload codes to ESP32-S3, open the serial monitor and set the baud 
rate to 115200, and the serial monitor will print out a network link address.

.. image:: img/phenomenon/25.2.png

If your ESP32-S3 has been in the process of connecting to router, but the inform
ation above has not been printed out, please re-check whether the router name and 
password have been entered correctly and press the reset key on ESP32-S3 WROOM to 
wait for a successful connection prompt.

Open a web browser, enter the IP address printed by the serial monitor in the 
address bar, and access it. Taking the Google browser as an example, here's what 
the browser prints out after successful access to ESP32S3's IP.

The effect is shown in the image below.

.. image:: img/phenomenon/25.2-1.png

Code
^^^^^^
The following is the main program code. You need include other code files in the same folder when write your own code.

.. code-block:: C

    #include "esp_camera.h"
    #include <WiFi.h>
    #include "sd_read_write.h"

    // Select camera model
    #define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

    #include "camera_pins.h"

    const char* ssid     = "********";   //input your wifi name
    const char* password = "********";   //input your wifi passwords

    void cameraInit(void);
    void startCameraServer();

    void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    cameraInit();
    sdmmcInit();
    removeDir(SD_MMC, "/video");
    createDir(SD_MMC, "/video");
    
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    startCameraServer();

    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
    }

    void loop() {
    // put your main code here, to run repeatedly:
    delay(10000);
    }

    void cameraInit(void){
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
    }

Project 25.3 Camera and SDcard
-------------------------------
In this chapter, we continue to use the camera and SD card. We will use the onboa
rd button as the shutter. When the button is pressed, the ESP32-S3 takes a photo 
and stores the photo in the SD folder.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- Type C USB Cable x1
- Memory Card x1

Connect
^^^^^^^
Connect ESP32-S3 to the computer using the USB cable.

.. image:: img/0/connect1.png

Sketch
^^^^^^^
Make sure your project folder contains the following images. These headers files make 
sure this program works

.. image:: img/software/25.3-1.png

**Sketch_25.3_Camera_SDcard**

.. image:: img/software/25.3.png

Compile and upload the code to the ESP32-S3. If your camera is not installed pro
perly, causing the camera to fail to initialize, or you have not inserted the SD 
card into the ESP32-S3 in advance, the on-board colored lights will turn on red 
as a reminder. If all is well, the onboard colored light will light up green. When 
the onboard BOOT button is pressed, the ESP32-S3 will capture the current camera 
image and save it in the "Camera" folder of the SD card. At the same time, the 
onboard LED lights up blue, and returns to green after taking a photo.

As shown in the image below, after uploading the code to the ESP32-S3, the ESP32
-S3 will automatically create a folder named "camera" in the SD card. Every time 
the BOOT button is pressed, the on-board colored light turns on blue, and ESP32-S3 
collects a photo information and stores it in the "camera" folder. Press the but
ton once to take a photo. When we press the RST button to reset the ESP32-S3, we 
can see that there are some photo files in the SD card folder. These photos you 
can read directly through the card reader.

.. image:: img/phenomenon/25.3.png

Code
^^^^^^
The following is the main program code. You need include other code files in the 
same folder when write your own code.

.. code-block:: C

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







