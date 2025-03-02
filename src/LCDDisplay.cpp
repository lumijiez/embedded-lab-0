#include "LCDDisplay.h"
LCDDisplay::LCDDisplay(int rs, int en, int d4, int d5, int d6, int d7)
: lcd(rs, en, d4, d5, d6, d7) {
}

void LCDDisplay::begin() {
  lcd.begin(16, 2);
}

void LCDDisplay::clear() {
  lcd.clear();
}

void LCDDisplay::setCursor(int col, int row) {
  lcd.setCursor(col, row);
}

void LCDDisplay::print(const char* text) {
  lcd.print(text);
}

void LCDDisplay::print(char c) {
  lcd.print(c);
}

void LCDDisplay::clearLine(int line) {
  lcd.setCursor(0, line);
  lcd.print(" ");
  lcd.setCursor(0, line);
}

void LCDDisplay::printWelcomeScreen() {
  clear();
  print("Password System");
  setCursor(0, 1);
  print("Press # to start");
}

void LCDDisplay::printPasswordPrompt() {
  clear();
  print("Enter password:");
  setCursor(0, 1);
}

void LCDDisplay::printPasswordMask(int length) {
  setCursor(0, 1);
  for (int i = 0; i < length; i++) {
    print('*');
  }
}
