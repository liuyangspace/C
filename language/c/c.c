/*
C

info:
    http://www.open-std.org
    http://www.open-std.org/JTC1/SC22/WG14/
分类：
    C99
    C11
    ANSI C
组成：指令，注释，标识量(常量/变量)，表达式，控制语句，函数
结构：
    1，程序入口函数: int main(int argc, char *argv[]){}
指令：（预处理）
    #include    引入头文件(文件包含), e.g:
                    #include <headFileName.h>
                    #include "headFileName.h"
                    #include HDR                // #define HDR "msdos.h"
    #define     宏定义(替换)，定义符号常量,宏,多行用反斜杠链接"\",结尾无分号, e.g:
                    #define markName replaceValue
                    #define  forever  for (;;)
                    #define  max(A, B)  ((A) > (B) ? (A) : (B))
                    #define  dprint(expr)   printf(#expr " = %g\n", expr)   // 参数名以#为前缀，实参将被加双引号
                    #define  paste(front, back)  front ## back              // ##参数链接，实参转为 frontback
    #undef      取消名字的宏定义，e.g:
                    #undef getchar
                    int getchar(void) { ... }
    条件包含：
    #if 常量整形表达式(可以使用表达式define()，不能包含sizeof,enum)
    #ifdef
    #ifndef
    #elif
    #else
    #endif
注释：
    \/* ... *\/ 多行注释(不能嵌套)，
    // 单行注释
    运算符：
标识量：(常量/变量)
    命名规范：由字母(区分大小写)、下划线、数字组成，首字符为字母或下划线
    常量修饰符：const
    预定义类型：
    作用域：
        extern
        static
        {}
控制语句：
    while(boolean){handle;}
    for(init;boolean;handle){handle;}
    if(boolean){handle;}[elseif(boolean){handle;}][else{handle;}]
函数：
    声明: [返回值类型] 函数名(参数...);
    定义: [返回值类型] 函数名(参数...){ 函数体; }
    使用: [变量 =] 函数名(参数...);

*/
#include <stdio.h> /* */

const char *keyword[] = { // 标识符
        // 存储类别:
        "auto",
        "register", // 寄存器变量(变量存于寄存器内，编辑器可能忽略)
        "extern",   // 外部声明引用，使用外部 声明
        "static",   // 静态修饰，载入时分配空间，仅本文件内可访问
        // 数据类型
        "void","unsigned","signed","short","int","long","float","double","char", //
        // 结构定义
        "const",
        "struct",
        "union",
        "enum",
        "typedef",  // 为类型取一个新的名字(别名)
        // 流程控制（顺序，分支，循环，跳转）
        "if","else","switch","case","default", // 分支
        "for","while","do", // 循环
        "goto","continue","break","return", // 跳转/结束
        // 其他
        "sizeof","volatile"
    };

const char *operator[] = { // 运算符 &
        // 算术
        "+","/","%",
        "-",    // 取负，减
        "*",    // 指针，乘
        "++","--",
        "?:",
        //
        "=","+=","-=","*=","/=","%=","&=","^=","|=","<<=",">>=", //
        // 关系运算
        ">",">=","<","<=","==","!=",
        // 逻辑
        "&&","||",
        // 位
        "&",    // 取地址，按位与
        "|","^","<<",">>",
        "~",    // 取反
        // 位移
        //
        "()","[]","->",".",
        //
        "(type)","sizeof"

    };

const chat *CStandardLibrary[] = {
        "stdio.h",
        "stdlib.h",
        "stddef.h",
        "limits.h",
        "ctype.h",
        "math.h",
        "string.h",
        "float.h",
        "ctype.h"
    };

void main(){

}