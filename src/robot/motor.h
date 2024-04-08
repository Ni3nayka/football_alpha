#pragma once

#define MOTOR_MAP 1 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

int channel_pwm = 0;

#define BOOST_MOTOR 1.2

// формулы для омни
// #define MOTORS_ANGLE_TO_SPEED abs

class Motor {
  public:
    void setup(int pin_1, int pin_2) {
      Motor::pin_1 = pin_1;
      Motor::pin_2 = pin_2;
      pinMode(Motor::pin_1,OUTPUT);
      pinMode(Motor::pin_2,OUTPUT);
      Motor::run();
    }
    void run(int speed=0) {
      speed = constrain(speed,-100,100)*MOTOR_MAP;
      // Serial.println(String(Motor::channel/2+1) + " " + String(speed) + "   " + String(Motor::channel) + " " + String(constrain(speed,0,255)) + "   " + String(Motor::channel+1) + " " + String(constrain(-speed,0,255)));
      // ledcWrite(Motor::channel, constrain(speed,0,255));
      // ledcWrite(Motor::channel+1, constrain(-speed,0,255));
    }
  private:
    int pin_1, pin_2;
};


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

class Motors {
  public:
    Motor motor_1;
    Motor motor_2;
    Motor motor_3;
    Motor motor_4;
    void setup() {
      pinMode(MOTOR_EN_12,OUTPUT);
      pinMode(MOTOR_EN_34,OUTPUT);
      digitalWrite(MOTOR_EN_12,1);
      digitalWrite(MOTOR_EN_34,1);
      motor_1.setup(MOTOR_1_IN1,MOTOR_1_IN2);
      motor_2.setup(MOTOR_2_IN1,MOTOR_2_IN2);
      motor_3.setup(MOTOR_3_IN1,MOTOR_3_IN2);
      motor_4.setup(MOTOR_4_IN1,MOTOR_4_IN2);
    }
    void run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
      // подготовка
      while (angle<0) angle+=360;
      while (angle>360) angle-=360;
      speed = constrain(speed,-100,100);
      int motor_1_4=0,motor_2_3=0;
      // кнопки буста
      if (!boost) speed /= BOOST_MOTOR;
      // вперед-назад
      if (arrow_y==0) { // по джойстику
        motor_1_4 = angle_to_speed(angle)*speed;
        motor_2_3 = angle_to_speed(angle+90)*speed;
      }
      else {  // по стрелкам
        motor_1_4 = 70*arrow_y;
        motor_2_3 = motor_1_4;
      }
      if (arrow_x==0 && arrow_y==0) {
        if (motor_1_4!=0 || motor_2_3!=0) rotation *= 0.04;
        else rotation*=0.6; // 0.6 0.7
      }
      else {
        if (arrow_y==0) rotation = 70*arrow_x;
        else rotation *= 0.02;
      }
      // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation));
      motor_1.run(motor_1_4+rotation);
      motor_2.run(motor_2_3-rotation);
      motor_3.run(motor_2_3+rotation);
      motor_4.run(motor_1_4-rotation);
    }

    void run_basic(int a=0,int b=0,int c=0,int d=0) {
      motor_1.run(a);
      motor_2.run(b);
      motor_3.run(c);
      motor_4.run(d);
    }
  private:
    float angle_to_speed(int angle) {
      float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
      if (speed_from_angle>1) speed_from_angle = 1;
      else if (speed_from_angle<-1) speed_from_angle = -1;
      return speed_from_angle;
    }
};