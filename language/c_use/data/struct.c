#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct point {
    int x;
    int y;
} typedef point ;

main(){
    point a,b={1,2};
    a.x=3;
    a.y=4;
    printf("(%d,%d)\n",a.x,a.y);
    printf("(%d,%d)\n",a.x,a.y);
    point *p;
    p = &a;
    printf("(%d,%d)\n",(*p).x,(*p).y);
    printf("(%d,%d)\n",p->x,p->y);
}


