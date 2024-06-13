#pragma once

#define MOTOR_MAP 2.5 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

class Motor {
  public:
    void setup(int pin_dir, int pin_pwm, float k=1.0) {
      Motor::pin_dir = pin_dir;
      Motor::pin_pwm = pin_pwm;
      pinMode(Motor::pin_dir,OUTPUT);
      pinMode(Motor::pin_pwm,OUTPUT);
      Motor::run();
      if (Motor::k>1.0) Motor::k = 1.0;
      else if (Motor::k<0) Motor::k = 0;
      Motor::k = k;
    }
    void run(int speed=0) {
      if (abs(speed)<5) speed = 0;
      else speed = constrain(speed,-100,100)*MOTOR_MAP*k;
      digitalWrite(Motor::pin_dir,speed>0);
      analogWrite(Motor::pin_pwm,abs(speed));
    }
  private:
    int pin_dir, pin_pwm;
    float k;
};


/*
расположение моторов:
перед сверху, где моторы 1,2
"перед вращения" (моторов) - считать направление, при котором робот поедет вперед
*в данном случае, моторы запаралелены: l=1,3 r=2,4
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
    void setup(float a=1.0,float b=1.0,float c=1.0,float d=1.0) {
      motor_1.setup(MOTOR_1_DIR,MOTOR_1_PWM,a);
      motor_2.setup(MOTOR_2_DIR,MOTOR_2_PWM,b);
      motor_3.setup(MOTOR_3_DIR,MOTOR_3_PWM,c);
      motor_4.setup(MOTOR_4_DIR,MOTOR_4_PWM,d);
    }
    void run(int a=0,int b=0,int c=0,int d=0) {
      motor_1.run(a);
      motor_2.run(b);
      motor_3.run(c);
      motor_4.run(d);
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
      motor_1.run(motor_1_4+rotation);
      motor_2.run(motor_2_3-rotation);
      motor_3.run(motor_2_3+rotation);
      motor_4.run(motor_1_4-rotation);
    }
  private:
    float angleToSpeed(int angle) {
      float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
      if (speed_from_angle>1) speed_from_angle = 1;
      else if (speed_from_angle<-1) speed_from_angle = -1;
      return speed_from_angle;
    }
};

Motors motors;