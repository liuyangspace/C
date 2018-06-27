/*
字符串类型
1，预定义类型：
    char
    char[]
    char *
    链接符：" "(空格)
    界定符：双引号
2，转义表示：
    常用字符及其转义：
        换行?     NL(LF)  \n
        横向制表符 HT      \t
        纵向制表符 VT      \v
        回退符     BS      \b
        回车符     CR      \r
        换页符     FF      \f
        页铃符     BEL     \a
        反斜杠     \       \\
        问号       ?       \?
        单引号     '       \'
        双引号     "       \"
        八进制     ooo     \ooo
        十六进制   hh      \xhh
4，常用函数：

5，预定义常量：
    EOF (end of file)


#参考:
    #include <string.h>

*/

size_t strlen (const char *);
char *strcpy (char *, const char *);
int strcmp (const char *, const char *);
char *strstr (const char *, const char *);
