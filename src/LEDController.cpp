#include "LEDController.h"

LEDController::LEDController(int pin) 
  : greenLedPin(pin), redLedPin(pin) {
  // Single LED constructor
}

LEDController::LEDController(int greenPin, int redPin)
  : greenLedPin(greenPin), redLedPin(redPin) {
  // Dual LED constructor
}

void LEDController::begin() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  reset();
  Serial.println("LEDs initialized");
}

void LEDController::indicateSuccess() {
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW);
  Serial.println("SUCCESS LED activated");
}

void LEDController::indicateFailure() {
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
  Serial.println("FAILURE LED activated");
}

void LEDController::reset() {
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  Serial.println("LEDs reset");
}
