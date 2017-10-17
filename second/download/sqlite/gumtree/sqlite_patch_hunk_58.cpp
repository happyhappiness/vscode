 **
 ** This file contains low-level memory allocation drivers for when
 ** SQLite will use the standard C-library malloc/realloc/free interface
 ** to obtain the memory it needs.
 **
 ** This file contains implementations of the low-level memory allocation
-** routines specified in the sqlite3_mem_methods object.  The content of
-** this file is only used if SQLITE_SYSTEM_MALLOC is defined.  The
-** SQLITE_SYSTEM_MALLOC macro is defined automatically if neither the
-** SQLITE_MEMDEBUG nor the SQLITE_WIN32_MALLOC macros are defined.  The
-** default configuration is to use memory allocation routines in this
-** file.
-**
-** C-preprocessor macro summary:
-**
-**    HAVE_MALLOC_USABLE_SIZE     The configure script sets this symbol if
-**                                the malloc_usable_size() interface exists
-**                                on the target platform.  Or, this symbol
-**                                can be set manually, if desired.
-**                                If an equivalent interface exists by
-**                                a different name, using a separate -D
-**                                option to rename it.
-**
-**    SQLITE_WITHOUT_ZONEMALLOC   Some older macs lack support for the zone
-**                                memory allocator.  Set this symbol to enable
-**                                building on older macs.
-**
-**    SQLITE_WITHOUT_MSIZE        Set this symbol to disable the use of
-**                                _msize() on windows systems.  This might
-**                                be necessary when compiling for Delphi,
-**                                for example.
+** routines specified in the sqlite3_mem_methods object.
+**
+** $Id: mem1.c,v 1.30 2009/03/23 04:33:33 danielk1977 Exp $
 */
 #include "sqliteInt.h"
 
 /*
 ** This version of the memory allocator is the default.  It is
 ** used when no other memory allocator is specified using compile-time
 ** macros.
 */
 #ifdef SQLITE_SYSTEM_MALLOC
