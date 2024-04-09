#pragma once

#include "SoftWarePWM.h"

#define MOTOR_MAP 1 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)


#define BOOST_MOTOR 1.2

// формулы для омни
// #define MOTORS_ANGLE_TO_SPEED abs

class Motor {
  public:
    void setup(int pin_1, int pin_2) {
      Motor::pin_1.setup(pin_1);
      Motor::pin_2.setup(pin_2);
      Motor::run();
    }
    void run(int speed=0) {
      speed = constrain(speed,-100,100)*MOTOR_MAP;
      // Serial.println(String(Motor::channel/2+1) + " " + String(speed) + "   " + String(Motor::channel) + " " + String(constrain(speed,0,255)) + "   " + String(Motor::channel+1) + " " + String(constrain(-speed,0,255)));
      Motor::pin_1.write(constrain(speed,0,100));
      Motor::pin_2.write(constrain(-speed,0,100));
    }
    void update_pwm() {
      Motor::pin_1.write_update();
      Motor::pin_2.write_update();
    }
  private:
    SoftWarePWM pin_1, pin_2;
};

class Motors {
  public:
    Motor motor_1;
    Motor motor_2;
    Motor motor_3;
    Motor motor_4;
    void setup() {
      setupSoftWarePWM();
      Motors::motor_1.setup(MOTOR_1_IN1,MOTOR_1_IN2);
      Motors::motor_2.setup(MOTOR_2_IN1,MOTOR_2_IN2);
      Motors::motor_3.setup(MOTOR_3_IN1,MOTOR_3_IN2);
      Motors::motor_4.setup(MOTOR_4_IN1,MOTOR_4_IN2);
    }
    void run(int a=0,int b=0,int c=0,int d=0) {
      Motors::motor_1.run(a);
      Motors::motor_2.run(b);
      Motors::motor_3.run(c);
      Motors::motor_4.run(d);
    }
  private:
};

Motors motors;

ISR(TIMER2_A) {
  motors.motor_1.update_pwm();
  motors.motor_2.update_pwm();
  motors.motor_3.update_pwm();
  motors.motor_4.update_pwm();
}