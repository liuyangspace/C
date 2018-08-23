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

// 图，边集( 邻接表 存储)
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
void bellmanFord(Graph *graph){
    //
    int NotReach = 100000;
    int distance[graph->size][graph->size],i,j;//记录到达点的最小代价
    for (i = 0; i < graph->size; ++i) {
        for (j = 0; j < graph->size; ++j) {
            distance[i][j]=NotReach;
        }
    }
    // 记录 路径
    int allPath[graph->size][graph->size][graph->size],k;
    for (i = 0; i < graph->size; ++i) {
        for (j = 0; j < graph->size; j++) {
            for (k = 0; k < graph->size; k++) {
                allPath[i][j][k]=NotReach;
            }
        }
    }
    allPath[0][0][0]=0;
    //
    distance[0][0]=0;//记0为起点
    int n;//已历经边数
    for (n=1; n<graph->size; n++) {
        // 遍历节点
        int target;
        for(target=0;target<graph->size;target++){// j 目标节点
            int source;
            for(source=0;source<graph->size;source++){
                if(distance[n-1][source]!=NotReach){//已到达点
                    Edge *tmp = shortConstFun(graph,source,target); // k 目标节点的相邻节点
                    if(tmp!=NULL && source==0 && tmp->value<distance[n-1][target] && tmp->value<distance[n][target]){
                        distance[n][target] = tmp->value;
                        // 记录 路径
                        allPath[n][target][0]=0;
                        allPath[n][target][1]=target;
                    } else if(tmp!=NULL &&  tmp->value+distance[n-1][source]<distance[n-1][target] && tmp->value+distance[n-1][source]<distance[n][target]){
                        distance[n][target] = tmp->value+distance[n-1][source];
                        // 记录 路径
                        int tmpCount = 0;
                        while(allPath[n-1][source][tmpCount]!=NotReach){
                            allPath[n][target][tmpCount]=allPath[n-1][source][tmpCount];
                            tmpCount++;
                        }
                        allPath[n][target][tmpCount]=target;
                    } else if(distance[n][target]==NotReach){
                        distance[n][target] = distance[n-1][target];
                        // 记录 路径
                        int tmpCount = 0;
                        while(allPath[n-1][target][tmpCount]!=NotReach){
                            allPath[n][target][tmpCount]=allPath[n-1][target][tmpCount];
                            tmpCount++;
                        }
                    }
                }
            }
        }
        // 求得点的最小代
    }
    //
    printf("\nBellmanFord: ");
    // 打印个节点最短距离
    printf("\nEdgeForCost: \n\tNode:\t");
    for (i = 0; i < graph->size; i++) {
        printf("\t%d ",i);
    }
    for (i = 0; i < graph->size; i++) {
        printf("\n\t(MaxEdge:%d) ",i);
        for (j = 0; j < graph->size; j++) {
            if(distance[i][j]==NotReach){
                printf("\tNo");
                continue;
            }
            printf("\t%d",distance[i][j]);
        }
    }
    // 打印路径
    printf("\nAllPath: ");
    for (i = 0; i < graph->size; i++) {
        printf("\n\t(Node:%d,MinCost:%d) ",i,distance[graph->size-1][i]);
        for (j = 0; j < graph->size; j++) {
            if(allPath[graph->size-1][i][j]==NotReach){
                break;
            }
            printf("\t%d",allPath[graph->size-1][i][j]);
        }
    }
}

//
int main(){
    Graph *graph = newGraph(7);
    // 构建
    addEdge(graph,newEdge(0,1,6));
    addEdge(graph,newEdge(0,2,5));
    addEdge(graph,newEdge(0,3,5));
    addEdge(graph,newEdge(1,4,-1));
    addEdge(graph,newEdge(2,1,-2));
    addEdge(graph,newEdge(2,4,1));
    addEdge(graph,newEdge(3,2,-2));
    addEdge(graph,newEdge(3,5,-1));
    addEdge(graph,newEdge(4,6,3));
    addEdge(graph,newEdge(5,6,3));
    //
    printGraph(graph);
    // 最短路径
    printf("\n\n");
    bellmanFord(graph);
}
