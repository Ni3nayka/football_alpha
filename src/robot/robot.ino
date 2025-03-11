/*
   code write for project:
   https://github.com/Ni3nayka/football_alpha/

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  May 2024
   modify: March 2025
*/

#include "pins.h"
#include "FlySky_uart.h"
#include "bumper.h"

#include "BTS7960_PRO.h"
BTS7960_PRO motors;

// #include "gy-25.h"
// GY25 gy25(12,8); // (TX,RX) - пины гироскопа
// GY25_1 gy25;

#define PUNCH_BUTTON_ON_FLYSKY_HIGH FLYSKY_BUTTON_SWA
#define PUNCH_BUTTON_ON_FLYSKY_LOW  FLYSKY_BUTTON_SWD

#define BOOST_ENABLE  // заккоментировать строку, если хотите отключить функцию ускорения по джойстику
#define NO_BOOST_PART 0.6

void setup() {
  // Serial.begin(9600);
  flysky.begin(Serial);
  // flysky.setup();
  motors.setup();
  // gy25.setup();
  setupBumper();
  // testMotors();
}

unsigned long int t = 0;
long int rotation = 0;

void loop() {
  mainFlysky();
  // mainFlyskyBeta();
  // gy25.update();
  // if (t<millis()) {
  //   gy25.print();
  //   t = millis() + 100;
  // }
  
}

float angleToSpeed(int angle) {
  float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
  if (speed_from_angle>1) speed_from_angle = 1;
  else if (speed_from_angle<-1) speed_from_angle = -1;
  return speed_from_angle;
}

void runVector(int speed=0, int angle=0, int rotation=0) {
  // подготовка
  while (angle<0) angle+=360;
  while (angle>360) angle-=360;
  speed = constrain(speed,-100,100);
  int motor_1_4=0,motor_2_3=0;
  // вперед-назад
  motor_1_4 = angleToSpeed(angle)*speed;
  motor_2_3 = angleToSpeed(angle+90)*speed;
  // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation));
  motors.run(1,motor_1_4+rotation);
  motors.run(2,motor_2_3-rotation);
  motors.run(3,motor_2_3+rotation);
  motors.run(4,motor_1_4-rotation);
}

long int napravlenie = 0;
bool napravlenie_flag = 0;

void mainFlysky() {
  // FlySky.test();
  // read pult
  #ifdef BOOST_ENABLE
  float boost = fmap(flysky.readChannel(FLYSKY_JOYSTICK_LEFT_Y)+100,0,200,NO_BOOST_PART,1);
  #endif
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
  if (abs(speed)<5) speed = 0; // поправка на погрешность пульта в нуле
  if (speed==0) rotation*=0.4;
  else rotation*=0.2;
  #ifdef BOOST_ENABLE
  speed *= boost;
  #endif

  // gy25.update();
  // if (rotation==0) {
  //   if (napravlenie_flag) {
  //     napravlenie_flag = 0;
  //     napravlenie = gy25.horizontal_angle;
  //   }
  //   long int e = napravlenie - gy25.horizontal_angle;
  //   if (abs(e)>5) rotation -= e*1.5;
  // } 
  // else napravlenie_flag = 1;
  

  // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation) + "   boost " + String(boost));
  runVector(speed,angle,rotation);
  // punch
  bool punch_low = flysky.readChannel(PUNCH_BUTTON_ON_FLYSKY_LOW)>0;
  bool punch_high = flysky.readChannel(PUNCH_BUTTON_ON_FLYSKY_HIGH)>0;
  if (punch_low!=global_punch_low_old) { 
    if (global_drimblrer_timer+500<millis()) solenoidPunchLow();
    else { // двойной клик, включаем\выключаем дримблеp
      global_drinbler_state = !global_drinbler_state;
    }
    global_drimblrer_timer = millis();

  }
  global_punch_low_old = punch_low;
  if (punch_high!=global_punch_high_old) solenoidPunchHigh();
  global_punch_high_old = punch_high;
  // drimbler
  drimblerRun(global_drinbler_state?DRIMBLER_ON_VALUE:DRIMBLER_MIN_VALUE);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void testMotors() {
  motors.runs(100,0,0,0); delay(2000);
  motors.runs(0,100,0,0); delay(2000);
  motors.runs(0,0,100,0); delay(2000);
  motors.runs(0,0,0,100); delay(2000);
  motors.runs(-100,0,0,0); delay(2000);
  motors.runs(0,-100,0,0); delay(2000);
  motors.runs(0,0,-100,0); delay(2000);
  motors.runs(0,0,0,-100); delay(2000);
  motors.runs();
}