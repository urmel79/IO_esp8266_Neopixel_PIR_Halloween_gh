# Halloween spooky Pumpkin with ESP8266

This project is an example application for ESP8266, a Styrofoam pumpkin illuminated by Neopixel LED ring and a mp3 sound output based on DFPlayer.

An additional PIR motion sensor connected via an interrupt input recognizes movements in the environment and causes the LED light pattern to switch from a cozy fire imitation to a "spooky" blue-green as well as playing any scary sounds in mp3 format from microSD card.

The basic idea comes from the blog at AZ-Delivery: https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/halloween-2019-der-kuerbis-erwacht-wieder.

## Visual impression

(Image follows)

(Video follows)

## Parts list

Following parts I have used in this project:

- breadboard half+ (400 holes)
- wire jumpers
- LiPo battery pack
- USB cable with mini USB plug
- breadboard power supply (with Mini-USB-**Input**)
- Wemos D1 Mini pro (ESP8266)
- Neopixel RGB LED ring, diameter 50 mm (with 12 seperate controllable RGB LEDs by WS2812B chip)
- DFPlayer mini MP3 player module
- microSD card (16 GB)
- passive speaker (2 W, 8 Ohm)
- PIR module (motion sensor based on HC-SR501)
- resistor 1 kOhm (for protecting RxD input of DFPlayer)
- capacitor 1000 µF (protecting the Neopixel LED module)

## Breadboard layout and schematics

With *Fritzing* (https://fritzing.org) I have created following breadboard layout:

![Breadboard Layout](./fritzing/esp8266_Neopixel_PIR_Halloween_Breadboard.png)

The schematics looks like this:

![Schematics](./fritzing/esp8266_Neopixel_PIR_Halloween_Schematics.png)

## Software libraries

## SDcard: file/folder layout

## Todo and known issues

[issue 2019-12-07] If esp8266 cannot connect to wifi at any reason, the program stucks.








<!--  -->
