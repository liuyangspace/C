/*
C

info:
    http://www.open-std.org
    http://www.open-std.org/JTC1/SC22/WG14/
分类：
    C99
    C11
    ANSI C
组成：
    形式(6种记号):标识符，关键字，常量，字符串字面值，运算符，分隔符。
    功能:指令(宏定义)，注释，标识量(常量/变量)，表达式，控制语句，函数(子程序或程序段/块)
结构：
    1，程序入口函数: int main(int argc, char *argv[]){}
*标识声明:
    one of : 候选项之一
    opt    : 可选的
指令：（预处理）
    三字符序列: 处理宏定义中的非ASCII字符(转义)
        ??=  #            ??(  [            ??<  {
        ??/  \            ??)  ]            ??>  }
        ??'  ^            ??!  |            ??-  ~
    行连接符: \
    分割符: 换行符
    分类:
        宏定义:
            #define 标识符(标识符表opt) 记号序列
                宏定义(替换)，定义符号常量,宏,结尾无分号, e.g:
                #define markName replaceValue
                #define  forever  for (;;)
                #define  max(A, B)  ((A) > (B) ? (A) : (B))
                #define  dprint(expr)   printf(#expr " = %g\n", expr)   // 参数名以#为前缀，实参将被加双引号
                #define  paste(front, back)  front ## back              // ##参数链接，实参转为 frontback
            #undef 标识符
                取消名字的宏定义，e.g:
                #undef getchar
        文件包含
            #include 记号序列
                引入头文件(文件包含), e.g:
                #include <headFileName.h>   // <>尖括号表示由预处理器在指定位置查找
                #include "headFileName.h"
                #include HDR                // #define HDR "msdos.h"
        条件包含：
            #if 常量整形表达式(可以使用表达式define()，不能包含sizeof,enum)
            #ifdef 标识符
            #ifndef 标识符
            #elif 常量整形表达式
            #else
            #endif
        预处理器控制指令:
            #line 常量 "文件名"opt
                行控制:告知编译器，下一行源代码的行号以十进制整形常量形式给出，且当前的输入文件是由该标识符命名的。
            #error 记号序列opt
                错误信息生成:告知预处理器打印包含该记号序列的诊断信息。
            #pragma 记号序列opt
                pragma:将使编译器执行一个与具体实现相关的操作(部分编译器不识别)。
            #
                空指令:无操作
        预定义名称:
            以下标识符是预定义的，不能取消或重新定义:
            __LINE__    // 当前源文件的行数，十进制常量
            __FILE__    // 正在被编译的源文件的名字，字符串字面值
            __DATE__    // 编译日期，字符串字面值，形式 "Mmm dd yyyy"
            __TIME__    // 编译时间，字符串字面值，形式 "hh:mm:ss"
            __STDC__    // 整形常量1
注释：
    \/* ... *\/ 多行注释(不能嵌套)，
    // 单行注释
标识量：(常量/变量)
    声明: 说明标识符含义，不分配存储空间,语法如下
        声明:
            声明说明符 初始化声明符表 opt
        声明说明符:
            存储类说明符 声明说明符 opt   //
            类型说明符 声明说明符 opt     //
            类型限定符 声明说明符 opt     // 类型限定符: const volatile
        初始化声明符表:
            初始化声明符
            初始化声明符表,初始化声明符
        初始化声明符:
            声明符
            声明符 = 初值
        存储类说明符: auto register static extern typedef
        类型说明符: void unsigned signed short int long float double char 结构或联合说明符 枚举说明符 类型定义名
        类型限定符: const volatile
        结构或联合说明符:
            结构或联合标识符 opt {结构声明表}
            结构或联合 标识符
        声明符:
            指针 opt 直接声明符
        直接声明符:
            标识符
            (声明符)
            直接声明符 [常量表达式 opt]
            直接声明符(形式参数类型表)
            直接声明符(标识符 opt)
        指针:
            * 类型限定符表 opt
            * 类型限定符表 opt 指针
        类型限定符表:
            类型限定符
            类型限定符表 类型限定符
    命名规范：由字母(区分大小写)、下划线、数字组成，首字符为字母或下划线
    常量修饰符：const
    初值: 于运算符=后，语法如下:
        初值:
            赋值表达式
            字符串字面值  // 主要用于 字符数组初始化
            {初值表}
            {初值表,}
        初值表:
            初值
            初值表,初值
表达式:
    左值: 对象是一个命名的存储区域，左值(lvalue)是引用某个对象的表达式。
    初等表达式:
        表示符
        常量
        字符串
        (表达式)
    后缀表达式:
        初等表达式
        后缀表达式[表达式]
        后缀表达式(参数表达式表 opt)
        后缀表达式.标识符
        后缀表达式->标识符
        后缀表达式++
        后缀表达式--
    参数表达式:
        赋值表达式
        参数表达式，赋值表达式
    一元表达式:
        后缀表达式
        ++一元表达式
        --一元表达式
        一元运算符 强制类型转换表达式
        sizeof 一元表达式
        sizeof(类型名)
    一元运算符: one of
        & * + - ~ !
    强制类型转换表达式:
        一元表达式
        (类型名)强制类型转换表达式
    乘法表达式(* / %)
    加法表达式(+ -)
    移位表达式(<< >>)
    关系表达式(< > <= >=)
    相等类表达式(== !=)
    位与逻辑(& ^ | && ||)
    条件表达式:
        逻辑或表达式
        逻辑或表达式?表达式:条件表达式
    赋值表达式(= *= /= %= += -= == <<= >>= &= ^= !=)
    逗号(限于圆括号内, e.g: f(a, (t=3, t+2), c))
    #常见表达式:
        数组引用
        函数使用
控制语句：
    循环语句:
        while(boolean){handle;}
        do{handle;}while(boolean)
        for(init;boolean;handle){handle;}
    分支语句:
        if(boolean){handle;}[elseif(boolean){handle;}][else{handle;}]
        switch(mark){case value: handle;break;[case value2: handle2;break;][default:handleN;]}
    表号语句:
        标识符:语句
        case 常量表达式:语句
        default:语句
        # 表号语句可用于 goto 跳转
    跳转语句:
        goto 标识符;
        continue;
        break;
        return 表达式opt;
函数：
    声明: [返回值类型] 函数名(参数,...);    //
    定义: [返回值类型] 函数名(参数,...){ 函数体; }
    运算: [变量 =] 函数名(参数...);

*/
#include <stdio.h> /* */

