#ifndef SERIAL_LOGGER_H
#define SERIAL_LOGGER_H

#include <Arduino.h>
#include <stdio.h>
#include "LEDController.h"
#include "StateManager.h"

class SerialLogger {
private:
    unsigned long _reportInterval;
    unsigned long _lastReportTime;
    FILE* _serialOutput;
    static int serialPutchar(char c, FILE* stream);
    
public:
    SerialLogger(unsigned long reportInterval = 1000);
    ~SerialLogger();
    void begin(unsigned long baudRate);
    FILE* getOutputStream();
    void reportStatus(const LEDController& led1, const LEDController& led2, const StateManager& stateManager);
    void update(const LEDController& led1, const LEDController& led2, const StateManager& stateManager);
};

#endif