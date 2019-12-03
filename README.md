# Halloween Pumpkin with ESP8266

Bei diesem Projekt handelt es sich um eine Beispielapplikation für ESP8266, einen per Neopixel-LED-Ring illuminierten Styropor-Kürbis und einer Soundausgabe auf Basis von DFPlayer. Ein zusätzlich über einen Interrupt-Eingang angeschlossenen PIR-Bewegungsmelder erkennt Bewegungen in der Umgebung und bewirkt ein Umschalten des LED-Lichtpatterns von einer gemütlichen Feuerimitation in ein "gruseliges" Blaugrün sowie das Abspielen von beliebigen gruseligen Sounds im mp3-Format.

Die grundsätzliche Idee stammt vom Blog bei AZ-Delivery: https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/halloween-2019-der-kuerbis-erwacht-wieder.

## Hier ein visueller Eindruck

(Bild)

(Video)

## Stückliste

Folgende Bauteile habe ich verbaut (abgesehen von einem Breadboard mit den entsprechenden Jumpern):

- LiPo Akku
- Breadboard-Spannungsversorgung (mit Mini-USB-**Eingang**)
- Wemos D1 Mini pro (ESP8266)
- Neopixel-LED-Ring (mit 12 einzeln ansteuerbaren RGB-LEDs)
- DFPlayer-Klon (mp3-Soundausgabe)
- microSD-Karte (16 GB)
- passiver Lautsprecher, 2 W, 8 Ohm
- PIR-Modul (Bewegungsmelder)

## Schaltplan

Mit Fritzing (https://fritzing.org) habe ich folgenden Schaltplan erstellt:

