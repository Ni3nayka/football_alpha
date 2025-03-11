#pragma once

#define SOLENOID_ANALOG_ENABLE_LOW  225 // пас
#define SOLENOID_ANALOG_ENABLE_HIGH 255 // удар
bool global_punch_low_old = 0; // запоминаем предыдущее состоянние рычажков
bool global_punch_high_old = 0;

unsigned long int global_drimblrer_timer = 0;
bool global_drinbler_state = 0;
#define DRIMBLER_MIN_VALUE 800
#define DRIMBLER_MAX_VALUE 2300
#define DRIMBLER_ON_VALUE 1500 // Это скорость работы дримблера

#define DRIMBLER_DISABLER_DURING_PUNCH

// #include <Servo.h>
// Servo ESC;     // create servo object to control the ESC

void setupBumper() {
  pinMode(SOLENOID_PIN,OUTPUT);
  pinMode(CHANNEL_DRIMBLER_PIN,OUTPUT);
    
  //for (long int t = millis()+2000; t>millis();) drimblerRun(DRIMBLER_MAX_VALUE);
  //for (long int t = millis()+4000; t>millis();) drimblerRun(DRIMBLER_MIN_VALUE);
  
  // ESC.attach(CHANNEL_DRIMBLER_PIN);
  // 800-2300
  // initialize
  // ESC.writeMicroseconds(2300); 
  // delay(2000);
  // ESC.writeMicroseconds(800); 
  // delay(4000); // 2000

}

void drimblerRun(int pos) {
  // int pos = global_drinbler_state?1500:800;
  digitalWrite(CHANNEL_DRIMBLER_PIN, 1);
  delayMicroseconds(pos);
  digitalWrite(CHANNEL_DRIMBLER_PIN, 0);
  delayMicroseconds(20000-pos);
}
    
void solenoidPunchDrimlerDisableEnable() { // bool enable = 1
    #ifdef DRIMBLER_DISABLER_DURING_PUNCH
    for (long int t = millis()+100; t>millis();) drimblerRun(DRIMBLER_MIN_VALUE);
    #endif
}

void solenoidPunchLow() {
  solenoidPunchDrimlerDisableEnable();
  analogWrite(SOLENOID_PIN,SOLENOID_ANALOG_ENABLE_LOW);
  delay(100);
  digitalWrite(SOLENOID_PIN,0);
}

void solenoidPunchHigh() {
  solenoidPunchDrimlerDisableEnable();
  analogWrite(SOLENOID_PIN,SOLENOID_ANALOG_ENABLE_HIGH);
  delay(100);
  digitalWrite(SOLENOID_PIN,0);
}


      // if (global_drinbler_state) {
      //   ESC.writeMicroseconds(1500); // middle
      // }
      // else {
      //   ESC.writeMicroseconds(800); // off
      // }
      // digitalWrite(CHANNEL_DRIMBLER_PIN,global_drinbler_state);
