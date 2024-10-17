#include <WiFi.h>

const char *ssid_AP     = "Your_AP"; //Enter the router name
const char *password_AP = "12345678"; //Enter the router password

IPAddress local_IP(192,168,1,100);//Set the IP address of ESP32 itself
IPAddress gateway(192,168,1,10);   //Set the gateway of ESP32 itself
IPAddress subnet(255,255,255,0);  //Set the subnet mask for ESP32 itself

void setup(){
  Serial.begin(115200);  // Initialize serial communication
  delay(2000);  // Wait for 2 seconds
  Serial.println("Setting soft-AP configuration ... ");
  WiFi.disconnect();  // Disconnect from any existing WiFi connection
  WiFi.mode(WIFI_AP);  // Set WiFi mode to Access Point

  // Configure the soft-AP with the specified IP, gateway, and subnet
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.println("Setting soft-AP ... ");
  boolean result = WiFi.softAP(ssid_AP, password_AP);  // Start the soft-AP
  if(result){
    Serial.println("Ready");
    // Print the IP address and MAC address of the soft-AP
    Serial.println(String("Soft-AP IP address = ") + WiFi.softAPIP().toString());
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
  }else{
    Serial.println("Failed!");
  }
  Serial.println("Setup End");
}
 
void loop() {
  // The loop is empty as this example only sets up the soft-AP
}