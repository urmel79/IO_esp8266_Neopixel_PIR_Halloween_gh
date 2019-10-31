// it expects the sd card to contain these three mp3 files
// but doesn't care whats in them
//
// sd:/mp3/0001_xxx.mp3
// sd:/mp3/0002_xxx.mp3
// sd:/mp3/0003_xxx.mp3

#include "function_dfplayer.hpp"

// includes implicit <sys/types.h> (necessary for SoftwareSerial)
// otherwise errors like 'ssize_t' does not name a type'
// #include <Arduino.h>

// Install EspSoftwareSerial by Peter Lerup
// Implementation of the Arduino software serial for ESP8266/ESP32.
// Important: v5.0.4 is the latest version what compiles without errors
// (current versions spill massive errors, maybe about interrupt handling?)
#include <SoftwareSerial.h> //Included SoftwareSerial Library

// install "DFPlayer Mini Mp3 by Makuna"
// https://github.com/Makuna/DFMiniMp3
#include <DFMiniMp3.h>

/*enum DfMp3_Error
{
    // from device
    DfMp3_Error_Busy = 1,
    DfMp3_Error_Sleeping,
    DfMp3_Error_SerialWrongStack,
    DfMp3_Error_CheckSumNotMatch,
    DfMp3_Error_FileIndexOut,
    DfMp3_Error_FileMismatch,
    DfMp3_Error_Advertise,
    // from library
    DfMp3_Error_RxTimeout = 0x81,
    DfMp3_Error_PacketSize,
    DfMp3_Error_PacketHeader,
    DfMp3_Error_PacketChecksum,
    DfMp3_Error_General = 0xff
};*/

// // implement a notification class,
// // its member methods will get called
// void Mp3Notify::OnError(uint16_t errorCode) {
//   // see DfMp3_Error for code meaning
//   Serial.println();
//   Serial.print("Com Error 0x");
//   Serial.println(errorCode, HEX);
// }
//
// void Mp3Notify::OnPlayFinished(uint16_t globalTrack) {
//   Serial.println();
//   Serial.print("Play finished for #");
//   Serial.println(globalTrack);
// }
//
// void Mp3Notify::OnCardOnline(uint16_t code) {
//   Serial.println();
//   Serial.print("Card online ");
//   Serial.println(code);
// }
//
// void Mp3Notify::OnUsbOnline(uint16_t code) {
//   Serial.println();
//   Serial.print("USB Disk online ");
//   Serial.println(code);
// }
//
// void Mp3Notify::OnCardInserted(uint16_t code) {
//   Serial.println();
//   Serial.print("Card inserted ");
//   Serial.println(code);
// }
//
// void Mp3Notify::OnUsbInserted(uint16_t code) {
//   Serial.println();
//   Serial.print("USB Disk inserted ");
//   Serial.println(code);
// }
//
// void Mp3Notify::OnCardRemoved(uint16_t code) {
//   Serial.println();
//   Serial.print("Card removed ");
//   Serial.println(code);
// }
//
// void Mp3Notify::OnUsbRemoved(uint16_t code) {
//   Serial.println();
//   Serial.print("USB Disk removed ");
//   Serial.println(code);
// }

// inline implementation of a notification class,
// its member methods will get called
class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("DFPlayer: Com Error 0x");
    Serial.println(errorCode, HEX);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
    Serial.println();
    Serial.print("DFPlayer: Play finished for #");
    Serial.println(globalTrack);
  }

  static void OnCardOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: Card online ");
    Serial.println(code);
  }

  static void OnUsbOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: USB Disk online ");
    Serial.println(code);
  }

  static void OnCardInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: Card inserted ");
    Serial.println(code);
  }

  static void OnUsbInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: USB Disk inserted ");
    Serial.println(code);
  }

  static void OnCardRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: Card removed ");
    Serial.println(code);
  }

  static void OnUsbRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("DFPlayer: USB Disk removed ");
    Serial.println(code);
  }
};


// instance a DFMiniMp3 object,
// defined with the above notification class and the hardware serial class
//
//DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

#define BAUD_RATE 9600

#if !defined(D1)
  #define D1 (5)
  #define D2 (4)
#endif

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines
//SoftwareSerial secondarySerial(10, 11); // RX, TX
SoftwareSerial mySoftwareSerial(D2, D1); // // RxD: GPIO4 (D2), TxD: GPIO5 (D1)

// instance a DFMiniMp3 object,
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(mySoftwareSerial);

bool initSS_mp3() {
  bool status;

  status = mySoftwareSerial.begin(BAUD_RATE);
  if (!status) Serial.println("DFPlayer: Something is wrong with the software serial line to MP3Player module.");

  return status;
}

void function_mp3_setup() {
  Serial.println("DFPlayer: Initializing DFPlayer ...");

  if ( !initSS_mp3() ) {
   ; // wait for serial port to connect
  }

  mp3.begin();

  // stop all playing
  mp3.stop();

  uint16_t volume = mp3.getVolume();
  Serial.print("DFPlayer: volume ");
  Serial.println(volume);
  mp3.setVolume(30); // volume range: 0 - 30

  uint16_t count = mp3.getTotalTrackCount();
  Serial.print("DFPlayer: files ");
  Serial.println(count);
}

// // volume range: 0 - 30
// void function_mp3_set_volume(uint8_t volume) {
//   Serial.print("DFPlayer: setting volume to ");
//   Serial.println(volume);
//   mp3.setVolume( volume );
// }

void function_mp3_alarm_play(uint16_t track) {
  Serial.print("DFPlayer: playing track ");
  Serial.println(track);
  mp3.playMp3FolderTrack( track );  // sd:/mp3/0001.mp3
}

// random play doesn't work => why?
void function_mp3_alarm_play_rndm() {
  Serial.println("DFPlayer: playing random track");
  mp3.playRandomTrackFromAll();
}

void function_mp3_alarm_stop() {
  Serial.println("DFPlayer: stopping track");
  mp3.stop();
}


//
