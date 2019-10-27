#include "function_wifi.hpp"

// #include "function_mqtt.hpp"
#include "function_ota.hpp"

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

void configureWifi() {
  Serial.println("Configuring Wi-Fi ...");
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  WiFi.softAPdisconnect(true); // deactivate wifi access point (soft AP)
  WiFi.mode(WIFI_STA);  // client mode
  Serial.print("Setting the ESP's hostname to: ");
  Serial.println(String(HOSTNAME));
  WiFi.hostname(String(HOSTNAME));
}

void connectToWifi() {
  // Serial.println("Connecting to Wi-Fi ...");
  // WiFi.mode(WIFI_STA);  // client mode
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

bool get_wifi_isConnected() {
  return WiFi.isConnected();
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi.");

  // Serial.print("Setting the ESP's hostname to: ");
  // Serial.println(String(HOSTNAME));
  // WiFi.hostname(String(HOSTNAME));
  Serial.print("ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi signal level: ");
  Serial.println(WiFi.RSSI());

  function_ota_setup(HOSTNAME);   // setup OTA functionality

  // connectToMqtt();
  // connectMqttPubTasks();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi.");
  // deactivateMqtt_reconnectTimer();
  wifiReconnectTimer.once(2, connectToWifi);
}

IPAddress get_wifi_IP() {
  return WiFi.localIP();
}

String get_wifi_IP_str() {
  return WiFi.localIP().toString().c_str();
}

String get_wifi_hostname() {
  return WiFi.hostname();
}

int get_wifi_RSSI() {
  return WiFi.RSSI();
}
