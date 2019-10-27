#ifndef config_hpp
#define config_hpp

// include your own wifi credentials here ...
#include "wifi_creds.hpp"

// choose hostname and sensors (done by build_flags in platformio.ini)
#ifdef WEMOS_D1_MINI
  #define HOSTNAME "Wemos_D1_mini"
  #define BOX_HAS_PIR     // PIR Bewegungsmelder
  // #define BOX_HAS_CCS811  // CO2-Sensor
  // #define BOX 'esp8266_d1_mini'
#elif WEMOS_D1_MINI_PRO
  #define HOSTNAME "Wemos_D1_mini_pro"
  #define BOX_HAS_PIR     // PIR Bewegungsmelder
  // #define BOX_HAS_CCS811  // CO2-Sensor
  // #define BOX 'esp8266_d1_box'
#elif NODE_MCU_LORA_1
  #define HOSTNAME "NodeMCU_LoRa_1"
  // #define BOX_HAS_PIR     // PIR Bewegungsmelder
  // #define BOX_HAS_CCS811  // CO2-Sensor
  #define BOX 'esp8266_node_mcu_lora_1'
#elif NODE_MCU_LORA_2
  #define HOSTNAME "NodeMCU_LoRa_2"
  // #define BOX_HAS_PIR     // PIR Bewegungsmelder
  // #define BOX_HAS_CCS811  // CO2-Sensor
  #define BOX 'esp8266_node_mcu_lora_2'
#elif DEAUTHER_OLED
  #define HOSTNAME "Deauther_oled"
  #define BOX 'esp8266_deauther_oled'
#endif

// choose mqtt broker (done by build_flags in platformio.ini)
#ifdef MQTT_RASPI_TOUCH
  //#define MQTT_HOST IPAddress(192, 168, 60, 190)
  #define MQTT_HOST "RaspiB3PiTouch7"
  #define MQTT_PORT 1883
#elif MQTT_RASPI_EPAPER
  #define MQTT_HOST "RaspiB3plus_ePaper"
  #define MQTT_PORT 1883
#endif

#ifdef WEMOS_D1_MINI_PRO
  #define MQTT_ROOT_TOPIC "d1_box"
#elif NODE_MCU_LORA_1
  #define MQTT_ROOT_TOPIC "lora_1"
#elif NODE_MCU_V2
  #define MQTT_ROOT_TOPIC "node_mcu"
#elif DEAUTHER_OLED
  #define MQTT_ROOT_TOPIC "deauther_oled"
#endif

#endif // config_hpp
