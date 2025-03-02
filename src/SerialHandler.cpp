#include "SerialHandler.h"

FILE SerialHandler::serialStdio = {0};

SerialHandler::SerialHandler(unsigned long baud) : baudRate(baud) {}

void SerialHandler::begin() {
    Serial.begin(baudRate);
    setupStreams();
    printWelcomeMessage();
}

void SerialHandler::setupStreams() {
    fdev_setup_stream(&serialStdio, serialPutchar, serialGetchar, _FDEV_SETUP_RW);
    stdout = &serialStdio;
    stdin = &serialStdio;
}

int SerialHandler::serialPutchar(char c, FILE* stream) {
    Serial.write(c);
    return c;
}

int SerialHandler::serialGetchar(FILE* stream) {
    while (!Serial.available());
    return Serial.read();
}

void SerialHandler::printWelcomeMessage() const {
    Serial.println("Turned on! 'led off' to turn OFF and 'led on' to turn ON.");
}

int putchar(int c) {
    return fputc(c, stdout);
}

int getchar(void) {
    return fgetc(stdin);
}