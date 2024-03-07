#pragma once

#include "user_data.h"

#define ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
#include <AVOCADO_esp.h>


class Pult: public AVOCADO_esp {
  public:
    int x,y,z;
    bool punch;
    void setup(int speed_boost=200) {
      AVOCADO_esp::setup();
      Pult::speed_boost = speed_boost;
      Pult::speed_boost_k = speed_boost/100.0;
    }
    void update() {
      AVOCADO_esp::update();
      if (Pult::gamepad_arrow[0]==0 && Pult::gamepad_arrow[1]==0) {
        if (Pult::gamepad_button[0]||Pult::gamepad_button[1]||Pult::gamepad_button[2]||Pult::gamepad_button[3]) {
          Pult::x = Pult::gamepad_joystick[0]*Pult::speed_boost_k;
          Pult::y = -Pult::gamepad_joystick[1]*Pult::speed_boost_k;
        }
        else {
          Pult::x = Pult::gamepad_joystick[0];
          Pult::y = -Pult::gamepad_joystick[1];
        }
      }
      else {
        Pult::x = Pult::gamepad_arrow[0]*speed_boost;
        Pult::y = Pult::gamepad_arrow[1]*speed_boost;
      }
      Pult::z = Pult::gamepad_joystick[3];
      Pult::punch = Pult::gamepad_button[4]||Pult::gamepad_button[5]||Pult::gamepad_button[6]||Pult::gamepad_button[7];
    }
    void test_print_operation() {
      Serial.print(Pult::x);
      Serial.print(" ");
      Serial.print(Pult::y);
      Serial.print(" ");
      Serial.print(Pult::z);
      Serial.print(" ");
      Serial.print(Pult::punch);
      Serial.println();
    }
    void test_print() {
      // button
      for (int i = 0; i<GAMEPAD_BUTTON_QUANTITY; i++) {
        Serial.print(Pult::gamepad_button[i]); // bool
      }
      Serial.print(" <> ");
      // allow
      for (int i = 0; i<GAMEPAD_ARROW_QUANTITY; i++) {
        Serial.print(Pult::gamepad_arrow[i]); // int
        Serial.print(" ");
      }
      Serial.print(" <> ");
      // joystick
      for (int i = 0; i<GAMEPAD_JOYSTICK_QUANTITY; i++) {
        Serial.print(Pult::gamepad_joystick[i]); // int
        Serial.print(" ");
      }
      Serial.println();
    }
  private:
    int speed_boost;
    float speed_boost_k;
};