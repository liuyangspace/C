/*

#include <stdlib.h>

size_t 表示 sizeof 返回的无符号整形
ptrdiff_t 两个指针间的带符号差值

*/


void *calloc (size_t, size_t);
void *malloc (size_t);
void *realloc (void *, size_t);
void free (void *);
void abort (void);
void exit (int);