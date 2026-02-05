Chapter 11 Photoresistor & LED
=====================================
In this chapter, we will learn how to use a photoresistor.

Project 11.1 NightLamp
------------------------

A photoresistor is very sensitive to the amount of light present. We can take 
advantage of the characteristic to make a nightlight with the following function: 
when the ambient light is less (darker environment) the LED will automatically 
become brighter to compensate and when the ambient light is greater (brighter environment) 
the LED will automatically dim to compensate.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- Resistor 10kΩ  x1
- Resistor 220Ω  x1
- Photoresistor x1
- LED x1
- Jumper Wire x4

Component knowledge
^^^^^^^^^^^^^^^^^^^^
:ref:`Photoresistor <cpn_photoresistor>`
"""""""""""""""""""""""""""""""""""""""""""

Connect
^^^^^^^^^^^
The circuit of this project is similar to project Soft Light. The only difference 
is that the input signal is changed from a potentiometer to a combination of a 
photoresistor and a resistor.

.. image:: img/connect/11.png

Sketch
^^^^^^^
The circuit used is similar to the project Soft Light. The only difference is that 
the input signal of the pin of ADC changes from a potentiometer to a combination 
of a photoresistor and a resistor.

**Sketch_11.1_Nightlamp**

.. image:: img/software/11.1.png

Download the code to ESP32-S3 WROOM, if you cover the photoresistor or increase 
the light shining on it, the brightness of the LED changes accordingly.

Code
^^^^^^
The following is the program code:

.. code-block:: C

    #define PIN_ANALOG_IN   1     // Define the analog input pin
    #define PIN_LED         14    // Define the LED pin (PWM output)
    #define CHAN            0     // Define the PWM channel
    #define LIGHT_MIN       372   // Minimum light sensor value
    #define LIGHT_MAX       2048  // Maximum light sensor value

    void setup() {
    // Configure LED pin for PWM output
    // Parameters: pin, frequency (1000 Hz), resolution (12-bit), channel
    ledcAttachChannel(PIN_LED, 1000, 12, CHAN);
    }

    void loop() {
    int adcVal = analogRead(PIN_ANALOG_IN); //read adc

    // Constrain ADC value between LIGHT_MIN and LIGHT_MAX, then map to PWM range
    int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  // adcVal re-map to pwmVal

    ledcWrite(PIN_LED, pwmVal);    // set the pulse width.
    delay(10);  // Short delay before next reading/update
    }

