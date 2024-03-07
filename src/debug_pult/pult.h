#pragma once

#include "user_data.h"

#define ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
#include <AVOCADO_esp.h>


class Pult: public AVOCADO_esp {
  public:
    int x,y,z;
    bool udar;
    void update() {
      AVOCADO_esp::update();
      Pult::x = -Pult::gamepad_joystick[1];
      Pult::y = Pult::gamepad_joystick[0];
      Pult::z = Pult::gamepad_joystick[3];
      Pult::udar = Pult::gamepad_button[4]||Pult::gamepad_button[5]||Pult::gamepad_button[6]||Pult::gamepad_button[7];
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
};