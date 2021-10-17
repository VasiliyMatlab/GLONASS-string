#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

typedef struct {
    uint16_t left;
    uint64_t right;
    uint8_t HC;
} String;

void printString(String mess);

#endif