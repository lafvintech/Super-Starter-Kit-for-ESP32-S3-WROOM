#include <WiFi.h>

const char *ssid_Router     = "xxxxxxxxxxx";  // Enter the router name
const char *password_Router = "xxxxxxxxxxx";  // Enter the router password
const char *ssid_AP         = "WIFI_Name"; // Enter the AP name
const char *password_AP     = "12345678";  // Enter the AP password

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up ESP32...");

  // Set up the soft-AP configuration
  Serial.println("Setting soft-AP configuration...");
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA); // Set the mode to both AP and STA
  Serial.println("Setting soft-AP...");
  boolean apResult = WiFi.softAP(ssid_AP, password_AP);
  if (apResult) {
    Serial.println("AP Ready");
    Serial.println(String("Soft-AP IP address = ") + WiFi.softAPIP().toString());
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
  } else {
    Serial.println("AP Failed!");
  }

  // Set up the station configuration
  Serial.println("\nSetting Station configuration...");
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ") + ssid_Router);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Setup End");
}

void loop() {
  // You can add code here to handle traffic between the AP and Station interfaces
}