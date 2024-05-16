#include "pins.h"
#include "motor.h"
#include "devices.h"
#include "FlySky.h"

#include "GY-25.h"
GY25 gy25(9, 10); // RX, TX
unsigned long int gy_25_time = 0;
unsigned long int flysky_update_time = 0;

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
  gy25.setup();
  solenoid.setup();
  FlySky.setup();
  motorsRun(0,0,0,0);
  // motorTester();
}

void loop() {
  gy25.update();
  // gyroTest();
  if (flysky_update_time<millis()) {
    flySkyMain();
    // flySkyTest();
    flysky_update_time = millis() + 50;
  }
  // motorTest();
}

void flySkyMain() {
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

