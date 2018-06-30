/*

预定义 类型名

    typedef 类型名 别名; // 类型别名
参考：
    <stddef.h>
    <ctype.h>
    <stdlib.h>
    <limits.h>
    <float.h>
*/

typedef __SIZE_TYPE__ size_t; // sizeof 返回的无符号整形
// 字符类型检测
int isalnum(int);   // isalpha() 或 isdigit()
int isalpha(int);   // isupper() 或 islower()
int iscntrl(int);   // 控制字符
int isdigit(int);   // 十进制数字
int isgraph(int);   // 除空格外的可打印字符
int islower(int);   // 小写字母
int isleadbyte (int);   //
int isprint(int);   // 包括空格的可打印字符
int ispunct(int);   // 除空格、字母、数字外的可打印字符
int isspace(int);   // 空格、换页、换行、回车、横向制表符、纵向制表符
int isupper(int);   // 大写字母
int isxdigit(int);  // 十六进制数字
int isblank (int);
// 类型转换
int atoi (const char *);
long atol (const char *);
double atof (const char *); //
double strtod (const char *, char **);
long strtol (const char *, char **, int);
unsigned long strtoul (const char *, char **, int);
//
// char
#define CHAR_BIT	8
#define MB_LEN_MAX	2
#define CHAR_MIN	0
#define CHAR_MAX	UCHAR_MAX
// signed char
#define SCHAR_MIN	(-128)
#define SCHAR_MAX	127
// unsigned char
#define UCHAR_MAX	255
// int
#define INT_MAX		2147483647
#define INT_MIN		(-INT_MAX-1)
#define UINT_MAX	0xFFFFFFFF  // unsigend int
// long
#define LONG_MAX	2147483647L
#define LONG_MIN	(-LONG_MAX-1)
#define ULONG_MAX	0xFFFFFFFFUL // unsigend long
// short
#define SHRT_MAX	32767
#define SHRT_MIN	(-SHRT_MAX-1)
#define USHRT_MAX	0xFFFF  // unsigend short
//
#define LLONG_MAX	9223372036854775807LL
#define LLONG_MIN	(-LLONG_MAX - 1)
#define ULLONG_MAX	(2ULL * LLONG_MAX + 1)