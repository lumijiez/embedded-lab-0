#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>

class ButtonController {
private:
    const int _buttonPin;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    bool _lastButtonState;
    bool _buttonState;
    
public:
    ButtonController(int buttonPin, unsigned long debounceDelay = 50);
    bool wasPressed();
    void update();
    bool getState() const;
};

#endif 