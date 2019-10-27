#include <Arduino.h>

#include "function_fastled_pir.hpp"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  function_pir_setup();

  delay(2000); // sanity delay
  function_fastled_setup();
}

void loop() {
  function_pir_change_palettes();

  function_fastled_handle();
}
