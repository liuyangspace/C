#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/dir.h>

#define NAME_MAX   14  /* longest filename component; */ /* system-dependent */

typedef struct {       /* portable directory entry */
    long ino;                  /* inode number */
    char name[NAME_MAX+1];     /* name + '\0' terminator */
} Dirent;

typedef struct {       /* minimal DIR: no buffering, etc. */
    int fd;               /* file descriptor for the directory */
    Dirent d;             /* the directory entry */
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

char *name;
//struct stat {  /* inode information returned by stat */
//    dev_t     st_dev;      /* device of inode */
//    ino_t     st_ino;      /* inode number */
//    short     st_mode;     /* mode bits */
//    short     st_nlink;    /* number of links to file */
//    short     st_uid;      /* owners user id */
//    short     st_gid;      /* owners group id */
//    dev_t     st_rdev;     /* for special files */
//    off_t     st_size;     /* file size in characters */
//    time_t    st_atime;    /* time last accessed */
//    time_t    st_mtime;    /* time last modified */
//    time_t    st_ctime;    /* time originally created */
//};
struct stat stbuf;
/* st_mode */

#undef S_IFMT
#undef S_IFDIR
#undef S_IFCHR
#undef S_IFBLK
#undef S_IFREG
#define S_IFMT    0160000  /* type of file: */
#define S_IFDIR   0040000  /* directory */
#define S_IFCHR   0020000  /* character special */
#define S_IFBLK   0060000  /* block special */
#define S_IFREG   0010000  /* regular */

#ifndef DIRSIZ
#define DIRSIZ  14
#endif
struct direct {   /* directory entry */
    ino_t d_ino;           /* inode number */
    char  d_name[DIRSIZ];  /* long name does not have '\0' */
};


//int stat(char *, struct stat_my *);
void dirwalk(char *, void (*fcn)(char *));
//stat(name, &stbuf);
int fstat(int fd, struct stat *);
void fsize(char *name);

main(){
    fsize("/tmp/test/");
}

/* fsize:  print the name of file "name" */
void fsize(char *name)   {
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR){
        dirwalk(name, fsize);
    }
    printf("%8ld %s %o\n", stbuf.st_size, name,stbuf.st_mode&S_IFMT);
}

#define MAX_PATH 1024
/* dirwalk:  apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
            continue;    /* skip self and parent */
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

/* opendir:  open a directory for readdir calls */
DIR *opendir(char *dirname)   {
    int fd;
    struct stat stbuf;
    DIR *dp;
    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

Dirent *readdir(DIR *dp)   {
    struct direct dirbuf;  /* local directory structure */
    static Dirent  d;      /* return: portable structure */

    char s[1];
    printf("\nreaddir:%d\n",read(dp->fd, s, 1));

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) /* slot not in use */
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';  /* ensure termination */
        return &d;
    }
    return NULL;
}


void closedir(DIR *dp)   {
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}