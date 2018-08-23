#include <stdlib.h>
#include <stdio.h>

#define GRAPH_MAX_SIZE 100
/*
 * Graph 图
 *
 * ADT:
 *  数据:
 *      节点的非空集合，节点二元组构成的边集。
 *  操作:
 *      new
 *      insert
 *      delete
 *      empty
 *
 * */
// 邻接表
// 边
typedef struct Edge {
    int key;
    struct Edge *next;
} Edge;
// 图，节点(顺序存储)
typedef struct Graph {
    int size;
    struct Edge *edge[GRAPH_MAX_SIZE];
} Graph;

Edge *newNode(int key){
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if(edge==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    edge->key=key;
    edge->next=NULL;
    return edge;
}

void printNode(Edge *edge){
    while (edge!=NULL){
        printf("\t%d =>",edge->key);
        edge = edge->next;
    }
}

Graph *newGraph(int size){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if(graph==NULL || size>GRAPH_MAX_SIZE){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    graph->size=size;
    int i;
    for (i = 0; i< GRAPH_MAX_SIZE ; i++) {
        graph->edge[i]=NULL;
    }
    return graph;
}
void addEdge(Graph *graph,int key1,int key2){
    if(key1>graph->size || key2>graph->size)
        return;
    //
    Edge *tmp = graph->edge[key1];
    int hasKey = 0;
    while (tmp){
        if(tmp->key==key2){
            hasKey=1;
        }
        tmp=tmp->next;
    }
    if (hasKey==0){
        Edge *key1Edge = newNode(key2);
        key1Edge->next = graph->edge[key1];
        graph->edge[key1] = key1Edge;
    }
    //
    tmp = graph->edge[key2];
    hasKey = 0;
    while (tmp){
        if(tmp->key==key1){
            hasKey=1;
        }
        tmp=tmp->next;
    }
    if (hasKey==0){
        Edge *key1Edge = newNode(key1);
        key1Edge->next = graph->edge[key2];
        graph->edge[key2] = key1Edge;
    }
}

void printGraph(Graph *graph){
    int i;
    printf("Graph:");
    for (i=1;i<=graph->size;i++) {
        printf("\n\tNode: %d : =>",i);
        printNode(graph->edge[i]);
    }
}

// 遍历

//深度优先
int visited[GRAPH_MAX_SIZE];
void dfs(Graph *graph,int k){
    visited[k]=1;
    printf("\t%d",k);
    Edge *tmp = graph->edge[k];
    while (tmp){
        if(visited[tmp->key]!=1) dfs(graph,tmp->key);
        tmp = tmp->next;
    }
}
//广度优先
int visitedList[GRAPH_MAX_SIZE];
int queue[GRAPH_MAX_SIZE];
int front = 0;
int rear = 0;
void bfs(Graph *graph,int k){
    if(visitedList[k]!=1)
        printf("\t%d",k);
    visitedList[k]=1;
    Edge *tmp = graph->edge[k];
    while (tmp){
        if(visitedList[tmp->key]!=1) {
            rear++;
            queue[rear]=tmp->key;
        }
        tmp = tmp->next;
    }
    if(front<rear){
        front++;
        bfs(graph,queue[front]);
    }
}

int main(){
    Graph *graph = newGraph(5);
    addEdge(graph,1,3);
    addEdge(graph,3,2);
    addEdge(graph,2,1);
    addEdge(graph,2,5);
    addEdge(graph,5,4);
    printGraph(graph);
    printf("\nDFS:");
    dfs(graph,1);
    printf("\nBFS:");
    bfs(graph,1);
}
