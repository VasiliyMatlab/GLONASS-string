#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "internal.h"

// Обнаружение и исправление одной ошибки
void one_error(String orig_message);
// Обнаружение 2-х или 4-х ошибок
void more_errors(String orig_message);

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор строки навигационного сообщения ГЛОНАСС\n");
    printf("Неверные биты будут подсвечиваться \033[31mкрасным\033[0m цветом\n");
    String message = {0};
    // Генерация информационной части сообщения
    srand(time(NULL));
    /*message.left  = rand() % 4096;
    message.right = ((uint64_t) rand()) << 33;
    message.right = message.right | (((uint64_t) rand()) << 2);
    message.right = message.right | (rand() % 4);*/
    /* 52 */
    message.left = 0b0000000000011;
    message.right = 0b1000100010110011011100001110100110001000101100110111000011101001;
    // message.left = 0b0011100100011;
    // message.right = 0b1111100000010001110000000100100111111000000100011100000001001001;
    // Вычисление кода Хэмминга
    message.HC = HammingCode(message);
    printf("Сгенерированная строка (последние 8 бит - код Хэмминга): \n");
    printStringHEX(message);
    printString(message);
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
    switch (num_err) {
        case 1:
            one_error(message);
            break;
        case 2:
            more_errors(message);
            break;
        case 4:
            more_errors(message);
            break;
        default:
            fprintf(stderr, "Ошибка: количество ошибок = %d\n", num_err);
            exit(EXIT_FAILURE);
    }
    return 0;
}

// Обнаружение и исправление одной ошибки
void one_error(String orig_message) {
    int error_bit = -1;
    printf("Хотите ввести сами номер бита ошибки? (Да или Нет) ");
    while (1) {
        char buf1[16];
        scanf("%s", buf1);
        // Если пользователь выбирает "Да"
        if (!(strcmp(buf1,"Да")) || !(strcmp(buf1,"да")) || 
            !(strcmp(buf1,"ДА"))) {
            printf("Введите номер искаженного бита (0-76): ");
            while (1) {
                char buf2[16];
                scanf("%s", buf2);
                memset(buf1, 0, 16);
                for (uint8_t i = 0; i < 16; i++)
                    buf1[i] = buf2[i];
                // Если введено число
                if (isNumber(buf2)) {
                    error_bit = atoi(buf1);
                    // Если введено верно, то идем дальше
                    if ((error_bit >= 0) && (error_bit <= 76))
                        goto skip;
                    // Если введено неверно, то вводим еще раз
                    error_bit = -1;
                    printf("Введенное число лежит вне диапазона; "
                        "попробуйте еще раз (0-76): ");
                    continue;
                }
                // Если введено не число
                printf("Неизвестный формат сообщения; "
                    "попробуйте еще раз (0-76): ");
            }
        }
        // Если пользователь выбирает "Нет"
        if (!(strcmp(buf1,"Нет")) || !(strcmp(buf1,"нет")) || 
            !(strcmp(buf1,"НЕТ"))) {
            // Генерируем случайное число и продолжаем
            error_bit = rand() % 77;
            printf("Номер искаженного бита: %d\n", error_bit);
            break;
        }
        // Иначе
        printf("Неизвестный тип сообщения; введите еще раз (Да, Нет): ");
    }
    skip: ;
    String damaged_message = orig_message;
    // Инверсия бита
    if (error_bit > 63)
        damaged_message.left = invertBit(damaged_message.left, error_bit - 64);
    else
        damaged_message.right = invertBit(damaged_message.right, error_bit);
    // Пересчет контрольной суммы
    damaged_message.HC = HammingCode(damaged_message);
    // Вывод на экран правильного сообщения и искаженного
    printf("Исходная и искаженная строки соответственно:\n");
    printString(orig_message);
    printDamagedString(damaged_message, error_bit);
    // Вычисление номера поврежденного бита
    uint8_t diff = 0;
    printf("Вычисление разницы между контрольными суммами:\n ");
    printHammingCode(orig_message.HC);
    printf("\n^\n ");
    printf("\033[4m");
    printHammingCode(damaged_message.HC);
    printf("\033[0m\n ");
    diff = orig_message.HC ^ damaged_message.HC;    // сложение по модулю 2
    printHammingCode(diff);
    printf("\nСделаем реверс бит:\n ");
    diff = reverseNumber(diff);
    printHammingCode(diff);
    printf(" = %u\n", diff);
    // Пересчет номера поврежденного бита
    if (diff < 4)
        diff -= 2;
    else if (diff < 8)
        diff -= 3;
    else if (diff < 16)
        diff -= 4;
    else if (diff < 32)
        diff -= 5;
    else if (diff < 64)
        diff -= 6;
    else
        diff -= 7;
    diff = 77 - diff;
    printf("При пересчете данного числа на номер разряда информационного "
        "сообщения (см. README.md)\nполучаем номер поврежденного бита: "
        "%d\n", diff);
    if (diff != error_bit) {
        //////////////////////////////////////////////!!!!!!! Реализовать лог ошибки
        exit(EXIT_FAILURE);
    }
    printf("Исходный номер поврежденного бита совпал с полученным\n");
    printf("Следовательно, мы можем исправить ошибку\n");
}

// Обнаружение 2-х или 4-х ошибок
void more_errors(String orig_message) {
    return;
}
