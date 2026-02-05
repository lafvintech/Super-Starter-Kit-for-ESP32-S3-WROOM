Chapter 13 Joystick
=========================
In the previous chapter, we have learned how to use rotary potentiometer. Now, 
let's learn a new electronic module joystick which working on the same principle 
as rotary potentiometer.

Project 13.1 Joystick
--------------------------
In this project, we will read the output data of a joystick and display it to the 
Terminal screen.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- Joystick x1
- Jumper Wire x5

Component knowledge
^^^^^^^^^^^^^^^^^^^^
:ref:`Joystick <cpn_joystick>`
"""""""""""""""""""""""""""""""""

Connect
^^^^^^^^^^^

.. image:: img/connect/13.png

Sketch
^^^^^^^
In this project’s code, We will read the ADC values of the X-axis and Y-axis of 
the joystick. The coordinate origin is in the upper left corner of the joystick, 
and then display these outputs in the terminal.

**Sketch_13.1_Joystick**

.. image:: img/software/13.1.png

Download the code to ESP32-S3 WROOM, open the serial port monitor, the baud rate 
is 115200, as shown in the figure below, shift (moving) the joystick or pressing 
it down will make the data change.

.. image:: img/phenomenon/13.1.png

Code
^^^^^^
The following is the program code:

.. code-block:: C

    int xyPins[] = {14, 13};   //x,y pins

    void setup() {
    Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
    }

    void loop() {
    int xVal = analogRead(xyPins[0]);  // Read X-axis value
    int yVal = analogRead(xyPins[1]);  // Read Y-axis value
    Serial.printf("X,Y: %d,\t%d\n", xVal, yVal);  // Print X and Y values
    delay(500);  // Wait for 500 milliseconds before next reading
    }

