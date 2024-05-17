#pragma once

#define MOTOR_MAP 2.5 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

class Motor {
  public:
    void setup(int pin_dir, int pin_pwm) {
      Motor::pin_dir = pin_dir;
      Motor::pin_pwm = pin_pwm;
      pinMode(Motor::pin_dir,OUTPUT);
      pinMode(Motor::pin_pwm,OUTPUT);
      Motor::run();
    }
    void run(int speed=0) {
      if (abs(speed)<5) speed = 0;
      else speed = constrain(speed,-100,100)*MOTOR_MAP;
      digitalWrite(Motor::pin_dir,speed>0);
      analogWrite(Motor::pin_pwm,abs(speed));
    }
  private:
    int pin_dir, pin_pwm;
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
    void setup() {
      motor_1.setup(MOTOR_1_DIR,MOTOR_1_PWM);
      motor_2.setup(MOTOR_2_DIR,MOTOR_2_PWM);
      motor_3.setup(MOTOR_3_DIR,MOTOR_3_PWM);
      motor_4.setup(MOTOR_4_DIR,MOTOR_4_PWM);
    }
    void run(int a=0,int b=0,int c=0,int d=0) {
      motor_1.run(a);
      motor_2.run(b);
      motor_3.run(c);
      motor_4.run(d);
    }
  private:
};

Motors motors;