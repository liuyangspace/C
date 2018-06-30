/*

UNIX系统调用

*/

int read(int fd, char *buf, int n); // 键盘读取变量的值
int write(int fd, char *buf, int n);

// <fcntl.h> <sys/file.h>
int open(char *name, int flags, int perms);
int creat(char *name, int perms);
int access (const char*, int);
int chsize (int, long );
int close (int);
int dup (int);
int dup2 (int, int);
int eof (int);
long filelength (int);
int isatty (int);
long lseek (int, long, int);
int read (int, void*, unsigned int);
int setmode (int, int);
int sopen (const char*, int, int, ...);
long tell (int);
int umask (int);
int unlink (const char*);
int write (int, const void*, unsigned int);