#pragma once

#include "pins.h"
#include "motor.h"

#include <SoftwareSerial.h>
SoftwareSerial btSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define BT_Serial btSerial 
#include <Trackduino_bluetooth.h>
Bluetooth bluetooth;

class Solenoid {
  public:
    void setup() {
      pinMode(SOLENOID_PIN,OUTPUT);
      digitalWrite(SOLENOID_PIN,0);
    }
    void punch() {
      digitalWrite(SOLENOID_PIN,1);
      delay(100);
      digitalWrite(SOLENOID_PIN,0);
    }
  private:
};

Solenoid solenoid;

