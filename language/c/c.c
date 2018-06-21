/*
C

info:
    http://www.open-std.org
    http://www.open-std.org/JTC1/SC22/WG14/

组成：指令，注释，标识量(常量/变量)，表达式，控制语句，函数
结构：
    1，程序从 main 函数（入口）开始运行
指令：
    #include    引入文件, e.g: #include <headFileName.h>;#include "headFileName.h"
    #define     定义符号常量,宏,结尾无分号, e.g: #define markName replaceValue
注释：
    \/* ... *\/ 多行注释(不能嵌套)，
    // 单行注释
    运算符：
标识量：(常量/变量)
    命名规范：由字母(区分大小写)、下划线、数字组成，首字符为字母或下划线
    常量修饰符：const
    预定义类型：
控制语句：
    while(boolean){handle;}
    for(init;boolean;handle){handle;}
    if(boolean){handle;}[elseif(boolean){handle;}][else{handle;}]
函数：
    声明: 返回值类型 函数名(参数...);
    定义: 返回值类型 函数名(参数...){ 函数体; }
    使用: [变量 =] 函数名(参数...);

*/
#include <stdio.h> /* */

const char * keyword[] = { // 标识符
        // 存储类别:
        "auto","register","extern","static",
        // 数据类型
        "void","unsigned","signed","short","int","long","float","double","char",
        // 结构定义
        "const","struct","union","enum","typedef",
        // 流程控制（顺序，分支，循环，跳转）
        "if","else","switch","case","default", // 分支
        "for","while","do", // 循环
        "goto","continue","break","return", // 跳转/结束
        // 其他
        "sizeof","volatile"
    };

const char * operator[] = { // 运算符
        // 算术
        ""
        // 逻辑
        // 位
    };

const chat * CStandardLibrary[] = {
        ""
    };

void main(){

}