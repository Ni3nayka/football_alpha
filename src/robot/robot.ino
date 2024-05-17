/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: May 2024
*/

#include "pins.h"
#include "motor.h"
#include "FlySky.h"

bool global_punch_one_old = 0;

void setup() {
  // Serial.begin(9600);
  FlySky.setup();
  motors.setup();
  pinMode(SOLENOID_PIN,OUTPUT);
  digitalWrite(SOLENOID_PIN,0);
  // testMotors();
  motors.run();
}

void loop() {
  // FlySky.test();
  // moves
  int x = FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_X);
  int y = FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  int rotation = FlySky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  if (x==0 && y==0) rotation*=0.4;
  else rotation*=0.2;
  // punch
  bool punch_one_new = FlySky.readChannel(FLYSKY_BUTTON_SWA)>0;
  bool punch_many = FlySky.readChannel(FLYSKY_BUTTON_SWD)>0;
  bool punch_one = punch_one_new!=global_punch_one_old;
  global_punch_one_old = punch_one_new;
  // Serial.println(String(y)+" "+String(x)+" "+String(punch));
  motors.run(y+x+rotation,y-x-rotation,y-x+rotation,y+x-rotation);
  if (punch_one || punch_many) solenoidPunch();
}

void solenoidPunch() {
  digitalWrite(SOLENOID_PIN,1);
  delay(100);
  digitalWrite(SOLENOID_PIN,0);
}

void testMotors() {
  motors.run(100,0,0,0); delay(2000);
  motors.run(0,100,0,0); delay(2000);
  motors.run(0,0,100,0); delay(2000);
  motors.run(0,0,0,100); delay(2000);
  motors.run(-100,0,0,0); delay(2000);
  motors.run(0,-100,0,0); delay(2000);
  motors.run(0,0,-100,0); delay(2000);
  motors.run(0,0,0,-100); delay(2000);
  motors.run();
}