/*
   arduino library for gy-25 module:
   https://github.com/Ni3nayka/gy-25

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  June 2024
   modify: June 2024

   ВНИМАНИЕ!!!
   Эта либа написана на коленке в самый последний момент, на основе разроаботок с предыдущей олимпиады, 
   по принципу "работает и ладно". Код - г@вно, но функционал выполняет
*/  

#pragma once

#if(defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega2560__))
#include <SoftwareSerial.h>
#elif (defined(ESP32)) 
#include "SoftwareSerial.h" 
#else
#error "lib not supported this board"
#endif

// SoftwareSerial mySerial(10, 11); // RX, TX


class GY25: private SoftwareSerial {  //(): public SoftwareSerial {
public:
  int angle[3];
  long int horizontal_angle;

  void setup() {
    GY25::begin(115200);
    delay(1000);
    GY25::write(0XA5);  // request the data
    GY25::write(0X52);
    GY25::horizontal_angle = 0;
    GY25::ggg_cache = 0;
    GY25::ggg_old = 0;
  }

  void calibration() {
    // setup time
    delay(3000);
    // Kalibrasi Tilt
    GY25::write(0xA5);
    GY25::write(0x54);
    // Jeda sebelum kalibrasi heading
    delay(1000);
    // Kalibrasi Heading
    GY25::write(0xA5);
    GY25::write(0x55);
    delay(100);
  }

  void update() {
    while (GY25::available()) {
      GY25::Re_buf[GY25::counter] = (unsigned char)GY25::read();
      if (GY25::counter == 0 && GY25::Re_buf[0] != 0xAA) return;
      GY25::counter++;
      if (GY25::counter == 8) {
        GY25::counter = 0;
        GY25::sign = 1;
      }
    }
    if (GY25::sign) {
      GY25::sign = 0;
      if (GY25::Re_buf[0] == 0xAA && GY25::Re_buf[7] == 0x55) {
        GY25::angle[0] = (GY25::Re_buf[1] << 8 | GY25::Re_buf[2]) / 100;
        GY25::angle[1] = (GY25::Re_buf[3] << 8 | GY25::Re_buf[4]) / 100;
        GY25::angle[2] = (GY25::Re_buf[5] << 8 | GY25::Re_buf[6]) / 100;
        #ifdef ESP32
        for (int i = 0; i<3; i++) {
          if (GY25::angle[i]>180) {
            GY25::angle[i] -= 654;
          } 
        }
        #endif
        // GY25::print();
        // gy25.update();
        int a = GY25::angle[0];
        if (a>100 && ggg_old<-100) GY25::ggg_cache -= 360;
        if (a<-100 && ggg_old>100) GY25::ggg_cache += 360;
        GY25::ggg_old = a;
        GY25::horizontal_angle = a + GY25::ggg_cache;
      }
    }
  }

  void print() {
    Serial.print(GY25::angle[0]);
    Serial.print(" ");
    Serial.print(GY25::angle[1]);
    Serial.print(" ");
    Serial.print(GY25::angle[2]);
    Serial.print(" ");
    Serial.print(GY25::horizontal_angle);
    Serial.println();
  }
private:
  using SoftwareSerial::SoftwareSerial;
  unsigned char counter = 0;  //buffer where the received data will be stored
  unsigned char sign = 0;
  unsigned char Re_buf[8];
  long int ggg_cache,ggg_old;
};

// ==============================================================================================================================================

// #define GY25_SERIAL Serial3
#ifdef GY25_SERIAL

class GY25_1 {
public:
  int angle[3];
  long int horizontal_angle;

  void setup() {
    GY25_SERIAL.begin(115200);
    GY25_1::calibration();
    delay(1000);
    GY25_SERIAL.write(0XA5);  // request the data
    GY25_SERIAL.write(0X52);
    GY25_1::horizontal_angle = 0;
    GY25_1::ggg_cache = 0;
    GY25_1::ggg_old = 0;
  }

  void calibration() {
    // setup time
    delay(3000);
    // Kalibrasi Tilt
    GY25_SERIAL.write(0xA5);
    GY25_SERIAL.write(0x54);
    // Jeda sebelum kalibrasi heading
    delay(1000);
    // Kalibrasi Heading
    GY25_SERIAL.write(0xA5);
    GY25_SERIAL.write(0x55);
    delay(100);
  }

  void update() {
    while (GY25_SERIAL.available()) {
      GY25_1::Re_buf[GY25_1::counter] = (unsigned char)GY25_SERIAL.read();
      if (GY25_1::counter == 0 && GY25_1::Re_buf[0] != 0xAA) return;
      GY25_1::counter++;
      if (GY25_1::counter == 8) {
        GY25_1::counter = 0;
        GY25_1::sign = 1;
      }
    }
    if (GY25_1::sign) {
      GY25_1::sign = 0;
      if (GY25_1::Re_buf[0] == 0xAA && GY25_1::Re_buf[7] == 0x55) {
        GY25_1::angle[0] = (GY25_1::Re_buf[1] << 8 | GY25_1::Re_buf[2]) / 100;
        GY25_1::angle[1] = (GY25_1::Re_buf[3] << 8 | GY25_1::Re_buf[4]) / 100;
        GY25_1::angle[2] = (GY25_1::Re_buf[5] << 8 | GY25_1::Re_buf[6]) / 100;
        int a = GY25_1::angle[0];
        if (a>100 && ggg_old<-100) GY25_1::ggg_cache -= 360;
        if (a<-100 && ggg_old>100) GY25_1::ggg_cache += 360;
        GY25_1::ggg_old = a;
        GY25_1::horizontal_angle = a + GY25_1::ggg_cache;
      }
    }
  }
  void print() {
    Serial.print(GY25_1::angle[0]);
    Serial.print(" ");
    Serial.print(GY25_1::angle[1]);
    Serial.print(" ");
    Serial.print(GY25_1::angle[2]);
    Serial.print(" ");
    Serial.print(GY25_1::horizontal_angle);
    Serial.println();
  }
private:
  // using SoftwareSerial::SoftwareSerial;
  unsigned char counter = 0;  //buffer where the received data will be stored
  unsigned char sign = 0;
  unsigned char Re_buf[8];
  long int ggg_cache,ggg_old;
};

#endif
