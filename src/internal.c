#include <stdio.h>
#include <ctype.h>
#include "internal.h"

// Вывод строки навигационного сообщения в бинарном виде
void printString(String mess) {
    for (int8_t i = 12; i >= 0; i--) {
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

// Вывод строки навигационного сообщения в шестнадцатеричном виде
void printStringHEX(String mess) {
    printf("0x%04X%lX %02X\n", mess.left, mess.right, mess.HC);
}

// Вывод поврежденной строки на экран
void printDamagedString(String mess, int bit) {
    for (int8_t i = 12; i >= 0; i--) {
        if ((1 << i) & mess.left) {
            // Если поврежденный бит
            //printf("i = %d bit = %d\n", i, bit - 64);
            if (i == (bit - 64))
                printf("\033[31m1\033[0m");
            // Иначе
            else
                printf("1");
        }
        else {
            // Если поврежденный бит
            if (i == (bit - 64))
                printf("\033[31m0\033[0m");
            // Иначе
            else
                printf("0");
        }
    }
    for (int8_t i = 63; i >= 0; i--) {
        if ((1 << i) & mess.right) {
            // Если поврежденный бит
            if (i == bit)
                printf("\033[31m1\033[0m");
            // Иначе
            else
                printf("1");
        }
        else {
            // Если поврежденный бит
            if (i == bit)
                printf("\033[31m0\033[0m");
            // Иначе
            else
                printf("0");
        }
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

// Вычисление кода Хэмминга
uint8_t HammingCode(String mess) {
    uint8_t code = 0;
    // Рассчет 7-го бита
    uint8_t ones_left  = countOnes(mess.left  & BIT_7_LEFT);
    uint8_t ones_right = countOnes(mess.right & BIT_7_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 7;
    // Рассчет 6-го бита
    ones_left  = countOnes(mess.left  & BIT_6_LEFT);
    ones_right = countOnes(mess.right & BIT_6_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 6;
    // Рассчет 5-го бита
    ones_left  = countOnes(mess.left  & BIT_5_LEFT);
    ones_right = countOnes(mess.right & BIT_5_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 5;
    // Рассчет 4-го бита
    ones_left  = countOnes(mess.left  & BIT_4_LEFT);
    ones_right = countOnes(mess.right & BIT_4_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 4;
    // Рассчет 3-го бита
    ones_left  = countOnes(mess.left  & BIT_3_LEFT);
    ones_right = countOnes(mess.right & BIT_3_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 3;
    // Рассчет 2-го бита
    ones_left  = countOnes(mess.left  & BIT_2_LEFT);
    ones_right = countOnes(mess.right & BIT_2_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 2;
    // Рассчет 1-го бита
    ones_left  = countOnes(mess.left  & BIT_1_LEFT);
    ones_right = countOnes(mess.right & BIT_1_RIGHT);
    code |= ((ones_left+ones_right) % 2 ? 1 : 0) << 1;
    // Нулевой бит всегда равен 0
    return code;
}

// Подсчет количества единиц в числе
uint8_t countOnes(uint64_t number) {
    uint8_t count = 0;
    while (number) {
        count++;
        number &= (number - 1);
    }
    return count;
}

// Проверка, является ли строка числом
bool isNumber(char *str) {
    while (*str)
        if (!isdigit(*str++))
            return false;
    return true;
}

// Инвертирование бита
uint64_t invertBit(uint64_t number, uint8_t bit) {
    uint64_t mask = 1 << bit;
    return (number & mask) ? (number & ~mask) : (number | mask);
}
