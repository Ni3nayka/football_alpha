#include "pins.h"
#include "motor.h"
#include "devices.h"

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
}

void loop() {
  loop_test();
}

void loop_test() {
  for (int i = -100; i<=100; i++) {
    motors.motor_4.run(i);
    delay(50);
    if (abs(i)>=99) delay(1000);
  }
}


