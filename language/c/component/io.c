/*

#include <stdio.h>

*/

// 单个字符 IO
int getchar (void); //（从 系统输入[标准输入/文件重定向/系统管道 等]）获取单个字符
int putchar(int);   // 输出单个字符（到系统标准输出）
// 格式化 IO
int scanf (const char *, ...);
int fscanf (FILE *, const char *, ...);     //从文件格式化读
int sscanf (const char *, const char *, ...);

int fprintf (FILE *, const char *, ...);    //从文件格式化写
int printf (const char *, ...);
int sprintf (char *, const char *, ...);
int vfprintf (FILE *, const char *, __VALIST);
int vprintf (const char *, __VALIST);
int vsprintf (char *, const char *, __VALIST);
// file IO
typedef struct _iobuf
{
  char	*_ptr;
  int	 _cnt;
  char	*_base;
  int	 _flag;
  int	 _file;
  int	 _charbuf;
  int	 _bufsiz;
  char	*_tmpfname;
} FILE;
#define stdin       // 系统标准输入
#define stdout      // 系统标准输出
#define stderr      // 系统标准错误
// 打开
FILE * fopen (const char *filename, const char *mode);  // 打开文件，文件名最长为 FILENAME_MAX 个字符
FILE * freopen (const char *filename, const char *mode, FILE *stream); // 打开文件，并关联指定流
// 读写
int getc (FILE *);          //从文件读单个字符
int getchar (void);
char * fgets (char *, int, FILE *); //从文件读多个字符
char * gets (char *);
int ungetc (int, FILE *);

int putc (int, FILE *);     //从文件写单个字符
int puts (const char *);
int putchar(int);
int fputs (const char *, FILE *);

size_t fread (void *, size_t, size_t, FILE *);//size_t 为sizeof返回的无符号整型
size_t fwrite (const void *, size_t, size_t, FILE *);
//
int fseek (FILE *, long, int);  //设置文件操作指针
long ftell (FILE *);            //返回文件操作指针
void rewind (FILE *);           //重置文件操作指针
int fgetpos (FILE *, fpos_t *);         //记录文件操作指针于fpos_t中
int fsetpos (FILE *, const fpos_t *);   //
int fflush (FILE *stream);
int fclose (FILE *stream);  //关闭系统文件资源，系统同时打开文件数最大为 FOPEN_MAX 个
//
int remove (const char *);  //删除
int rename (const char *, const char *);    //重命名
FILE * tmpfile (void);      //创建一个临时文件，在 fclose 时自动删除
char * tmpnam (char *);     //生成一个与已打开文件不同的文件名，

int setvbuf (FILE *, char *, int, size_t);  //设置缓冲模式
void setbuf (FILE *, char *);               //设置缓冲模式

//
void clearerr (FILE *);
int ferror (FILE *stream);
int feof (FILE *stream);
void perror (const char *);