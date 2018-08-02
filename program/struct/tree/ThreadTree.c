#include <stdlib.h>
#include <stdio.h>

/*
 * ThreadTree 线索二叉树
 *
 * */

// 节点
typedef struct Node {
    int data;  //
    int leftThread; // 若 leftThread = 1，则 左孩子指向线索
    int rightThread; // 若 rightThread = 1，则 右孩子指向线索
    struct Node * left;
    struct Node * right;
} Node; //

Node *newNode(int value){
    Node *node = (Node  *)malloc(sizeof(Node));
    if(node==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    node->data=value;
    node->leftThread=0;
    node->rightThread=0;
    node->left=NULL;
    node->right=NULL;
    return node;
}

// 普通二叉树转线索二叉树
void toThreadTree(Node *node,Node *pre,Node *suf){
    if(node!=NULL){
        if(node->left==NULL){
            node->leftThread = 1;
            node->left=pre;
        } else{
            node->leftThread = 0;
            toThreadTree(node->left,pre,node);
        }
        if(node->right==NULL){
            node->rightThread = 1;
            node->right=suf;
        } else{
            node->rightThread = 0;
            toThreadTree(node->right,node,suf);
        }
    }
}

// 树
typedef struct {
    Node *node; // 指向树根
} Tree;

Tree *newTree(){
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->node=NULL;
    return tree;
}

// 深度优先
// LVR (无栈)中序遍历
void cenOrder(Node *node){
    Node *tmp = node;
    int preRightTHread = 0;
    int rootCount = 0;
    printf("\nLVR:");
    while (1){
        if(tmp==node) {
            rootCount++;
        }
        if(rootCount>=3){
            break;
        }
        if(tmp->rightThread==0 && preRightTHread==0 ){
            while (tmp->leftThread==0){
                tmp = tmp->left;
            }
        }
        printf("\t%d",tmp->data);
        if(tmp->rightThread==1){
            preRightTHread = 1;
        } else{
            preRightTHread = 0;
        }
        tmp = tmp->right;
    }
}

int main(){
    //
    Tree *tree = newTree();
    Node *node1 = newNode(123);
    Node *node2 = newNode(456);
    Node *node3 = newNode(789);
    Node *node4 = newNode(34);
    Node *node5 = newNode(445);
    Node *node6 = newNode(776);
    Node *node7 = newNode(342);
    Node *node8 = newNode(437);
    Node *node9 = newNode(112);
    tree->node = node1;
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    node4->left = node8;
    node4->right = node9;
    printf(        "\n       123"
                   "\n      /    \\"
                   "\n    456    789"
                   "\n    / \\    /  \\"
                   "\n  34 445  776 342"
                   "\n /  \\"
                   "\n437 112");
    //
    toThreadTree(node1,node1,node1);
    cenOrder(node1);
}
