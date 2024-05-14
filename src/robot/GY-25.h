// https://static-eu.insales.ru/files/1/1580/10954284/original/Описание_GY25__курс__крен__тангаж_.pdf
// https://metanit.com/cpp/tutorial/5.10.php

/*
#include "GY-25.h"
GY25 gy25(4, 5); // RX, TX
void setup() {
  Serial.begin(9600);
  gy25.setup();
}
long int t = 0;
void loop() {
  gy25.update();
  if (t < millis()) {
    gy25.print();
    t = millis() + 100;
  }
}
*/

#pragma once

#include <SoftwareSerial.h>

class GY25: private SoftwareSerial {  //(): public SoftwareSerial {
public:
  int angle[3];

  void setup() {
    GY25::begin(115200);
    delay(1000);
    GY25::write(0XA5);  // request the data
    GY25::write(0X52);
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
        //GY25::print();
      }
    }
  }

  void print() {
    Serial.print(GY25::angle[0]);
    Serial.print(" ");
    Serial.print(GY25::angle[1]);
    Serial.print(" ");
    Serial.print(GY25::angle[2]);
    Serial.println();
  }
private:
  using SoftwareSerial::SoftwareSerial;
  unsigned char counter = 0;  //buffer where the received data will be stored
  unsigned char sign = 0;
  unsigned char Re_buf[8];
};