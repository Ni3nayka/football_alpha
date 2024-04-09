#include "pins.h"
#include "motor.h"
#include "devices.h"

#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;

void setup() {
  Serial.begin(9600);
  // bluetooth.setup();
  motors.setup();
  solenoid.setup();
}

void loop() {
  for (int i = -100; i<=100; i++) {
    motors.motor_1.run(i);
    delay(50);
  }
}

/*void loop() {
  pult.update();
  // run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
  motors.run(pult.speed,pult.angle,pult.z,pult.arrow_x,pult.arrow_y,pult.boost);
  if (pult.punch) punch();
  // pult.test_print();
  // pult.test_print_operation();
}*/



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



class Motors2 {
  /*
  расположение моторов:
  перед сверху, где моторы 1,2
  "перед вращения" (моторов) - считать направление, при котором робот поедет вперед
  -----
  / 1 2 \
  |     |
  \ 3 4 /
  -----
  */
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
    void run(int speed=0, int angle=0, int rotation=0, int arrow_x=0, int arrow_y=0, bool boost=false) {
      // подготовка
      while (angle<0) angle+=360;
      while (angle>360) angle-=360;
      speed = constrain(speed,-100,100);
      int motor_1_4=0,motor_2_3=0;
      // кнопки буста
      if (!boost) speed /= BOOST_MOTOR;
      // вперед-назад
      if (arrow_y==0) { // по джойстику
        motor_1_4 = angle_to_speed(angle)*speed;
        motor_2_3 = angle_to_speed(angle+90)*speed;
      }
      else {  // по стрелкам
        motor_1_4 = 70*arrow_y;
        motor_2_3 = motor_1_4;
      }
      if (arrow_x==0 && arrow_y==0) {
        if (motor_1_4!=0 || motor_2_3!=0) rotation *= 0.04;
        else rotation*=0.6; // 0.6 0.7
      }
      else {
        if (arrow_y==0) rotation = 70*arrow_x;
        else rotation *= 0.02;
      }
      // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation));
      motor_1.run(motor_1_4+rotation);
      motor_2.run(motor_2_3-rotation);
      motor_3.run(motor_2_3+rotation);
      motor_4.run(motor_1_4-rotation);
    }

    void run_basic(int a=0,int b=0,int c=0,int d=0) {
      motor_1.run(a);
      motor_2.run(b);
      motor_3.run(c);
      motor_4.run(d);
    }
  private:
    float angle_to_speed(int angle) {
      float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
      if (speed_from_angle>1) speed_from_angle = 1;
      else if (speed_from_angle<-1) speed_from_angle = -1;
      return speed_from_angle;
    }
};