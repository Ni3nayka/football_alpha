#include "SoftWarePWM.h"
#include "pins.h"

#include "motor.h"
Motors motors;

#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;            // создадим объект для управления блютузом

void setup() {
  // motor

  pinMode(A3, OUTPUT); // Все каналы ШИМ устанавливаются как выходы
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  setupSoftWarePWM();


  bluetooth.setup();            // инициализируем блютуз

  Serial.begin(9600);
  motors.setup();
  pinMode(SOLINOID_PIN,OUTPUT);
  digitalWrite(SOLINOID_PIN,0);
}

/*void loop() {
  pult.update();
  // run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
  motors.run(pult.speed,pult.angle,pult.z,pult.arrow_x,pult.arrow_y,pult.boost);
  if (pult.punch) punch();
  // pult.test_print();
  // pult.test_print_operation();
}*/

void loop() { // Получаем заполнение ШИМ с потенциометров
  dutyA3++;// = map(analogRead(A0), 0, 1023, 0, ); // У каждого канала свой потенциометр
  if (dutyA3>PWM_DEPTH) dutyA3 = 0;
  dutyA4 = 0;
  dutyA5 = 0;
  delay(100);  // Других задач нет - можно поставить delay (иначе ставим millis() таймер)
}

void punch() {
  digitalWrite(SOLINOID_PIN,1);
  delay(100);
  digitalWrite(SOLINOID_PIN,0);
}

void loop_bluetooth () {

  // обновить блютуз
  bluetooth.update();

  int X = bluetooth.x;          // взять данные с джойстика, по оси X
  // bluetooth.x - взять данные с джойстика, по оси X [-100;100]
  // bluetooth.y - взять данные с джойстика, по оси Y [-100;100]
  // bluetooth.z - взять данные с джойстика, по оси Z [-100;100]
  // bluetooth.w - взять данные с джойстика, по оси W [-100;100]
  
  int aX = bluetooth.ax;        // взять угол наклона телефона по оси Х
  // bluetooth.ax - взять данные с акселерометра, по оси X [-100;100]
  // bluetooth.ay - взять данные с акселерометра, по оси Y [-100;100]
  // bluetooth.az - взять данные с акселерометра, по оси Z [-100;100]
     
  int S1 = bluetooth.slider[1]; // взять данные с первого слайдера
  // bluetooth.slider[1]; - взять данные с ползунка номер 1 [0;180]
  // bluetooth.slider[2]; - взять данные с ползунка номер 2 [0;180]
  // bluetooth.slider[3]; - взять данные с ползунка номер 3 [0;180]
  
  if (bluetooth.f[1]) {         // если кнопка f1 нажата
    digitalWrite(13, HIGH);     // включаем светодиод
  }
  else {                        // иначе
    digitalWrite(13, LOW);      // выключаем светодиод
  }
  // bluetooth.f[1] - состояние кнопки f1 [0;1]
  // bluetooth.f[2] - состояние кнопки f2 [0;1]
  // bluetooth.f[3] - состояние кнопки f3 [0;1]
  // bluetooth.f[4] - состояние кнопки f4 [0;1]
  // bluetooth.f[5] - состояние кнопки f5 [0;1]
  // bluetooth.f[6] - состояние кнопки f6 [0;1]
}