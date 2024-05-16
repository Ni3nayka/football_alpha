#pragma once

/*#include <SoftwareSerial.h>
SoftwareSerial btSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define BT_Serial btSerial 
#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;

bluetooth.setup();
loop_bluetooth();

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
}*/

void testMotorPins() {
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

void flySkyMainVector() {
  // for (int i = 0; i<14; i++) Serial.print(String(FlySky.readChannel(i)) + " "); Serial.println();
  // int joystick_left_y = FlySky.readChannel(2);
  // int joystick_left_x = FlySky.readChannel(3);
  // int joystick_right_y = FlySky.readChannel(1);
  // int joystick_right_x = FlySky.readChannel(0);
  // motors.motor_1.run(FlySky.readChannel(0));
  // int forward = joystick_right_y*EXACT_FORWARD_K + (joystick_left_y+100)/2;
  // int turn = (joystick_left_x + joystick_right_x)*TURN_K;
  // int left_speed = forward + turn;
  // int right_speed = forward - turn;
  // Serial.println(String(left_speed) + " " + String(right_speed));
  // MotorShield.motors(left_speed, right_speed);
  delay(10);
}

void motorTest() {
  for (int i = -100; i<100; i++) {
    motor_1.start(i);
    // Serial.println(i);
    if (abs(i)>98) delay(1000);
    delay(100);
  }
}

void motorTester() {
  motorsRun(100,100,100,100); delay(2000);
  motorsRun(40,40,40,40); delay(2000);
  motorsRun(-100,-100,-100,-100); delay(2000);
  motorsRun(0,0,0,0);
}

void flySkyTest() {
  Serial.print(FlySky.readChannel(FLYSKY_JOYSTICK_LEFT_X));
  Serial.print(" ");
  Serial.print(FlySky.readChannel(FLYSKY_JOYSTICK_LEFT_Y));
  Serial.print(" ");
  Serial.print(FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_X));
  Serial.print(" ");
  Serial.print(FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y));
  Serial.print(" ");
  Serial.print(FlySky.readChannel(FLYSKY_BUTTON_SWA));
  Serial.print(" ");
  Serial.print(FlySky.readChannel(FLYSKY_BUTTON_SWD));
  Serial.println();
  // delay(10);
}

void gyroTest() {
  if (gy_25_time < millis()) {
    gy25.print();
    gy_25_time = millis() + 100;
  }
}