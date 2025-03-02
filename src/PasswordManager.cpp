#include "PasswordManager.h"
#include <string.h>
PasswordManager::PasswordManager(const char* initialPassword, LCDDisplay& lcd,
KeypadHandler& keypad, LEDController& leds)
: lcd(lcd), keypad(keypad), leds(leds) {
  password = initialPassword;
  resetInput();
  needClear = true;
  isPasswordMode = false;
}
void PasswordManager::begin() {
  lcd.begin();
  keypad.begin();
  leds.begin();
  lcd.printWelcomeScreen();
  Serial.begin(9600);
  Serial.println("Password Verification System");
}

void PasswordManager::update() {
  char key = keypad.getKey();
  if (key != 0) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    // Mode switch to password entry
    if (key == '#' && !isPasswordMode) {
      isPasswordMode = true;
      lcd.printPasswordPrompt();
      resetInput();
      needClear = false;
      return;
    }
    if (isPasswordMode) {
      handlePasswordMode(key);
    } else {
      handleNormalMode(key);
    }
  }
}

void PasswordManager::handleNormalMode(char key) {
  if (needClear) {
    lcd.clear();
    needClear = false;
  }
  lcd.setCursor(0, 0);
  lcd.print("Key: ");
  lcd.print(key);
}

void PasswordManager::handlePasswordMode(char key) {
  if (key == '*') {
  // Backspace functionality
    if (backspace()) {
      lcd.clearLine(1);
      lcd.printPasswordMask(getInputLength());
    }
  }
  else if (key == '#') {
  // Submit and verify password
    bool isCorrect = checkPassword();
    lcd.clear();
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
    lcd.printWelcomeScreen();
    isPasswordMode = false;
    needClear = true;
    resetInput();
  }
  else if (addKey(key)) {
  // Add character to input and update display
    lcd.clearLine(1);
    lcd.printPasswordMask(getInputLength());
  }
}

void PasswordManager::resetInput() {
  inputIndex = 0;
  input[inputIndex] = '\0';
}
bool PasswordManager::addKey(char key) {
  if (inputIndex < 16) {
    input[inputIndex] = key;
    inputIndex++;
    input[inputIndex] = '\0';
    return true;
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
  bool isCorrect = true;
  for (int i = 0; password[i] != '\0' && i < inputIndex; i++) {
    if (password[i] != input[i]) {
      isCorrect = false;
      break;
    }
  }
  // Also check length to prevent partial matches
  if (strlen(password) != inputIndex) {
    isCorrect = false;
  }
  return isCorrect;
}