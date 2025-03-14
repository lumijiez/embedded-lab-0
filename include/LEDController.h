#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

class LEDController {
private:
    const int _ledPin;
    bool _state;
    bool _isBlinking;
    unsigned long _previousMillis;
    unsigned long _blinkInterval;
    unsigned long _blinkCount;
    
public:
    LEDController(int ledPin);
    void turnOn();
    void turnOff();
    void toggle();
    bool getState() const;
    void enableBlinking(bool enable);
    bool isBlinkingEnabled() const;
    void setBlinkInterval(unsigned long interval);
    unsigned long getBlinkInterval() const;
    unsigned long getBlinkCount() const;
    void update();
};

#endif