#include <stdlib.h>
#include <stdio.h>

#define HEAP_MAX_SIZE 100

/*
 * SearchTree 二叉查找树
 *
 * 约定:
 *  (1) 树中每个节点有一个关键字
 *  (2) 若有左子树，左子树节点都小于根关键字
 *  (3) 若有右子树，右子树节点都大于根关键字
 *  (4) 左右子树均为二叉查找树
 *
 * */

// 节点
typedef struct Node {
    int key;
    int value;  //
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int key,int value){
    Node *node = (Node  *)malloc(sizeof(Node));
    if(node==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    node->key=key;
    node->value=value;
    node->left=NULL;
    node->right=NULL;
    return node;
}

void printNode(Node *node){
    printf("\t(%d=>%d,%d,%d)",node->key,node->value,node->left?node->left->key:0,node->right?node->right->key:0);
}

// 顺序存储堆
typedef struct SearchTree {
    int size;
    Node *root;   // 大根堆
} SearchTree;

SearchTree *newSearchTree(){
    SearchTree *searchTree = (SearchTree  *)malloc(sizeof(SearchTree));
    if(searchTree==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    searchTree->size=0;
    searchTree->root=NULL;
    return searchTree;
}
//
int empty(SearchTree *searchTree){
    if(searchTree->size==0){
        return 1;
    }
    return 0;
}

//
void put(SearchTree *searchTree,Node *node){
    Node *tmp = searchTree->root;
    if(tmp==NULL) {
        searchTree->root = node;
    } else{
        while (tmp){
            if(tmp->key>node->key){
                if(tmp->left==NULL){
                    tmp->left = node;
                    return;
                }
                tmp = tmp->left;
            } else if(tmp->key<node->key){
                if(tmp->right==NULL){
                    tmp->right = node;
                    return;
                }
                tmp = tmp->right;
            } else if(tmp->key==node->key){
                tmp->value = node->value;
                return;
            }
        }
    }
}
//
Node *get(SearchTree *searchTree,int key){
    Node *tmp = searchTree->root;
    while (tmp){
        if(tmp->key==key){
            break;
        }
        if(tmp->key>key){
            tmp = tmp->left;
        }
        if(tmp->key<key){
            tmp = tmp->right;
        }
    }
    return tmp;
}
//
Node *popMax(Node *node){
    if(node==NULL)
        return node;
    Node *tmp = node;
    Node *parent=node;
    while (tmp->right){
        parent = tmp;
        tmp->right;
    }
    parent->right=NULL;
    return tmp;
}
void deleteNode(SearchTree *searchTree,int key){
    Node *tmp = searchTree->root;
    Node *parent = NULL;
    while (tmp){
        if(tmp->key==key){
            Node *target;
            if(tmp->left && tmp->right){
                target = popMax(tmp->left);
            } else{
                target = tmp->left?tmp->left:tmp->right;
            }
            if(target==tmp->left) tmp->left=NULL;
            if(target==tmp->right) tmp->right=NULL;
            if(parent){
                if(parent->left==tmp){
                    parent->left = target;
                } else{
                    parent->right = target;
                }
            } else{
                searchTree->root = target;
            }
            target->left = tmp->left;
            target->right = tmp->right;
            break;
        }
        parent = tmp;
        if(tmp->key>key){
            tmp = tmp->left;
        } else if(tmp->key<key){
            tmp = tmp->right;
        }
    }
}

void cenOrder(Node *node){
    if(node){
        cenOrder(node->left);
        printNode(node);
        cenOrder(node->right);
    }
}
void printSearchTree(SearchTree *searchTree){
    printf("\nSearchTree:");
    if(searchTree->root)
        printf("\t%d",searchTree->root->key);
    cenOrder(searchTree->root);
}

int main(){
    SearchTree *searchTree = newSearchTree();
    put(searchTree,newNode(5,123));
    printSearchTree(searchTree);
    put(searchTree,newNode(4,667));
    printSearchTree(searchTree);
    put(searchTree,newNode(7,456));
    put(searchTree,newNode(6,453));
    put(searchTree,newNode(8,765));
    printSearchTree(searchTree);
    printf("\n");
    printNode(get(searchTree,7));
    deleteNode(searchTree,7);
    printSearchTree(searchTree);
    deleteNode(searchTree,5);
    deleteNode(searchTree,11);
    printSearchTree(searchTree);
}
