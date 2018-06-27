#include <stdio.h>
/*
 * extern 声明 外部变量使用
 * 打印最长子句
 * */
#define MAXLINE 1000   /* maximum input line length */

int getLine(void);
void copy(void);

char line[1000];
char longest[1000];
int max = 0;

/* print longest input line; specialized version */
main()   {
    int len;
    extern int max;
    extern char longest[];
    max = 0;
    while ((len = getLine()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0)
        /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline:  specialized version */
int getLine(void)   {
    int c, i;
    extern char line[];
    for (i = 0; i < MAXLINE - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}
/* copy: specialized version */
void copy(void)   {
    int i;
    extern char line[], longest[];
    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
