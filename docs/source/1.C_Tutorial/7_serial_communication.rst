Chapter 7 Serial Communication
=================================
Serial Communication is a means of communication between different devices/devices. 
This section describes ESP32-S3’s Serial Communication

Project 7.1 Serial Print
------------------------
This project uses ESP32-S3’s serial communicator to send data to the computer and 

print it on the serial monitor.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- Type C USB Cable x1

Connect
^^^^^^^^^^^
Connect ESP32-S3 to the computer with USB cable.

.. image:: img/0/connect1.png

Sketch
^^^^^^^
**Sketch_07.1_SerialPrinter**


.. image:: img/software/7.1.png

Download the code to ESP32-S3 WROOM, open the serial port monitor, set the baud 
rate to 115200, and press the reset button. As shown in the following figure:

.. image:: img/phenomenon/7.1.png

Code
^^^^^^
The following is the program code:

.. code-block:: C

    void setup() {
    Serial.begin(115200);
    Serial.println("ESP32S3 initialization completed!");
    }

    void loop() {
    Serial.printf("Running time : %.1f s\r\n", millis() / 1000.0f);
    delay(1000);
    }


Project 7.2 Serial Read and Write
------------------------------------
From last section, we use serial port on ESP32-S3 to send data to a com
puter, now we will use that to receive data from computer. 

Component and circuit are the same as in the previous project.

Sketch
^^^^^^^
**Sketch_07.2_SerialRW**

.. image:: img/software/7.2.png

Download the code to ESP32-S3 WROOM, open the serial monitor, and set the top 
right corner to Newline, 115200. As shown in the following figure:

Then type characters like 'ABCDEFG' into the data sent at the top, and press 
Ctrl+Enter to send the message.

.. image:: img/phenomenon/7.2.png

Code
^^^^^^
The following is the program code:

.. code-block:: C

    String inputString = "";      //a String to hold incoming data
    bool stringComplete = false;  // whether the string is complete

    void setup() {
    Serial.begin(115200);
    Serial.println(String("\nESP32S3 initialization completed!\r\n")
                    + String("Please input some characters,\r\n")
                    + String("select \"Newline\" below and Ctrl + Enter to send message to ESP32S3. \r\n"));
    }

    void loop() {
    if (Serial.available()) {         // judge whether data has been received
        char inChar = Serial.read();         // read one character
        inputString += inChar;
        if (inChar == '\n') {
        stringComplete = true;
        }
    }
    if (stringComplete) {
        Serial.printf("inputString: %s \r\n", inputString);
        inputString = "";
        stringComplete = false;
    }
    }

In loop(), determine whether the serial port has data, if so, read and save the 
data, and if the newline character is read, print out all the data that has been read.














