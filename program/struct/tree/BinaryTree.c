#include <stdlib.h>
#include <stdio.h>

/*
 * Tree 二叉树
 *
 * */

// 节点
typedef struct Node {
    int data;  //
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
    node->left=NULL;
    node->right=NULL;
    return node;
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
// VLR 先序
void preOrder(Node *node){
    if(node){
        printf("\t%d",node->data);
        preOrder(node->left);
        preOrder(node->right);
    }
}

// LVR 中序
void cenOrder(Node *node){
    if(node){
        cenOrder(node->left);
        printf("\t%d",node->data);
        cenOrder(node->right);
    }
}

// LRV 后序
void postOrder(Node *node){
    if(node){
        postOrder(node->left);
        postOrder(node->right);
        printf("\t%d",node->data);
    }
}

// 广度优先
void breadthOrder(Tree *tree){
    Node *nodeList[100];
    nodeList[0]=tree->node;
    int i = 0;
    int right = 0;
    while (i<=right){
        printf("\t%d",nodeList[i]->data);
        if(nodeList[i]->left){
            right++;
            nodeList[right] = nodeList[i]->left;
        }
        if(nodeList[i]->right){
            right++;
            nodeList[right] = nodeList[i]->right;
        }
        i++;
    }
}

// copy
Node *copy(Node *node){
    if(node==NULL){
        return NULL;
    }
    Node *node1 = newNode(node->data);
    node1->left = copy(node->left);
    node1->right = copy(node->right);
    return node1;
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
    printf("\nVLR:");
    preOrder(tree->node);
    printf("\nLVR:");
    cenOrder(tree->node);
    printf("\nLRV:");
    postOrder(tree->node);
    printf("\nB:");
    breadthOrder(tree);
    //
    printf("\nCopy:");
    Tree *tree1 = newTree();
    tree1->node = copy(tree->node);
    breadthOrder(tree1);
}
