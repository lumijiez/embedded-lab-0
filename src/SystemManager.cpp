#include "SystemManager.h"

#define BUTTON_1 12
#define BUTTON_2 11
#define BUTTON_3 10
#define LED_1 9
#define LED_2 8
#define INIT_STATE 5
#define MIN_STATE 1
#define MAX_STATE 20
#define LOG_INTERVAL 1000
#define LOOP_DELAY 10
#define BAUD_RATE 9600 
#define MIN_INTERVAL_LIMIT 100
#define MAX_INTERVAL_LIMIT 5000

SystemManager::SystemManager() :
    _button1(BUTTON_1), 
    _button2(BUTTON_2), 
    _button3(BUTTON_3),  
    _led1(LED_1, true),     
    _led2(LED_2),    
    _stateManager(INIT_STATE, MIN_STATE, MAX_STATE),  
    _logger(LOG_INTERVAL),
    _loopDelay(LOOP_DELAY) {
}

void SystemManager::setup() {
    _logger.begin(BAUD_RATE);
    _stateManager.setIntervalLimits(MIN_INTERVAL_LIMIT, MAX_INTERVAL_LIMIT);
    _led2.setBlinkInterval(_stateManager.getBlinkInterval());
}

void SystemManager::loop() {
    handleButton1();
    handleButtons2And3();
    updateLEDs();
    _logger.update(_led1, _led2, _stateManager);
    
    delay(_loopDelay);
}

void SystemManager::handleButton1() {
    if (_button1.wasPressed()) {
        _led1.toggle();
        _led2.enableBlinking(!_led1.getState());
    }
}

void SystemManager::handleButtons2And3() {
    if (_button2.wasPressed()) {
        _stateManager.increment();
        _led2.setBlinkInterval(_stateManager.getBlinkInterval());
    }
    
    if (_button3.wasPressed()) {
        _stateManager.decrement();
        _led2.setBlinkInterval(_stateManager.getBlinkInterval());
    }
}

void SystemManager::updateLEDs() {
    _led1.update();
    _led2.update();
}