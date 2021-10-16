#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

struct {
    bool       k1;
    uint8_t    k2;
    uint64_t   k3;
    uint32_t   k4;
} Message;

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор первой строки первого кадра навигационного сообщения ГЛОНАСС\n");
    // Генерация случайных чисел
    Message.k1 = 0;
    srand(time(NULL));
    Message.k2 = rand() % 256;
    Message.k3 = ((uint64_t) rand() % 2) << (64 - 1);
    Message.k3 = Message.k3 | (((uint64_t) rand() % 2) << (32 - 1));
    Message.k3 = Message.k3 | ((uint64_t) rand() << 32);
    Message.k3 = Message.k3 | (uint64_t) rand();
    printf("k2 = %d = 0x%X\n", Message.k2, Message.k2);
    printf("k3 = %lu = 0x%lX\n", Message.k3, Message.k3);
    return 0;
}