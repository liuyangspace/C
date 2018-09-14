#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * m-B-Tree
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
    struct DataGroup *data[TREE_M];// 正常情况下只能使用TREE_M-1个空间，分配 TREE_M 个空间 便于分裂
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
DataGroup *addData(Node *parent,Node *node,DataGroup *data){
    if(parent->n==-1 && node==NULL){     // 空树
        parent->first = newNode(1,NULL);
        parent->first->data[0] = data;
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
    } else{
        // 插入
        nodeInsertData(node,data,i);
        if(node->n>=TREE_M){ // 有多余节点，分裂
            DataGroup * newSplitData = splitNode(node);
            if(parent->n==-1){ // 根节点被分裂 高度加一
                parent->first = newNode(1,parent->first);
                parent->first->data[0] = newSplitData;
                return NULL;
            }
            return newSplitData; // 通知父节点有新数据
        }
    }
    return NULL;
}

// 删除

int rotation(   // 旋转节点
        Node *parent,   // 父节点
        int i,          // 需要调度节点 在 父节点的位置
        Node *p         // 需要调度节点
){
// 左右孩子调度
    Node *brotherNode = NULL;
    // 左孩子 查找是否可调度
    if(i == 0 ){
        if(parent->first->n+1 > ceil(TREE_M/2.0)){
            brotherNode = parent->first;
        }
    } else if( i > 0 ){
        if(parent->data[i-1]->node->n+1 > ceil(TREE_M/2.0)){
            brotherNode = parent->data[i-1]->node;
        }
    }
    // 从 左孩子 调度
    if(brotherNode != NULL){
        DataGroup *moveData = newData(parent->data[i]->key,p->first);
        p->first = brotherNode->data[brotherNode->n-1]->node;
        parent->data[i]->key = brotherNode->data[brotherNode->n-1]->key;
        nodeDeleteDataLast(brotherNode);
        nodeInsertDataFirst(p,moveData);
        return 0;   // 调度成功
    } else {// 右孩子 查找是否可调度
        if(i == -1){
            if(parent->data[0]->node->n+1 > ceil(TREE_M/2.0)){
                brotherNode = parent->data[0]->node;
            }
        }else if(i < parent->n-1){
            if(parent->data[i+1]->node->n+1 > ceil(TREE_M/2.0)){
                brotherNode = parent->data[i+1]->node;
            }
        }
        // 从 右孩子 调度
        if(brotherNode != NULL){
            DataGroup *moveData = newData(parent->data[i+1]->key,brotherNode->first);
            brotherNode->first = brotherNode->data[0]->node;
            parent->data[i+1]->key = brotherNode->data[0]->key;
            nodeDeleteDataFirst(brotherNode);
            nodeInsertDataLast(p,moveData);
            return 0;   // 调度成功
        }
    }
    return 1;   // 调度失败
}
void join(Node *parent,int i){ // 合并节点
    Node *leftChild,*rightChild;
    if(i==-1){
        i = 0;
    }
    if(i<=0){
        leftChild = parent->first;
    } else{
        leftChild = parent->data[i-1]->node;
    }
    rightChild = parent->data[i]->node;
    nodeInsertDataLast(leftChild,newData(parent->data[i]->key,rightChild->first));
    int j;
    for (j = 0; j < rightChild->n; ++j) {
        nodeInsertDataLast(leftChild,rightChild->data[j]);
    }
    nodeDeleteData(parent,i);
}
int removeData(     // 删除
        Node *parent,   // 当前节点的父节点
        Node *node,     // 当前节点
        int key,        // 目标删除节点的关键字
        Node *removeParent, // 目标删除节点的父节点
        int removeIndex // 目标节点 的位置
){
    if(node==NULL){
        if(removeParent==NULL){
            return 0;
        }
        return 1;   // 通知父节点需要被删除
    }
    int result,i;
    Node *p;
    int pi; // 记录p位置
    if(removeParent==NULL){
        p = node->first;
        pi = -1;
        for (i = 0; i < node->n; ++i) {
            if(key==node->data[i]->key){
                removeParent = node;
                removeIndex = i;
                break;
            } else if(key<node->data[i]->key){
                break;
            }
            p = node->data[i]->node; // 于孩子内 查找
            pi = i;
        }
    } else{ // 找到目标节点 寻找其左孩子的最大节点 (以替代)
        i = node->n-1;
        pi = i;
        p = node->data[i]->node;
    }
    result = removeData(node,p,key,removeParent,removeIndex);
    if(result == 1 && removeParent!=NULL){ // 找到 替代节点
        removeParent->data[removeIndex]->key = node->data[i]->key;
        node->data[i] = NULL;
        for (i = i+1; i < node->n ; ++i) {
            node->data[i-1] = node->data[i];
        }
        node->data[--node->n] = NULL;
        //
        if(node->n+1 < ceil(TREE_M/2.0)){
            return 2; // 通知父节点需要 平衡操作( 左右孩子调度 或 合并 )
        }
    } else if(result == 2){
        int rotationResult = rotation(node,pi,p); // 尝试旋转
        if(rotationResult!=0){
            join(node,pi);   // 合并
            if(node->n+1 < ceil(TREE_M/2.0)){
                if(parent->n==-1 && node->n < 1){ // 根合并 高度减一
                    parent->first = node->first;
                }
                return 2;
            }
        }
    }
    return 0;
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
        printf("\tn:0,()");
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
    addData(tree,tree->first,newData(50,NULL));
    addData(tree,tree->first,newData(80,NULL));
    addData(tree,tree->first,newData(10,NULL));
    addData(tree,tree->first,newData(20,NULL));
    addData(tree,tree->first,newData(90,NULL));
    addData(tree,tree->first,newData(70,NULL));
    addData(tree,tree->first,newData(60,NULL));
    addData(tree,tree->first,newData(95,NULL));

    //
    printNode(tree,0);
    //
    printf("\nfindNode:\n");
    printNode(findNode(tree,60),1);
    //
    removeData(tree,tree->first,70,NULL,-1);
    removeData(tree,tree->first,10,NULL,-1);
    removeData(tree,tree->first,60,NULL,-1);
    removeData(tree,tree->first,95,NULL,-1);
    removeData(tree,tree->first,90,NULL,-1);
    removeData(tree,tree->first,20,NULL,-1);
    printNode(tree,0);
}
