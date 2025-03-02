#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <Arduino.h>
#include "LEDController.h"

class CommandProcessor {
public:
    CommandProcessor(LEDController& ledCtrl);
    void processInput();

private:
    LEDController& ledController;
    static const int MAX_COMMAND_LENGTH = 10;
    void processLEDCommand(char* command);
    void printInvalidCommand() const;
};

#endif