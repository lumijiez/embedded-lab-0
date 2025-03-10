#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(int rs, int en, int d4, int d5, int d6, int d7)
  : lcd(rs, en, d4, d5, d6, d7) {
  // Constructor
}

void LCDDisplay::begin() {
  lcd.begin(16, 2);
  Serial.println("LCD initialized");
}

void LCDDisplay::clear() {
  lcd.clear();
  Serial.println("LCD cleared");
}

void LCDDisplay::setCursor(int col, int row) {
  lcd.setCursor(col, row);
}

void LCDDisplay::print(const char* text) {
  lcd.print(text);
  Serial.print("LCD text: ");
  Serial.println(text);
}

void LCDDisplay::print(char c) {
  lcd.print(c);
  Serial.print("LCD char: ");
  Serial.println(c);
}

void LCDDisplay::write(char c) {
  lcd.write(c);
  // For debugging
  if (c >= 32 && c <= 126) { // Only print printable ASCII
    Serial.print("LCD write: ");
    Serial.println(c);
  } else if (c == '\n') {
    lcd.setCursor(0, 1); // Move to the next line
    Serial.println("LCD newline");
  }
}

void LCDDisplay::clearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; i++) {
    lcd.print(' ');
  }
  lcd.setCursor(0, line);
  Serial.print("LCD line cleared: ");
  Serial.println(line);
}