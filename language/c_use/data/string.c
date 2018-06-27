#include <stdio.h>
/*
 * 字符串操作
 * */

//
void print_EOF(){
    printf("%d",EOF);
}

// 镜像输出
void print_input(){
    int c;
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}

// 统计字符串长度
void char_count(){
    long nc;
    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);
}

//  字符串反转
void reverse(){
    int i=0;
    int max=1000;
    int out[max];
    int in;
    while((in = getchar()) != EOF && i<max){
        out[i]=in;
        i++;
    }
    while(i>=0){
        putchar(out[i]);
        i--;
    }
}