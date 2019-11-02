#include "function_fastled_pir.hpp"

#include "function_dfplayer.hpp"

bool gReverseDirection = false;

#if defined(BOX_HAS_PIR)
  unsigned long g_ul_PIR_lastTrigger = 0;
  unsigned long g_ul_PIR_time_span = 0;
  boolean g_b_PIR_startTimer = false;
  const int g_ci_PIR_delayTime = 9; // delay in [s]
#endif

CRGB leds[NUM_LEDS];

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
//
// The three static ones are:
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;

void function_pir_setup( void ) {
#ifdef BOX_HAS_PIR
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(PIR_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), interrupt_pir_motion_detection, HIGH);

  // setup DFPlayer
  function_mp3_setup();

  // switch wifi LED off
  digitalWrite(LED_PIN, HIGH); // due to negative logic of internal Wifi LED of Wemos D1 mini
#endif
}

void function_fastled_setup( void ) {
  FastLED.addLeds<CHIPSET, NEO_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  gPal = HeatColors_p;

  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
}

// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

void function_Fire2012WithPalette( void ) {
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
}

void function_pir_change_palettes( void ) {
#ifdef BOX_HAS_PIR
  if (!g_b_PIR_startTimer) {
    gPal = HeatColors_p;
  }
  else {
    //gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White );
    //gPal = CRGBPalette16( CRGB::Black, CRGB::Green, CRGB::Purple,  CRGB::White );
    gPal = CRGBPalette16( CRGB::Green, CRGB::Blue );
    // gPal = CRGBPalette16( CRGB::Purple, CRGB::White );
    // digitalWrite(LED_PIN, LOW); // due to negative logic of internal Wifi LED of Wemos D1 mini
  }
#else
  gPal = HeatColors_p;
  //gPal = CRGBPalette16( CRGB::Black, CRGB::Green, CRGB::Purple,  CRGB::White );
  //gPal = CRGBPalette16( CRGB::Green, CRGB::Blue );
#endif
}

void function_fastled_handle( void ) {
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

// Checks if motion was detected, sets LED HIGH and starts a timer
// Note: IRAM_ATTR is used to run the interrupt code in RAM,
// otherwise code is stored in flash and it’s slower.
// void IRAM_ATTR detectsMovement() {     // IRAM_ATTR for esp32
void ICACHE_RAM_ATTR interrupt_pir_motion_detection() {  // ICACHE_RAM_ATTR for esp8266
#if defined(BOX_HAS_PIR)
  // don't start again while playing
  if ( !g_b_PIR_startTimer ) {
    Serial.println("### I C U ! ###");

    digitalWrite(LED_PIN, LOW); // due to negative logic of internal Wifi LED of Wemos D1 mini

    // start playing alarm sound
    function_mp3_alarm_play(2, 14); // play in folder 02 track number 14

    // random play doesn't work => why?
    // function_mp3_alarm_play_rndm();

    // // count detections
    // g_i_PIR_count_per_minute++;
    g_ul_PIR_lastTrigger = millis();

    g_b_PIR_startTimer = true;
  }
  else Serial.println("### Don't start again while playing ###");
#endif
}

void function_pir_handle_timer( void ) {
#if defined(BOX_HAS_PIR)
  g_ul_PIR_time_span = (millis() - g_ul_PIR_lastTrigger) / 1000; // (current time [ms] - last Trigger) in s

  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(g_b_PIR_startTimer && (g_ul_PIR_time_span > g_ci_PIR_delayTime)) {
    Serial.println("### Hrmph - You're GONE ... ###");
    Serial.print("Motion stopped after ");
    Serial.print(g_ul_PIR_time_span);
    Serial.println(" s");

    digitalWrite(LED_PIN, HIGH); // due to negative logic of internal Wifi LED of Wemos D1 mini

    // stop playing alarm sound
    function_mp3_alarm_stop();

    g_b_PIR_startTimer = false;
  }
#endif
}

//
