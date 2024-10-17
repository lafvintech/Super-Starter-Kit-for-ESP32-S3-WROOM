Chapter 9 Potentiometer & LED
===============================
We have already learned about the use of ADC and PWM. In this chapter, we will 
learn how to use a potentiometer to control the brightness of LED.

Project 9.1 Soft Light
--------------------------
In this project, we will make a soft light. We will use an ADC Module to read ADC 
values of a potentiometer and map it to duty cycle of the PWM used to control the 
brightness of a LED. Then you can change the brightness of a LED by adjusting the 
potentiometer.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- Resistor 220Ω x1
- Potentiometer(10k) x1
- LED x1
- Jumper Wire x5

Connect
^^^^^^^^^^^^
.. image:: img/connect/9.1.png

Code
^^^^^^^
Move the program folder “Super_Starter_Kit_for_ESP32_S3/Python/Python_C
odes” to disk(D) in advance with the path of “D:/Micropython_Codes”.

Open “Thonny”, click “This computer” >> “D:” >> “Micropython_Codes” >> “09.1_Soft_L
ED” and double click “Soft_LED.py”.

**09.1_Soft_LED**

.. image:: img/software/9.1.png

Click “Run current script”. Rotate the handle of potentiometer and the brightness 
of LED will change correspondingly. 

The following is the code:

.. code-block:: python

    from machine import Pin,PWM,ADC
    import time

    pwm =PWM(Pin(14,Pin.OUT),1000)
    adc=ADC(Pin(1))
    adc.atten(ADC.ATTN_11DB)
    adc.width(ADC.WIDTH_12BIT)

    def remap(value,oldMin,oldMax,newMin,newMax):
        return int((value)*(newMax-newMin)/(oldMax-oldMin))

    try:
        while True:
            adcValue=adc.read()
            pwmValue=remap(adcValue,0,4095,0,1023)
            pwm.duty(pwmValue)
            print(adcValue,pwmValue)
            time.sleep_ms(100)
    except:
        pwm.deinit()


In the code, read the ADC value of the potentiometer. The ADC value range is 
0-4095. However, the default input range of the duty() function is 0-1023. 
Therefore, we need to write a remap() function to map the read ADC value to a 
value that conforms to the input range of the duty() function.

Project 9.2 Soft Colorful Light
---------------------------------

In this project, 3 potentiometers are used to control the RGB LED and in principle 
it is the same as the Soft Light project. Namely, read the voltage value of the 
potentiometer and then convert it to PWM used to control LED brightness. Difference 
is that the original project only controlled one LED, but this project required (3) 
RGB LEDs.

Component List
^^^^^^^^^^^^^^^
- ESP32-S3-WROOM x1
- GPIO Extension Board x1
- 830 Tie-Points Breadboard x1
- Resistor 220Ω  x3
- Potentiometer(10k) x3
- LED-RGB x1
- Jumper Wire x13

Connect
^^^^^^^

.. image:: img/connect/9.2.png

Code
^^^^^^
Open “Thonny”, click “This computer” >> “D:” >> “Micropython_Codes” >> “09.2_Soft_C
olorful_Light” and double click “Soft_Colorful_Light.py”.

**09.2_Soft_Colorful_Light**

.. image:: img/software/9.2.png

Click “Run current script” and control the change of RGBLED color by rotating 
the handles of three rotary potentiometers. 

The following is the program code:

.. code-block:: python
    
    from machine import Pin,PWM,ADC
    import time

    pwm0=PWM(Pin(40,Pin.OUT),10000)
    pwm1=PWM(Pin(39,Pin.OUT),10000)
    pwm2=PWM(Pin(38,Pin.OUT),10000)
    adc0=ADC(Pin(12))
    adc1=ADC(Pin(13))
    adc2=ADC(Pin(14))
    adc0.atten(ADC.ATTN_11DB)
    adc1.atten(ADC.ATTN_11DB)
    adc2.atten(ADC.ATTN_11DB)
    adc0.width(ADC.WIDTH_12BIT)
    adc1.width(ADC.WIDTH_12BIT)
    adc2.width(ADC.WIDTH_12BIT)

    def remap(value,oldMin,oldMax,newMin,newMax):
        return int((value)*(newMax-newMin)/(oldMax-oldMin))

    try:
        while True:
            pwm0.duty(1023-remap(adc0.read(),0,4095,0,1023))
            pwm1.duty(1023-remap(adc1.read(),0,4095,0,1023))
            pwm2.duty(1023-remap(adc2.read(),0,4095,0,1023))
            time.sleep_ms(100)
    except:
        pwm0.deinit()
        pwm1.deinit()
        pwm2.deinit()

In the code, read the ADC value of 3 potentiometers and map it into PWM duty cyc
le to control the control 3 LEDs with different color of RGBLED, respectively.

