#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

void myprintf(char *,...);
void myscanf(char *,...);

/* word frequency count */
main()   {
    FILE *fp;

    char *filePath = "/tmp/test/CMakeLists.txt";
    char *model = "r";

    fp = fopen(filePath,model);

    if(fp==NULL){
        printf("open file failure！\n");
        return 0;
    }

    int c;
    while((c = getc(fp)) != EOF){
        putchar(c);
    }

    fclose(fp);
}
