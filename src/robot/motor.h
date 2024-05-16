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

#include <AFMotor.h> // Подключаем библиотеку для работы с шилдом 

#define MOTOR_MAP 2.5 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

class Motor: public AF_DCMotor {
  public:
    using AF_DCMotor::AF_DCMotor;
    void start(int speed=0) {
      speed = constrain(speed,-100,100)*MOTOR_MAP;
      Motor::setSpeed(abs(speed));
      // Serial.println(speed);
      Motor::run(speed>0?FORWARD:(speed<0?BACKWARD:RELEASE));
    }
    void stop() {
      Motor::start();
    }
  private:
};

Motor motor_1(1);
Motor motor_2(2);
Motor motor_3(3);
Motor motor_4(4);

float angle_to_speed(int angle) {
  float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
  if (speed_from_angle>1) speed_from_angle = 1;
  else if (speed_from_angle<-1) speed_from_angle = -1;
  return speed_from_angle;
}

void motorsRun(int a=0,int b=0,int c=0,int d=0) {
  motor_1.start(a);
  motor_2.start(b);
  motor_3.start(c);
  motor_4.start(d);
}

void motorsRunVector(int speed=0, int angle=0, int rotation=0) {
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
  motor_1.start(motor_1_4+rotation);
  motor_2.start(motor_2_3-rotation);
  motor_3.start(motor_2_3+rotation);
  motor_4.start(motor_1_4-rotation);
}