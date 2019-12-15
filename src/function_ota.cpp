#include "function_ota.hpp"

void function_ota_setup( const char *chr_hostname ) {
  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(chr_hostname);

  // No authentication by default
  ArduinoOTA.setPassword("esp8266");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    // [bug] external interrupts conflict with wifi connection attempts and
    // ota updates and lead to sporadic crashes!
    // [fix (workaround)] disable external interrupts temporarily
    // reference https://www.mikrocontroller.net/topic/460256#5573848
    ETS_GPIO_INTR_DISABLE();

    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    // enable external interrupts again
    ETS_GPIO_INTR_ENABLE();

    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    // disable external interrupts (they cause sporadic crashes!)
    // reference https://www.mikrocontroller.net/topic/460256#5573848
    ETS_GPIO_INTR_DISABLE();

    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
  Serial.println("OTA ready");
}

void function_ota_handle( ) {
  ArduinoOTA.handle();
}
