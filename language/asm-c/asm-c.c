/*

# 不同CPU、编译器、汇编器、链接器 语法格式略有不同

内联汇编
    windows vs/linux gcc c-asm:
        format:
            __asm__ (
                汇编语句部分
                ：输出部分 (凡是要写进去的参数都写到输出部分)
                ：输入部分 (凡是要读的参数都写到输入部分)
                ：破坏描述部分
            );
            asm(statements);
        e,g:
            #define ZEND_SIGNED_MULTIPLY_LONG(a, b, lval, dval, usedval) do {	\
            	zend_long __tmpvar; 											\
            	__asm__ ("imul %3,%0\n"											\
            		"adc $0,%1" 												\
            			: "=r"(__tmpvar),"=r"(usedval) 							\
            			: "0"(a), "r"(b), "1"(0));								\
            	if (usedval) (dval) = (double) (a) * (double) (b);				\
            	else (lval) = __tmpvar;											\
            } while (0)
    arm keil:
        e.g:
            int myFunction(int i) {
                int r0;
                __asm {
                    ADD r0, i, 1
                    EOR i, r0, i
                }
                return i;
            }

内嵌汇编
    windows/linux c-asm:

    arm keil:
        e.g:
            __asm void myFunction(const char *src, char *dst) {
                loop LDRB  r2, [r0], #1  //R0保存第一个参数
                STRB  r2, [r1], #1  //R1保存第二个参数
                CMP   r2, #0
                BNE   loop
                BLX    lr  //返回指令须要手动加入
            }

外联汇编:

    arm keil:
        info:
            把汇编语言程序与C语言程序链接到一起
            1、  确保汇编语言中的过程被定义为PUBLIC，过程名以下划线开始。例如，在C语言中叫做“sum”到汇编语言中就应该是“_sum”.
            2、  在C语言程序中过程定义为外部类型，例如在例子2中的extern cursor (int,int)。
            3、  用汇编器对汇编语言程序汇编，得到ASM.obj文件。
            4、  用C语言编译器编译C语言程序，得到C.obj文件。
            5、  用链接器将它们链接到一起生成可执行文件： link ASM.obj + C.obj
        e.g:
            C语言部分如下:
                extern cursor (int,int),
                main()
                {
                    cursor(15,12);
                }
            汇编语言部分如下:
                .MODEL  SMALL
                .CODE
                PUBLIC
                _CURSOR PROC
                PUSH  BP
                    MOV  BP,SP
                    MOV  DH,[BP+4]
                    MOV  DL,[BP+6]
                    MOV  AH,02
                    MOV  BH,00
                    INT  10H
                    POP  BP
                    RET
                _CURSOR ENDP


*/