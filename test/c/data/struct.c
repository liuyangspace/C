#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct point {
    int x;
    int y;
} typedef point ;

point list[3] = {
        {1,1},
        {2,3},
        {3,3},
};

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

    printf("List:\n");
    int j;
    printf("%d\n",sizeof a);
    printf("%d\n",sizeof list);
    for(j=0;j< sizeof list ;j++) {
        printf("(%d,%d)\n",list[j].x,list[j].y);
    }
}


