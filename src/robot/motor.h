#pragma once

/*
расположение моторов:
перед сверху, где моторы 1,2
"перед вращения" (моторов) - считать направление, при котором робот поедет вперед
-----
/ 1 2 \
|     |
\ 3 4 /
-----
*/

#include "SoftWarePWM.h"

#define MOTOR_MAP 1 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

// #define BOOST_MOTOR 1.2

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
      speed = constrain(speed,-100,100)*MOTOR_MAP; // *Motor::reverse
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
    // char reverse = 1; // -1,1
};

float angle_to_speed(int angle) {
  float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
  if (speed_from_angle>1) speed_from_angle = 1;
  else if (speed_from_angle<-1) speed_from_angle = -1;
  return speed_from_angle;
}

class Motors {
  public:
    Motor motor_1;
    Motor motor_2;
    Motor motor_3;
    Motor motor_4;
    void setup() {
      // setupSoftWarePWM();
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
    void run_vector(int speed=0, int angle=0, int rotation=0) {
      // подготовка
      while (angle<0) angle+=360;
      while (angle>360) angle-=360;
      speed = constrain(speed,-100,100);
      rotation = constrain(rotation,-100,100);
      int motor_1_4=0,motor_2_3=0;
      // вперед-назад
      motor_1_4 = angle_to_speed(angle)*speed;
      motor_2_3 = angle_to_speed(angle+90)*speed;
      // if (motor_1_4!=0 || motor_2_3!=0) rotation *= 0.04;
      // else rotation*=0.6;
      // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation));
      Motors::motor_1.run(motor_1_4+rotation);
      Motors::motor_2.run(motor_2_3-rotation);
      Motors::motor_3.run(motor_2_3+rotation);
      Motors::motor_4.run(motor_1_4-rotation);
    }
  private:
};

Motors motors;