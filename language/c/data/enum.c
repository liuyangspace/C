/*
enum 枚举

语法:
    枚举说明符:
        enum 标识符 opt {枚举符表}
        enum 标识符
    枚举符表:
        枚举符
        枚举符表,枚举符
    枚举符:
        标识符
        标识符 = 常量表达式
e.g: enum boolean { NO=0, YES=1 };
枚举值为int型，默认从0开始。可以相同(名字不可相同)

*/

enum boolean { NO, YES };
enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };