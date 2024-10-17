Driver installation
=========================

Installing the CH343 Driver (Importance)
----------------------------------------
Windows
^^^^^^^^
**Check whether CH343 has been installed**

ESP32-S3 WROOM uses CH343 to download codes. So before using it, we need to 
install CH343 driver in our computers.

1. Connect your computer and ESP32-S3 WROOM with a USB cable.

.. figure:: img/C_preparation/esp32_4.png
   :align: center

1. Turn to the main interface of your computer, select “This PC” and right-click 
to select “Manage”.

.. figure:: img/C_preparation/driver_5.png
   :align: center

3. Click “Device Manager”. If your computer has installed CH343, you can see“USB
-Enhances-SERIAL CH343 (COMx)”. And you can click here to move to the next step.

.. figure:: img/C_preparation/driver_6.png
   :align: center

**Installing CH343**

1. First, download CH343 driver, click `HERE <http://www.wch-ic.com/search?t=all
&q=ch343>`_ to download the appropriate one based on your operating system. 

.. figure:: img/C_preparation/driver_7.png
   :align: center

If you would not like to download the installation package, you can open 
“Lafvin_Super_Starter_Kit_for_ESP32_S3/CH343”, we have prepared the installation package.

.. figure:: img/C_preparation/driver_8.png
   :align: center

1. Open the folder “Lafvin_Super_Starter_Kit_for_ESP32_S3/CH343/Windows/”

.. figure:: img/C_preparation/driver_9.png
   :align: center

3. Double click “CH343SER.EXE”.

.. figure:: img/C_preparation/driver_10.png
   :align: center

4. Click “INSTALL” and wait for the installation to complete.

.. figure:: img/C_preparation/driver_11.png
   :align: center

5. Install successfully. Close all interfaces.

.. figure:: img/C_preparation/driver_12.png
   :align: center

6. When ESP32-S3 WROOM is connected to computer, select “This PC”, right-click 
to select “Manage” and click “Device Manager” in the newly pop-up dialog box, 
and you can see the following interface.

.. figure:: img/C_preparation/driver_6.png
   :align: center

7. So far, CH343 has been installed successfully. Close all dialog boxes.


MacOS
^^^^^^

1. First, download CH343 driver, click `HERE <http://www.wch-ic.com/search?t=all
&q=ch343>`_ to download the appropriate one based on your operating system. 

.. figure:: img/C_preparation/driver_7.png
   :align: center

If you would not like to download the installation package, you can open 
“Lafvin_Super_Starter_Kit_for_ESP32_S3/CH343”, we have prepared the installation package.
Second, open the folder “Lafvin_Super_Starter_Kit_for_ESP32_S3/CH343/MAC/”

.. figure:: img/C_preparation/driver_13.png
   :align: center

Third, click Continue.

.. figure:: img/C_preparation/driver_14.png
   :align: center

Fourth, click Install.

.. figure:: img/C_preparation/driver_15.png
   :align: center

Then, waiting Finsh.

.. figure:: img/C_preparation/driver_16.png
   :align: center

Finally, restart your PC.

.. figure:: img/C_preparation/driver_17.png
   :align: center

If you still haven't installed the CH340 by following the steps above, you can 
view readme.pdf to install it.

.. figure:: img/C_preparation/driver_18.png
   :align: center


Programming Software
------------------------
The Arduino IDE, known as Arduino Integrated Development Environment, provides 
all the software support needed to complete an Arduino project. It is a programming 
software specifically designed for Arduino, provided by the Arduino team, that 
allows us to write programs and upload them to the Arduino board. 

The Arduino IDE 2.0 is an open-source project. It is a big step from its sturdy 
predecessor, Arduino IDE 1.x, and comes with revamped UI, improved board & library 
manager, debugger, autocomplete feature and much more.

In this tutorial, we will show how to download and install the Arduino IDE 2.0 
on your Windows, Mac, or Linux computer.

Requirements
^^^^^^^^^^^^^^^^

* Windows - Win 10 and newer, 64 bits
* Linux - 64 bits
* Mac OS Intel - Version 10.14: "Mojave" or newer, 64 bits
* Mac OS Apple Silicon - Version 11: "Big Sur" or newer, 64 bits