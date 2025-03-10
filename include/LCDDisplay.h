#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal.h>
#include <Arduino.h>

class LCDDisplay {
private:
  LiquidCrystal lcd;
  
public:
  LCDDisplay(int rs, int en, int d4, int d5, int d6, int d7);
  void begin();
  void clear();
  void setCursor(int col, int row);
  void print(const char* text);
  void print(char c);
  void write(char c);
  void clearLine(int line);
};

#endif