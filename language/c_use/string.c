#include <stdio.h>
/*
 * 字符串操作
 * */

void print_EOF(){
    printf("%d",EOF);
}

void print_input(){
    int c;
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}

void char_count(){
    long nc;
    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);
}