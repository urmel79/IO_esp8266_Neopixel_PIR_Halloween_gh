#ifndef function_dfplayer_hpp
#define function_dfplayer_hpp

// includes implicit <sys/types.h> (necessary for SoftwareSerial)
// otherwise errors like 'ssize_t' does not name a type'
#include <Arduino.h>

// // implement a notification class,
// // its member methods will get called
// class Mp3Notify
// {
// public:
//   void OnError(uint16_t errorCode);
//
//   void OnPlayFinished(uint16_t globalTrack);
//
//   void OnCardOnline(uint16_t code);
//
//   void OnUsbOnline(uint16_t code);
//
//   void OnCardInserted(uint16_t code);
//
//   void OnUsbInserted(uint16_t code);
//
//   void OnCardRemoved(uint16_t code);
//
//   void OnUsbRemoved(uint16_t code);
// };

bool initSS_mp3();

void function_mp3_setup();

// void function_mp3_set_volume(uint8_t volume);

void function_mp3_alarm_play(uint16_t track);

// random play doesn't work => why?
void function_mp3_alarm_play_rndm();

void function_mp3_alarm_stop();


#endif // function_dfplayer_hpp
