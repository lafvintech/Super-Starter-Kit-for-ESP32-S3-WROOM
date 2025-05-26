Chapter 16 Relay & Motor
=========================
In this chapter, we will learn a kind of special switch module, relay module.

Project 16.1 Control Motor with Potentiometer
------------------------------------------------
Control the direction and speed of the motor with a potentiometer.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- L293D x1
- 9V Battery Connector x1
- Potentiometer(10k) x1
- Motor & Fan x1
- Jumper Wire

Connect
^^^^^^^^^^^
Use caution when connecting this circuit, because the DC motor is a high-power 
component, do not use the power provided by the ESP32-S3 to power the motor directly, 
which may cause permanent damage to your ESP32-S3! The logic circuit can be powered 
by the ESP32-S3 power or an external power supply, which should share a common 
ground with ESP32-S3.

.. image:: img/connect/16.png

Note: the motor circuit uses A large current, about 0.2-0.3A without load.We rec
ommend that you use a 9V battery to power the extension board.

Sketch
^^^^^^^
**Sketch_16.1_Control_Motor_by_L293D**

.. image:: img/software/16.1.png

Download code to ESP32-S3 WROOM, Rotate the potentiometer clockwise, and the motor 
will gradually accelerate and rotate in one direction. Rotate the potentiometer in 
the opposite direction, and the motor will decelerate, stop, and then rotate in 
the other direction.

.. image:: img/phenomenon/16.1.png

Code
^^^^^^
The following is the program code:

.. code-block:: C

    int in1Pin = 13;      // Define L293D channel 1 pin
    int in2Pin = 14;      // Define L293D channel 2 pin
    int enable1Pin = 12;  // Define L293D enable 1 pin
    int channel = 0;

    boolean rotationDir;  // Define a variable to save the motor's rotation direction
    int rotationSpeed;    // Define a variable to save the motor rotation speed

    void setup() {
    Serial.begin(115200);
    // Initialize the pin into an output mode:
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enable1Pin, OUTPUT);

    ledcAttachChannel(enable1Pin, 1000, 11, channel);//Set PWM to 11 bits, range is 0-2047
    }

    void loop() {
    int potenVal = analogRead(A0);      // Convert the voltage of rotary potentiometer into digital
    //Compare the number with value 2048, 
    //if more than 2048, clockwise rotates, otherwise, counter clockwise rotates
    rotationSpeed = potenVal - 2048;
    if (potenVal > 2048)
        rotationDir = true;
    else
        rotationDir = false;
    // Calculate the motor speed
    rotationSpeed = abs(potenVal - 2048);
    //Control the steering and speed of the motor
    Serial.println(rotationSpeed);
    delay(100);
    driveMotor(rotationDir, constrain(rotationSpeed,0,2048));
    }

    void driveMotor(boolean dir, int spd) {
    // Control motor rotation direction
    if (dir) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
    }
    else {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
    }
    // Control motor rotation speed
    ledcWrite(enable1Pin, spd);
    }



