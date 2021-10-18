#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "internal.h"

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор строки навигационного сообщения ГЛОНАСС\n");
    String orig_message = {0};
    // Генерация информационной части сообщения
    srand(time(NULL));
    orig_message.left  = rand() % 4096;
    orig_message.right = ((uint64_t) rand()) << 33;
    orig_message.right = orig_message.right | (((uint64_t) rand()) << 2);
    orig_message.right = orig_message.right | (rand() % 4);
    // Вычисление кода Хэмминга
    orig_message.HC = HammingCode(orig_message);
    printf("Сгенерированная строка (последние 8 бит - код Хэмминга): \n");
    printStringHEX(orig_message);
    printString(orig_message);
    // Выбор количества ошибок
    printf("Введите количество ошибок в строке (1, 2 или 4): ");
    int num_err = 0;
    while (1) {
        char buf[16];
        scanf("%s", buf);
        if (!(strcmp(buf, "1")) || !(strcmp(buf, "2")) || 
            !(strcmp(buf, "4"))) {
            num_err = atoi(buf);
            break;
        }
        printf("Неверное количество ошибок - должно быть 1, 2 или 4\n");
        printf("Введите число еще раз: ");

    }
    return 0;
}
