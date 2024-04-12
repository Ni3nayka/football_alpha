#pragma once

#define MOTOR_MAP 2.5 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

#define BOOST_MOTOR 1.2

// формулы для омни
// #define MOTORS_ANGLE_TO_SPEED abs

class Motor {
  public:
    void setup(int pin_pwm, int pin_dir, float k=1.0) {
      Motor::pin_pwm = pin_pwm;
      Motor::pin_dir = pin_dir;
      pinMode(Motor::pin_pwm,OUTPUT);
      pinMode(Motor::pin_dir,OUTPUT);
      Motor::k = k;
      if (Motor::k>1.0) Motor::k = 1.0;
      if (Motor::k<-1.0) Motor::k = -1.0;
      Motor::run();
    }
    void run(int speed=0) {
      speed = constrain(speed,-100,100)*MOTOR_MAP*Motor::k;
      // Serial.println(String(Motor::channel/2+1) + " " + String(speed) + "   " + String(Motor::channel) + " " + String(constrain(speed,0,255)) + "   " + String(Motor::channel+1) + " " + String(constrain(-speed,0,255)));      
      // Serial.println(speed);
      analogWrite(Motor::pin_pwm,abs(speed));
      digitalWrite(Motor::pin_dir,speed>0);
    }
  private:
    int pin_pwm, pin_dir;
    float k;
};

class Motors {
  public:
    Motor motor_1;
    Motor motor_2;
    Motor motor_3;
    Motor motor_4;
    void setup(float k1=1.0, float k2=1.0, float k3=1.0, float k4=1.0) {
      Motors::motor_1.setup(MOTOR_1_IN1,MOTOR_1_IN2,k1);
      Motors::motor_2.setup(MOTOR_2_IN1,MOTOR_2_IN2,k2);
      Motors::motor_3.setup(MOTOR_3_IN1,MOTOR_3_IN2,k3);
      Motors::motor_4.setup(MOTOR_4_IN1,MOTOR_4_IN2,k4);
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