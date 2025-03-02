#include "LEDController.h"

LEDController::LEDController(int pin) : ledPin(pin) {
  pinMode(ledPin, OUTPUT);
}

LEDController::LEDController(int greenPin, int redPin)
  : greenLedPin(greenPin), redLedPin(redPin) {
}

void LEDController::begin() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  reset();
}

void LEDController::indicateSuccess() {
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW);
}

void LEDController::indicateFailure() {
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
}

void LEDController::reset() {
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

void LEDController::turnOn() {
  digitalWrite(ledPin, HIGH);
}

void LEDController::turnOff() {
  digitalWrite(ledPin, LOW);
}
