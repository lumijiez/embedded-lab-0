#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

class LEDController {
public:
  LEDController(int pin = LED_BUILTIN);
  LEDController(int greenPin, int redPin);
  void begin();
  void indicateSuccess();
  void indicateFailure();
  void reset();
  
private:
  int greenLedPin;
  int redLedPin;
};

#endif