//#define MINOUTPUT 
#define AMIN 192// N=16 264 | N=20 450 | N=32 1456
#define SHORTCODE
#define JOBS
#define LIST
#define STAB

#define MINN  3
#define MAXN 99
#define MINK  2
#define MAXK  9
#define MINT  3
#define MAXT  9

#define NOTSET 127
#define COUNTSTEP 100
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __UNIX__
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#else
#include <time.h>
#define DOSTIME
#endif

#ifdef __osf__ /* OSF auf den alphas */
#define time_factor CLK_TCK
#endif

#ifdef __sgi /* Silicon Graphics */
#define time_factor CLK_TCK 
#define SIGNED 
#endif

#ifdef sun /* Sun */
#define time_factor 60
#endif

#ifdef __hpux /* Hewlet Packard */
#define time_factor CLK_TCK
#endif

#ifdef __dec /* DEC */
#define time_factor 60
#endif

#ifdef __ultrix /* DEC */
#define time_factor 60
#endif        /* thanks to Gunnar */

#ifdef time_factor
#define UNIXTIME
#endif

#ifdef DOSTIME
#define time_factor CLK_TCK
#endif

#ifdef SHORTCODE
#define APP "scd"
#else
#define APP "lst"
#endif

typedef int SCHAR;
typedef unsigned long ULONG;
typedef unsigned int UINT;
#define INF 999
#define MAXNUB 64
 char opt_a[20],opt_d[20];
 int Asort_a;
int Asort_d;
int Dsort_a;
 int Dsort_d;
double start_t;
unsigned long minnum; 
