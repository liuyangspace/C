#include <stdlib.h>
#include <stdio.h>

#define GRAPH_MAX_SIZE 100
/*
 * 有向图
 *  有向，非负  最短路径
 *
 * */

// 边
typedef struct Edge {
    int parent;
    int child;
    int value;
    struct Edge *next;
} Edge;

// 图，边集(按代价非递减 邻接表 存储)
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
    edge->next=NULL;
    return edge;
}

void printEdge(Edge *edge){
    printf("\t(%d,%d,%d)",edge->parent,edge->child,edge->value);
}

Graph *newGraph(int size){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if(graph==NULL){
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
// 构建邻接表，边代价非递减
void addEdge(Graph *graph,Edge *edge){
    Edge *tmp = graph->edge[edge->parent];
    if(tmp==NULL){
        graph->edge[edge->parent] = edge;
    } else if(edge->value<=tmp->value){
        edge->next = tmp;
        graph->edge[edge->parent] = edge;
    }else{
        Edge *parent=NULL;
        do{
            parent = tmp;
            tmp = tmp->next;
        }while (tmp!=NULL && edge->value>tmp->value);
        if(tmp!=NULL)
            edge->next = tmp;
        parent->next = edge;
    }
}

void printGraph(Graph *graph){
    int i;
    printf("Graph:");
    for (i=0;i<graph->size;i++) {
        printf("\n\tNode: %d : =>",i);
        //printNode(graph->edge[i]);
        Edge *tmp = graph->edge[i];
        while(tmp!=NULL) {
            printEdge(tmp);
            tmp=tmp->next;
        }
    }
}

// 求 i节点 到 未到达点的 最短邻接边
Edge *shortEdgeFun(Graph *graph,int i,int *distance){
    Edge *tmp=graph->edge[i];
    while (tmp!=NULL && distance[tmp->child]!=-1){
        if(distance[tmp->child]==-1)
            return tmp;
        tmp=tmp->next;
    }
    return tmp;
}
// 求 i节点 到 target节点 的 邻接边
Edge *shortConstFun(Graph *graph,int i,int target){
    Edge *tmp=graph->edge[i];
    while (tmp!=NULL){
        if(tmp->child==target)
            return tmp;
        tmp=tmp->next;
    }
    return NULL;
}
void shortestPath(Graph *graph){
    //
    int distance[graph->size],i;//记录到达点的最小代价
    for (i = 0; i < graph->size; ++i) {
        distance[i]=-1;
    }
    // 记录 路径
    int allPath[graph->size][graph->size],j;
    for (i = 0; i < graph->size; ++i) {
        for (j = 0; j < graph->size; j++) {
            allPath[i][j]=-1;
        }
    }
    allPath[0][0]=0;
    //
    distance[0]=0;//记0为起点
    int n;//已到达节点数
    printf("\nShortCostEdge: ");
    for (n=1; n<graph->size; n++) {
        // 取最小代价连通点
        int j;
        Edge *shortEdge=NULL;
        for(j=0;j<graph->size;j++){
            if(distance[j]!=-1){//已到达点
                Edge *tmp = shortEdgeFun(graph,j,distance);
                if(shortEdge==NULL || (tmp!=NULL && shortEdge->value>tmp->value))
                    shortEdge = tmp;
            }
        }
        if(shortEdge==NULL){
            fprintf(stderr,"Map is not connected!");
            exit(-1);
        }
        // 取最小代价连通点的 最小路径代价
        int target = shortEdge->child;
        int targetCost = distance[shortEdge->parent]+shortEdge->value;
        Edge *costEdge = shortEdge;
        for(j=0;j<graph->size;j++){
            if(distance[j]!=-1){//已到达点
                Edge *tmp = shortConstFun(graph,j,target);
                if(tmp!=NULL){
                    if(targetCost>distance[j]+tmp->value){
                        targetCost = distance[j]+tmp->value;
                        costEdge = tmp;
                    }
                }
            }
        }
        // 求得点的最小代价
        distance[target]=targetCost;
        printEdge(costEdge);
        // 复制路径
        int k=0;
        while (allPath[costEdge->parent][k]!=-1){
            allPath[costEdge->child][k]=allPath[costEdge->parent][k];
            k++;
        }
        allPath[costEdge->child][k]=costEdge->child;
    }
    // 打印路径
    printf("\nAllPath: ");
    for (i = 0; i < graph->size; ++i) {
        printf("\n\t(TargetNode:%d,Cost:%d) ",i,distance[i]);
        for (j = 0; j < graph->size; j++) {
            if(allPath[i][j]==-1)
                break;
            printf("\t%d",allPath[i][j]);
        }
    }
}

//
int main(){
    Graph *graph = newGraph(6);
    // 构建
    addEdge(graph,newEdge(0,1,50));
    addEdge(graph,newEdge(0,2,45));
    addEdge(graph,newEdge(0,3,10));
    addEdge(graph,newEdge(1,2,10));
    addEdge(graph,newEdge(1,3,15));
    addEdge(graph,newEdge(2,4,30));
    addEdge(graph,newEdge(3,0,20));
    addEdge(graph,newEdge(3,4,15));
    addEdge(graph,newEdge(4,1,20));
    addEdge(graph,newEdge(4,2,35));
    addEdge(graph,newEdge(4,5,3));
    addEdge(graph,newEdge(5,2,5));
    //
    printGraph(graph);
    // 最短路径
    printf("\n\n");
    shortestPath(graph);
}
