/*
   code write for project:
   https://github.com/Ni3nayka/Monster_car

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  March 2024
   modify: March 2024

   links:
   https://dronebotworkshop.com/radio-control-arduino-car/
*/

#pragma once

#include "IBusBM.h"

// IBusBM ibus;

class MyFlySky: public IBusBM {
  public:
    int readChannel(byte channelInput, int minLimit=-100, int maxLimit=100, int defaultValue=0) {
      uint16_t ch = IBusBM::readChannel(channelInput);
      if (ch < 100) return defaultValue;
      return map(ch, 1000, 2000, minLimit, maxLimit);
    }
  private:
  // for (int i = 0; i<14; i++) Serial.print(String(FlySky.readChannel(i)) + " "); Serial.println();
};

MyFlySky flysky;