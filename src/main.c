#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "internal.h"

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор строки первого навигационного сообщения ГЛОНАСС\n");
    String message = {0};
    // Генерация информационной части сообщения
    srand(time(NULL));
    message.left  = rand() % 4096;
    message.right = ((uint64_t) rand()) << 33;
    message.right = message.right | (((uint64_t) rand()) << 2);
    message.right = message.right | (rand() % 4);
    // Вычисление кода Хэмминга
    message.HC = HammingCode(message);
    printf("Сгенерированная строка (последние 8 бит - код Хэмминга): \n");
    printStringHEX(message);
    printString(message);
    return 0;
}
