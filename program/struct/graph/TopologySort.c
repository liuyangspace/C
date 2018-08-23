#include <stdlib.h>
#include <stdio.h>

#define GRAPH_MAX_SIZE 100
/*
 * AOV(活动节点网络) 拓扑序
 *  存储 邻接表
 *
 * */

// 边
typedef struct Edge {
    int parent; // 前驱
    int node; // 节点序号
    struct Edge *next;
} Edge;
// 节点
typedef struct Node {
    int inCount; //
    struct Edge *edge;
} Node;
// 图，边集( 邻接表 存储)
typedef struct Graph {
    int size;
    struct Node *nodeList[GRAPH_MAX_SIZE];
} Graph;

Edge *newEdge(int parent,int node){
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if(edge==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    edge->parent=parent;
    edge->node=node;
    edge->next=NULL;
    return edge;
}

void printEdge(Edge *edge){
    printf("\t%d =>",edge->node);
}

Graph *newGraph(int size){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size=size;
    int i;
    for (i = 0; i< GRAPH_MAX_SIZE ; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->inCount=0;
        node->edge=NULL;
        graph->nodeList[i]=node;
    }
    return graph;
}
// 构建邻接表，边代价非递减
void addEdge(Graph *graph,Edge *edge){
    edge->next = graph->nodeList[edge->parent]->edge;
    graph->nodeList[edge->parent]->edge = edge;
    graph->nodeList[edge->node]->inCount++;
}

void printGraph(Graph *graph){
    int i;
    printf("Graph:");
    for (i=0;i<graph->size;i++) {
        printf("\n\t(Node:%d,In:%d) : =>",i,graph->nodeList[i]->inCount);
        //printNode(graph->edge[i]);
        Edge *tmp = graph->nodeList[i]->edge;
        while(tmp!=NULL) {
            printEdge(tmp);
            tmp=tmp->next;
        }
    }
}

// 拓扑序
void topSort(Graph *graph){
    int i,stack[GRAPH_MAX_SIZE],top = -1;
    //
    for (i = 0; i < graph->size; ++i) {
        if(graph->nodeList[i]->inCount==0){
            stack[++top]=i;
        }
    }
    printf("\ntopSort:\n");
    for (i = 0; i < graph->size; ++i) {
        if(top==-1){
            printf("\nCycle !\n");
        } else{
            int j = stack[top--];
            printf("\t%d",j);
            Edge *tmp = graph->nodeList[j]->edge;
            while(tmp!=NULL){
                graph->nodeList[tmp->node]->inCount--;
                if(graph->nodeList[tmp->node]->inCount==0){
                    stack[++top]=tmp->node;
                }
                tmp=tmp->next;
            }
        }
    }
}

//
int main(){
    Graph *graph = newGraph(6);
    // 构建
    addEdge(graph,newEdge(0,1));
    addEdge(graph,newEdge(0,2));
    addEdge(graph,newEdge(0,3));
    addEdge(graph,newEdge(1,4));
    addEdge(graph,newEdge(2,4));
    addEdge(graph,newEdge(2,5));
    addEdge(graph,newEdge(3,4));
    addEdge(graph,newEdge(3,5));
    addEdge(graph,newEdge(3,2));
    //
    printGraph(graph);
    // 最短路径
    printf("\n\n");
    topSort(graph);
}
