#include <stdlib.h>
#include <stdio.h>

/*
 * 折半查找
 * */
int compare(int ,int );
int find(int,int * ,int,int);

int main(){
    int list[]={1,3,4,6,9,24,55,66,232,433,559,856};
    int count = (sizeof list)/ sizeof(int);
    //
    int j = find(55,list,0,count-1);
    printf("%d\t",j);
}

int find(int target,int list[],int left,int right){
    // 递归结束
    if(left>right){
        return 0;
    }
    //
    int middle = (left+right)/2;
    switch (compare(target,list[middle])){
        case -1:
            right=middle-1;
            break;
        case 0:
            return 1;
        case 1:
            left=middle+1;
            break;
    }
    return find(target,list,left,right);
}

// 比较
int compare(int left,int right){
    return left>right?1:(left<right?-1:0);
}