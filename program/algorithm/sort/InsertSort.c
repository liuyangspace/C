#include <stdlib.h>
#include <stdio.h>

/*
 * 插入排序
 *
 * */

// 元素
typedef struct Element {
    int key; // 前驱
    int value;
} Element;

typedef struct SortList {
    int size; // 前驱
    Element *list[100];
} SortList;

Element *newElement(int key,int value){
    Element *element = (Element *)malloc(sizeof(Element));
    if(element==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    element->key=key;
    element->value=value;
    return element;
}

SortList *newSortList(){
    SortList *sortList = (SortList *)malloc(sizeof(SortList));
    if(sortList==NULL){
        fprintf(stderr,"No more Memory!");
        exit(-1);
    }
    sortList->size=0;
    return sortList;
}

void insertSort(SortList *sortList,Element *e){
    sortList->list[sortList->size]=e;
    int i=sortList->size;
    while(i>0 && sortList->list[i]->key<sortList->list[i-1]->key){
        Element *tmp = sortList->list[i];
        sortList->list[i] = sortList->list[i-1];
        sortList->list[i-1] = tmp;
        i--;
    }
    sortList->size++;
}

void printSortList(SortList *sortList){
    int i;
    for (i = 0; i < sortList->size; ++i) {
        printf(" (%d,%d) ",sortList->list[i]->key,sortList->list[i]->value);
    }
}

int main(){
    SortList *sortList = newSortList();
    insertSort(sortList,newElement(5,0));
    insertSort(sortList,newElement(4,0));
    insertSort(sortList,newElement(3,0));
    insertSort(sortList,newElement(2,0));
    insertSort(sortList,newElement(1,0));
    printSortList(sortList);
}