const char *keyword[] = { // 标识符
        // 存储类别:
        "auto",     // 自动分配存储(运行堆)
        "register", // 寄存器变量(变量存于寄存器内，编辑器可能忽略)
        "extern",   // 外部声明引用，使用外部 声明
        "static",   // 静态修饰，载入时分配空间(静态栈)，仅本文件内可访问
        // 数据类型
        "void","unsigned","signed","short","int","long","float","double","char", //
        // 结构定义
        "const",    // 常量
        "struct",   // 结构
        "union",    // 联合
        "enum",     // 枚举
        "typedef",  // 为类型取一个新的名字(别名)
        // 流程控制（顺序，分支，循环，跳转）
        "if","else","switch","case","default", // 分支
        "for","while","do", // 循环
        "goto","continue","break","return", // 跳转/结束
        // 其他
        "sizeof",   // 取字节数
        "volatile"  // 屏蔽编译器优化
        // 已废弃关键字: entry
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
        "assert.h",
        "errno.h",
        "stdio.h",
        "stdlib.h",
        "stddef.h",
        "stdarg.h",
        "setjmp.h",
        "string.h",
        "signal.h",
        "limits.h",
        "locale.h",
        "ctype.h",
        "math.h",
        "time.h",
        "float.h",
        "ctype.h"
    };

int main(int argc, char *argv[]){

}