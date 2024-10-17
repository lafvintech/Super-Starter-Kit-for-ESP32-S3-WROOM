String inputString = "";      //a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  Serial.println(String("\nESP32S3 initialization completed!\r\n")
                + String("Please input some characters,\r\n")
                + String("select \"Newline\" below and Ctrl + Enter to send message to ESP32S3. \r\n"));
  // Print initialization and instruction messages
}

void loop() {
  if (Serial.available()) {         // judge whether data has been received
    char inChar = Serial.read();         // read one character
    inputString += inChar;  // Add the character to the input string
    if (inChar == '\n') {  // If the incoming character is a newline
      stringComplete = true;  // Set the flag to indicate a complete string
    }
  }
  
  if (stringComplete) {  // If a complete string has been received
    Serial.printf("inputString: %s \r\n", inputString);  // Print the received string
    inputString = "";  // Clear the string for the next input
    stringComplete = false;  // Reset the completion flag
  }
}