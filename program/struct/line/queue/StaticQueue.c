#include <stdlib.h>
#include <stdio.h>

/*
 * Queue 队列(循环队列)
 *  FIFO
 *  front 队首
 *  rear 队尾
 *  put 进队
 *  pop 出队
 * */

#define QUEUE_MAX_SIZE 101

// 节点
typedef struct {
    int key;  //
} QueueElement; //

QueueElement *newQueueElement(int key){
    QueueElement *queueElement = (QueueElement  *)malloc(sizeof(QueueElement));
    queueElement->key=key;
    return queueElement;
}

void distoryStackFrame(QueueElement *queueElement){
    free(queueElement);
}

void printQueueElement(QueueElement *queueElement){
    printf("QueueElement:%d",queueElement->key);
}
// 队列
typedef struct {
    int front; // 指向队首前一元素
    int rear;  // 指向队尾元素
    QueueElement *queueElement[QUEUE_MAX_SIZE];
} Queue;

Queue *newQueue(){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front=-1;
    queue->rear=-1;
    return queue;
}

void distoryStack(Queue *queue){
    free(queue);
}

//
int isEmpty(Queue *queue){
    if(queue->front==queue->rear){
        return 1;
    }
    return 0;
}

int isFull(Queue *queue){
    if((queue->rear+1)%QUEUE_MAX_SIZE==queue->front || (queue->front==-1&&(queue->rear==QUEUE_MAX_SIZE-1))){
        return 1;
    }
    return 0;
}

int lenght(Queue *queue){
    return (queue->rear+QUEUE_MAX_SIZE-queue->front)%QUEUE_MAX_SIZE;
}

void put(Queue *queue,QueueElement *queueElement){
    if(isFull(queue)){
        fprintf(stderr,"Queue Overflow !");
        exit(-1);
    }
    queue->rear=(queue->rear+1)%QUEUE_MAX_SIZE;
    queue->queueElement[queue->rear]=queueElement;
}

QueueElement *pop(Queue *queue){
    if(isEmpty(queue)){
        fprintf(stderr,"Stack Empty !");
        exit(-1);
    }
    queue->front=(queue->front+1)%QUEUE_MAX_SIZE;
    QueueElement *tmp = queue->queueElement[queue->front];
    queue->queueElement[queue->front]=NULL;
    return tmp;
}

void printQueue(Queue *queue){
    int i=queue->front;
    int last=queue->rear;
    printf("\nQueue:\n");
    for(;i!=last;){
        i=(i+1)%QUEUE_MAX_SIZE;
        printf("\t");
        printQueueElement(queue->queueElement[i]);
    }
}

int main(){
    Queue *queue = newQueue();
    put(queue,newQueueElement(123));
    printQueue(queue);
    put(queue,newQueueElement(456));
    printQueue(queue);
    put(queue,newQueueElement(789));
    printQueue(queue);
    printf("\n");
    printQueueElement(pop(queue));
    printQueue(queue);
    pop(queue);
    printQueue(queue);
    pop(queue);
    printQueue(queue);
    pop(queue);
    printQueue(queue);
}
