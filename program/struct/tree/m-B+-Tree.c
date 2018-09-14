#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * m-B+-Tree
 *
 * */

#define TREE_M 3
#define DATA_M 4

// 元素

typedef struct DataGroup {  // 索引 元组
    int key;
    struct Node *node;
} DataGroup;

typedef struct DataArray {  // 数据元组 双向链表
    struct DataArray *previous;
    struct DataArray *next;
    int n;
    int key[DATA_M];        // 数据关键子 有序数组
} DataArray;

typedef struct Node {
    int n;
    struct Node *first;
    struct DataGroup *data[TREE_M];// 正常情况下只能使用TREE_M-1个空间，分配 TREE_M 个空间 便于分裂
    DataArray * dataArray;
} Node;

//typedef union NodeUnion {
//    Node *node;
//    DataArray * dataArray;
//} NodeUnion;

Node *newNode(int n,Node *first){
    Node *node = (Node *)malloc(sizeof(Node));
    node->n = n;
    node->first = first;
    int i;
    for (i = 0; i < TREE_M; ++i) {
        node->data[i]=NULL;
    }
    node->dataArray = NULL;
    return node;
}

DataGroup *newData(int key,Node *node){
    DataGroup *dataGroup = (DataGroup *)malloc(sizeof(DataGroup));
    dataGroup->key = key;
    dataGroup->node = node;
    return dataGroup;
}

DataArray *newDataArray(DataArray *previous,DataArray *next){
    DataArray *dataArray = (DataArray *)malloc(sizeof(DataArray));
    dataArray->previous = previous;
    dataArray->next = next;
    dataArray->n = 0;
    int i;
    for (i = 0; i < DATA_M; ++i) {
        dataArray->key[i]=NULL;
    }
    return dataArray;
}

//
DataArray *dataAddKey(DataArray *data,int key){
    int outKey = key;
    int tmp,i;
    for (i = 0; i < data->n; ++i) {
        if( data->key[i] > key ){
            tmp = data->key[i];
            data->key[i] = outKey;
            outKey = tmp;
        }
    }
    data->key[data->n++] = outKey;
    return data;
}

// 数组 插入 与 移动
void nodeInsertData(    // 按位置插入数据
        Node *node,
        DataGroup *addData, //  插入元素
        int i               //  插入位置
){
    node->n++;
    DataGroup *outData = addData;
    DataGroup *tmp;
    while (i<node->n){ // 后置节点后移
        tmp = node->data[i];
        node->data[i] = outData;
        outData = tmp;
        i++;
    }
}

DataGroup *nodeDeleteData(    // 按位置移除数据
        Node *node,
        int i               //  移除的位置
){
    DataGroup *removeData = node->data[i];
    node->n--;
    while (i<node->n){ // 后置节点后移
        node->data[i] = node->data[i+1];
        i++;
    }
    node->data[node->n] = NULL;
    return removeData;
}

void nodeInsertDataFirst( Node *node, DataGroup *addData){
    nodeInsertData(node,addData,0);
}
void nodeInsertDataLast( Node *node, DataGroup *addData){
    int i = node->n;
    nodeInsertData(node,addData,i);
}
void nodeDeleteDataFirst( Node *node){
    nodeDeleteData(node,0);
}
void nodeDeleteDataLast( Node *node){
    int i = node->n-1;
    nodeDeleteData(node,i);
}
// 添加
// 分裂
DataGroup *splitNode(Node *node){ // 分裂满节点
    // 移除中间节点
    int i;
    int midIndex = (int)ceil(node->n/2.0)-1;
    int maxIndex = node->n-1;
    DataGroup *midData = node->data[midIndex];
    Node *newSplitNode = newNode(0,midData->node);

    node->data[midIndex] = NULL;
    node->n--;
    //
    for (i = midIndex+1; i <= maxIndex; ++i) {
        //
        newSplitNode->data[newSplitNode->n++] = node->data[i];
        //
        node->data[i] = NULL;
        node->n--;
    }
    return newData(midData->key,newSplitNode);
}
DataGroup *splitData(DataArray *dataArray){
    int i;
    int midBack = 1;
    if(dataArray->n%2==0){
        midBack = 0;
    }
    int midIndex = (int)ceil(dataArray->n/2.0)-midBack;
    int maxIndex = dataArray->n-1;
    int midData = dataArray->key[midIndex];
    Node *newSplitNode = newNode(0,NULL);
    DataArray *newSplitDataArray = newDataArray(dataArray,dataArray->next);
    newSplitNode->dataArray = newSplitDataArray;
    dataArray->next = newSplitDataArray;
    for (i = midIndex; i <= maxIndex ; ++i) {
        newSplitDataArray->key[newSplitDataArray->n++] = dataArray->key[i];
        dataArray->key[i] = NULL;
        dataArray->n--;
    }
    DataGroup *newSplitData = newData(midData,NULL);
    newSplitData->node = newSplitNode;
    return newSplitData;
}
DataGroup *addData(Node *parent,Node *node,DataGroup *data){
    if(parent->n==-1 && node==NULL){     // 空树
        parent->first = newNode(0,NULL);
        DataArray *dataArray = newDataArray(NULL,NULL);
        dataAddKey(dataArray,data->key);
        parent->first->dataArray = dataArray;
        return NULL;
    }
    // 查找目标位置
    Node *p = node->first;
    int i;
    for (i = 0; i < node->n; ++i) {
        if(data->key<node->data[i]->key){
            break;
        }
        p = node->data[i]->node;
    }
    // 插入
    if(data->node==NULL && p!=NULL){    // 非叶子节点 与子节点比较
        DataGroup *newSplitData = addData(node,p,data);
        if(newSplitData!=NULL){  // 子节点被分裂
            newSplitData = addData(parent,node,newSplitData); // 新数据加入本节点
            return newSplitData; // 通知父节点是否有新数据
        }
    } else {
        //
        if (node->n == 0) { // 数据节点
            DataArray *dataArray = node->dataArray;
            dataAddKey(dataArray, data->key);
            if (dataArray->n >= DATA_M) {//
                DataGroup *newData = splitData(dataArray);
                if(parent->n == -1){ // 根节点被分裂 高度加一
                    parent->first = newNode(1,parent->first);
                    parent->first->data[0] = newData;
                    return NULL;
                }
                return newData;
            }
        } else{     // 索引节点
            nodeInsertData(node,data,i);
            if(node->n >= TREE_M){ // 有多余节点，分裂
                DataGroup * newSplitData = splitNode(node);
                if(parent->n == -1){ // 根节点被分裂 高度加一
                    parent->first = newNode(1,parent->first);
                    parent->first->data[0] = newSplitData;
                    return NULL;
                }
                return newSplitData; // 通知父节点有新数据
            }
        }
    }
    return NULL;
}

