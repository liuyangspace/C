#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * m-Tree
 *
 * */

#define TREE_M 3

// 元素

typedef struct DataGroup {
    int key;
    struct Node *node;
} DataGroup;

typedef struct Node {
    int n;
    struct Node *first;
    struct DataGroup *data[TREE_M];
} Node;

Node *newNode(int n,Node *first){
    Node *node = (Node *)malloc(sizeof(Node));
    node->n = n;
    node->first = first;
    int i;
    for (i = 0; i < TREE_M; ++i) {
        node->data[i]=NULL;
    }
    return node;
}

DataGroup *newData(int key,Node *node){
    DataGroup *dataGroup = (DataGroup *)malloc(sizeof(DataGroup));
    dataGroup->key = key;
    dataGroup->node = node;
    return dataGroup;
}

// 添加
Node *addData(Node *root,int key){
    if(root==NULL){
        root = newNode(0,NULL);
        return addData(root,key);
    }
    // 查找目标位置
    Node *p = root->first;
    int i;
    for (i = 0; i < root->n; ++i) {
        if(key<root->data[i]->key){
            break;
        }
        p = root->data[i]->node;
    }
    // 插入
    if(p!=NULL){    // 与子节点比较
        addData(p,key);
    } else{
        if(root->n>=TREE_M-1){  // 本节点已满，添加子节点
            p = newNode(0,NULL);
            if(i==0){
                root->first = p;
            } else{
                root->data[i-1]->node = p;
            }
            addData(p,key);
        } else{ // 插入
            DataGroup *outData = newData(key,NULL);
            DataGroup *tmp;
            root->n++;
            while (i<root->n){
                tmp = root->data[i];
                root->data[i] = outData;
                outData = tmp;
                i++;
            }
        }
    }
    return root;
}

// 横向打印树
void printNode(Node *treeRoot,int h){
    if(treeRoot==NULL){
        printf("\tNULL");
        return;
    }
    int i,j;
    for (i=0;i<treeRoot->n;i++){
        if(i==0){
            printf("\t(");
        }
        printf("%d,",treeRoot->data[i]->key);
        if(i==treeRoot->n-1){
            printf(")");
        }
    }
    //
    printf("\n");
    for (j = 0; j < h; ++j) {
        printf("\t");
    }
    printf("- c0");
    printNode(treeRoot->first,h+1);
    for (i=0;i<treeRoot->n;i++){
        printf("\n");
        for (j = 0; j < h; ++j) {
            printf("\t");
        }
        printf("- c:%d",i+1);
        printNode(treeRoot->data[i]->node,h+1);
    }
}

// 查找
Node * findNode(Node *tree,int key){
    if(tree==NULL){
        return NULL;
    }
    Node *p = tree->first;
    int i=0;
    for (i = 0; i < tree->n; ++i) {
        if(key==tree->data[i]->key){
            return tree;
        } else if(key<tree->data[i]->key){
            break;
        }
        p = tree->data[i]->node;
    }
    return findNode(p,key);
}

int main(){

    Node *tree = NULL;
    tree = addData(tree,20);
    addData(tree,40);
    addData(tree,10);
    addData(tree,15);
    addData(tree,25);
    addData(tree,30);
    addData(tree,28);
    addData(tree,45);
    addData(tree,50);
    //
    printf("\nM-TREE-1:\n");
    printNode(tree,1);
    //addNode(tree,newNode(1),&balance);
    printf("\nM-TREE-2:\n");
    printNode(findNode(tree,28),1);


}
