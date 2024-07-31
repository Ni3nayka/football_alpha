/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: May 2024
*/

#include "pins.h"
// #include "motor.h"
// #include "FlySky.h"
#include "FlySky_uart.h"

#include "BTS7960_PRO.h"
BTS7960_PRO motors;

#include "gy-25.h"
GY25 gy25(12,8); // (TX,RX) - пины гироскопа
// GY25_1 gy25;

void setup() {
  // Serial.begin(9600);
  flysky.begin(Serial);
  // flysky.setup();
  motors.setup();
  gy25.setup();
}

unsigned long int t = 0;
long int rotation = 0;

void loop() {
  mainFlysky();
  // gy25.update();
  // if (t<millis()) {
  //   gy25.print();
  //   t = millis() + 100;
  // }
  
}

void mainFlysky() {
  int x=0,y=0;
  x = flysky.readChannel(FLYSKY_JOYSTICK_RIGHT_X);
  y = -flysky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  int rotation_new = flysky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  if (abs(rotation_new)>50) {
    if (t<millis()) {
      rotation -= rotation_new/abs(rotation_new); 
      t = millis()+10;
    } 
  }

  gy25.update();
  long int e = rotation - gy25.horizontal_angle;
  if (abs(e)>5) x -= e*3;

  motors.run(1,y-x);
  motors.run(2,y+x);
}