#ifndef function_fastled_pir_hpp
#define function_fastled_pir_hpp

#include <FastLED.h>

#include "config.hpp"

#define NEO_PIN     3   // Pin for accessing Neopixel LED ring (RX PIN = GPIO3)

#if defined(BOX_HAS_PIR)
  // The ESP8266 supports interrupts in any GPIO, except GPIO16 (= D0)!
  #define PIR_PIN     14  // PIR Bewegungsmelder an D5 (= GPIO14)
  #define LED_PIN     2   // internal Wifi LED of Wemos D1 mini (negative logic)
#endif

#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    12

#define BRIGHTNESS  64
#define FRAMES_PER_SECOND 60

// bool gReverseDirection = false;

// CRGB leds[NUM_LEDS];

void function_pir_setup( void );

void function_fastled_setup( void );

void function_Fire2012WithPalette( void );

void function_pir_change_palettes( void );

void function_fastled_handle( void );

void ICACHE_RAM_ATTR interrupt_pir_motion_detection();

void function_pir_handle_timer( void );

#endif // function_fastled_pir_hpp
