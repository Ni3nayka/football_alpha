#pragma once

#include "user_data.h"

#define ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
#include <AVOCADO_esp.h>

class Pult: public AVOCADO_esp {
  public:
    int x,y,z,angle,speed;
    bool punch;
    void setup(float speed_boost=2.0) {
      AVOCADO_esp::setup();
      Pult::speed_boost = speed_boost;
      // Pult::speed_boost_k = speed_boost/100.0;
    }
    void update() {
      AVOCADO_esp::update();
      if (Pult::gamepad_arrow[0]==0 && Pult::gamepad_arrow[1]==0) {
        Pult::x = Pult::gamepad_joystick[0];
        Pult::y = -Pult::gamepad_joystick[1];
        if (!(Pult::gamepad_button[0]||Pult::gamepad_button[1]||Pult::gamepad_button[2]||Pult::gamepad_button[3])) { // если не нажаты кнопки (слева)
          // без ускорения
          Pult::x /= Pult::speed_boost;
          Pult::y /= Pult::speed_boost;
        }
      }
      else {
        // ускорение стрелками (слева)
        Pult::x = Pult::gamepad_arrow[0]*100;
        Pult::y = Pult::gamepad_arrow[1]*100;
      }
      Pult::z = Pult::gamepad_joystick[3];
      Pult::punch = Pult::gamepad_button[4]||Pult::gamepad_button[5]||Pult::gamepad_button[6]||Pult::gamepad_button[7]||Pult::gamepad_button[10]||Pult::gamepad_button[11];
      if (Pult::x==0 && Pult::y==0) Pult::angle = 0;
      else {
        Pult::angle = atan(float(Pult::x)/float(Pult::y))*57.3;
        if (Pult::y<0) {
          if (Pult::x>0) Pult::angle+=180;
          else Pult::angle-=180;
        }
      }
      Pult::speed = max(abs(Pult::x),abs(Pult::y));
      Serial.println("speed " + String(Pult::speed) + "   angle " + String(Pult::angle) +  + "   rotation " + String(Pult::z));
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
    float speed_boost;
    // float speed_boost_k;
};