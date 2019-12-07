# Halloween spooky Pumpkin with ESP8266

<!-- Bei diesem Projekt handelt es sich um eine Beispielapplikation für ESP8266, einen per Neopixel-LED-Ring illuminierten Styropor-Kürbis und einer Soundausgabe auf Basis von DFPlayer.  -->
This project is an example application for ESP8266, a Styrofoam pumpkin illuminated by Neopixel LED ring and a mp3 sound output based on DFPlayer.

<!-- Ein zusätzlich über einen Interrupt-Eingang angeschlossenen PIR-Bewegungsmelder erkennt Bewegungen in der Umgebung und bewirkt ein Umschalten des LED-Lichtpatterns von einer gemütlichen Feuerimitation in ein "gruseliges" Blaugrün sowie das Abspielen von beliebigen gruseligen Sounds im mp3-Format. -->
An additional PIR motion sensor connected via an interrupt input recognizes movements in the environment and causes the LED light pattern to switch from a cozy fire imitation to a "spooky" blue-green as well as playing any scary sounds in mp3 format from microSD card.

<!-- Die grundsätzliche Idee stammt vom Blog bei AZ-Delivery:  -->
The basic idea comes from the blog at AZ-Delivery: https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/halloween-2019-der-kuerbis-erwacht-wieder.

## Visual impression

(Image follows)

(Video follows)

## Parts list

<!-- Folgende Bauteile habe ich verbaut (abgesehen von einem Breadboard mit den entsprechenden Jumpern): -->
Following parts I have used in this project:

- Breadboard half+ (400 holes)
- wire jumpers
- LiPo battery pack
- breadboard power supply (with Mini-USB-**Input**)
- Wemos D1 Mini pro (ESP8266)
- Neopixel RGB LED ring, (with 12 seperate controllable RGB LEDs by WS2812B chip)
- DFPlayer clone (mp3 sound module)
- microSD card (16 GB)
- passive speaker (2 W, 8 Ohm)
- PIR module (motion sensor)
- resistor 1 kOhm (for protecting RxD input of DFPlayer)
- capacitor 1000 µF (protecting the Neopixel LED module)

## Breadboard layout and schematics

<!-- Mit Fritzing (https://fritzing.org) habe ich folgenden Schaltplan erstellt: -->
With *Fritzing* (https://fritzing.org) I have created following breadboard layout:

![Breadboard Layout](./fritzing/esp8266_Neopixel_PIR_Halloween_Breadboard.png)

The schematics looks like this:

![Schematics](./fritzing/esp8266_Neopixel_PIR_Halloween_Schematics.png)

## Software libraries

## SDcard: file/folder layout


## Mp3 Module: file/folder layout












<!--  -->
