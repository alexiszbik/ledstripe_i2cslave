#include <Wire.h>
#include "StripeEngine.h"

#define LED_TEST 13

#define CC_SPEED 3
#define CC_RAINBOWSPEED 4

#define NOTE_START 72

StripeEngine stripeEngine;

void setup() {
  stripeEngine.setup(NOTE_START);

  Serial.begin(9600);

  pinMode (LED_TEST, OUTPUT);

  Wire.begin(9); 

  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {

  byte command = Wire.read();
  byte dataA = Wire.read();
  byte dataB = Wire.read();

  if (command == 0) {
    stripeEngine.setColor(dataA, dataB);
    digitalWrite(LED_TEST, dataB == 0 ? LOW : HIGH);
  } else if (command == 1) {
    if (dataA == CC_SPEED) {
      stripeEngine.setDecayTime(dataB);
    }
    if (dataA == CC_RAINBOWSPEED) {
      stripeEngine.setRainbowTime(dataB);
    }
  }
}

void loop() {
  stripeEngine.loop();
  delay(10);
}