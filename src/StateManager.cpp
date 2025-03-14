#include "StateManager.h"

#define MIN_INTERVAL 100
#define MAX_INTERVAL 5000
#define INTERVAL_MULTIPLIER 100UL

StateManager::StateManager(int initialState, int minState, int maxState) :
    _stateVariable(initialState),
    _minState(minState),
    _maxState(maxState),
    _minInterval(MIN_INTERVAL),
    _maxInterval(MAX_INTERVAL) {
}

void StateManager::increment() {
    _stateVariable++;
    if (_stateVariable > _maxState) _stateVariable = _maxState;
}

void StateManager::decrement() {
    _stateVariable--;
    if (_stateVariable < _minState) _stateVariable = _minState;
}

int StateManager::getState() const {
    return _stateVariable;
}

unsigned long StateManager::getBlinkInterval() const {
    unsigned long interval = static_cast<unsigned long>(_stateVariable) * INTERVAL_MULTIPLIER;
    
    if (interval < static_cast<unsigned long>(_minInterval) || _stateVariable < _minState) {
        interval = static_cast<unsigned long>(_minInterval);
    }
    
    if (interval > static_cast<unsigned long>(_maxInterval)) {
        interval = static_cast<unsigned long>(_maxInterval);
    }
    
    return interval;
}

void StateManager::setIntervalLimits(int minInterval, int maxInterval) {
    _minInterval = minInterval;
    _maxInterval = maxInterval;
}