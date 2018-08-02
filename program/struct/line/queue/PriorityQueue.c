#include <stdlib.h>
#include <stdio.h>

/*
 * PriorityQueue 优先级队列
 *
 * ADT PriorityQueue:
 *  Data: n>0个具有优先级标识的元素集合
 *  Operation:
 *      new
 *      empty
 *      pop
 *      push
 *
 * */

// 节点
typedef struct Node {
    int data;  //
    int priority; // 优先级
    struct Node * next;
} Node;

typedef struct PriorityQueue {
    struct Node * tail;     // 优先级 队尾（循环队列）
} PriorityQueue; //

Node *newNode(int value,int priority){
    Node *node = (Node  *)malloc(sizeof(Node));
    if(node==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    node->data=value;
    node->priority=priority;
    node->next=NULL;
    return node;
}

void printNode(Node *node){
    printf("\t(%d,%d)",node->priority,node->data);
}

PriorityQueue *newPriorityQueue(){
    PriorityQueue *priorityQueue = (PriorityQueue  *)malloc(sizeof(PriorityQueue));
    if(priorityQueue==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    priorityQueue->tail=NULL;
    return priorityQueue;
}

//
int empty(PriorityQueue *priorityQueue){
    if(priorityQueue->tail==NULL){
        return 1;
    }
    return 0;
}

void pop(PriorityQueue *priorityQueue,Node *node){
    if(empty(priorityQueue)==1){
        priorityQueue->tail = node;
        node->next = node;
    } else{
        Node *tmp = priorityQueue->tail->next;
        if(tmp->priority < node->priority){
            node->next = tmp;
            priorityQueue->tail->next = node;
        } else{
            while( 1 ){
                if(tmp->next==priorityQueue->tail->next || tmp->next->priority<node->priority){
                    break;
                }
                tmp = tmp->next;
            }
            node->next = tmp->next;
            tmp->next = node;
            if(tmp == priorityQueue->tail){
                priorityQueue->tail = node;
            }
        }
    }
}

Node *push(PriorityQueue *priorityQueue){
    if(empty(priorityQueue)){
        fprintf(stderr,"Queue is Empty !\n");
        exit(-1);
    }
    Node *tmp = priorityQueue->tail->next;
    if(tmp->next==priorityQueue->tail){
        priorityQueue->tail = NULL;
    } else{
        priorityQueue->tail->next = tmp->next;
    }
    return tmp;
}

void printPriorityQueue(PriorityQueue *priorityQueue){
    printf("\nPriorityQueue:");
    if(empty(priorityQueue)==0){
        Node *tmp = priorityQueue->tail->next;
        while (1){
            printNode(tmp);
            tmp = tmp->next;
            if(tmp==priorityQueue->tail->next) break;
        }
    }
}

int main(){
    PriorityQueue *priorityQueue = newPriorityQueue();
    pop(priorityQueue,newNode(123,1));
    printPriorityQueue(priorityQueue);
    pop(priorityQueue,newNode(456,3));
    printPriorityQueue(priorityQueue);
    pop(priorityQueue,newNode(789,2));
    printPriorityQueue(priorityQueue);
    pop(priorityQueue,newNode(100,0));
    printPriorityQueue(priorityQueue);
    //
    push(priorityQueue);
    printPriorityQueue(priorityQueue);
    push(priorityQueue);
    printPriorityQueue(priorityQueue);
    push(priorityQueue);
    printPriorityQueue(priorityQueue);
    push(priorityQueue);
    printPriorityQueue(priorityQueue);
    push(priorityQueue);
    printPriorityQueue(priorityQueue);
}