// 删除

int removeData(     // 删除
        Node *parent,   // 当前节点的父节点
        Node *node,     // 当前节点
        int key,        // 目标删除节点的关键字
        Node *removeParent, // 目标删除节点的父节点
        int removeIndex // 目标节点 的位置
){

}

// 横向打印树
void printNode(Node *treeRoot,int h){
    if(treeRoot==NULL){
        printf("\tNULL");
        return;
    }
    if(treeRoot->n==-1){
        printf("\nM-TREE-1:\n");
        printNode(treeRoot->first,h+1);
        return;
    }
    int i,j;
    if(treeRoot->n==0){
        if(treeRoot->dataArray!=NULL){
            DataArray *dataArray = treeRoot->dataArray;
            printf("\tDATA:n:0,dn:%d\t(",treeRoot->dataArray->n);
            for (i = 0; i < dataArray->n; ++i) {
                printf("%d,",dataArray->key[i]);
            }
            printf(")\t");
            //
            printf("[ ");
            if(dataArray->previous==NULL){
                printf("NULL");
            } else{
                printf("(%d,...)",dataArray->previous->key[0]);
            }
            printf(" <= , => ");
            if(dataArray->next==NULL){
                printf("NULL");
            } else{
                printf("(%d,...)",dataArray->next->key[0]);
            }
            printf(" ]");
        } else{
            printf("\tn:0,()");
        }
        return;
    }
    for (i=0;i<treeRoot->n;i++){
        if(i==0){
            printf("\tn:%d,(",treeRoot->n);
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
    printf("- c:0");
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
    if(tree->n==-1){
        return findNode(tree->first,key);
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

    Node *tree = newNode(-1,NULL); // 指向树的节点，不参与排序 等
    addData(tree,tree->first,newData(2,NULL));
    addData(tree,tree->first,newData(4,NULL));
    addData(tree,tree->first,newData(6,NULL));
    addData(tree,tree->first,newData(12,NULL));
    addData(tree,tree->first,newData(16,NULL));
    addData(tree,tree->first,newData(18,NULL));
    addData(tree,tree->first,newData(20,NULL));
    addData(tree,tree->first,newData(25,NULL));
    addData(tree,tree->first,newData(32,NULL));
    addData(tree,tree->first,newData(36,NULL));
    addData(tree,tree->first,newData(40,NULL));
    addData(tree,tree->first,newData(50,NULL));
    addData(tree,tree->first,newData(60,NULL));
    addData(tree,tree->first,newData(71,NULL));
    addData(tree,tree->first,newData(72,NULL));
    addData(tree,tree->first,newData(80,NULL));
    addData(tree,tree->first,newData(82,NULL));
    addData(tree,tree->first,newData(84,NULL));
    addData(tree,tree->first,newData(13,NULL));
    addData(tree,tree->first,newData(14,NULL));
    addData(tree,tree->first,newData(85,NULL));
    addData(tree,tree->first,newData(86,NULL));
    addData(tree,tree->first,newData(87,NULL));
    addData(tree,tree->first,newData(88,NULL));
    addData(tree,tree->first,newData(89,NULL));
    addData(tree,tree->first,newData(90,NULL));
//    addData(tree,tree->first,newData(20,NULL));
//    addData(tree,tree->first,newData(90,NULL));
//    addData(tree,tree->first,newData(70,NULL));
//    addData(tree,tree->first,newData(60,NULL));
//    addData(tree,tree->first,newData(95,NULL));

    //
    printNode(tree,0);
//    //
//    printf("\nfindNode:\n");
//    printNode(findNode(tree,60),1);
//    //
//    removeData(tree,tree->first,70,NULL,-1);
//    removeData(tree,tree->first,10,NULL,-1);
//    removeData(tree,tree->first,60,NULL,-1);
//    removeData(tree,tree->first,95,NULL,-1);
//    removeData(tree,tree->first,90,NULL,-1);
//    removeData(tree,tree->first,20,NULL,-1);
//    printNode(tree,0);
}
