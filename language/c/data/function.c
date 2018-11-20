/*
函数:

声明: [返回值类型(默认int)] 函数名([类型名/形式参数],...); // 旧时声明为: [返回值类型(默认int)] 函数名()
定义: [返回值类型(默认int)] 函数名(形式参数,...){ 函数体(语句); }
使用: [变量 =] 函数名(实参...);
类型名语法:
    类型名:
        说明符限定符表 抽象声明符 opt
    抽象声明符:
        指针
        指针opt 直接抽象声明符
    直接抽象声明符:
        (抽象声明符)
        直接抽象声明符opt [ 常量表达式opt ]
        直接抽象声明符opt [ 形式参数类型表opt ]
    e.g:
        int
        int *
        int *[3]
        int (*)[]
        int *()
        int (*[])(void)

# ,... 变长参数列表，基于 <stdarg.h>中的宏定义，在第一版C中禁用(这些表示法起源于 C++)
# C语言对非指针类型传参默认为传值(相对于传地址)
e.g:
    int *comp(void *, ,,,); // 声明函数comp,接受 通用类型指针，返回 int 指针
参考:
    <stdarg.h>
    <setjmp.h>
*/

// 无名可变参数
#define va_list         // 声明变量依次引用各参数
#define va_start(v,l)   // 初始化 va_list 的变量指向第一个无名参数
#define va_arg(v,l)     // 返回一个参数，并后移指针
#define va_end(v)       // 清理 va_list 资源

#define	setjmp(jmp_buf env)         //将状态信息保存到env
void longjmp (jmp_buf, int);        //恢复状态