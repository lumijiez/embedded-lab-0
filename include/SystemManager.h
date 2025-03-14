#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include "ButtonController.h"
#include "LEDController.h"
#include "StateManager.h"
#include "SerialLogger.h"

class SystemManager {
private:
    ButtonController _button1;
    ButtonController _button2;
    ButtonController _button3;
    LEDController _led1;
    LEDController _led2;
    StateManager _stateManager;
    SerialLogger _logger;
    const unsigned long _loopDelay;
    
public:
    SystemManager();
    void setup();
    void loop();
    
private:
    void handleButton1();
    void handleButtons2And3();
    void updateLEDs();
};

#endif