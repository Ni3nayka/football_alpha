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
  pinMode(SOLINOID_PIN,OUTPUT);
  digitalWrite(SOLINOID_PIN,0);
  // test
}

void loop() {
  pult.update();
  // pult.test_print();
  // pult.test_print_operation();
}

void punch() {
  digitalWrite(SOLINOID_PIN,1);
  delay(100);
  digitalWrite(SOLINOID_PIN,0);
}