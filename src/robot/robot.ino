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

#define NO_BOOST_PART 0.6

void setup() {
  // Serial.begin(9600);
  flysky.setup();
  motors.setup();
  pinMode(SOLENOID_PIN,OUTPUT);
  digitalWrite(SOLENOID_PIN,0);
  // testMotors();
  motors.run();
}

void loop() {
  mainFlysky();
}

void mainFlysky() {
  // FlySky.test();
  // read pult
  float boost = fmap(flysky.readChannel(FLYSKY_JOYSTICK_LEFT_Y)+100,0,200,NO_BOOST_PART,1);
  int x = flysky.readChannel(FLYSKY_JOYSTICK_RIGHT_X);
  int y = flysky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  int rotation = flysky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  // translate pult
  int angle = 0, speed = 0;
  if (x!=0 || y!=0) {
    angle = atan(float(x)/float(y))*57.3;
    if (y<0) {
      if (x>0) angle+=180;
      else angle-=180;
    }
  }
  speed = max(abs(x),abs(y));
  if (speed==0) rotation*=0.4;
  else rotation*=0.2;
  speed *= boost;
  // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation) + "   boost " + String(boost));
  motors.runVector(speed,angle,rotation);
  // punch
  bool punch_one_new = flysky.readChannel(FLYSKY_BUTTON_SWA)>0;
  bool punch_many = flysky.readChannel(FLYSKY_BUTTON_SWD)>0;
  bool punch_one = punch_one_new!=global_punch_one_old;
  global_punch_one_old = punch_one_new;
  if (punch_one || punch_many) solenoidPunch();
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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