#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <Arduino.h>

class StateManager {
private:
    int _stateVariable;
    int _minState;
    int _maxState;
    int _minInterval;
    int _maxInterval;
    
public:
    StateManager(int initialState = 0, int minState = 1, int maxState = 50);
    void increment();
    void decrement();
    int getState() const;
    unsigned long getBlinkInterval() const;
    void setIntervalLimits(int minInterval, int maxInterval);
};

#endif