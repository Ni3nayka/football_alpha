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
  FlySky.setup();
  motors.setup();
  pinMode(SOLENOID_PIN,OUTPUT);
  digitalWrite(SOLENOID_PIN,0);
  motors.run();
}

void loop() {
  // FlySky.test();
  int x = FlySky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  int y = FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  bool punch = FlySky.readChannel(FLYSKY_BUTTON_SWA)>0 || FlySky.readChannel(FLYSKY_BUTTON_SWD)>0;
  // Serial.println(String(y)+" "+String(x)+" "+String(punch));
  motors.run(x+y,x-y);
  if (punch) solenoidPunch();
}

void solenoidPunch() {
  digitalWrite(SOLENOID_PIN,1);
  delay(100);
  digitalWrite(SOLENOID_PIN,0);
}