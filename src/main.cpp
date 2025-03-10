// Main File (main.cpp)
#include <Arduino.h>
#include <stdio.h>
#include "LCDDisplay.h"
#include "KeypadHandler.h"
#include "PasswordManager.h"
#include "LEDController.h"

// Declare objects first so they can be used in the putchar/getchar functions
LCDDisplay lcd(12, 11, 5, 4, 3, 2);
KeypadHandler keypad;
LEDController leds(9, 10);

// Create FILE streams for stdin and stdout
static FILE lcd_stdout = {0};
static FILE keypad_stdin = {0};

// Custom function for stdout to write to LCD
int lcd_putchar(char c, FILE *stream) {
  lcd.write(c);
  return 0;
}

// Custom function for stdin to read from keypad
int keypad_getchar(FILE *stream) {
  char key;
  // Wait for key press
  do {
    key = keypad.getKey();
    delay(10); // Small delay to prevent CPU overload
  } while (key == 0);
  
  return key;
}

PasswordManager passwordManager("1234", lcd, keypad, leds);

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  
  // Set up stdio streams
  fdev_setup_stream(&lcd_stdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  fdev_setup_stream(&keypad_stdin, NULL, keypad_getchar, _FDEV_SETUP_READ);
  
  // Redirect stdout to LCD and stdin to keypad
  stdout = &lcd_stdout;
  stdin = &keypad_stdin;
  
  // Initialize components
  lcd.begin();
  keypad.begin();
  leds.begin();
  
  // Print startup message using stdio
  Serial.println("Password Verification System Starting");
  printf("Password System\nPress # to start");
  
  passwordManager.begin();
}

void loop() {
  passwordManager.update();
  delay(1);
}