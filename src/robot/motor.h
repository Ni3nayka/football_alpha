#pragma once

#define PWM_RIGHT 10 
#define DIR_RIGHT 12
#define PWM_LEFT  11
#define DIR_LEFT  13

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
    Motor motor_l;
    Motor motor_r;
    void setup() {
      motor_l.setup(DIR_LEFT,PWM_LEFT);
      motor_r.setup(DIR_RIGHT,PWM_RIGHT);
    }
    void run(int l=0,int r=0) {
      motor_l.run(l);
      motor_r.run(r);
    }
  private:
};

Motors motors;