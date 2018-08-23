#include <stdlib.h>
#include <stdio.h>

#define GRAPH_MAX_SIZE 100
/*
 * 图 最小代价生成树
 *
 * Kruskal
 *
 *
 * */

// 边
typedef struct Edge {
    int parent;
    int child;
    int value;
} Edge;

// 图，边集(按代价 小根堆 存储)
typedef struct Graph {
    int size;
    struct Edge *edge[GRAPH_MAX_SIZE];
} Graph;

Edge *newEdge(int parent,int child,int value){
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if(edge==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    edge->parent=parent;
    edge->child=child;
    edge->value=value;
    return edge;
}

void printEdge(Edge *edge){
    printf("\t(%d,%d,%d)",edge->parent,edge->child,edge->value);
}

Graph *newGraph(){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if(graph==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    graph->size=0;
    int i;
    for (i = 0; i< GRAPH_MAX_SIZE ; i++) {
        graph->edge[i]=NULL;
    }
    return graph;
}
// 进堆
void addEdge(Graph *graph,Edge *edge){
    graph->size++;
    int i = graph->size;
    while (i!=1 && edge->value<graph->edge[i/2]->value){
        graph->edge[i] = graph->edge[i/2];
        i=i/2;
    }
    graph->edge[i]=edge;
}
// 出堆
Edge *getEdge(Graph *graph){
    if(graph->size==0){
        return NULL;
    }
    Edge *result = graph->edge[1];
    Edge *edge =  graph->edge[graph->size];
    int i = 1;
    while (i<graph->size){
        int j = 0;
        if((2*i+1)<graph->size && graph->edge[2*i+1]->value<edge->value && graph->edge[2*i+1]->value<graph->edge[2*i]->value){
            graph->edge[i] = graph->edge[2*i+1];
            j = i*2+1;
        } else if(2*i<graph->size && graph->edge[2*i]->value<edge->value){
            graph->edge[i] = graph->edge[2*i];
            j = i*2;
        }
        if(j==0)
            break;
        i = j;
    }
    graph->edge[i] = edge;
    graph->size--;
    return result;
}

void printGraph(Graph *graph){
    int i;
    printf("Graph:");
    for (i=1;i<=graph->size;i++) {
        printf("\n\tNode: %d : =>",i);
        //printNode(graph->edge[i]);
    }
}

// 双链表 判断是否成环
typedef struct Node {
    int key;
    struct Node *nextSet;
    struct Node *nextKey;
} Node;
Node *node = NULL;
Node *newNode(int key){
    Node *node = (Node *)malloc(sizeof(Node));
    if(node==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    node->key=key;
    node->nextSet=NULL;
    node->nextKey=NULL;
    return node;
}
int isRing(int key1,int key2){
    if(node==NULL){
        node = newNode(key1);
        Node *node2 = newNode(key2);
        node->nextKey = node2;
        //node2->nextSet = NULL;
        //node->nextSet = node;
        return 0;
    }
    Node *nodeSet = node;

    int hasKey1 = 0;
    Node *key1Set = NULL;
    Node *parentKey1Set = NULL;
    Node *key1Last = NULL;

    int hasKey2 = 0;
    Node *key2Set = NULL;
    Node *parentKey2Set = NULL;
    Node *key2Last = NULL;

    Node *parenNode = NULL;
    while (nodeSet){
        Node *nodeKey = nodeSet;
        while (nodeKey){
            if(nodeKey->key==key1){
                hasKey1 = 1;
                key1Set = nodeSet;
                parentKey1Set = parenNode;
            }
            if(nodeKey->key==key2){
                hasKey2 = 1;
                key2Set = nodeSet;
                parentKey2Set = parenNode;
            }
            if(nodeKey->nextKey==NULL){
                if(key1Set==nodeSet){
                    key1Last = nodeKey;
                }
                if(key2Set==nodeSet){
                    key2Last = nodeKey;
                }
            }
            nodeKey = nodeKey->nextKey;
        }
        parenNode = nodeSet;
        nodeSet = nodeSet->nextSet;
    }
    if(hasKey1==1 && hasKey2==1){
        if(key1Set==key2Set){
            return 1;
        } else{
            if(parentKey1Set!=NULL){
                key2Last->nextKey=key1Set;
                parentKey1Set->nextSet = key1Set->nextSet;
            } else{
                key1Last->nextKey=key2Set;
                parentKey2Set->nextSet = key2Set->nextSet;
            }
        }
    } else if(hasKey1==1){
        key1Last->nextKey = newNode(key2);
    } else if(hasKey2==1){
        key2Last->nextKey = newNode(key1);
    } else{
        Node *node1 = newNode(key1);
        Node *node2 = newNode(key2);
        node1->nextKey = node2;
        node1->nextSet = node->nextSet;
        node->nextSet = node1;
    }
    return 0;
}

// Kruskal 法 最小代价生成树
int main(){
    Graph *graph = newGraph();
    // 进堆
    addEdge(graph,newEdge(0,1,28));
    addEdge(graph,newEdge(0,5,10));
    addEdge(graph,newEdge(1,2,16));
    addEdge(graph,newEdge(1,6,14));
    addEdge(graph,newEdge(2,3,12));
    addEdge(graph,newEdge(3,4,22));
    addEdge(graph,newEdge(3,6,18));
    addEdge(graph,newEdge(4,5,25));
    addEdge(graph,newEdge(4,6,24));
    // 出堆
    Edge *edge;
    int n = 7;
    int count = 0;
    while ((edge=getEdge(graph))!=NULL && count<(n-1)){
        if(isRing(edge->parent,edge->child)==0){
            printEdge(edge);
        }
    }
}
