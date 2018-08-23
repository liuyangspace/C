#include <stdlib.h>
#include <stdio.h>

/*
 * 冒泡排序
 * */

int compare(int ,int );
void swap(int * ,int *);
void sort(int[] ,int);

int main(){
    int list[]={1,24,3,55,856,9,559,9,5,232,433,6,66};
    int count = (sizeof list)/ sizeof(int);
    sort(list,count);
    //
    int j;
    for (j = 0; j < count; ++j) {
        printf("%d\t",list[j]);
    }
}

// 冒泡
void sort(int list[],int count){
    int i,j;
    for (j = 0; j < count-1; j++) {
        for (i = 0; i < count-1-j; i++) {
            if(compare(list[i],list[i+1])>0){
                swap(&list[i],&list[i+1]);
            }
        }
    }
}

// 比较
int compare(int left,int right){
    return left>right?1:(left<right?-1:0);
}

// 交换
void swap(int *left,int *right){
    int blank;
    blank = *left;
    *left = *right;
    *right = blank;
}