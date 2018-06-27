/*
pointer

声明指针:
    int *p ;        // 声明指针，指向int类型的地址
    void *p;        // 通用类型指针
    int *p[];       // 指针数组
    int (*p)[];     // 数组指针,指向int数组的指针
指针运算:
    int q; p = &q;  // 取变量地址，指针赋值
    *p = q;         // 取指针值
    #形参中 char a[] 等价于 char *a
    *p++ = val;     //进栈，指针自增运算
    val = *--p;     //出栈，指针自减运算
    int *p.*q;p-q;  // 指针间可以进行减法，不能进行加法
数组指针:
    int a[];
    int *p=a;   // 指向int数组的指针
函数指针:
    int add(int a, int b);
    int (*p)(int a, int b); // 声明
    p=add; // 初始化，函数指针, 指向函数 add()
    p(1,2); // 使用
    (*p)(1,2); // 使用
*/