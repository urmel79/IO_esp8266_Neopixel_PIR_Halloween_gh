#ifndef function_wifi_hpp
#define function_wifi_hpp

#include <ESP8266WiFi.h>
#include <Ticker.h>

#include "config.hpp"

void configureWifi();
void connectToWifi();

void onWifiConnect(const WiFiEventStationModeGotIP& event);

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);

IPAddress get_wifi_IP();
String get_wifi_IP_str();
String get_wifi_hostname();
int get_wifi_RSSI();
bool get_wifi_isConnected();

#endif // function_wifi_hpp
