#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

// Структура строки навигационного сообщения
typedef struct {
    uint16_t left;  // старшие информационные 13 бит (остальное не исп.)
    uint64_t right; // младшие информационные 64 бита
    uint8_t HC;     // 8 бит кода Хэмминга
} String;

// Битовые маски для вычисления кода Хэмминга
#define BIT_7_LEFT  0x1B56
#define BIT_7_RIGHT 0xAAAD5555555AAAAA
#define BIT_6_LEFT  0x16CD
#define BIT_6_RIGHT 0x999B333333366666
#define BIT_5_LEFT  0x0E3C
#define BIT_5_RIGHT 0x7878F0F0F0F1E1E1
#define BIT_4_LEFT  0x01FC
#define BIT_4_RIGHT 0x07F80FF00FF01FE0
#define BIT_3_LEFT  0x0003
#define BIT_3_RIGHT 0xFFF8000FFFF0001F
#define BIT_2_LEFT  0x0000
#define BIT_2_RIGHT 0x0007FFFFFFF00000
#define BIT_1_LEFT  0x0000
#define BIT_1_RIGHT 0x00000000000FFFFF


// Вывод строки навигационного сообщения в бинарном виде
void printString(String mess);
// Вывод строки навигационного сообщения в шестнадцатеричном виде
void printStringHEX(String mess);
// Вычисление кода Хэмминга
uint8_t HammingCode(String mess);
// Подсчет количества единиц в числе
uint8_t countOnes(uint64_t number);

#endif
