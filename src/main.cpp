#include "LCDDisplay.h"
#include "KeypadHandler.h"
#include "PasswordManager.h"
#include "LEDController.h"

LCDDisplay lcd(12, 11, 5, 4, 3, 2);
KeypadHandler keypad;
LEDController leds(9, 10);
PasswordManager passwordManager("1234", lcd, keypad, leds);

void setup() {
  passwordManager.begin();
}
void loop() {
  passwordManager.update();
  delay(50);
} 