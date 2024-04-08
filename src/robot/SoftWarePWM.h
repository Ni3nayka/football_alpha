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
    }
    void write(int pwm) {
      if (counter > PWM_DEPTH) {
      // Переполнение счетчика - все каналы ШИМ устанавливаются в HIGH
      if (dutyA3 > 0) fastWrite(A3, HIGH); // Устанавливаем HIGH, только если заполнение >0 (быстрый digitalWrite)
      if (dutyA4 > 0) fastWrite(A4, HIGH); // Решает проблему слабого свечения LED при заполнении = 0
      fastWrite(A5, HIGH); // Можно и не проверять на 0, если используется электродвигатель или лампа накаливания
      counter = 0;                // Обнуляем счетчик ВРУЧНУЮ
    }

    if (counter == dutyA3) fastWrite(A3, LOW); // Проверяем все каналы на совпадение счетчика со значением заполнения
    if (counter == dutyA4) fastWrite(A4, LOW); // При совпадении переводим канал в состояние LOW
    if (counter == dutyA5) fastWrite(A5, LOW);
    }
  private:
    byte pin, duty;
};

/*
   Софтверный ШИМ
*/
void pwmTick() {
  static volatile uint8_t counter = 0;  // Счетчик

  if (counter > PWM_DEPTH) {
    // Переполнение счетчика - все каналы ШИМ устанавливаются в HIGH
    if (dutyA3 > 0) fastWrite(A3, HIGH); // Устанавливаем HIGH, только если заполнение >0 (быстрый digitalWrite)
    if (dutyA4 > 0) fastWrite(A4, HIGH); // Решает проблему слабого свечения LED при заполнении = 0
    fastWrite(A5, HIGH); // Можно и не проверять на 0, если используется электродвигатель или лампа накаливания
    counter = 0;                // Обнуляем счетчик ВРУЧНУЮ
  }

  if (counter == dutyA3) fastWrite(A3, LOW); // Проверяем все каналы на совпадение счетчика со значением заполнения
  if (counter == dutyA4) fastWrite(A4, LOW); // При совпадении переводим канал в состояние LOW
  if (counter == dutyA5) fastWrite(A5, LOW);

  counter++;                                        // Инкремент счетчика
}

ISR(TIMER2_A) {
  pwmTick();    // Тикер ШИМ в прерывании таймера (можно перенести код тикера сюда)
}

volatile byte dutyA3 = 0; // Переменные для хранения заполнения ШИМ
volatile byte dutyA4 = 0; // Можно упаковать в массив при желании
volatile byte dutyA5 = 0;
