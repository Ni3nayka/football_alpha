// https://alexgyver.ru/lessons/pwm-signal/
// https://github.com/AlexGyver/tutorials/blob/master/soft_pwm_lesson/examples/pwm_custom/FastIO.h

#pragma once

#include "FastIO.h"       // Либа быстрого ввода/вывода

#define PWM_HZ 100      // частота ШИМ
const int SOFT_PWM_TIME_DELTA = 1000/PWM_HZ;

// Можно выбрать от 2 до 254 (больше нельзя)
// В данном случае ШИМ имеет пределы 0 - 15 (4 бита, 16 градаций)

#define MAX_SOFT_PWM 8
int _not_using_soft_pwm_pins[MAX_SOFT_PWM] = {0};
int _not_using_soft_pwm_value[MAX_SOFT_PWM] = {0};
unsigned long int _not_using_soft_pwm_timer_pin[MAX_SOFT_PWM] = {0};
int _not_using_soft_pwm_counter = 0;
unsigned long int _not_using_soft_pwm_time = 0;

void pwmUpdate() {
  if (_not_using_soft_pwm_time<millis()) {
    // enable
    for (int i = 0; i<_not_using_soft_pwm_counter; i++) {
      fastWrite(_not_using_soft_pwm_pins[i],1);
      _not_using_soft_pwm_timer_pin[i] = millis() + _not_using_soft_pwm_value[i];
    }
    _not_using_soft_pwm_time = millis() + SOFT_PWM_TIME_DELTA;
  } else {
    // disable
    for (int i = 0; i<_not_using_soft_pwm_counter; i++) {
      if (_not_using_soft_pwm_timer_pin[i]<millis()) 
        fastWrite(_not_using_soft_pwm_pins[i],0);
    }
  }
  
}

class SoftWarePWM {
  public:
    void setup(int pin) {
      if (_not_using_soft_pwm_counter<MAX_SOFT_PWM) {
        SoftWarePWM::number = _not_using_soft_pwm_counter;
        pinMode(pin, OUTPUT);
        _not_using_soft_pwm_pins[_not_using_soft_pwm_counter] = pin;
        _not_using_soft_pwm_value[_not_using_soft_pwm_counter] = 0;
        _not_using_soft_pwm_counter++;
      } else {
        SoftWarePWM::number = -1;
      }
    }
    void write(int pwm) {
      // pwm = [-100,100]
      if (SoftWarePWM::number!=-1) {
        pwm = constrain(pwm,-100,100)/10;
        _not_using_soft_pwm_value[SoftWarePWM::number] = pwm;
      }
    }
    void write_update() {
      pwmUpdate();
    }
  private:
    int number;
};