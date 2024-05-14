#pragma once

#include <SoftwareSerial.h>
SoftwareSerial btSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define BT_Serial btSerial 
#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;

// bluetooth.setup();
// loop_bluetooth();

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