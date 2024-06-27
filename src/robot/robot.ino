/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: May 2024
*/

#include "pins.h"
#include "motor.h"
// #include "FlySky.h"
#include "FlySky_uart.h"

Motor motor_1;
Motor motor_2;

#include "gy-25.h"
GY25 gy25(9,2); // (TX,RX) - пины гироскопа
// GY25_1 gy25;

void setup() {
  // Serial.begin(9600);
  flysky.begin(Serial);
  // flysky.setup();
  motor_1.setup(MOTOR_1_DIR,MOTOR_1_PWM);
  motor_2.setup(MOTOR_2_DIR,MOTOR_2_PWM,-1.0);
  motor_1.run();
  motor_2.run();
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
  y = flysky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  int rotation_new = flysky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  if (abs(rotation_new)>50) {
    if (t<millis()) {
      rotation -= rotation_new/abs(rotation_new); 
      t = millis()+10;
    } 
  }

  gy25.update();
  long int e = rotation - gy25.horizontal_angle;
  if (abs(e)>5) x -= e*3.5;

  motor_1.run(y-x);
  motor_2.run(y+x);
}