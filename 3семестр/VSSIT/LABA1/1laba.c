#include <stdio.h>

void print_bit(void *ptr, size_t size) {
    unsigned char *p = (unsigned char*)ptr;
    
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (p[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    char c = -1;
    short s = 1;
    int i = -23;

    unsigned char uc = 23;
    unsigned short us = 1;
    unsigned int ui = -10;

    float f = -1.0;
    double d = 10.2;

    printf("Целые знаковые числа:\n");
    printf("char: %d\n", c);//1
    print_bit(&c, sizeof(c));
    printf("short: %d\n", s);//2
    print_bit(&s, sizeof(s));
    printf("int: %d\n", i);//4
    print_bit(&i, sizeof(i));
    
    printf("\nЦелые беззнаковые числа:\n");
    printf("unsigned char: %d\n", uc);//1
    print_bit(&uc, sizeof(uc));
    printf("short: %d\n", us);//2
    print_bit(&s, sizeof(us));
    printf("unsigned int: %d\n", ui);
    print_bit(&ui, sizeof(ui));//8

    printf("\nДробные числа с плавающей точкой:\n");
    printf("float: %f\n", f);//4
    print_bit(&f, sizeof(f));
    printf("double: %f\n", d);//8
    print_bit(&d, sizeof(d));

    return 0;
}