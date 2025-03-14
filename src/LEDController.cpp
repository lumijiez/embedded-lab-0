#include "LEDController.h"

#define BLINK_INTERVAL 500

LEDController::LEDController(int ledPin) :
    _ledPin(ledPin),
    _state(false),
    _isBlinking(false),
    _previousMillis(0),
    _blinkInterval(BLINK_INTERVAL),
    _blinkCount(0) {
    
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, LOW);
}

void LEDController::turnOn() {
    _state = true;
    digitalWrite(_ledPin, HIGH);
}

void LEDController::turnOff() {
    _state = false;
    digitalWrite(_ledPin, LOW);
}

void LEDController::toggle() {
    _state = !_state;
    digitalWrite(_ledPin, _state);
}

bool LEDController::getState() const {
    return _state;
}

void LEDController::enableBlinking(bool enable) {
    _isBlinking = enable;
    if (!enable) {
        turnOff();
    }
}

bool LEDController::isBlinkingEnabled() const {
    return _isBlinking;
}

void LEDController::setBlinkInterval(unsigned long interval) {
    _blinkInterval = interval;
}

unsigned long LEDController::getBlinkInterval() const {
    return _blinkInterval;
}

unsigned long LEDController::getBlinkCount() const {
    return _blinkCount;
}

void LEDController::update() {
    if (_isBlinking) {
        unsigned long currentMillis = millis();
        
        if (currentMillis - _previousMillis >= _blinkInterval) {
            _previousMillis = currentMillis;
            toggle();
            if (_state)_blinkCount++;
        }
    }
}