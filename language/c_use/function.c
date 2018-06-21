#include <stdio.h>
/*
 *
 * */

int power(int m,int n);


main(){
    printf("%d",power(3,9));
}

int power(int m,int n){
    int result = m;
    int i;
    for (i = 1; i < n; ++i) {
        result = result*m;
    }
    return result;
}