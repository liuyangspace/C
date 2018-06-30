/*
字符串类型
1，预定义类型：
    char
    char[]
    char *
    字符字面值:
        界定符：双引号"
        语法: "..." // 双引号引注的字符
        类型: 字符数组
        存储: static // 静态

    链接符：" "(空格)
    结束符: \0
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
    #include <ctype.h>

*/

size_t strlen (const char *);                       //字符串长度
char *strcpy (char *, const char *);                //复制
char *strncpy (char *, const char *, size_t);
char *strcat (char *s, const char *t);              //链接字符串
char *strncat (char *s, const char *t, size_t);     //链接字符串,将t的前n个字符链接至s末
int strcmp (const char *, const char *);            //比较
int strncmp (const char *, const char *, size_t);
char *strchr (const char *, int);                   //出现位置
char *strrchr (const char *, int)
char *strstr (const char *, const char *);          //判断字符串str2是否是str1的子串
size_t strspn (const char *, const char *);         //前缀
size_t strcspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strerror (int);
char *strtok (char *, const char *);
//
void *memcpy (void *, const void *, size_t);        //字符数组拷贝
void *memmove (void *, const void *, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);
void *memset (void *, int, size_t);
//
int tolower (int);  //
int toupper (int);  //
