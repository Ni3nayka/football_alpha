#include "pins.h"
#include "motor.h"
#include "devices.h"
#include "FlySky.h"

/* расположение моторов:
перед сверху, где моторы 1,2
"перед вращения" (моторов) - считать направление, при котором робот поедет вперед
-----
/ 1 2 \
|     |
\ 3 4 /
----- */

void setup() {
  Serial.begin(9600);
  motors.setup();
  solenoid.setup();
  FlySky.begin(Serial3); // Serial3
  //motor_tester();
  motors.run(0,0,0,0);
}

void loop() {
  flySky_main();
}

void motor_tester() {
  motors.run(100,100,100,100); delay(500);
  motors.run(40,40,40,40); delay(500);
  motors.run(-100,-100,-100,-100); delay(500);
  motors.run(0,0,0,0);
}

void flySky_main() {
  for (int i = 0; i<14; i++) Serial.print(String(FlySky.readChannel(i)) + " "); Serial.println();
  int joystick_left_y = FlySky.readChannel(2);
  int joystick_left_x = FlySky.readChannel(3);
  int joystick_right_y = FlySky.readChannel(1);
  int joystick_right_x = FlySky.readChannel(0);
  // int forward = joystick_right_y*EXACT_FORWARD_K + (joystick_left_y+100)/2;
  // int turn = (joystick_left_x + joystick_right_x)*TURN_K;
  // int left_speed = forward + turn;
  // int right_speed = forward - turn;
  // Serial.println(String(left_speed) + " " + String(right_speed));
  // MotorShield.motors(left_speed, right_speed);
  delay(10);
}



