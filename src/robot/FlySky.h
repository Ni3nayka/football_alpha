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
    int readChannel(int channelInput, int minLimit=-100, int maxLimit=100, int defaultValue=0, int minValue=7){
      int ch = pulseIn(channelInput, HIGH, 30000);
      if (ch < 100) return defaultValue;
      ch = map(ch, 1000, 2000, minLimit, maxLimit);
      if (abs(ch)<minValue) return 0;
      return ch;
    }
    void test() {
      Serial.print(MyFlySky::readChannel(FLYSKY_JOYSTICK_LEFT_X));
      Serial.print(" ");
      Serial.print(MyFlySky::readChannel(FLYSKY_JOYSTICK_LEFT_Y));
      Serial.print(" ");
      Serial.print(MyFlySky::readChannel(FLYSKY_JOYSTICK_RIGHT_X));
      Serial.print(" ");
      Serial.print(MyFlySky::readChannel(FLYSKY_JOYSTICK_RIGHT_Y));
      Serial.print(" ");
      Serial.print(MyFlySky::readChannel(FLYSKY_BUTTON_SWA));
      Serial.print(" ");
      Serial.print(MyFlySky::readChannel(FLYSKY_BUTTON_SWD));
      Serial.println();
      delay(10);
    }
  private:
};

MyFlySky flysky;


    