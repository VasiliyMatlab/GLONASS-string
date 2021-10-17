#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "internal.h"

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор первой строки первого кадра навигационного сообщения ГЛОНАСС\n");
    String message = {0};
    // Генерация случайных чисел
    srand(time(NULL));
    message.left  = rand() % 8192;
    message.right = ((uint64_t) rand()) << 33;
    message.right = message.right | (((uint64_t) rand()) << 2);
    message.right = message.right | (rand() % 4);
    printString(message);
    return 0;
}