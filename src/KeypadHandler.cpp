#include "KeypadHandler.h"

KeypadHandler::KeypadHandler() {
  // Constructor
}

void KeypadHandler::begin() {
  // Initialize row pins as inputs with pull-up resistors
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  Serial.println("Keypad initialized");
}

char KeypadHandler::checkSerialInput() {
  if (Serial.available()) {
    return Serial.read();
  }
  return 0;
}

char KeypadHandler::getKey() {
  // Check for serial input first (allows input from Serial Monitor)
  char serialKey = checkSerialInput();
  if (serialKey != 0) {
    Serial.print("Serial input: ");
    Serial.println(serialKey);
    return serialKey;
  }
  
  // Scan the keypad matrix
  char key = 0;
  for (int c = 0; c < 4; c++) {
    digitalWrite(colPins[c], LOW);
    for (int r = 0; r < 4; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        key = keys[r][c];
        // Simple debounce - wait until key is released
        while (digitalRead(rowPins[r]) == LOW) {
          delay(10);
        }
        Serial.print("Key pressed: ");
        Serial.println(key);
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
  return key;
}