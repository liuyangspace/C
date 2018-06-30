/*

参考:
    <stdlib.h>
    <assert.h>
    <stdarg.h>
    <signal.h>
    <time.h>

*/

// 内存
void *calloc (size_t, size_t);
void *malloc (size_t);
void *realloc (void *, size_t);
void free (void *);
// 终止
void abort (void);
void exit (int);
int atexit (void (*)(void));
// 执行
int system (const char *);
char *getenv (const char *);
//
void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void qsort (void *, size_t, size_t, int (*)(const void *, const void *));
// assert
#define assert(e)       ((e) ? (void)0 : _assert(#e, __FILE__, __LINE__))
// signal
void signal(int, void (*handler)(int sig)));    // 处理异常（算术逻辑，中断，）
    /*
        handler:
            SIG_DFL     默认实现定义的行为
            SIG_IGN     忽略该信息
            其他        自定义行为，函数的参数sig为以下值 之一:
                            SIGABRT     程序异常终止，例如 abort() 引起的终止
                            SIGFPE      算术运算出错，例如 除数为0 或 溢出
                            SIGILL      非法函数映像，例如 非法指令
                            SIGINT      用于交互式目的信号,例如 中断
                            SIGSEGV     非法存储器访问, 例如 访问不存在的内存单元
                            SIGTERM     发送给程序的终止请求
    */
int raise (int sig);                            // 发送中断信号量，
// time
typedef long clock_t;
struct tm
{ /* A structure for storing the attributes of a broken-down time; (once
   * again, it isn't defined elsewhere, so no guard is necessary).  Note
   * that we are within the scope of <time.h> itself, so we must provide
   * the complete structure declaration here.
   */
  int  tm_sec;  	/* Seconds: 0-60 (to accommodate leap seconds) */
  int  tm_min;  	/* Minutes: 0-59 */
  int  tm_hour; 	/* Hours since midnight: 0-23 */
  int  tm_mday; 	/* Day of the month: 1-31 */
  int  tm_mon;  	/* Months *since* January: 0-11 */
  int  tm_year; 	/* Years since 1900 */
  int  tm_wday; 	/* Days since Sunday (0-6) */
  int  tm_yday; 	/* Days since Jan. 1: 0-365 */
  int  tm_isdst;	/* +1=Daylight Savings Time, 0=No DST, -1=unknown */
};
/* MS_DOS 时间类型 */
 /* Current versions of MSVC define time_t ambiguously, in terms of
  * one of the following unambiguous internal types:
  */
  typedef __int32 __time32_t;	/* unambiguous 32-bit time_t */
  typedef __int64 __time64_t;	/* unambiguous 64-bit time_t */

# if __MSVCRT_VERSION__ < __MSVCR80_DLL || defined _USE_32BIT_TIME_T
  /* From MSVCR80.DLL onwards, Microsoft have royally messed up the
   * definition of time_t; maintain POSIX consistency, (as MSVCRT.DLL
   * itself does), unless the user is explicitly using one of these
   * brain damaged DLL variants, and has not elected to retain the
   * 32-bit time_t representation.
   */
   typedef __time32_t time_t;

# else
  /* Microsoft's brain damaged default, from MSVCR80.DLL onwards.
   */
   typedef __time64_t time_t;
//
clock_t  clock(void);                   // 程序占用CPU时间
time_t time(time_t *);                  // 返回当前时间
double difftime(time_t, time_t);        // 计算时间差值（秒）
time_t mktime(struct tm *);             // 将 tm类型 转换为 time_t类型
char *asctime (const struct tm *);      // 输出 tm类型 为如 "Sun Jan 3 15:14:13 1988\n\0" 格式
char *ctime (const time_t *);           // 将 time_t 转换为当地时间
struct tm *gmtime (const time_t *);     // 将 time_t 转换为UTC(世界协调时间)
struct tm *localtime (const time_t *);  // 将 time_t 转换为当地时间
size_t strftime (char *s, size_t smax, const char *fmt, const struct tm *tp);  // 格式化时间
