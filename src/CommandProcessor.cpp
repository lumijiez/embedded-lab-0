#include "CommandProcessor.h"
#include <stdio.h>
#include <string.h>

CommandProcessor::CommandProcessor(LEDController& ledCtrl) : ledController(ledCtrl) {}

void CommandProcessor::processInput() {
    char command[MAX_COMMAND_LENGTH];
    
    if (scanf("%9s", command) == 1) {
        if (strcmp(command, "led") == 0) {
            scanf("%9s", command);
            processLEDCommand(command);
        } else {
            printInvalidCommand();
        }
    }
}

void CommandProcessor::processLEDCommand(char* command) {
    if (strcmp(command, "on") == 0) {
        ledController.turnOn();
        printf("LED turned ON\n");
    } else if (strcmp(command, "off") == 0) {
        ledController.turnOff();
        printf("LED turned OFF\n");
    } else {
        printf("Unknown command\n");
    }
}

void CommandProcessor::printInvalidCommand() const {
    printf("Invalid command format. Use 'led on' or 'led off'.\n");
}