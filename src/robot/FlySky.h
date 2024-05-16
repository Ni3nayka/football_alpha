/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: May 2024

   links:
   https://dronebotworkshop.com/radio-control-arduino-car/
*/

#pragma once

class MyFlySky {
  public:
    void setup() {
      pinMode(FLYSKY_JOYSTICK_LEFT_X, INPUT);
      pinMode(FLYSKY_JOYSTICK_LEFT_Y, INPUT);
      pinMode(FLYSKY_JOYSTICK_RIGHT_X, INPUT);
      pinMode(FLYSKY_JOYSTICK_RIGHT_Y, INPUT);
      pinMode(FLYSKY_BUTTON_SWA, INPUT);
      pinMode(FLYSKY_BUTTON_SWD, INPUT);
    }
    int readChannel(int channelInput, int minLimit=-100, int maxLimit=100, int defaultValue=0){
      int ch = pulseIn(channelInput, HIGH, 30000);
      if (ch < 100) return defaultValue;
      return map(ch, 1000, 2000, minLimit, maxLimit);
    }
  private:
};

MyFlySky FlySky;


    