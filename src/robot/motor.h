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