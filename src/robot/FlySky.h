/*
   code write for project:
   https://github.com/Ni3nayka/Monster_car

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  March 2024
   modify: March 2024

   links:
   https://dronebotworkshop.com/radio-control-arduino-car/
*/

#pragma once

unsigned long int pulseIn1(int pin, bool state, unsigned long int timeout=10000) {
  unsigned long int t = micros();
  while (digitalRead(pin)==state && micros()-t<timeout);
  t = micros();
  while (digitalRead(pin)!=state && micros()-t<timeout);
  while (digitalRead(pin)==state && micros()-t<timeout);
  return micros() - t;
}

class MyFlySky {
  public:
    void setup() {
      pinMode(FLYSKY_JOYSTICK_LEFT_X, INPUT);
      pinMode(FLYSKY_JOYSTICK_LEFT_Y, INPUT);
      pinMode(FLYSKY_JOYSTICK_RIGHT_X, INPUT);
      pinMode(FLYSKY_JOYSTICK_RIGHT_Y, INPUT);
      pinMode(FLYSKY_BUTTON_SWA, INPUT);
      pinMode(FLYSKY_BUTTON_SWD, INPUT);
    }
    int readChannel(byte channelPin, int minLimit=-100, int maxLimit=100, int defaultValue=0) {
      uint16_t ch = pulseIn1(channelPin, HIGH, 30000);
      if (ch < 100) return defaultValue;
      return map(ch, 1000, 2000, minLimit, maxLimit);
      // return pulseIn(channelPin, HIGH, 30000);
    }
  private:
};

MyFlySky FlySky;
/*
#define CH1 13
#define CH2 12
#define CH3 11
#define CH4 10
#define CH5 9
#define CH6 6

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;

// Boolean to represent switch value
int ch6Value;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup(){
  // Set up serial monitor
  Serial.begin(9600);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}


void loop() {
  
  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readChannel(CH6, -100, 100, 0);
  
  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.print(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);
  
  delay(10);
}
*/