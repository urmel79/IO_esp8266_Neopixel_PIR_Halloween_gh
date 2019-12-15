#include <Arduino.h>

// include wifi functionality for asynchronous wifi handling
#include "function_wifi.hpp"

// include OTA functionality (ability for Over The Air updates)
#include "function_ota.hpp"

#include "function_fastled_pir.hpp"

void setup() {
  // Serial.begin(9600);
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  configureWifi();

  delay(1000); // sanity delay

  // configureMqtt(); // setup MQTT functionality

  connectToWifi();

  delay(1000); // sanity delay

  function_pir_setup();

  delay(1000); // sanity delay
  function_fastled_setup();
}

void loop() {
  if (get_wifi_isConnected()) {
    function_ota_handle();  // call handler function for OTA
  }

  function_pir_change_palettes();

  function_pir_handle_timer();

  function_Fire2012WithPalette(); // run simulation frame, using palette colors

  function_fastled_handle();
}
