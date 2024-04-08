#include "SoftWarePWM.h"
#include "pins.h"

#include "motor.h"
Motors motors;

void setup() {
  // motor

  pinMode(A3, OUTPUT); // Все каналы ШИМ устанавливаются как выходы
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  setupSoftWarePWM();

  Serial.begin(9600);
  motors.setup();
  pinMode(SOLINOID_PIN,OUTPUT);
  digitalWrite(SOLINOID_PIN,0);
}

/*void loop() {
  pult.update();
  // run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
  motors.run(pult.speed,pult.angle,pult.z,pult.arrow_x,pult.arrow_y,pult.boost);
  if (pult.punch) punch();
  // pult.test_print();
  // pult.test_print_operation();
}*/

void loop() { // Получаем заполнение ШИМ с потенциометров
  dutyA3++;// = map(analogRead(A0), 0, 1023, 0, ); // У каждого канала свой потенциометр
  if (dutyA3>PWM_DEPTH) dutyA3 = 0;
  dutyA4 = 0;
  dutyA5 = 0;
  delay(100);  // Других задач нет - можно поставить delay (иначе ставим millis() таймер)
}

void punch() {
  digitalWrite(SOLINOID_PIN,1);
  delay(100);
  digitalWrite(SOLINOID_PIN,0);
}