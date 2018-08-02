#include <stdlib.h>
#include <stdio.h>

/*
 * 多项式
 * */

#define MAX_DEGREE 101

// 存储结构 线性表
typedef struct polynamial {
    int degree; // 指数
    float coef; // 系数
    struct polynamial *next; //
} polynamial; // 顺序多项式

// 多项式加法
polynamial polynamialAdd(polynamial a,polynamial b){
    polynamial result = {0,0,NULL} ;
    polynamial *aIndex=&a,*bIndex=&b;
    polynamial *tmpIndex;
    tmpIndex=&result;
    do{
        polynamial *tmp = malloc(sizeof(polynamial));
        if(!aIndex){
            tmp->degree=bIndex->degree;
            tmp->coef=bIndex->coef;
            tmp->next=NULL;
            bIndex=bIndex->next;
        } else if(!bIndex){
            tmp->degree=aIndex->degree;
            tmp->coef=aIndex->coef;
            tmp->next=NULL;
            aIndex=aIndex->next;
        } else if(aIndex->degree<bIndex->degree){
            tmp->degree=aIndex->degree;
            tmp->coef=aIndex->coef;
            tmp->next=NULL;
            aIndex=aIndex->next;
        } else if(aIndex->degree==bIndex->degree){
            tmp->degree=bIndex->degree;
            tmp->coef=aIndex->coef+bIndex->coef;
            tmp->next=NULL;
            aIndex=aIndex->next;
            bIndex=bIndex->next;
        } else{
            tmp->degree=bIndex->degree;
            tmp->coef=bIndex->coef;
            tmp->next=NULL;
            bIndex=bIndex->next;
        }
        tmpIndex->next=tmp;
        tmpIndex=tmpIndex->next;
    }while (aIndex || bIndex);
    return result;
}

// 打印 多项式
void polynamialPrint(polynamial a){
    int i=0;
    polynamial *tmp = &a;
    do{
        if(i!=0) printf(" + ");
        printf("%fx^%d",tmp->coef,tmp->degree);
        i++;
        tmp=tmp->next;
    }while (tmp);
    printf("\n");
}

int main(){
    //
    polynamial polynamialA1 = {1,2,NULL};
    polynamial polynamialA2 = {2,4,NULL};
    polynamialA1.next = & polynamialA2;
    polynamialPrint(polynamialA1);
    //
    polynamial polynamialA3 = {2,3,NULL};
    polynamial polynamialA4 = {3,5,NULL};
    polynamialA3.next = & polynamialA4;
    polynamialPrint(polynamialA3);
    //
    polynamialPrint(polynamialAdd(polynamialA1,polynamialA3));

}
