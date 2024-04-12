#include "pins.h"
#include "motor.h"
#include "devices.h"

#include <SoftwareSerial.h>
SoftwareSerial btSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define BT_Serial btSerial 
#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;

void setup() {
  Serial.begin(9600);
  bluetooth.setup();
  // motors.setup();
  solenoid.setup();
  test_motor();
}

void test_motor() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);

  digitalWrite(A0,1);
  digitalWrite(A1,0);
  digitalWrite(A2,1);
  digitalWrite(A3,0);
  digitalWrite(A4,1);
  digitalWrite(A5,0);
  digitalWrite(A6,1);
  digitalWrite(A7,0);
  delay(5000);
  digitalWrite(A0,0);
  digitalWrite(A1,1);
  digitalWrite(A2,0);
  digitalWrite(A3,1);
  digitalWrite(A4,0);
  digitalWrite(A5,1);
  digitalWrite(A6,0);
  digitalWrite(A7,1);
  delay(5000);
  digitalWrite(A0,0);
  digitalWrite(A1,0);
  digitalWrite(A2,0);
  digitalWrite(A3,0);
  digitalWrite(A4,0);
  digitalWrite(A5,0);
  digitalWrite(A6,0);
  digitalWrite(A7,0);
  delay(5000);

  // motors.motor_1.run(-100);
  // motors.motor_2.run(-100);
  // motors.motor_3.run(-100);
  // motors.motor_4.run(-100);
  // delay(5000);
  // motors.motor_1.run(0);
  // motors.motor_2.run(0);
  // motors.motor_3.run(0);
  // motors.motor_4.run(0);
}

void loop() {
  // loop_test();
  loop_bluetooth();
}

void loop_test() {
  for (int i = -100; i<=100; i++) {
    motors.motor_1.run(i);
    delay(50);
  }
}

void loop_bluetooth() {
  bluetooth.update();
  // motor
  int angle = 0;
  if (bluetooth.x==0 && bluetooth.y==0) angle = 0;
  else {
    angle = atan(float(bluetooth.x)/float(bluetooth.y))*57.3;
    if (bluetooth.y<0) {
      if (bluetooth.x>0) angle+=180;
      else angle-=180;
    }
  }
  int speed = max(abs(bluetooth.x),abs(bluetooth.y));
  int rotate = bluetooth.z; // x y z w [-100;100]
  run(speed, angle, rotate);
  // solenoid
  bool punch = bluetooth.f[1] || bluetooth.f[2] || bluetooth.f[3] || bluetooth.f[4] || bluetooth.f[5] || bluetooth.f[6];
  //bool punch = abs(bluetooth.ay)>50;
  if (punch) solenoid.punch();
  // test
  Serial.println("speed: " + String(speed) + "   " + "angle: " + String(angle) + "   " + "rotate: " + String(rotate) + "   " + "punch: " + String(punch));
}


float angle_to_speed(int angle) {
  float speed_from_angle = fabs(fabs(angle/45.0-9)-4)-2;
  if (speed_from_angle>1) speed_from_angle = 1;
  else if (speed_from_angle<-1) speed_from_angle = -1;
  return speed_from_angle;
}
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
void run(int speed, int angle, int rotation) {
  // подготовка
  while (angle<0) angle+=360;
  while (angle>360) angle-=360;
  speed = constrain(speed,-100,100);
  int motor_1_4=0,motor_2_3=0;
  // вперед-назад
  motor_1_4 = angle_to_speed(angle)*speed;
  motor_2_3 = angle_to_speed(angle+90)*speed;
  if (motor_1_4!=0 || motor_2_3!=0) rotation *= 0.04;
  else rotation*=0.6;
  // Serial.println("speed " + String(speed) + "   angle " + String(angle) +  + "   rotation " + String(rotation));
  motors.motor_1.run(motor_1_4+rotation);
  motors.motor_2.run(motor_2_3-rotation);
  motors.motor_3.run(motor_2_3+rotation);
  motors.motor_4.run(motor_1_4-rotation);
}