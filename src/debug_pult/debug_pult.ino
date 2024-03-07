#include "pult.h"

Pult pult;

void setup() {
  Serial.begin(115200);
  pult.setup();
}

void loop() {
  pult.update();
  pult.test_print();
  Serial.println(pult.x);
}