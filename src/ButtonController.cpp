#include "ButtonController.h"

ButtonController::ButtonController(int buttonPin, unsigned long debounceDelay) :
    _buttonPin(buttonPin),
    _lastDebounceTime(0),
    _debounceDelay(debounceDelay),
    _lastButtonState(HIGH),
    _buttonState(HIGH) {
    
    pinMode(_buttonPin, INPUT_PULLUP);
}

bool ButtonController::wasPressed() {
    bool result = false;
    int reading = digitalRead(_buttonPin);
    
    if (reading != _lastButtonState) _lastDebounceTime = millis();

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _buttonState) {
            _buttonState = reading;
            if (_buttonState == LOW) result = true;
        }
    }
    
    _lastButtonState = reading;
    
    return result;
}

void ButtonController::update() {
    int reading = digitalRead(_buttonPin);
    
    if (reading != _lastButtonState) _lastDebounceTime = millis();
    
    if ((millis() - _lastDebounceTime) > _debounceDelay)
        if (reading != _buttonState) _buttonState = reading;
    
    _lastButtonState = reading;
}

bool ButtonController::getState() const {
    return _buttonState;
}