#include "pins.h"

#define ENABLE_AVOCADO_ESP_WIFI_BOOT
#include "pult.h"
Pult pult;

#include "motor.h"
Motors motors;


void setup() {
  Serial.begin(115200);
  pult.setup(1.2);
  motors.setup();
  pinMode(SOLINOID_PIN,OUTPUT);
  digitalWrite(SOLINOID_PIN,0);
}

void loop() {
  pult.update();
  // run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
  motors.run(pult.speed,pult.angle,pult.z,pult.arrow_x,pult.arrow_y,pult.boost);
  if (pult.punch) punch();
  // pult.test_print();
  // pult.test_print_operation();
}

void punch() {
  digitalWrite(SOLINOID_PIN,1);
  delay(100);
  digitalWrite(SOLINOID_PIN,0);
}