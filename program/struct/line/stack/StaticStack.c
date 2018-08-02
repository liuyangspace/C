#include <stdlib.h>
#include <stdio.h>

/*
 * Stack 栈
 *  LIFO
 *  top 栈顶
 *  push 进栈
 *  pop 出栈
 *
 *
 * */

#define STACK_MAX_SIZE 101

// 栈帧
typedef struct {
    int key;  //
} StackFrame; //

StackFrame *newStackFrame(int key){
    StackFrame *stackFrame = (StackFrame  *)malloc(sizeof(StackFrame));
    stackFrame->key=key;
    return stackFrame;
}

void distoryStackFrame(StackFrame *stackFrame){
    free(stackFrame);
}

void printStackFrame(StackFrame *stackFrame){
    printf("StackFrame:%d",stackFrame->key);
}
// 栈
typedef struct {
    int top;
    StackFrame *stackFrames[STACK_MAX_SIZE];
} Stack;

Stack *newStack(){
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top=-1;
    return stack;
}

void distoryStack(Stack *stack){
    free(stack);

}

//
int isEmpty(Stack *stack){
    if(stack->top<=-1){
        return 1;
    }
    return 0;
}

int isFull(Stack *stack){
    if(stack->top>=STACK_MAX_SIZE-2){
        return 1;
    }
    return 0;
}

int lenght(Stack *stack){
    return stack->top+2;
}

void push(Stack *stack,StackFrame *stackFrame){
    if(isFull(stack)){
        fprintf(stderr,"Stack Overflow !");
        exit(-1);
    }
    stack->top++;
    stack->stackFrames[stack->top]=stackFrame;
}

StackFrame *pop(Stack *stack){
    if(isEmpty(stack)){
        fprintf(stderr,"Stack Empty !");
        exit(-1);
    }
    StackFrame *tmp = stack->stackFrames[stack->top];
    stack->stackFrames[stack->top]=NULL;
    stack->top--;
    return tmp;
}

void printStack(Stack *stack){
    int i=stack->top;
    printf("\nStack:\n");
    for(;i>=0;i--){
        printf("\t%d\t",i);
        printStackFrame(stack->stackFrames[i]);
        printf("\n");
    }
}

int main(){
    Stack *stack = newStack();
    push(stack,newStackFrame(123));
    printStack(stack);
    push(stack,newStackFrame(456));
    printStack(stack);
    printStackFrame(pop(stack));
    printStack(stack);
    printStackFrame(pop(stack));
    printStackFrame(pop(stack));
}
