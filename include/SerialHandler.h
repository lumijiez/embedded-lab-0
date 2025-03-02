#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>
#include <stdio.h>

class SerialHandler {
public:
    SerialHandler(unsigned long baudRate = 9600);
    void begin();
    void setupStreams();
    static int serialPutchar(char c, FILE* stream);
    static int serialGetchar(FILE* stream);
    void printWelcomeMessage() const;

private:
    unsigned long baudRate;
    static FILE serialStdio;
};

#undef putchar
#undef getchar

int putchar(int c);
int getchar(void);

#endif