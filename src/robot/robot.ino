/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: May 2024
*/

#include "motor.h"
#include "FlySky.h"

#define SOLENOID_PIN 2

void setup() {
  // Serial.begin(9600);
  FlySky.begin(Serial);
  motors.setup();
  pinMode(SOLENOID_PIN,OUTPUT);
  digitalWrite(SOLENOID_PIN,0);
  motors.run();
}

void loop() {
  // for (int i = 0; i<14; i++) Serial.print(String(FlySky.readChannel(i)) + " "); Serial.println();
  int x = FlySky.readChannel(3);
  int y = FlySky.readChannel(1);
  bool punch = FlySky.readChannel(6)>0 || FlySky.readChannel(7)>0;
  // Serial.println(String(y)+" "+String(x)+" "+String(punch));
  motors.run(x+y,x-y);
  if (punch) solenoidPunch();
}

void solenoidPunch() {
  digitalWrite(SOLENOID_PIN,1);
  delay(100);
  digitalWrite(SOLENOID_PIN,0);
}