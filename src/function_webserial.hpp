#ifndef function_webserial_hpp
#define function_webserial_hpp

// use the fixed version of WebSerial.h in ./include
#include <WebSerial_bk.h>

// includes implicit <sys/types.h> (necessary for SoftwareSerial)
// otherwise errors like 'ssize_t' does not name a type'
#include <Arduino.h>

WebSerialClass* function_webserial_init( void );

void function_webserial_recvMsg( uint8_t *data, size_t len );

WebSerialClass* function_webserial_get_object( void );














#endif // function_webserial_hpp
