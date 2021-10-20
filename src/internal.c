// Содержание:
//      Заголовочные файлы
//      Прототипы локальных функций
//      Глобальные функции
//      Локальные функции

//----------------------------Заголовочные файлы-------------------------------
// Заголовочные файлы из стандартной библиотеки C
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Пользовательские заголовочные файлы
#include "internal.h"

//-------------------------Прототипы локальных функций-------------------------
// Вывод строки навигационного сообщения в шестнадцатеричном виде
static void printStringHEX(FILE *stream, String mess);

//----------------------------Глобальные функции-------------------------------
// Вывод кода Хэмминга в бинарном виде
void printHammingCode(FILE *stream, uint8_t code) {
    for (int8_t i = 7; i >= 0; i--) {
        if ((1 << i) & code)
            fprintf(stream, "1");
        else
            fprintf(stream, "0");
    }
}

// Вывод строки навигационного сообщения в бинарном виде
void printString(FILE *stream, String mess) {
    // Вывод старших 13-ти бит
    for (int8_t i = 12; i >= 0; i--) {
        // Если разряд равен единице
        if ((1 << i) & mess.left)
            fprintf(stream, "1");
        // Иначе разряд равен нулю
        else
            fprintf(stream, "0");
    }
    // Вывод младших 64-х бит
    for (int8_t i = 63; i >= 0; i--) {
        // Если разряд равен единице
        if (((uint64_t) 1 << i) & mess.right)
            fprintf(stream, "1");
        // Иначе разряд равен нулю
        else
            fprintf(stream, "0");
    }
    // Вывод контрольной суммы
    fprintf(stream, " ");
    printHammingCode(stream, mess.HC);
    fprintf(stream, "\n");
}

// Вывод поврежденной строки на экран
void printDamagedString(FILE *stream, String mess, Errors bit_error) {
    // Вывод старших 13-ти бит
    for (int8_t i = 12; i >= 0; i--) {
        // Если разряд равен единице
        if ((1 << i) & mess.left) {
            // Если разряд находится в списке ошибочных
            if (isin(bit_error.mass, bit_error.count, i+64))
                fprintf(stream, "\033[31m1\033[0m");
            // Иначе
            else
                fprintf(stream, "1");
        }
        // Иначе разряд равен нулю
        else {
            // Если разряд находится в списке ошибочных
            if (isin(bit_error.mass, bit_error.count, i+64))
                fprintf(stream, "\033[31m0\033[0m");
            // Иначе
            else
                fprintf(stream, "0");
        }
    }
    // Вывод младших 64-х бит
    for (int8_t i = 63; i >= 0; i--) {
        // Если разряд равен единице
        if (((uint64_t) 1 << i) & mess.right) {
            // Если разряд находится в списке ошибочных
            if (isin(bit_error.mass, bit_error.count, i))
                fprintf(stream, "\033[31m1\033[0m");
            // Иначе
            else
                fprintf(stream, "1");
        }
        // Иначе разряд равен нулю
        else {
            // Если разряд находится в списке ошибочных
            if (isin(bit_error.mass, bit_error.count, i))
                fprintf(stream, "\033[31m0\033[0m");
            // Иначе
            else
                fprintf(stream, "0");
        }
    }
    // Вывод контрольной суммы
    fprintf(stream, " ");
    printHammingCode(stream, mess.HC);
    fprintf(stream, "\n");
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
    uint64_t mask = (uint64_t) 1 << bit;
    return (number & mask) ? (number & ~mask) : (number | mask);
}

// Реверс бит числа
uint8_t reverseNumber(uint8_t number) {
    number = ((number & 0xF0) >> 4) | ((number & 0x0F) << 4);
    number = ((number & 0xCC) >> 2) | ((number & 0x33) << 2);
    number = ((number & 0xAA) >> 1) | ((number & 0x55) << 1);
    return number;
}

// Проверка, содержится ли число в массиве
bool isin(uint8_t *mass, uint8_t size, uint8_t number) {
    for (uint8_t i = 0; i < size; i++)
        if (mass[i] == number)
            return true;
    return false;
}

// Вывод лога ошибки
void printErrorLog(id_t id, String orig_mess, String damaged_mess, \
                   Errors bit_error) {
    fprintf(stderr, "Произошла неизвестная ошибка. Обратитесь к автору "
        "данной программы, предоставив ему\nлог ошибки, записанный "
        "в текущей директории под именем 'ErrorLog.txt'\n");
    
    // Вывод в консоль
    fprintf(stderr, "Содержание файла 'ErrorLog.txt':\n"
        "------------------------------------------------------------"
        "--------------------------\n");
    fprintf(stderr, "id = %u\n", id);
    fprintf(stderr, "Исходная строка:\n");
    printStringHEX(stderr, orig_mess);
    printString(stderr, orig_mess);
    fprintf(stderr, "Искаженная строка:\n");
    printStringHEX(stderr, damaged_mess);
    printDamagedString(stderr, damaged_mess, bit_error);
    fprintf(stderr, "Структура ошибок:\n");
    fprintf(stderr, "count = %u\n", bit_error.count);
    fprintf(stderr, "mass  = ");
    for (uint8_t i = 0; i < bit_error.count; i++)
        fprintf(stderr, "%u, ", bit_error.mass[i]);
    fprintf(stderr, "\b\b  \b\b\n\n");

    // Запись в файл
    FILE *file = fopen("ErrorLog.txt", "w");
    if (!file) {
        fprintf(stderr, "Error: Ошибка открытия файла\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "id = %u\n", id);
    fprintf(file, "Исходная строка:\n");
    printStringHEX(file, orig_mess);
    printString(file, orig_mess);
    fprintf(file, "Искаженная строка:\n");
    printStringHEX(file, damaged_mess);
    printDamagedString(file, damaged_mess, bit_error);
    fprintf(file, "Структура ошибок:\n");
    fprintf(file, "count = %u\n", bit_error.count);
    fprintf(file, "mass  = ");
    for (uint8_t i = 0; i < bit_error.count; i++)
        fprintf(file, "%u, ", bit_error.mass[i]);
    fprintf(file, "\b\b  \b\b\n");
    if (fclose(file)) {
        fprintf(stderr, "Error: Ошибка закрытия файла\n");
        exit(EXIT_FAILURE);
    }
}

//----------------------------Локальные функции--------------------------------
// Вывод строки навигационного сообщения в шестнадцатеричном виде
static void printStringHEX(FILE *stream, String mess) {
    fprintf(stream, "0x%04X%lX %02X\n", mess.left, mess.right, mess.HC);
}
