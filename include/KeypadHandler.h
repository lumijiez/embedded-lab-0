#ifndef KEYPAD_HANDLER_H
#define KEYPAD_HANDLER_H

#include <Arduino.h>

class KeypadHandler {
private:
  int rowPins[4] = {A3, A2, A1, A0};
  int colPins[4] = {A4, A5, 6, 7};
  
  // Matrix layout for keypad keys
  char keys[4][4] = {
    {'*', '7', '4', '1'},
    {'0', '8', '5', '2'},
    {'#', '9', '6', '3'},
    {'D', 'C', 'B', 'A'}
  };
  
public:
  KeypadHandler();
  void begin();
  char getKey();
  char checkSerialInput();
};

#endif