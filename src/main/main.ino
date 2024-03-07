#include "user_data.h"
#include "pult.h"

#define ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
#include <AVOCADO_esp.h>
AVOCADO_esp esp;

void setup() {
  Serial.begin(115200);
  esp.setup();
}

void loop() {
  esp.update();
  
  // button
  for (int i = 0; i<GAMEPAD_BUTTON_QUANTITY; i++) {
    Serial.print(esp.gamepad_button[i]); // bool
  }

  Serial.print(" <> ");
  
  // allow
  for (int i = 0; i<GAMEPAD_ARROW_QUANTITY; i++) {
    Serial.print(esp.gamepad_arrow[i]); // int
    Serial.print(" ");
  }
  
  Serial.print(" <> ");
  
  // joystick
  for (int i = 0; i<GAMEPAD_JOYSTICK_QUANTITY; i++) {
    Serial.print(esp.gamepad_joystick[i]); // int
    Serial.print(" ");
  }
    
  Serial.println();
}