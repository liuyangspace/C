#include <stdlib.h>
#include <stdio.h>

#define HEAP_MAX_SIZE 100

/*
 * Heap 大根堆（完全二叉树）
 *  适合顺序存储
 *  下滑法
 * V > L > R
 *
 * */

// 节点
typedef struct Node {
    int data;  //
} Node;

Node *newNode(int value){
    Node *node = (Node  *)malloc(sizeof(Node));
    if(node==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    node->data=value;
    return node;
}

void printNode(Node *node){
    printf("\t%d",node->data);
}

// 顺序存储堆
typedef struct Heap {
    int size;
    Node *heap[HEAP_MAX_SIZE];   // 大根堆
} Heap;

Heap *newHeap(){
    Heap *heap = (Heap  *)malloc(sizeof(Heap));
    if(heap==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    heap->size=0;
    return heap;
}

//
int empty(Heap *heap){
    if(heap->size==0){
        return 1;
    }
    return 0;
}

int full(Heap *heap){
    if(heap->size==HEAP_MAX_SIZE){
        return 1;
    }
    return 0;
}

// 把新节点放至位置n+1，从第n+1个位置上滑至合适位置（满足父亲大于孩子）
void push(Heap *heap,Node *node){
    if(full(heap)){
        fprintf(stderr,"Heap is Full!");
        exit(-1);
    }
    heap->size++;
    int i = heap->size;
    while (i!=1 && node->data>heap->heap[i/2]->data){
        heap->heap[i] = heap->heap[i/2];
        i = i/2;
    }
    heap->heap[i] = node;
}

// 删除根，第n个元素 从根下滑至合适位置（满足父亲大于孩子）
Heap *pop(Heap *heap){
    if(empty(heap)){
        fprintf(stderr,"Heap is Empty!");
        exit(-1);
    }
    int i = 1;
    Node *tmp = heap->heap[heap->size];
    heap->size--;
    heap->heap[1]=tmp;
    int parent = 1;
    int child = 2;
    while (child<=heap->size){
        if(child<heap->size && heap->heap[child]->data<heap->heap[child+1]->data){
            child = child+1;
        }
        if(tmp->data > heap->heap[child]->data){
            break;
        }
        heap->heap[parent] = heap->heap[child];
        parent = child;
        child = child*2;
    }
    heap->heap[parent] = tmp;
    return  heap;
}

void printHeap(Heap *heap){
    printf("\nHeap:");
    int i=1;
    for (i=1;i<=heap->size;i++){
        printNode(heap->heap[i]);
        printf(",%d",i);
    }
}

int main(){
    Heap *heap = newHeap();
    push(heap,newNode(2));
    printHeap(heap);
    push(heap,newNode(3));
    push(heap,newNode(4));
    push(heap,newNode(7));
    push(heap,newNode(9));
    push(heap,newNode(8));
    printHeap(heap);
    pop(heap);
    printHeap(heap);
}
