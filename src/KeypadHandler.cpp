#include "KeypadHandler.h"
KeypadHandler::KeypadHandler() {}

void KeypadHandler::begin() {
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

char KeypadHandler::getKey() {
  char key = 0;

  // Scan the keypad using a matrix scan approach
  for (int c = 0; c < 4; c++) {
    digitalWrite(colPins[c], LOW);
    for (int r = 0; r < 4; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        key = keys[r][c];
        // Simple debounce - wait until key is released
        while (digitalRead(rowPins[r]) == LOW) {
          delay(10);
        }
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
  return key;
}