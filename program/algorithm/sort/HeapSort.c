#include <stdlib.h>
#include <stdio.h>

/*
 * 堆排序
 *
 * */

// 元素
typedef struct Element {
    int key;
} Element;

//
void printSortList(Element *sortList[],int size){
    int i;
    printf("\nElementList:");
    for (i = 0; i < size; ++i) {
        printf(" (%d,%d) ",i,sortList[i]->key);
    }
}

// 构建局部 initList[rootIndex:lastIndex] 大根堆
void partHeap(Element *initList[],int rootIndex,int lastIndex){
    int child = rootIndex*2;
    Element *tmp = initList[rootIndex];
    while (child<=lastIndex){
        if(child+1<=lastIndex && initList[child+1]->key>initList[child]->key){ // 取孩子中最大值
            child = child+1;
        }
        if(tmp->key>initList[child]->key){ // 符和父亲大于孩子条件
            break;
        } else{
            initList[child/2] = initList[child]; // 孩子上滑至父亲位置
            child = child*2; // 比较孩子的孩子
        }
    }
    initList[child/2] = tmp; // 确定根节点下滑的位置
}

//
void swap(Element *initList[],int left,int right){
    Element *tmp = initList[left];
    initList[left] = initList[right];
    initList[right] = tmp;
}

//
void heapSort(Element *initList[],int lastIndex){
    int i;
    // 将待排序列 initList[1:lastIndex] 构建成大根堆
    for (i = lastIndex/2; i >0 ; --i) { // 从 所有非叶子节点自下而上构建大根堆
        partHeap(initList,i,lastIndex);
    }
    // 构建 有序序列
    for ( i = lastIndex; i >0 ; --i) {
        swap(initList,1,i); // 取出堆根(堆中最大值)，移至序列尾部相应位置
        partHeap(initList,1,i-1); // 余下节点重新构建大根堆
    }
}

int main(){
    Element a0 = {0};// 占位，不参与排序
    Element a1 = {26};
    Element a2 = {5};
    Element a3 = {77};
    Element a4 = {1};
    Element a5 = {61};
    Element a6 = {11};
    Element a7 = {59};
    Element a8 = {15};
    Element a9 = {48};
    Element a10 = {19};
    Element *initList[] = {&a0,&a1,&a2,&a3,&a4,&a5,&a6,&a7,&a8,&a9,&a10};
    printSortList(initList,11);
    heapSort(initList,10);
    printSortList(initList,11);
}
