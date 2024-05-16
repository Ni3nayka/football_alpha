#include "pins.h"
#include "motor.h"
#include "devices.h"
#include "FlySky.h"
#include "tests.h"

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
  solenoid.setup();
  FlySky.setup();
  motorsRun(0,0,0,0);
  // motor_tester();
}

void loop() {
  flySky_main();
  // flySky_test();
  // motor_test();
}

void flySky_main() {
  int y = FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_Y);
  int x = FlySky.readChannel(FLYSKY_JOYSTICK_RIGHT_X);
  int rotation = FlySky.readChannel(FLYSKY_JOYSTICK_LEFT_X);
  bool punch = FlySky.readChannel(FLYSKY_BUTTON_SWA)>90 || FlySky.readChannel(FLYSKY_BUTTON_SWD)>90;
  // Serial.println(String(y)+" "+String(x)+" "+String(rotation)+" "+String(punch));
  motor_1.start(y+x+rotation);
  motor_2.start(y-x-rotation);
  motor_3.start(y-x+rotation);
  motor_4.start(y+x-rotation);
  if (punch) solenoid.punch();
}

