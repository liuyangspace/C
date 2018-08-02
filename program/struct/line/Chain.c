#include <stdlib.h>
#include <stdio.h>

/*
 * Chain 链表
 *
 * */

#define NODE_MAX_SIZE 101

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
    printf(" Node:%d -> ",node->key);
}
// 链表
typedef struct {
    Node *node;
} Chain;

Chain *newChain(){
    Chain *chain = (Chain *)malloc(sizeof(Chain));
    chain->node=NULL;
    return chain;
}

//
int isEmpty(Chain *chain){
    if(chain->node==NULL){
        return 1;
    }
    return 0;
}

void put(Chain *chain,Node *node){
    node->next = chain->node;
    chain->node = node;
}

Node *get(Chain *chain){
    if(isEmpty(chain)){
        fprintf(stderr,"Stack Empty !");
        exit(-1);
    }
    Node *tmp = chain->node;
    chain->node = tmp->next;
    return tmp;
}

void printChain(Chain *chain){
    printf("\nChain:\t");
    Node *tmp = chain->node;
    while (tmp){
        printNode(tmp);
        tmp = tmp->next;
    }
}

int main(){
    Chain *chain = newChain();
    put(chain,newNode(123));
    printChain(chain);
    put(chain,newNode(456));
    printChain(chain);
    put(chain,newNode(789));
    printChain(chain);
    printf("\n");
    printNode(get(chain));
    printChain(chain);
}
