#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H
#include <Arduino.h>
#include "LCDDisplay.h"
#include "KeypadHandler.h"
#include "LEDController.h"

class PasswordManager {
private:
  const char* password;
  char input[17]; // Buffer for storing user input (16 chars + null terminator)
  int inputIndex;
  LCDDisplay& lcd;
  KeypadHandler& keypad;
  LEDController& leds;
  bool needClear;
  bool isPasswordMode;

public:
  PasswordManager(const char* initialPassword, LCDDisplay& lcd, KeypadHandler&
  keypad, LEDController& leds);
  void begin();
  void update();
  void resetInput();
  bool addKey(char key);
  bool backspace();
  int getInputLength();
  bool checkPassword();
  void handleNormalMode(char key);
  void handlePasswordMode(char key);
};
#endif