.. _cpn_oled:

0.96 inch OLED Display Module
==================================

.. image:: img/oled.png
    :width: 300
    :align: center

Introduction
---------------------------
An OLED (Organic Light-Emitting Diode) display module is a device that uses organic compounds to produce light when an electric current passes through them, allowing it to display text, graphics, and images on a thin and flexible screen.

One of the primary benefits of an OLED display is that it generates its own light and does not require an additional backlight source. This results in OLED displays often having superior contrast, brightness, and viewing angles compared to LCD displays.

Another key characteristic of OLED displays is their ability to achieve deep black levels. In an OLED display, each pixel emits its own light, so to create a black color, the individual pixel can be completely turned off.

OLED displays also have lower power consumption since only the illuminated pixels draw current. This makes them particularly suitable for battery-powered devices like smartwatches, health trackers, and other portable electronics.

Principle
---------------------------
An OLED display module consists of an OLED panel and an OLED driver chip. The panel has tiny pixels made of organic materials that emit light when an electric current passes through electrodes. The driver chip uses the I2C protocol to control these pixels by converting signals from the Arduino into commands. Libraries like Adafruit SSD1306 help initialize the display, set brightness, and render text or images.

In this tutorial, we will use the SSD1306 model, a monochrome, 0.96-inch display with 128x64 pixels, as shown in the figure below.

**Example**

* :ref:`Basic_0.96_inch_OLED` (Basic Project)
* :ref:`Ext_Ping-Pong_Game` (Extension_Project)
* :ref:`Ext_Real-time_Weather_OLED` (Extension_Project)