#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * AVL
 *
 * */

// 元素
typedef struct Node {
    int data;
    int bf;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *newNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->bf = 0;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

// 横向打印树
void printNode(Node *treeRoot,int h, char leftOrRight){if(h>10)return;
    if(h==0){
        printf("TREE:\n");
    }
    int i = 0;
    for (i=0;i<=h;i++){
        if(i==h){
            printf("-%c:\t",leftOrRight);
        } else{
            printf(" \t");
        }
    }
    printf("(%d,%d)\n",treeRoot->data,treeRoot->bf);
    if(treeRoot->leftChild!=NULL){
        printNode(treeRoot->leftChild,h+1,'l');
    }
    if(treeRoot->rightChild!=NULL){
        printNode(treeRoot->rightChild,h+1,'r');
    }
}

//
// 左旋
void leftRotation(Node *grandParentNode,int leftOrRight,Node *parentNode,int *balance){
    // LL : 插入 parentNode节点左孩子的左孩子
    Node *newRoot;
    Node *childNode = parentNode->leftChild;
    if(childNode->bf==1){
        parentNode->leftChild = childNode->rightChild;
        childNode->rightChild = parentNode;

        parentNode->bf = 0;
        childNode->bf = 0;
        *balance = 1;
        newRoot =  childNode;
    } else { // LR : 插入 parentNode节点左孩子的右孩子
        Node *grandChildNode = childNode->rightChild;

        parentNode->leftChild = grandChildNode->rightChild;
        childNode->rightChild = grandChildNode->leftChild;
        grandChildNode->leftChild = childNode;
        grandChildNode->rightChild = parentNode;
        switch (grandChildNode->bf){
            case -1:
                parentNode->bf = 0;
                childNode->bf = 1;
                break;
            case 0:
                parentNode->bf = 0;
                childNode->bf = 0;
                break;
            case 1:
                parentNode->bf = -1;
                childNode->bf = 0;
                break;
            default:
                break;
        }
        grandChildNode->bf = 0;
        *balance = 1;
        newRoot = grandChildNode;
    }
    if(leftOrRight==-1){
        grandParentNode->leftChild = newRoot;
    } else{
        grandParentNode->rightChild = newRoot;
    }
}

// 右旋（与左旋为左右镜像操作）
void rightRotation(Node *grandParentNode,int leftOrRight,Node *parentNode,int *balance){
    // RR
    Node *newRoot;
    Node *childNode = parentNode->rightChild;
    if(childNode->bf==-1){
        parentNode->rightChild = childNode->leftChild;
        childNode->leftChild = parentNode;

        parentNode->bf = 0;
        childNode->bf = 0;
        *balance = 1;
        newRoot =  childNode;
    } else { // RL
        Node *grandChildNode = childNode->leftChild;

        parentNode->rightChild = grandChildNode->leftChild;
        childNode->leftChild = grandChildNode->rightChild;
        grandChildNode->leftChild = parentNode;
        grandChildNode->rightChild = childNode;
        switch (grandChildNode->bf){
            case -1:
                parentNode->bf = 1;
                childNode->bf = 0;
                break;
            case 0:
                parentNode->bf = 0;
                childNode->bf = 0;
                break;
            case 1:
                parentNode->bf = 0;
                childNode->bf = -1;
                break;
            default:
                break;
        }
        grandChildNode->bf = 0;
        *balance = 1;
        newRoot = grandChildNode;
    }
    if(leftOrRight==-1){
        grandParentNode->leftChild = newRoot;
    } else{
        grandParentNode->rightChild = newRoot;
    }
}

// 构建AVL
// leftOrRight -1 left 1 right
int addNode(    // AVL 添加节点
        Node *grandParentNode,  // 改节点的父节点
        int leftOrRight,        // 标识该节点是父节点的 左孩子(-1) 或 右孩子(1)
        Node *parentNode,       // 改节点, 用于比较的节点
        Node *node,             // 加入的节点
        int *balance            // 标识以该节点为根的子树是否需要"平衡操作"
){
    if(parentNode==NULL){       // 空树 处理
        parentNode = node;      // 加入节点
        parentNode->bf = 0;
        parentNode->leftChild = NULL;
        parentNode->rightChild = NULL;
        *balance = 0;           // 新增节点 通知父节点需要"平衡操作"
        return 1;               // 通知 父节点需要加入节点
    } else if(node->data < parentNode->data){
        int result = addNode(parentNode,-1,parentNode->leftChild,node,balance);
        if(result==1){
            parentNode->leftChild = node;   // 加入节点
        }
        if(*balance==0){        // 平衡操作
            parentNode->bf = parentNode->bf + 1;
            if(parentNode->bf == 0) {
                *balance = 1;
            } else if(parentNode->bf>1){    // 左右子树高度差超过1
                leftRotation(grandParentNode,leftOrRight,parentNode,balance); // 左旋操作
            }
        }
    } else if(node->data > parentNode->data){
        int result = addNode(parentNode,1,parentNode->rightChild,node,balance);
        if(result==1){
            parentNode->rightChild = node;  // 加入节点
        }
        if(*balance==0){        // 平衡操作
            parentNode->bf = parentNode->bf - 1;
            if(parentNode->bf == 0) {
                *balance = 1;
            }else if(parentNode->bf<-1){    // 左右子树高度差超过1
                rightRotation(grandParentNode,leftOrRight,parentNode,balance);  // 右旋操作
            }
        }
    }
    return 0;   // 正常返回
}

// 删除节点
void removeLeftRotation(Node *grandParentNode,int leftOrRight,Node *parentNode,int *balance){
    Node *childNode = parentNode->leftChild;
    if(childNode->bf==0){
        parentNode->leftChild = childNode->rightChild;
        childNode->rightChild = parentNode;
        if(leftOrRight==-1){
            grandParentNode->leftChild = childNode;
        } else{
            grandParentNode->rightChild = childNode;
        }
        parentNode->bf = 1;
        childNode->bf = -1;
        *balance = 1;
    } else{
        leftRotation(grandParentNode,leftOrRight,parentNode,balance);
        *balance = 0;
    }
}
void removeRightRotation(Node *grandParentNode,int leftOrRight,Node *parentNode,int *balance){
    Node *childNode = parentNode->rightChild;//
    if(childNode->bf==0){
        parentNode->rightChild = childNode->leftChild;
        childNode->leftChild = parentNode;
        if(leftOrRight==-1){
            grandParentNode->rightChild = childNode;
        } else{
            grandParentNode->leftChild = childNode;
        }
        parentNode->bf = -1;
        childNode->bf = 1;
        *balance = 1;
    } else{
        rightRotation(grandParentNode,leftOrRight,parentNode,balance);
        *balance = 0;
    }
}

// return 1 从空孩子返回 -2 从左孩子返回 2 从右孩子返回
int removeNode(
        Node *grandParentNode,      // 改节点的父节点
        int leftOrRight,            // 标识该节点是父节点的 左孩子(-1) 或 右孩子(1)
        Node *parentNode,           // 改节点, 用于比较的节点
        int key,                    // 待删除节点的关键子
        int *balance,               // 标识以该节点为根的子树是否需要"平衡操作"
        Node *removeParent,         // 待删除节点的父亲
        int removeLeftOrRight       // 标识待删除节点是其父节点的 左孩子(-1) 或 右孩子(1)
){
    // parentNode
    if(grandParentNode==NULL){      // 空树
        return 0;
    }
    int result = 0;
    //
    if(parentNode==NULL){
        *balance = 1;
        if(removeParent==NULL){
            return 0;               // 未找到 待删除节点
        } else{
            return 1;               // 通知父节点，需要移动父节点，从空孩子返回
        }
    } else if(removeParent!=NULL){  // 已找到 待删除节点
        result = removeNode(parentNode,1,parentNode->rightChild,key,balance,removeParent,removeLeftOrRight); // 寻找 待删除节点 左子树的最大节点（用于替代待删除节点）
    } else if(key <= parentNode->data ){
        if(key == parentNode->data){ // 找到 待删除节点
            result = removeNode(parentNode,-1,parentNode->leftChild,key,balance,grandParentNode,leftOrRight); // 寻找 待删除节点 左子树的最大节点（用于替代待删除节点）
            if(leftOrRight==-1){
                parentNode = grandParentNode->leftChild;
            } else{
                parentNode = grandParentNode->rightChild;
            }
        } else {
            result = removeNode(parentNode,-1,parentNode->leftChild,key,balance,removeParent,removeLeftOrRight);
        }
    }else if(key > parentNode->data){
        result = removeNode(parentNode,1,parentNode->rightChild,key,balance,removeParent,removeLeftOrRight);
    }
    // 旋转
    if(*balance==0){    // 平衡操作
        if(key == grandParentNode->data){ // 父节点已被替换
            if(removeLeftOrRight==-1){
                grandParentNode = removeParent->leftChild;
            } else if(removeLeftOrRight==1){
                grandParentNode = removeParent->rightChild;
            }
        }
        if(result==-2){
            parentNode->bf = parentNode->bf-1;
            if(parentNode->bf<-1){
                removeRightRotation(grandParentNode,leftOrRight,parentNode,balance);
            } else if(parentNode->bf==-1){
                *balance=1;
            }
        } else if(result==2){
            parentNode->bf = parentNode->bf+1;
            if(parentNode->bf>1){
                removeLeftRotation(grandParentNode,leftOrRight,parentNode,balance);
            } else if(parentNode->bf==1){
                *balance=1;
            }
        }
    }
    // 节点替换
    if(result==1){ // 移动 parentNode
        *balance = 0;
        Node *moveNode = parentNode;
        // 处理 待移动节点的孩子 并移除节点
        Node *nextNode = NULL;
        if(moveNode->leftChild!=NULL){
            nextNode = moveNode->leftChild;
        } else{
            nextNode = moveNode->rightChild;
        }
        if(leftOrRight==-1){
            grandParentNode->leftChild = nextNode;
            grandParentNode->bf = grandParentNode->bf-1;
        } else{
            grandParentNode->rightChild = nextNode;
            grandParentNode->bf = grandParentNode->bf+1;
        }
        // 处理 待删除节点的孩子 并用 移动节点替代删除节点
        if(removeLeftOrRight==-1){
            moveNode->leftChild = removeParent->leftChild->leftChild;
            moveNode->rightChild = removeParent->leftChild->rightChild;
            moveNode->bf = removeParent->leftChild->bf;
            removeParent->leftChild = moveNode;
        } else{
            moveNode->leftChild = removeParent->rightChild->leftChild;
            moveNode->rightChild = removeParent->rightChild->rightChild;
            moveNode->bf = removeParent->rightChild->bf;
            removeParent->rightChild = moveNode;
        }
    }
    if(leftOrRight==-1){
        return  -2;     // 从左孩子返回
    } else{
        return 2;       // 从右孩子返回
    }
}

// 查找
Node * findNode(Node *tree,int key){
    if(tree==NULL){
        return NULL;
    }
    if(tree->data==key){
        return tree;
    } else if(tree->data > key){
        return findNode(tree->leftChild,key);
    } else if(tree->data < key){
        return findNode(tree->rightChild,key);
    }
}

int main(){

    int balance = 1;
    Node *tree = newNode(0);// 指向根节点的节点，仅作指向, 不参与排序
    Node *root = newNode(8);// 根节点

    tree->leftChild = root;
    //addNode(tree,newNode(1),&balance);
    addNode(tree,-1,tree->leftChild,newNode(9),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(10),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(2),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(1),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(5),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(3),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(6),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(4),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(7),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(11),&balance);
    //printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(12),&balance);
    printNode(tree,0,'l');
    //
    //removeNode(tree,-1,tree->leftChild,12,&balance,NULL,0);
    //printNode(tree,0,'l');
    //removeNode(tree,-1,tree->leftChild,11,&balance,NULL,0);
    //printNode(tree,0,'l');
    //removeNode(tree,-1,tree->leftChild,9,&balance,NULL,0);
    //printNode(tree,0,'l');
    //removeNode(tree,-1,tree->leftChild,10,&balance,NULL,0);
    //printNode(tree,0,'l');
    removeNode(tree,-1,tree->leftChild,10,&balance,NULL,0);
    printNode(tree,0,'l');
    printNode(findNode(tree->leftChild,12),0,'l');
}
