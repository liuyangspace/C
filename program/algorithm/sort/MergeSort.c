#include <stdlib.h>
#include <stdio.h>

/*
 * 归并排序
 *
 * */

// 元素
typedef struct Element {
    int key;
} Element;

// 归并两个有序序列 initList[i,m] initList[m+1,n]
void merge(Element *initList[],Element *mergeList[],int i,int m,int n){
    int k=i,j=m+1;
    while (i<=m && j<=n){
        if(initList[i]->key > initList[j]->key){
            mergeList[k++] = initList[j++];
        } else{
            mergeList[k++] = initList[i++];
        }
    }
    if(i>m){
        while (j<=n){
            mergeList[k++] = initList[j++];
        }
    } else{
        while (i<=m){
            mergeList[k++] = initList[i++];
        }
    }
}

// 将序列initList[0:n]安每组size个元素分组，并做相邻两两归并
void mergeEach(Element *initList[],Element *mergeList[],int n,int size){
    int i;
    for (i = 0; i+2*size-1 < n ; i=i+size*2) {
        merge(initList,mergeList,i,i+size-1,i+2*size-1);
    }
    if(i+size-1<n){
        merge(initList,mergeList,i,i+size-1,n);
    } else{
        while (i<=n){
            mergeList[i] = initList[i];
            i++;
        }
    }
}

// 对 initList[0:n] 做 归并排序
void mergeSort(Element *initList[],int n){
    Element *mergeList[n];
    int size=1;
    while (size<n){
        mergeEach(initList,mergeList,n,size);
        size = size*2;
        mergeEach(mergeList,initList,n,size);
        size = size*2;
    }
}

void printSortList(Element *sortList[],int size){
    int i;
    printf("\nElementList:");
    for (i = 0; i < size; ++i) {
        printf(" (%d) ",sortList[i]->key);
    }
}

int main(){
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
    Element *initList[] = {&a1,&a2,&a3,&a4,&a5,&a6,&a7,&a8,&a9,&a10};
    printSortList(initList,10);
    mergeSort(initList,9);
    printSortList(initList,10);
}
