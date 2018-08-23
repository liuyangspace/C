#include <stdlib.h>
#include <stdio.h>

#define GRAPH_MAX_SIZE 100
/*
 * AOE(活动边网络) 关键路径
 *  存储 邻接表
 *
 * */

// 边 活动
typedef struct Edge {
    int parent; // 前驱
    int child;  // 后继
    int time;   // 耗时
    struct Edge *next;
} Edge;
// 节点 事件
typedef struct Node {
    int inCount; // 入度
    int earliestTime; // 事件最早开始时间最
    int latestTime;  // 事件最迟开始时间最
    struct Edge *outEdge;   // 出边
    struct Edge *inEdge;    // 入边
} Node;
// 图，边集( 邻接表 存储)
typedef struct Graph {
    int size;
    struct Node *nodeList[GRAPH_MAX_SIZE];
    int topSort[GRAPH_MAX_SIZE];    // 拓扑序
} Graph;

Edge *newEdge(int parent,int child,int time){
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if(edge==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    edge->parent=parent;
    edge->child=child;
    edge->time=time;
    edge->next=NULL;
    return edge;
}

void printEdge(Edge *edge){
    printf(" => (%d,%d,%d)",edge->parent,edge->child,edge->time);
}

Graph *newGraph(int size){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size=size;
    int i;
    for (i = 0; i< graph->size ; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->inCount=0;
        node->earliestTime=-1;
        node->latestTime=-1;
        node->outEdge=NULL;
        node->inEdge=NULL;
        graph->nodeList[i]=node;
    }
    return graph;
}
// 构建邻接表，边代价非递减
void addEdge(Graph *graph,Edge *edge){
    // 出边
    edge->next = graph->nodeList[edge->parent]->outEdge;
    graph->nodeList[edge->parent]->outEdge = edge;
    graph->nodeList[edge->child]->inCount++;
    // 入边
    Edge *inEdge = newEdge(edge->parent,edge->child,edge->time);
    inEdge->next = graph->nodeList[edge->child]->inEdge;
    graph->nodeList[edge->child]->inEdge = inEdge;
}

void printGraph(Graph *graph){
    int i;
    printf("Graph:\nOutEdge:");
    for (i=0;i<graph->size;i++) {
        printf("\n\t(Event:%d,In:%d) : ",i,graph->nodeList[i]->inCount);
        //printNode(graph->edge[i]);
        Edge *tmp = graph->nodeList[i]->outEdge;
        while(tmp!=NULL) {
            printEdge(tmp);
            tmp=tmp->next;
        }
    }
    printf("\nInEdge:");
    for (i=0;i<graph->size;i++) {
        printf("\n\t(Event:%d) : ",i);
        //printNode(graph->edge[i]);
        Edge *tmp = graph->nodeList[i]->inEdge;
        while(tmp!=NULL) {
            printEdge(tmp);
            tmp=tmp->next;
        }
    }
}

// 拓扑序 计算 事件最早开始时间
void topSort(Graph *graph){
    int i,stack[graph->size],top = -1;
    //
    for (i = 0; i < graph->size; ++i) {
        if(graph->nodeList[i]->inCount==0){
            stack[++top]=i;
        }
    }
    graph->nodeList[0]->earliestTime=0;// 事件起点
    printf("\ntopSort(Event,EarliestTime):\n");
    for (i = 0; i < graph->size; ++i) {
        if(top==-1){
            printf("\nCycle !\n");
        } else{
            int j = stack[top--];
            graph->topSort[i]=j;
            printf("\t(%d,%d)",j,graph->nodeList[j]->earliestTime);
            Edge *tmp = graph->nodeList[j]->outEdge;
            while(tmp!=NULL){
                graph->nodeList[tmp->child]->inCount--;
                if(graph->nodeList[tmp->child]->earliestTime < graph->nodeList[tmp->parent]->earliestTime+tmp->time){
                    graph->nodeList[tmp->child]->earliestTime = graph->nodeList[tmp->parent]->earliestTime+tmp->time;
                }
                if(graph->nodeList[tmp->child]->inCount==0){
                    stack[++top]=tmp->child;
                }
                tmp=tmp->next;
            }
        }
    }
}
// 事件最迟开始时间
void eventLatestTime(Graph *graph){
    int i;
    graph->nodeList[graph->size-1]->latestTime = graph->nodeList[graph->size-1]->earliestTime;
    for (i = graph->size-1; i >=0; --i) {
        Edge *tmp = graph->nodeList[graph->topSort[i]]->outEdge;
        while(tmp!=NULL){
            if(graph->nodeList[graph->topSort[i]]->latestTime == -1 || graph->nodeList[graph->topSort[i]]->latestTime > graph->nodeList[tmp->child]->latestTime-tmp->time){
                graph->nodeList[graph->topSort[i]]->latestTime = graph->nodeList[tmp->child]->latestTime-tmp->time;
            }
            tmp = tmp->next;
        }
    }
    // 打印 事件(节点) 信息
    int j;
    printf("\nEventInfo:\n\tEvent\tEarliestTime\tLatestTime\tSlack");
    for (j = 0; j < graph->size; ++j) {
        printf("\n\t%d\t%d\t\t%d\t\t%d",j,graph->nodeList[j]->earliestTime,graph->nodeList[j]->latestTime,graph->nodeList[j]->latestTime-graph->nodeList[j]->earliestTime);
    }
    // 打印 活动(边) 信息
    printf("\nActiveInfo:\n\tActive\tEarliestTime\tLatestTime\tSlack");
    for (j = 0; j < graph->size; ++j) {
        Edge *tmp = graph->nodeList[j]->outEdge;
        while(tmp!=NULL){
            int tmpEarliestTime = graph->nodeList[tmp->parent]->earliestTime;
            int tmpLatestTime = graph->nodeList[tmp->child]->latestTime-tmp->time;
            printf("\n\t(%d,%d,%d)\t%d\t\t%d\t\t%d",tmp->parent,tmp->child,tmp->time,tmpEarliestTime,tmpLatestTime,tmpLatestTime-tmpEarliestTime);
            tmp=tmp->next;
        }
    }
}
//
int main(){
    Graph *graph = newGraph(9);
    // 构建
    addEdge(graph,newEdge(0,1,6));
    addEdge(graph,newEdge(0,2,4));
    addEdge(graph,newEdge(0,3,5));
    addEdge(graph,newEdge(1,4,1));
    addEdge(graph,newEdge(2,4,1));
    addEdge(graph,newEdge(3,5,2));
    addEdge(graph,newEdge(4,6,9));
    addEdge(graph,newEdge(4,7,7));
    addEdge(graph,newEdge(5,7,4));
    addEdge(graph,newEdge(6,8,2));
    addEdge(graph,newEdge(7,8,4));
    //
    printGraph(graph);
    // 最短路径
    printf("\n\n");
    topSort(graph);
    printf("\n\n");
    eventLatestTime(graph);
}
