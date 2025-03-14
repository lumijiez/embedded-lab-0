#include "SerialLogger.h"

int SerialLogger::serialPutchar(char c, FILE* stream) {
    Serial.write(c);
    return 0;
}

SerialLogger::SerialLogger(unsigned long reportInterval) :
    _reportInterval(reportInterval),
    _lastReportTime(0),
    _serialOutput(nullptr) {
}

SerialLogger::~SerialLogger() {
    if (_serialOutput) fclose(_serialOutput);
}

void SerialLogger::begin(unsigned long baudRate) {
    Serial.begin(baudRate);
    
    _serialOutput = fdevopen(serialPutchar, NULL);
    
    printf("System initialized\n");
}

FILE* SerialLogger::getOutputStream() {
    return _serialOutput;
}

void SerialLogger::reportStatus(const LEDController& led1, const LEDController& led2, const StateManager& stateManager) {
    printf("LED1 State: %s | LED2 Active: %s | LED2 State: %s | State Variable: %d | Blink Interval: %lu ms | Blink Count: %lu\n",
           led1.getState() ? "ON" : "OFF",
           led2.isBlinkingEnabled() ? "YES" : "NO",
           led2.getState() ? "ON" : "OFF",
           stateManager.getState(),
           led2.getBlinkInterval(),
           led2.getBlinkCount());
}

void SerialLogger::update(const LEDController& led1, const LEDController& led2, const StateManager& stateManager) {
    unsigned long currentTime = millis();
    
    if (currentTime - _lastReportTime >= _reportInterval) {
        _lastReportTime = currentTime;
        reportStatus(led1, led2, stateManager);
    }
}