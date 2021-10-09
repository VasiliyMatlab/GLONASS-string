#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Генератор первой строки первого кадра навигационного сообщения ГЛОНАСС\n");
    return 0;
}