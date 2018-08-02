#include <stdlib.h>
#include <stdio.h>

/*
 * ChainQueue 链表队列(双向链表)
 *
 * */

#define QUEUE_MAX_SIZE 101

// 节点
typedef struct Node {
    int key;  //
    struct Node * next;
    struct Node * preview;
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
    Node *node; // 指向队首
} Queue;

Queue *newQueue(){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->node=NULL;
    return queue;
}

//
int isEmpty(Queue *queue){
    if(queue->node==NULL){
        return 1;
    }
    return 0;
}

void put(Queue *queue,Node *node){
    if(queue->node==NULL){
        queue->node = node;
        node->next = node;
        node->preview = node;
    }
    node->next = queue->node;
    node->preview = queue->node->preview;
    node->preview->next = node;
    queue->node->preview = node;
    queue->node = node;
}

Node *pop(Queue *queue){
    if(isEmpty(queue)){
        fprintf(stderr,"Stack Empty !");
        exit(-1);
    }
    Node *tmp = queue->node->preview;
    tmp->preview->next = tmp->next;
    queue->node->preview = tmp->preview;
    return tmp;
}

void printQueue(Queue *queue){
    printf("\nQueue:\n");
    Node *tmp = queue->node;
    do{
        printNode(tmp);
        tmp = tmp->next;
    }while (tmp!=queue->node);
}

int main(){
    Queue *queue = newQueue();
    put(queue,newNode(123));
    printQueue(queue);
    put(queue,newNode(456));
    printQueue(queue);
    put(queue,newNode(789));
    printQueue(queue);
    printf("\n");
    printNode(pop(queue));
    printQueue(queue);
}
