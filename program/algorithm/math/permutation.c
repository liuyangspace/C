#include <stdlib.h>
#include <stdio.h>

/*
 * 置换(排列)输出
 * */
void swap(char *left,char *right);
void copy(char *left,char *right,int count);

void perm(char * ,int,int,void (*handle)(char *,int));
void out(char *,int);

int count = 0;

int main(){
    char list[]={'a','b','c','d'};
    int count = (sizeof list)/ sizeof(char);
    //
    perm(list,0,count-1,out);
}

void perm(char list[],int left,int right,void (*handle)(char *,int)){
    if(left==right){
        handle(list,right);
    }
    int i;
    for (i = left; i <= right; ++i) {
        char tmp[right];
        copy(tmp,list,right);
        swap(&tmp[left],&tmp[i]);
        perm(tmp,left+1,right,handle);
    }
}
//
void out(char *list,int right){
    int j;
    count++;
    printf("%d\t(",count);
    for (j=0;j<=right;j++){
        printf("%c,",list[j]);
    }
    printf(")\n");
}
// 交换
void swap(char *left,char *right){
    char blank;
    blank = *left;
    *left = *right;
    *right = blank;
}
//
void copy(char *left,char *right,int count){
    int i;
    for (i=0;i<=count;i++){
        left[i]=right[i];
    }
}