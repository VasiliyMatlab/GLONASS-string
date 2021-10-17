#include <stdio.h>
#include "internal.h"
#include <unistd.h>
void printString(String mess) {
    for (int8_t i = 13; i >= 0; i--) {
        if ((1 << i) & mess.left)
            printf("1");
        else
            printf("0");
    }
    for (int8_t i = 63; i >= 0; i--) {
        if ((1 << i) & mess.right)
            printf("1");
        else
            printf("0");
    }
    printf(" ");
    for (int8_t i = 7; i >= 0; i--) {
        if ((1 << i) & mess.HC)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}