#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>
#include <stdbool.h>

// Структура строки навигационного сообщения
typedef struct {
    uint16_t left;  // старшие информационные 13 бит (остальное не исп.)
    uint64_t right; // младшие информационные 64 бита
    uint8_t HC;     // 8 бит кода Хэмминга
} String;

// Структура битовых ошибок
typedef struct {
    uint8_t count;  // количество ошибок
    uint8_t *mass;  // разряды ошибок
} Errors;

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

// Вывод кода Хэмминга в бинарном виде
void printHammingCode(FILE *stream, uint8_t code);
// Вывод строки навигационного сообщения в бинарном виде
void printString(FILE *stream, String mess);
// Вывод строки навигационного сообщения в шестнадцатеричном виде
void printStringHEX(FILE *stream, String mess);
// Вывод поврежденной строки на экран
void printDamagedString(FILE *stream, String mess, Errors bit_error);
// Вычисление кода Хэмминга
uint8_t HammingCode(String mess);
// Подсчет количества единиц в числе
uint8_t countOnes(uint64_t number);
// Проверка, является ли строка числом
bool isNumber(char *str);
// Инвертирование бита
uint64_t invertBit(uint64_t number, uint8_t bit);
// Реверс бит числа
uint8_t reverseNumber(uint8_t number);
// Проверка, содержится ли число в массиве
bool isin(uint8_t *mass, uint8_t size, uint8_t number);
// Вывод лога ошибки
void printErrorLog(id_t id, String orig_mess, String damaged_mess, Errors bit_error);

#endif
