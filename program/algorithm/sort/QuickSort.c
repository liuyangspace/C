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

void addElement(SortList *sortList,Element *element){
    sortList->list[sortList->size++]=element;
}

void swap(SortList *sortList,int left,int right){
    Element *tmp = sortList->list[left];
    sortList->list[left] = sortList->list[right];
    sortList->list[right] = tmp;
}

void printSortList(SortList *sortList){
    int i;
    printf("\nElementList");
    for (i = 0; i < sortList->size; ++i) {
        printf(" (%d,%d) ",sortList->list[i]->key,sortList->list[i]->value);
    }
}

void debugSortList(SortList *sortList,int left,int right){
    int i;
    printf("\nSortInfo: ");
    for (i = 0; i < sortList->size; ++i) {
        if(i==left) {
            printf("[");
        }
        printf(" %d ",sortList->list[i]->key);
        if(i==right) {
            printf("]");
        }
    }
}

void quickSort1(SortList *sortList,int left,int right){
    if(left>=right) return;
    debugSortList(sortList,left,right);
    int i = left,j = right+1;
    Element *element =  sortList->list[left];
    do{
        do{
            i++;
        }while (sortList->list[i]->key<element->key);
        do{
            j--;
        }while (sortList->list[j]->key>element->key);
        if(i<j) {
            swap(sortList,i,j);
        }
    }while (i<j);
    //
    swap(sortList,left,j);
    quickSort1(sortList,left,j-1);
    quickSort1(sortList,j+1,right);
}

void quickSort2(SortList *sortList,int left,int right){
    if(left>=right) return;
    debugSortList(sortList,left,right);
    int i = left,j = right;
    Element *element =  sortList->list[left];
    while (i<j){
        while (sortList->list[i]->key<element->key){
            i++;
        }
        while (sortList->list[j]->key>element->key){
            j--;
        }
        if(i<j) {
            swap(sortList,i,j);
        }
    }
    //
    quickSort2(sortList,left,i-1);
    quickSort2(sortList,i+1,right);
}

int main(){
    SortList *sortList = newSortList();
    addElement(sortList,newElement(26,0));
    addElement(sortList,newElement(5,0));
    addElement(sortList,newElement(37,0));
    addElement(sortList,newElement(1,0));
    addElement(sortList,newElement(61,0));
    addElement(sortList,newElement(11,0));
    addElement(sortList,newElement(59,0));
    addElement(sortList,newElement(15,0));
    addElement(sortList,newElement(48,0));
    addElement(sortList,newElement(19,0));
    printSortList(sortList);
    printf("\nquickSort1");
    quickSort1(sortList,0,sortList->size-1);
    printSortList(sortList);

    //
    SortList *sortList2 = newSortList();
    addElement(sortList2,newElement(26,0));
    addElement(sortList2,newElement(5,0));
    addElement(sortList2,newElement(37,0));
    addElement(sortList2,newElement(1,0));
    addElement(sortList2,newElement(61,0));
    addElement(sortList2,newElement(11,0));
    addElement(sortList2,newElement(59,0));
    addElement(sortList2,newElement(15,0));
    addElement(sortList2,newElement(48,0));
    addElement(sortList2,newElement(19,0));
    printf("\nquickSort2");
    quickSort2(sortList2,0,sortList2->size-1);
    printSortList(sortList2);
}
