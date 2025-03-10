#include "PasswordManager.h"
#include <stdio.h>
#include <string.h>

PasswordManager::PasswordManager(const char* initialPassword, LCDDisplay& lcd, 
                                KeypadHandler& keypad, LEDController& leds)
  : lcd(lcd), keypad(keypad), leds(leds) {
  password = initialPassword;
  resetInput();
  isPasswordMode = false;
}

void PasswordManager::begin() {
  isPasswordMode = false;
  Serial.println("Password Manager initialized");
}

void PasswordManager::update() {
  char key;
  if (scanf("%c", &key) == 1) {
    Serial.print("Key processed: ");
    Serial.println(key);
    
    // Mode switch to password entry
    if (key == '#' && !isPasswordMode) {
      promptForPassword();
      return;
    }
    
    if (isPasswordMode) {
      if (key == '*') {
        // Backspace functionality
        if (backspace()) {
          lcd.clearLine(1);
          lcd.setCursor(0, 1);
          for (int i = 0; i < getInputLength(); i++) {
            lcd.print('*');
          }
        }
      }
      else if (key == '#') {
        // Submit and verify password
        processPassword();
      }
      else if (addKey(key)) {
        // Add character to input and update mask
        lcd.clearLine(1);
        lcd.setCursor(0, 1);
        for (int i = 0; i < getInputLength(); i++) {
          lcd.print('*');
        }
      }
    } else {
      // In normal mode, just echo key presses
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Key pressed:");
      lcd.setCursor(0, 1);
      lcd.print(key);
    }
  }
}

void PasswordManager::promptForPassword() {
  isPasswordMode = true;
  resetInput();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter password:");
  lcd.setCursor(0, 1);
  Serial.println("Entering password mode");
}

void PasswordManager::processPassword() {
  bool isCorrect = checkPassword();
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (isCorrect) {
    lcd.print("Access Granted!");
    leds.indicateSuccess();
    Serial.println("Correct password entered");
  } else {
    lcd.print("Access Denied!");
    leds.indicateFailure();
    Serial.println("Incorrect password entered");
  }
  
  delay(2000);
  leds.reset();
  
  // Return to welcome screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Password System");
  lcd.setCursor(0, 1);
  lcd.print("Press # to start");
  
  isPasswordMode = false;
  resetInput();
}

void PasswordManager::resetInput() {
  inputIndex = 0;
  input[inputIndex] = '\0';
  Serial.println("Input reset");
}

bool PasswordManager::addKey(char key) {
  // Only add numeric keys and A-D keys
  if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'D')) {
    if (inputIndex < 16) {
      input[inputIndex] = key;
      inputIndex++;
      input[inputIndex] = '\0';
      return true;
    }
  }
  return false;
}

bool PasswordManager::backspace() {
  if (inputIndex > 0) {
    inputIndex--;
    input[inputIndex] = '\0';
    return true;
  }
  return false;
}

int PasswordManager::getInputLength() {
  return inputIndex;
}

bool PasswordManager::checkPassword() {
  // Compare entered password with stored password
  Serial.print("Checking password: ");
  Serial.println(input);
  
  // Check if input matches password
  if (strlen(password) != inputIndex) {
    return false;
  }
  
  for (int i = 0; i < inputIndex; i++) {
    if (password[i] != input[i]) {
      return false;
    }
  }
  
  return true;
}