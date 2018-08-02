#include <stdlib.h>
#include <stdio.h>

/*
 * ChainStack 链表栈
 *
 * */

#define STACK_MAX_SIZE 101

// 节点
typedef struct Node {
    int key;  //
    struct Node * next;
} Node; //

Node *newNode(int key){
    Node *node = (Node  *)malloc(sizeof(Node));
    node->key=key;
    return node;
}

void printNode(Node *node){
    printf(" Node:%d \n",node->key);
}
// 链表
typedef struct {
    Node *node;
} Stack;

Stack *newStack(){
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->node=NULL;
    return stack;
}

//
int isEmpty(Stack *stack){
    if(stack->node==NULL){
        return 1;
    }
    return 0;
}

void push(Stack *stack,Node *node){
    node->next = stack->node;
    stack->node = node;
}

Node *pop(Stack *stack){
    if(isEmpty(stack)){
        fprintf(stderr,"Stack Empty !");
        exit(-1);
    }
    Node *tmp = stack->node;
    stack->node = tmp->next;
    return tmp;
}

void printStack(Stack *stack){
    printf("\nChain:\n");
    Node *tmp = stack->node;
    while (tmp){
        printNode(tmp);
        tmp = tmp->next;
    }
}

int main(){
    Stack *chain = newStack();
    push(chain,newNode(123));
    printStack(chain);
    push(chain,newNode(456));
    printStack(chain);
    push(chain,newNode(789));
    printStack(chain);
    printf("\n");
    printNode(pop(chain));
    printStack(chain);
}
