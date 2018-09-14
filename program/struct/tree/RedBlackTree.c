#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * 红黑树
 *  包含以下性质的扩展二叉树
 *  性质:
 *      RB1 : 根节点与外部节点为黑节点
 *      RB2 : 从根至任意外部节点的路径上红节点不能连续
 *      RB3 : 从根至任意外部节点的路径上黑节点数目相同
 * */

typedef enum color { RED, BLACK } Color;

// 元素
typedef struct Node {
    int data;
    Color color;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *newNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

// 横向打印树
void printNode(Node *treeRoot,int h, char leftOrRight){//if(h>10)return;
    if(h==0){
        printf("Red-Black-TREE:\n");
    }
    int i = 0;
    for (i=0;i<=h;i++){
        if(i==h){
            printf("-%c:\t",leftOrRight);
        } else{
            printf(" \t");
        }
    }
    printf("(%d,%s)\n",treeRoot->data,treeRoot->color==RED?"red":"black");
    if(treeRoot->leftChild!=NULL){
        printNode(treeRoot->leftChild,h+1,'l');
    }
    if(treeRoot->rightChild!=NULL){
        printNode(treeRoot->rightChild,h+1,'r');
    }
}

// 颜色变换
void changeColor(Node *grandParentNode,int height){
    if(height!=1){
        grandParentNode->color = RED;
    }
    grandParentNode->leftChild->color = BLACK;
    grandParentNode->rightChild->color = BLACK;
}

// 旋转
// 左旋
void leftRotation(Node *grandGrandParentNode,int leftOrRight){
    // LL : 插入 parentNode节点左孩子的左孩子
    Node *newRoot;
    Node *grandParentNode;
    if(leftOrRight==-1){
        grandParentNode = grandGrandParentNode->leftChild;
    } else{
        grandParentNode = grandGrandParentNode->rightChild;
    }
    Node *parentNode = grandParentNode->leftChild;
    Node *childNode = parentNode->leftChild;
    if(childNode!=NULL && childNode->color==RED){
        grandParentNode->leftChild = parentNode->rightChild;
        parentNode->rightChild = grandParentNode;

        parentNode->color = BLACK;
        grandParentNode->color = RED;
        newRoot =  parentNode;
    } else { // LR : 插入 parentNode节点左孩子的右孩子
        childNode = parentNode->rightChild;

        grandParentNode->leftChild = childNode->rightChild;
        parentNode->rightChild = childNode->leftChild;
        childNode->leftChild = parentNode;
        childNode->rightChild = grandParentNode;

        childNode->color = BLACK;
        grandParentNode->color = RED;

        newRoot = childNode;
    }
    if(leftOrRight==-1){
        grandGrandParentNode->leftChild = newRoot;
    } else{
        grandGrandParentNode->rightChild = newRoot;
    }
}

// 右旋（与左旋为左右镜像操作）
void rightRotation(Node *grandGrandParentNode,int leftOrRight){
    // RR
    Node *newRoot;
    Node *grandParentNode;
    if(leftOrRight==-1){
        grandParentNode = grandGrandParentNode->leftChild;
    } else{
        grandParentNode = grandGrandParentNode->rightChild;
    }
    Node *parentNode = grandParentNode->rightChild;
    Node *childNode = parentNode->rightChild;
    if(childNode!=NULL && childNode->color==RED){
        grandParentNode->rightChild = parentNode->leftChild;
        parentNode->leftChild = grandParentNode;

        parentNode->color = BLACK;
        grandParentNode->color = RED;
        newRoot =  parentNode;
    } else { // RL
        childNode = parentNode->leftChild;

        grandParentNode->rightChild = childNode->leftChild;
        parentNode->leftChild = childNode->rightChild;
        childNode->leftChild = grandParentNode;
        childNode->rightChild = parentNode;

        childNode->color = BLACK;
        grandParentNode->color = RED;

        newRoot = childNode;
    }
    if(leftOrRight==-1){
        grandParentNode->leftChild = newRoot;
    } else{
        grandParentNode->rightChild = newRoot;
    }
}

//

void rotation(Node *grandGrandParentNode,int leftOrRight){
    Node *grandParentNode;
    if(leftOrRight==-1){
        grandParentNode = grandGrandParentNode->leftChild;
    } else{
        grandParentNode = grandGrandParentNode->rightChild;
    }
    if(grandParentNode->leftChild->color==RED){
        leftRotation(grandGrandParentNode,leftOrRight);
    } else if(grandParentNode->rightChild->color==RED){
        rightRotation(grandGrandParentNode,leftOrRight);
    }
}

// 构建AVL
// leftOrRight -1 left 1 right
// return 0 正常返回 1 RB2判断
int addNode(    // AVL 添加节点
        Node *grandParentNode,  // 改节点的父节点
        int leftOrRight,        // 标识该节点是父节点的 左孩子(-1) 或 右孩子(1)
        Node *parentNode,       // 改节点, 用于比较的节点
        Node *node,             // 加入的节点
        int height              // grandParentNode节点所处树高
){
    int result = 0;
    if(parentNode==NULL){
        parentNode = node;
        parentNode->leftChild = NULL;
        parentNode->rightChild = NULL;
        if(height==0){  // 空树 处理
            if(leftOrRight==-1){
                grandParentNode->leftChild = parentNode;
            } else{
                grandParentNode->rightChild = parentNode;
            }
            parentNode->color = BLACK;  // 性质 RB1
            return 0;
        } else{
            parentNode->color = RED;
        }
        return 1;               // 通知 父节点需 性质 RB2 判断
    } else if(node->data < parentNode->data){
        result = addNode(parentNode,-1,parentNode->leftChild,node,height+1);
        if(result==1){
            parentNode->leftChild = node;   // 加入节点
        }
    } else if(node->data > parentNode->data){
        result = addNode(parentNode,1,parentNode->rightChild,node,height+1);
        if(result==1){
            parentNode->rightChild = node;  // 加入节点
        }
    }
    if(result==1 && parentNode->color==RED){
        if(parentNode->color==RED){
            Node *parentBrotherNode;
            if(leftOrRight==-1){
                parentBrotherNode = grandParentNode->rightChild;
            } else{
                parentBrotherNode = grandParentNode->leftChild;
            }
            if(parentBrotherNode!=NULL && parentBrotherNode->color==RED){
                changeColor(grandParentNode,height);
                return 2;   // 通知 父节点需 性质 RB2 判断
            } else{
                return 3;   // 通知 父节点需 旋转
            }
        }
    } else if(result==2 && grandParentNode->color==RED){
        return 1;           // 通知 父节点需 性质 RB2 判断
    } else if(result==3){
        rotation(grandParentNode,leftOrRight);
    }
    return 0;
}

// 删除节点
// return 1 从空孩子返回 -2 从左孩子返回 2 从右孩子返回
int removeNode(
        Node *grandParentNode,      // 改节点的父节点
        int leftOrRight,            // 标识该节点是父节点的 左孩子(-1) 或 右孩子(1)
        Node *parentNode,           // 改节点, 用于比较的节点
        int key,                    // 待删除节点的关键子
        int *balance,               // 标识以该节点为根的子树是否需要"平衡操作"
        Node *removeParent,         // 待删除节点的父亲
        int removeLeftOrRight       // 标识待删除节点是其父节点的 左孩子(-1) 或 右孩子(1)
);
// 合并多个 红黑树
int joinTree();
// 分裂 红黑树
int divisionTree();

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

    //addNode(tree,newNode(1),&balance);
    addNode(tree,-1,tree->leftChild,newNode(50),0);
    addNode(tree,-1,tree->leftChild,newNode(10),0);
    addNode(tree,-1,tree->leftChild,newNode(80),0);//printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(70),0);//printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(90),0);//printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(60),0);printNode(tree,0,'l');
    addNode(tree,-1,tree->leftChild,newNode(65),0);printNode(tree,0,'l');

}