-#if defined(__APPLE__) && !defined(SQLITE_WITHOUT_ZONEMALLOC)
-
-/*
-** Use the zone allocator available on apple products unless the
-** SQLITE_WITHOUT_ZONEMALLOC symbol is defined.
-*/
-#include <sys/sysctl.h>
-#include <malloc/malloc.h>
-#ifdef SQLITE_MIGHT_BE_SINGLE_CORE
-#include <libkern/OSAtomic.h>
-#endif /* SQLITE_MIGHT_BE_SINGLE_CORE */
-static malloc_zone_t* _sqliteZone_;
-#define SQLITE_MALLOC(x) malloc_zone_malloc(_sqliteZone_, (x))
-#define SQLITE_FREE(x) malloc_zone_free(_sqliteZone_, (x));
-#define SQLITE_REALLOC(x,y) malloc_zone_realloc(_sqliteZone_, (x), (y))
-#define SQLITE_MALLOCSIZE(x) \
-        (_sqliteZone_ ? _sqliteZone_->size(_sqliteZone_,x) : malloc_size(x))
-
-#else /* if not __APPLE__ */
-
-/*
-** Use standard C library malloc and free on non-Apple systems.  
-** Also used by Apple systems if SQLITE_WITHOUT_ZONEMALLOC is defined.
-*/
-#define SQLITE_MALLOC(x)             malloc(x)
-#define SQLITE_FREE(x)               free(x)
-#define SQLITE_REALLOC(x,y)          realloc((x),(y))
-
-/*
-** The malloc.h header file is needed for malloc_usable_size() function
-** on some systems (e.g. Linux).
-*/
-#if HAVE_MALLOC_H && HAVE_MALLOC_USABLE_SIZE
-#  define SQLITE_USE_MALLOC_H 1
-#  define SQLITE_USE_MALLOC_USABLE_SIZE 1
-/*
-** The MSVCRT has malloc_usable_size(), but it is called _msize().  The
-** use of _msize() is automatic, but can be disabled by compiling with
-** -DSQLITE_WITHOUT_MSIZE.  Using the _msize() function also requires
-** the malloc.h header file.
-*/
-#elif defined(_MSC_VER) && !defined(SQLITE_WITHOUT_MSIZE)
-#  define SQLITE_USE_MALLOC_H
-#  define SQLITE_USE_MSIZE
-#endif
-
-/*
-** Include the malloc.h header file, if necessary.  Also set define macro
-** SQLITE_MALLOCSIZE to the appropriate function name, which is _msize()
-** for MSVC and malloc_usable_size() for most other systems (e.g. Linux).
-** The memory size function can always be overridden manually by defining
-** the macro SQLITE_MALLOCSIZE to the desired function name.
-*/
-#if defined(SQLITE_USE_MALLOC_H)
-#  include <malloc.h>
-#  if defined(SQLITE_USE_MALLOC_USABLE_SIZE)
-#    if !defined(SQLITE_MALLOCSIZE)
-#      define SQLITE_MALLOCSIZE(x)   malloc_usable_size(x)
-#    endif
-#  elif defined(SQLITE_USE_MSIZE)
-#    if !defined(SQLITE_MALLOCSIZE)
-#      define SQLITE_MALLOCSIZE      _msize
-#    endif
-#  endif
-#endif /* defined(SQLITE_USE_MALLOC_H) */
-
-#endif /* __APPLE__ or not __APPLE__ */
 
 /*
 ** Like malloc(), but remember the size of the allocation
 ** so that we can find it later using sqlite3MemSize().
 **
 ** For this low-level routine, we are guaranteed that nByte>0 because
 ** cases of nByte<=0 will be intercepted and dealt with by higher level
 ** routines.
 */
 static void *sqlite3MemMalloc(int nByte){
-#ifdef SQLITE_MALLOCSIZE
-  void *p;
-  testcase( ROUND8(nByte)==nByte );
-  p = SQLITE_MALLOC( nByte );
-  if( p==0 ){
-    testcase( sqlite3GlobalConfig.xLog!=0 );
-    sqlite3_log(SQLITE_NOMEM, "failed to allocate %u bytes of memory", nByte);
-  }
-  return p;
-#else
   sqlite3_int64 *p;
   assert( nByte>0 );
-  testcase( ROUND8(nByte)!=nByte );
-  p = SQLITE_MALLOC( nByte+8 );
+  nByte = ROUND8(nByte);
+  p = malloc( nByte+8 );
   if( p ){
     p[0] = nByte;
     p++;
-  }else{
-    testcase( sqlite3GlobalConfig.xLog!=0 );
-    sqlite3_log(SQLITE_NOMEM, "failed to allocate %u bytes of memory", nByte);
   }
   return (void *)p;
-#endif
 }
 
 /*
 ** Like free() but works for allocations obtained from sqlite3MemMalloc()
 ** or sqlite3MemRealloc().
 **
 ** For this low-level routine, we already know that pPrior!=0 since
 ** cases where pPrior==0 will have been intecepted and dealt with
 ** by higher-level routines.
 */
 static void sqlite3MemFree(void *pPrior){
-#ifdef SQLITE_MALLOCSIZE
-  SQLITE_FREE(pPrior);
-#else
   sqlite3_int64 *p = (sqlite3_int64*)pPrior;
   assert( pPrior!=0 );
   p--;
-  SQLITE_FREE(p);
-#endif
-}
-
-/*
-** Report the allocated size of a prior return from xMalloc()
-** or xRealloc().
-*/
-static int sqlite3MemSize(void *pPrior){
-#ifdef SQLITE_MALLOCSIZE
-  assert( pPrior!=0 );
-  return (int)SQLITE_MALLOCSIZE(pPrior);
-#else
-  sqlite3_int64 *p;
-  assert( pPrior!=0 );
-  p = (sqlite3_int64*)pPrior;
-  p--;
-  return (int)p[0];
-#endif
+  free(p);
 }
 
 /*
 ** Like realloc().  Resize an allocation previously obtained from
 ** sqlite3MemMalloc().
 **
 ** For this low-level interface, we know that pPrior!=0.  Cases where
 ** pPrior==0 while have been intercepted by higher-level routine and
-** redirected to xMalloc.  Similarly, we know that nByte>0 because
+** redirected to xMalloc.  Similarly, we know that nByte>0 becauses
 ** cases where nByte<=0 will have been intercepted by higher-level
 ** routines and redirected to xFree.
 */
 static void *sqlite3MemRealloc(void *pPrior, int nByte){
-#ifdef SQLITE_MALLOCSIZE
-  void *p = SQLITE_REALLOC(pPrior, nByte);
-  if( p==0 ){
-    testcase( sqlite3GlobalConfig.xLog!=0 );
-    sqlite3_log(SQLITE_NOMEM,
-      "failed memory resize %u to %u bytes",
-      SQLITE_MALLOCSIZE(pPrior), nByte);
-  }
-  return p;
-#else
   sqlite3_int64 *p = (sqlite3_int64*)pPrior;
   assert( pPrior!=0 && nByte>0 );
-  assert( nByte==ROUND8(nByte) ); /* EV: R-46199-30249 */
+  nByte = ROUND8(nByte);
+  p = (sqlite3_int64*)pPrior;
   p--;
-  p = SQLITE_REALLOC(p, nByte+8 );
+  p = realloc(p, nByte+8 );
   if( p ){
     p[0] = nByte;
     p++;
-  }else{
-    testcase( sqlite3GlobalConfig.xLog!=0 );
-    sqlite3_log(SQLITE_NOMEM,
-      "failed memory resize %u to %u bytes",
-      sqlite3MemSize(pPrior), nByte);
   }
   return (void*)p;
-#endif
+}
+
+/*
+** Report the allocated size of a prior return from xMalloc()
+** or xRealloc().
+*/
+static int sqlite3MemSize(void *pPrior){
+  sqlite3_int64 *p;
+  if( pPrior==0 ) return 0;
+  p = (sqlite3_int64*)pPrior;
+  p--;
+  return (int)p[0];
 }
 
 /*
 ** Round up a request size to the next valid allocation size.
 */
 static int sqlite3MemRoundup(int n){
