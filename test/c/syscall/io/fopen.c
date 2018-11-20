#include <fcntl.h>
#include <stdlib.h>

#undef NULL
#undef BUFSIZ

#define NULL      0
#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20 /* max #files open at once */
typedef struct _iobuf {
    int  cnt;       /* characters left */
    char *ptr;      /* next character position */
    char *base;     /* location of buffer */
    int  flag;      /* mode of file access */
    int  fd;        /* file descriptor */
} FILE;

enum _flags {
    _READ   = 01,   /* file open for reading */
    _WRITE  = 02,   /* file open for writing */
    _UNBUF  = 04,   /* file is unbuffered */
    _EOF    = 010,  /* EOF has occurred on this file */
    _ERR    = 020   /* error occurred on this file */
};

//extern FILE _iob[OPEN_MAX];

FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1 },
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flag & _EOF) != 0)
#define ferror(p)   ((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)
#define getc(p)   (--(p)->cnt >= 0 \
    ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
    ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar()   getc(stdin)
#define putcher(x)  putc((x), stdout)
FILE *fopen(char *name, char *mode);

main(){

    char *filePath = "/tmp/test/CMakeLists.txt";
    FILE *f ;
    f = fopen(filePath,"r");

    if(f==NULL){
        write(1,"fopen error!",12);
        return 0;
    }

    char *s;
    int bufSize = 16;
    s = (char *)malloc(bufSize);
    if(read(f->fd,s,bufSize)<bufSize){
        write(1,"read error!\n",12);
    }
    write(1,s,bufSize);

}

#define PERMS 0777    /* RW for owner, group, others */
FILE *fopen(char *name, char *mode)   {
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a'){
        write(1,"mode error :",12);
        write(1,mode,1);
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;        /* found free slot */
    if (fp >= _iob + OPEN_MAX)   /* no free slots */{
        write(1,"open file too many!",11);
        return NULL;
    }
    if (*mode == 'w'){
        fd = creat(name, PERMS);
        if(fd<1){
            write(1,"create file error!",11);
        }
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1){
            fd = creat(name, PERMS);
            if(fd<1){
                write(1,"create file error!",11);
            }
        }
        lseek(fd, 0L, 2);
    } else{
        fd = open(name, O_RDWR, 0);
        if(fd<1){
            write(1,"open file error!",11);
        }
    }
    if (fd == -1)         /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)   {
    int bufsize;
    if ((fp->flag&(_READ|_EOF)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)     /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;       /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}