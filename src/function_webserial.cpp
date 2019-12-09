#include "function_webserial.hpp"

// #include <WebSerial.h>

#include <ESPAsyncWebServer.h>

AsyncWebServer webserver(80);
WebSerialClass ws;

// void function_webserial_init( void ) {
//
//   // WebSerial is accessible at "<IP Address>/webserial" in browser
//   ws.begin(&webserver);
//   ws.msgCallback(function_webserial_recvMsg);
//   webserver.begin();
//
// }

WebSerialClass* function_webserial_init( void ) {
  // WebSerialClass ws;
  // WebSerial is accessible at "<IP Address>/webserial" in browser
  ws.begin(&webserver);
  ws.msgCallback(function_webserial_recvMsg);
  webserver.begin();

  return &ws;
}

void function_webserial_recvMsg( uint8_t *data, size_t len ) {
  ws.println("Received Data...");
  String d = "";
  for(uint i=0; i < len; i++){
    d += char(data[i]);
  }
  ws.println(d);
}

WebSerialClass* function_webserial_get_object( void ) {
  return &ws;
}



















//
