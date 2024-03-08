#include "pins.h"

#define ENABLE_AVOCADO_ESP_WIFI_BOOT
#include "pult.h"
Pult pult;

#include "motor.h"
Motors motors;

void setup() {
  Serial.begin(115200);
  pult.setup();
  motors.setup();
}

void loop() {
  pult.update();
  pult.test_print_operation();
}