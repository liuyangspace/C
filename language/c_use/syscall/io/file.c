#include <stdio.h>
#include <fcntl.h>

main()  /* copy input to output */
{
    int fd;
    char *s;
    char *filePath = "/tmp/test/test.txt";
    //char *filePath = "E:\\myplace\\test\\c_test\\test.txt";
    fd = creat(filePath,0777);
    if(fd==-1){
        write(1,"can't create file!\n",19);
    }
    fd = open(filePath, O_RDWR, 0);//O_RDONLY,O_WRONLY,O_RDWR
    write(fd,"This is test!",13);
    //fd = open(filePath, O_RDONLY, 0);//O_RDONLY,O_WRONLY,_RDWR
    lseek(fd,0L,0);
    read(fd,s,10);
    write(1,s,10);
    write(1,"\n",1);
    write(1,"test",4);
    write(1,"\n",1);
    close(fd);
    unlink(filePath);
}

