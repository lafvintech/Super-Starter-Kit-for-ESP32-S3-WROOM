#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "String.h"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
char rxload[20];

// Define UUIDs for the BLE service and characteristics
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define LED 2  // Define LED pin

// Callback class for BLE server events
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
  }
};

// Callback class for BLE characteristic events
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = String(pCharacteristic->getValue().c_str());
    if (rxValue.length() > 0) {
      for (int i = 0; i < 20; i++) {
        rxload[i] = 0;
      }
      for (int i = 0; i < rxValue.length(); i++) {
        rxload[i] = (char)rxValue[i];
      }
    }
  }
};

// Function to set up BLE
void setupBLE(String BLEName) {
  const char *ble_name = BLEName.c_str();
  BLEDevice::init(ble_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void setup() {
  pinMode(LED, OUTPUT);  // Set LED pin as output
  setupBLE("ESP32S3_Bluetooth");
  Serial.begin(115200);
  Serial.println("\nThe device started, now you can pair it with Bluetooth!");
}

void loop() {
  long now = millis();
  if (now - lastMsg > 100) {  // Check every 100ms
    if (deviceConnected && strlen(rxload) > 0) {
      if (strncmp(rxload, "led_on", 6) == 0) {  // If received command is "led_on"
        digitalWrite(LED, HIGH);  // Turn on LED
      }
      if (strncmp(rxload, "led_off", 7) == 0) {  // If received command is "led_off"
        digitalWrite(LED, LOW);  // Turn off LED
      }
      Serial.println(rxload);  // Print received command
      memset(rxload,0,sizeof(rxload));  // Clear rxload buffer
    }
    lastMsg = now;
  }
}