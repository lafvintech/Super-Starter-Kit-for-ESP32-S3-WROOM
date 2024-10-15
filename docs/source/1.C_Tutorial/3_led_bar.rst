Chapter 3 LED Bar
=========================
We have learned how to control a LED blinking, next we will learn how to control 
a number of LEDs.

Project 3.1 Flowing Light
--------------------------
In this project, we use a number of LEDs to make a flowing light.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- Resistor 220Ω x10
- Jumper Wire x10
- LED Bar Graph x1

Connect
^^^^^^^

.. image:: img/connect/3.png

If LED bar does not work, try to rotate it for 180°. The label is random.

Sketch
^^^^^^^
This project is designed to make a flowing water lamp. Which are these actions: 
First turn LED1 ON, then turn it OFF. Then turn LED2 ON, and then turn it OFF... 
and repeat the same to all 10 LEDs until the last LED is turns OFF. This process 
is repeated to achieve the “movements” of flowing water. 
Upload following sketch:
:guilabel:`LAFVIN_Super_Starter_Kit_For_Esp32_S3\Sketches\Sketch_03.1_ButtonAndLed.`

.. image:: img/software/3.1.png

Download the code to ESP32-S3 WROOM and LED bar graph will light up from left to 
right and from right to left.

.. image:: img/phenomenon/3.1.png
    
Code
^^^^^^
The following is the program code:

.. code-block:: C

    byte ledPins[] = {21, 47, 48, 38, 39, 40, 41, 42, 2, 1};
    int ledCounts;

    void setup() {
    ledCounts = sizeof(ledPins);
    for (int i = 0; i < ledCounts; i++) {
        pinMode(ledPins[i], OUTPUT);
        }
    }

    void loop() {
    for (int i = 0; i < ledCounts; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(100);
        digitalWrite(ledPins[i], LOW);
    }
    for (int i = ledCounts - 1; i > -1; i--) {
        digitalWrite(ledPins[i], HIGH);
        delay(100);
        digitalWrite(ledPins[i], LOW);
        }
    }
