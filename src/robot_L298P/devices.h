#pragma once

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

