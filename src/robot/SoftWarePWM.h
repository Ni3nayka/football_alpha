// https://alexgyver.ru/lessons/pwm-signal/
// https://github.com/AlexGyver/tutorials/blob/master/soft_pwm_lesson/examples/pwm_custom/FastIO.h

#pragma once

#include <GyverTimers.h>  // Либа прерываний по таймеру
#include "FastIO.h"       // Либа быстрого ввода/вывода
#define PWM_DEPTH 100      // Предел счета таймера, определяет разрешение ШИМ
// Можно выбрать от 2 до 254 (больше нельзя)
// В данном случае ШИМ имеет пределы 0 - 15 (4 бита, 16 градаций)

void setupSoftWarePWM() {
  Timer2.setFrequency(40000);     // Заводим прерывания таймера 2 на 40кгц
  Timer2.enableISR();             // Вкл. прерывания таймера
}

class SoftWarePWM {
  public:
    void setup(int pin) {
      SoftWarePWM::pin = pin;
      pinMode(SoftWarePWM::pin, OUTPUT);
      SoftWarePWM::duty = 0;
      SoftWarePWM::counter = 0;
    }
    void write(int pwm) {
      SoftWarePWM::duty = pwm;
      SoftWarePWM::write_update();
    }
    void write_update() {
      // if (SoftWarePWM::duty==0) digitalWrite(SoftWarePWM::pin, LOW); 
      // else {
      if (SoftWarePWM::counter > PWM_DEPTH) {
        // Переполнение счетчика - все каналы ШИМ устанавливаются в HIGH
        // if (dutyA4 > 0) fastWrite(A4, HIGH); // Решает проблему слабого свечения LED при заполнении = 0, можно и не проверять на 0, если используется электродвигатель или лампа накаливания
        fastWrite(SoftWarePWM::pin, HIGH);
        SoftWarePWM::counter = 0; // Обнуляем счетчик ВРУЧНУЮ
      }
      if (SoftWarePWM::counter == SoftWarePWM::duty) fastWrite(SoftWarePWM::pin, LOW); 
      // }
      SoftWarePWM::counter++;
    }
  private:
    byte pin, duty;
    volatile uint8_t counter;
};

// SoftWarePWM pin;
// ISR(TIMER2_A) {
//   pin.write_update();
// }