#include <stdio.h>
#include <fcntl.h>

main()  /* copy input to output */
{
    char *s;
    read(0,s,8);
    write(1,s,8);
    write(1,"test",8);
}

char mygetc(){
    char s[1];
    read(0,s,1);
    return s[0];
}
