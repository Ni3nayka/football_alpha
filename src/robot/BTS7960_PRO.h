/*
   arduino library for gy-25 module:
   https://github.com/Ni3nayka/BTS7960_PRO

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  July 2024
   modify: July 2024

   links:
   https://arduinoplus.ru/74hc595-arduino/
*/  

#pragma once

#define QUANTITY_MOTORS 4

#define LATCH_PIN 7
#define CLOCK_PIN 4
#define DATA_PIN  2

const int MOTOR_PWM_PIN[QUANTITY_MOTORS] = {6,3,9,5};
const int MOTOR_DIR_1[QUANTITY_MOTORS] = { // 2,1,0,5
  0b00100000,
  0b01000000,
  0b10000000,
  0b00000100,
};
const int MOTOR_DIR_2[QUANTITY_MOTORS] = { // 3,4,7,6
  0b00010000,
  0b00001000,
  0b00000001,
  0b00000010,
};

class BTS7960_PRO {
  public:
    void setup() {
      pinMode(LATCH_PIN, OUTPUT);
      pinMode(DATA_PIN, OUTPUT);
      pinMode(CLOCK_PIN, OUTPUT);
      for (int i = 0; i<QUANTITY_MOTORS; i++) {
        BTS7960_PRO::speed[i] = 0;
        BTS7960_PRO::block[i] = 0;
        pinMode(MOTOR_PWM_PIN[i],OUTPUT);
      }
    }
    void run(int number, int speed=0, bool update=1) {
      BTS7960_PRO::runBasic(number,speed,0,update);
    }
    void runs(int a=0, int b=0, int c=0, int d=0) {
      BTS7960_PRO::run(1,a,0);
      BTS7960_PRO::run(2,b,0);
      BTS7960_PRO::run(3,c,0);
      BTS7960_PRO::run(4,d);
    }
    void blockMotor(int number, bool update=1) {
      BTS7960_PRO::runBasic(number,0,1,update);
    }
    void blockMotors() {
      for (int i = 0; i<QUANTITY_MOTORS; i++) {
        BTS7960_PRO::blockMotor(i,0);
      }
      BTS7960_PRO::update();
    }
    void runWithBlock(int number, int speed=0, bool update=1) {
      if (speed==0) blockMotor(number,update);
      else run(number,speed,update);
    }
    void runWithBlocks(int a=0, int b=0, int c=0, int d=0) {
      BTS7960_PRO::runWithBlock(1,a,0);
      BTS7960_PRO::runWithBlock(2,b,0);
      BTS7960_PRO::runWithBlock(3,c,0);
      BTS7960_PRO::runWithBlock(4,d);
    }
  private:
    int speed[QUANTITY_MOTORS];
    bool block[QUANTITY_MOTORS];
    void runBasic(int number, int speed=0, bool block=0, bool update=1) {
      if (number<1 || number>QUANTITY_MOTORS) return;
      BTS7960_PRO::speed[number-1] = constrain(speed,-100,100)*2.55*int(!block);
      BTS7960_PRO::block[number-1] = block;
      if (update) BTS7960_PRO::update();
    }
    void update() {
      int direction = 0;
      for (int i = 0; i<QUANTITY_MOTORS; i++) {
        if (BTS7960_PRO::block[i]) direction += MOTOR_DIR_1[i] + MOTOR_DIR_2[i];
        else if (BTS7960_PRO::speed[i]>0) direction += MOTOR_DIR_1[i];
        else if (BTS7960_PRO::speed[i]<0) direction += MOTOR_DIR_2[i];
        analogWrite(MOTOR_PWM_PIN[i],abs(BTS7960_PRO::speed[i]));
      }
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, direction);
      digitalWrite(LATCH_PIN, HIGH);
    }
};