#pragma once

// устанавливаем настройки формирования ШИМ
#define MOTOR_PWM_HZ 15000 // частота ШИМ
#define MOTOR_BITS 8 // разрядность (для управления) ШИМ
#define MOTOR_MAP 2.5 // для перевода скорости из размерности 100 в размерность в соответствии с MOTOR_BITS (8 бит => 255 "ШИМ" ~ 250)

int channel_pwm = 0;

// формулы для омни
// #define MOTORS_ANGLE_TO_SPEED abs

class Motor {
  public:
    void setup(int pin_1, int pin_2) {
      // настраиваем ШИМ в соответствии с ранее указанными настройками
      ledcSetup(channel_pwm, MOTOR_PWM_HZ, MOTOR_BITS);
      ledcSetup(channel_pwm+1, MOTOR_PWM_HZ, MOTOR_BITS);
      // назначаем контакт и канал для формирования ШИМ
      ledcAttachPin(pin_1, channel_pwm);
      ledcAttachPin(pin_2, channel_pwm+1);
      // "занимаем" каналы ШИМ
      Motor::channel = channel_pwm;
      channel_pwm+=2;
      // переключаем ШИМы в ноль(чтобы все стояло)
      Motor::run();
    }
    void run(int speed=0) {
      speed = constrain(speed,-100,100)*MOTOR_MAP;
      ledcWrite(Motor::channel, abs(speed));
      ledcWrite(Motor::channel+1, abs(-speed));
    }
  private:
    //int pin_1, pin_2;
    int channel; // channel_pwm
};


'''
расположение моторов:
перед сверху, где моторы 1,2
"перед вращения" (моторов) - считать направление, при котором робот поедет вперед
 -----
/ 1 2 \
|     |
\ 3 4 /
 -----
'''

class Motors {
  public:
    Motor motor_1;
    Motor motor_2;
    Motor motor_3;
    Motor motor_4;
    void setup() {
      motor_1.setup(MOTOR_1_IN1,MOTOR_1_IN2);
      motor_2.setup(MOTOR_2_IN1,MOTOR_2_IN2);
      motor_3.setup(MOTOR_3_IN1,MOTOR_3_IN2);
      motor_4.setup(MOTOR_4_IN1,MOTOR_4_IN2);
    }
    void run(int speed=0, int angle=0, int rotation=0) {
      speed = constrain(speed,-100,100);
      int motor_1_4 = angle_to_speed(angle+270)*speed;
      int motor_1_4 = angle_to_speed(angle)*speed;
      motor_1.run(motor_1_4);
      motor_2.run(motor_2_3);
      motor_3.run(motor_2_3);
      motor_4.run(motor_1_4);
    }
  private:
    float angle_to_speed(int angle) {
      float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
      if (speed_from_angle>1) speed_from_angle = 1;
      else if (speed_from_angle<-1) speed_from_angle = -1;
      return speed_from_angle;
    }
};