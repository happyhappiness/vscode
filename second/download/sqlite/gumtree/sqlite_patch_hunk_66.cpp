 /*
 ** The winFile structure is a subclass of sqlite3_file* specific to the win32
 ** portability layer.
 */
 typedef struct winFile winFile;
 struct winFile {
-  const sqlite3_io_methods *pMethod; /*** Must be first ***/
-  sqlite3_vfs *pVfs;      /* The VFS used to open this file */
+  const sqlite3_io_methods *pMethod;/* Must be first */
   HANDLE h;               /* Handle for accessing the file */
-  u8 locktype;            /* Type of lock currently held on this file */
+  unsigned char locktype; /* Type of lock currently held on this file */
   short sharedLockByte;   /* Randomly chosen byte used as a shared lock */
-  u8 ctrlFlags;           /* Flags.  See WINFILE_* below */
   DWORD lastErrno;        /* The Windows errno from the last I/O error */
-#ifndef SQLITE_OMIT_WAL
-  winShm *pShm;           /* Instance of shared memory on this file */
-#endif
-  const char *zPath;      /* Full pathname of this file */
-  int szChunk;            /* Chunk size configured by FCNTL_CHUNK_SIZE */
+  DWORD sectorSize;       /* Sector size of the device file is on */
 #if SQLITE_OS_WINCE
-  LPWSTR zDeleteOnClose;  /* Name of file to delete when closing */
-  HANDLE hMutex;          /* Mutex used to control access to shared lock */
+  WCHAR *zDeleteOnClose;  /* Name of file to delete when closing */
+  HANDLE hMutex;          /* Mutex used to control access to shared lock */  
   HANDLE hShared;         /* Shared memory segment used for locking */
   winceLock local;        /* Locks obtained by this instance of winFile */
   winceLock *shared;      /* Global shared lock memory for the file  */
 #endif
-#if SQLITE_MAX_MMAP_SIZE>0
-  int nFetchOut;                /* Number of outstanding xFetch references */
-  HANDLE hMap;                  /* Handle for accessing memory mapping */
-  void *pMapRegion;             /* Area memory mapped */
-  sqlite3_int64 mmapSize;       /* Usable size of mapped region */
-  sqlite3_int64 mmapSizeActual; /* Actual size of mapped region */
-  sqlite3_int64 mmapSizeMax;    /* Configured FCNTL_MMAP_SIZE value */
-#endif
 };
 
 /*
-** The winVfsAppData structure is used for the pAppData member for all of the
-** Win32 VFS variants.
+** Forward prototypes.
 */
-typedef struct winVfsAppData winVfsAppData;
-struct winVfsAppData {
-  const sqlite3_io_methods *pMethod; /* The file I/O methods to use. */
-  void *pAppData;                    /* The extra pAppData, if any. */
-  BOOL bNoLock;                      /* Non-zero if locking is disabled. */
-};
+static int getSectorSize(
+    sqlite3_vfs *pVfs,
+    const char *zRelative     /* UTF-8 file name */
+);
 
 /*
-** Allowed values for winFile.ctrlFlags
+** The following variable is (normally) set once and never changes
+** thereafter.  It records whether the operating system is Win95
+** or WinNT.
+**
+** 0:   Operating system unknown.
+** 1:   Operating system is Win95.
+** 2:   Operating system is WinNT.
+**
+** In order to facilitate testing on a WinNT system, the test fixture
+** can manually set this value to 1 to emulate Win98 behavior.
 */
-#define WINFILE_RDONLY          0x02   /* Connection is read only */
-#define WINFILE_PERSIST_WAL     0x04   /* Persistent WAL mode */
-#define WINFILE_PSOW            0x10   /* SQLITE_IOCAP_POWERSAFE_OVERWRITE */
-
-/*
- * The size of the buffer used by sqlite3_win32_write_debug().
- */
-#ifndef SQLITE_WIN32_DBG_BUF_SIZE
-#  define SQLITE_WIN32_DBG_BUF_SIZE   ((int)(4096-sizeof(DWORD)))
-#endif
-
-/*
- * The value used with sqlite3_win32_set_directory() to specify that
- * the data directory should be changed.
- */
-#ifndef SQLITE_WIN32_DATA_DIRECTORY_TYPE
-#  define SQLITE_WIN32_DATA_DIRECTORY_TYPE (1)
+#ifdef SQLITE_TEST
+int sqlite3_os_type = 0;
+#else
+static int sqlite3_os_type = 0;
 #endif
 
 /*
- * The value used with sqlite3_win32_set_directory() to specify that
- * the temporary directory should be changed.
- */
-#ifndef SQLITE_WIN32_TEMP_DIRECTORY_TYPE
-#  define SQLITE_WIN32_TEMP_DIRECTORY_TYPE (2)
-#endif
+** Return true (non-zero) if we are running under WinNT, Win2K, WinXP,
+** or WinCE.  Return false (zero) for Win95, Win98, or WinME.
+**
+** Here is an interesting observation:  Win95, Win98, and WinME lack
+** the LockFileEx() API.  But we can still statically link against that
+** API as long as we don't call it when running Win95/98/ME.  A call to
+** this routine is used to determine if the host is Win95/98/ME or
+** WinNT/2K/XP so that we will know whether or not we can safely call
+** the LockFileEx() API.
+*/
+#if SQLITE_OS_WINCE
+# define isNT()  (1)
+#else
+  static int isNT(void){
+    if( sqlite3_os_type==0 ){
+      OSVERSIONINFO sInfo;
+      sInfo.dwOSVersionInfoSize = sizeof(sInfo);
+      GetVersionEx(&sInfo);
+      sqlite3_os_type = sInfo.dwPlatformId==VER_PLATFORM_WIN32_NT ? 2 : 1;
+    }
+    return sqlite3_os_type==2;
+  }
+#endif /* SQLITE_OS_WINCE */
 
 /*
- * If compiled with SQLITE_WIN32_MALLOC on Windows, we will use the
- * various Win32 API heap functions instead of our own.
- */
-#ifdef SQLITE_WIN32_MALLOC
-
-/*
- * If this is non-zero, an isolated heap will be created by the native Win32
- * allocator subsystem; otherwise, the default process heap will be used.  This
- * setting has no effect when compiling for WinRT.  By default, this is enabled
- * and an isolated heap will be created to store all allocated data.
- *
- ******************************************************************************
- * WARNING: It is important to note that when this setting is non-zero and the
- *          winMemShutdown function is called (e.g. by the sqlite3_shutdown
- *          function), all data that was allocated using the isolated heap will
- *          be freed immediately and any attempt to access any of that freed
- *          data will almost certainly result in an immediate access violation.
- ******************************************************************************
- */
-#ifndef SQLITE_WIN32_HEAP_CREATE
-#  define SQLITE_WIN32_HEAP_CREATE        (TRUE)
-#endif
+** Convert a UTF-8 string to microsoft unicode (UTF-16?). 
+**
+** Space to hold the returned string is obtained from malloc.
+*/
+static WCHAR *utf8ToUnicode(const char *zFilename){
+  int nChar;
+  WCHAR *zWideFilename;
 
-/*
- * This is the maximum possible initial size of the Win32-specific heap, in
- * bytes.
- */
-#ifndef SQLITE_WIN32_HEAP_MAX_INIT_SIZE
-#  define SQLITE_WIN32_HEAP_MAX_INIT_SIZE (4294967295U)
-#endif
+  nChar = MultiByteToWideChar(CP_UTF8, 0, zFilename, -1, NULL, 0);
+  zWideFilename = malloc( nChar*sizeof(zWideFilename[0]) );
+  if( zWideFilename==0 ){
+    return 0;
+  }
+  nChar = MultiByteToWideChar(CP_UTF8, 0, zFilename, -1, zWideFilename, nChar);
+  if( nChar==0 ){
+    free(zWideFilename);
+    zWideFilename = 0;
+  }
+  return zWideFilename;
+}
 
 /*
- * This is the extra space for the initial size of the Win32-specific heap,
- * in bytes.  This value may be zero.
- */
-#ifndef SQLITE_WIN32_HEAP_INIT_EXTRA
-#  define SQLITE_WIN32_HEAP_INIT_EXTRA  (4194304)
-#endif
+** Convert microsoft unicode to UTF-8.  Space to hold the returned string is
+** obtained from malloc().
+*/
+static char *unicodeToUtf8(const WCHAR *zWideFilename){
+  int nByte;
+  char *zFilename;
 
-/*
- * Calculate the maximum legal cache size, in pages, based on the maximum
- * possible initial heap size and the default page size, setting aside the
- * needed extra space.
- */
-#ifndef SQLITE_WIN32_MAX_CACHE_SIZE
-#  define SQLITE_WIN32_MAX_CACHE_SIZE   (((SQLITE_WIN32_HEAP_MAX_INIT_SIZE) - \
-                                          (SQLITE_WIN32_HEAP_INIT_EXTRA)) / \
-                                         (SQLITE_DEFAULT_PAGE_SIZE))
-#endif
+  nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, 0, 0, 0, 0);
+  zFilename = malloc( nByte );
+  if( zFilename==0 ){
+    return 0;
+  }
+  nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, zFilename, nByte,
+                              0, 0);
+  if( nByte == 0 ){
+    free(zFilename);
+    zFilename = 0;
+  }
+  return zFilename;
+}
 
 /*
- * This is cache size used in the calculation of the initial size of the
- * Win32-specific heap.  It cannot be negative.
- */
-#ifndef SQLITE_WIN32_CACHE_SIZE
-#  if SQLITE_DEFAULT_CACHE_SIZE>=0
-#    define SQLITE_WIN32_CACHE_SIZE     (SQLITE_DEFAULT_CACHE_SIZE)
-#  else
-#    define SQLITE_WIN32_CACHE_SIZE     (-(SQLITE_DEFAULT_CACHE_SIZE))
-#  endif
-#endif
+** Convert an ansi string to microsoft unicode, based on the
+** current codepage settings for file apis.
+** 
+** Space to hold the returned string is obtained
+** from malloc.
+*/
+static WCHAR *mbcsToUnicode(const char *zFilename){
+  int nByte;
+  WCHAR *zMbcsFilename;
+  int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
 
-/*
- * Make sure that the calculated cache size, in pages, cannot cause the
- * initial size of the Win32-specific heap to exceed the maximum amount
- * of memory that can be specified in the call to HeapCreate.
- */
-#if SQLITE_WIN32_CACHE_SIZE>SQLITE_WIN32_MAX_CACHE_SIZE
-#  undef SQLITE_WIN32_CACHE_SIZE
-#  define SQLITE_WIN32_CACHE_SIZE       (2000)
-#endif
+  nByte = MultiByteToWideChar(codepage, 0, zFilename, -1, NULL,0)*sizeof(WCHAR);
+  zMbcsFilename = malloc( nByte*sizeof(zMbcsFilename[0]) );
+  if( zMbcsFilename==0 ){
+    return 0;
+  }
+  nByte = MultiByteToWideChar(codepage, 0, zFilename, -1, zMbcsFilename, nByte);
+  if( nByte==0 ){
+    free(zMbcsFilename);
+    zMbcsFilename = 0;
+  }
+  return zMbcsFilename;
+}
 
 /*
- * The initial size of the Win32-specific heap.  This value may be zero.
- */
-#ifndef SQLITE_WIN32_HEAP_INIT_SIZE
-#  define SQLITE_WIN32_HEAP_INIT_SIZE   ((SQLITE_WIN32_CACHE_SIZE) * \
-                                         (SQLITE_DEFAULT_PAGE_SIZE) + \
-                                         (SQLITE_WIN32_HEAP_INIT_EXTRA))
-#endif
+** Convert microsoft unicode to multibyte character string, based on the
+** user's Ansi codepage.
+**
+** Space to hold the returned string is obtained from
+** malloc().
+*/
+static char *unicodeToMbcs(const WCHAR *zWideFilename){
+  int nByte;
+  char *zFilename;
+  int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
 
-/*
- * The maximum size of the Win32-specific heap.  This value may be zero.
- */
-#ifndef SQLITE_WIN32_HEAP_MAX_SIZE
-#  define SQLITE_WIN32_HEAP_MAX_SIZE    (0)
-#endif
+  nByte = WideCharToMultiByte(codepage, 0, zWideFilename, -1, 0, 0, 0, 0);
+  zFilename = malloc( nByte );
+  if( zFilename==0 ){
+    return 0;
+  }
+  nByte = WideCharToMultiByte(codepage, 0, zWideFilename, -1, zFilename, nByte,
+                              0, 0);
+  if( nByte == 0 ){
+    free(zFilename);
+    zFilename = 0;
+  }
+  return zFilename;
+}
 
 /*
- * The extra flags to use in calls to the Win32 heap APIs.  This value may be
- * zero for the default behavior.
- */
-#ifndef SQLITE_WIN32_HEAP_FLAGS
-#  define SQLITE_WIN32_HEAP_FLAGS       (0)
-#endif
+** Convert multibyte character string to UTF-8.  Space to hold the
+** returned string is obtained from malloc().
+*/
+char *sqlite3_win32_mbcs_to_utf8(const char *zFilename){
+  char *zFilenameUtf8;
+  WCHAR *zTmpWide;
 
+  zTmpWide = mbcsToUnicode(zFilename);
+  if( zTmpWide==0 ){
+    return 0;
+  }
+  zFilenameUtf8 = unicodeToUtf8(zTmpWide);
+  free(zTmpWide);
+  return zFilenameUtf8;
+}
 
 /*
-** The winMemData structure stores information required by the Win32-specific
-** sqlite3_mem_methods implementation.
+** Convert UTF-8 to multibyte character string.  Space to hold the 
+** returned string is obtained from malloc().
 */
-typedef struct winMemData winMemData;
-struct winMemData {
-#ifndef NDEBUG
-  u32 magic1;   /* Magic number to detect structure corruption. */
-#endif
-  HANDLE hHeap; /* The handle to our heap. */
-  BOOL bOwned;  /* Do we own the heap (i.e. destroy it on shutdown)? */
-#ifndef NDEBUG
-  u32 magic2;   /* Magic number to detect structure corruption. */
-#endif
-};
+static char *utf8ToMbcs(const char *zFilename){
+  char *zFilenameMbcs;
+  WCHAR *zTmpWide;
 
-#ifndef NDEBUG
-#define WINMEM_MAGIC1     0x42b2830b
-#define WINMEM_MAGIC2     0xbd4d7cf4
-#endif
+  zTmpWide = utf8ToUnicode(zFilename);
+  if( zTmpWide==0 ){
+    return 0;
+  }
+  zFilenameMbcs = unicodeToMbcs(zTmpWide);
+  free(zTmpWide);
+  return zFilenameMbcs;
+}
 
-static struct winMemData win_mem_data = {
-#ifndef NDEBUG
-  WINMEM_MAGIC1,
-#endif
-  NULL, FALSE
-#ifndef NDEBUG
-  ,WINMEM_MAGIC2
-#endif
-};
+#if SQLITE_OS_WINCE
+/*************************************************************************
+** This section contains code for WinCE only.
+*/
+/*
+** WindowsCE does not have a localtime() function.  So create a
+** substitute.
+*/
+#include <time.h>
+struct tm *__cdecl localtime(const time_t *t)
+{
+  static struct tm y;
+  FILETIME uTm, lTm;
+  SYSTEMTIME pTm;
+  sqlite3_int64 t64;
+  t64 = *t;
+  t64 = (t64 + 11644473600)*10000000;
+  uTm.dwLowDateTime = t64 & 0xFFFFFFFF;
+  uTm.dwHighDateTime= t64 >> 32;
+  FileTimeToLocalFileTime(&uTm,&lTm);
+  FileTimeToSystemTime(&lTm,&pTm);
+  y.tm_year = pTm.wYear - 1900;
+  y.tm_mon = pTm.wMonth - 1;
+  y.tm_wday = pTm.wDayOfWeek;
+  y.tm_mday = pTm.wDay;
+  y.tm_hour = pTm.wHour;
+  y.tm_min = pTm.wMinute;
+  y.tm_sec = pTm.wSecond;
+  return &y;
+}
 
-#ifndef NDEBUG
-#define winMemAssertMagic1() assert( win_mem_data.magic1==WINMEM_MAGIC1 )
-#define winMemAssertMagic2() assert( win_mem_data.magic2==WINMEM_MAGIC2 )
-#define winMemAssertMagic()  winMemAssertMagic1(); winMemAssertMagic2();
-#else
-#define winMemAssertMagic()
-#endif
+/* This will never be called, but defined to make the code compile */
+#define GetTempPathA(a,b)
 
-#define winMemGetDataPtr()  &win_mem_data
-#define winMemGetHeap()     win_mem_data.hHeap
-#define winMemGetOwned()    win_mem_data.bOwned
-
-static void *winMemMalloc(int nBytes);
-static void winMemFree(void *pPrior);
-static void *winMemRealloc(void *pPrior, int nBytes);
-static int winMemSize(void *p);
-static int winMemRoundup(int n);
-static int winMemInit(void *pAppData);
-static void winMemShutdown(void *pAppData);
+#define LockFile(a,b,c,d,e)       winceLockFile(&a, b, c, d, e)
+#define UnlockFile(a,b,c,d,e)     winceUnlockFile(&a, b, c, d, e)
+#define LockFileEx(a,b,c,d,e,f)   winceLockFileEx(&a, b, c, d, e, f)
 
-const sqlite3_mem_methods *sqlite3MemGetWin32(void);
-#endif /* SQLITE_WIN32_MALLOC */
+#define HANDLE_TO_WINFILE(a) (winFile*)&((char*)a)[-offsetof(winFile,h)]
 
 /*
-** The following variable is (normally) set once and never changes
-** thereafter.  It records whether the operating system is Win9x
-** or WinNT.
-**
-** 0:   Operating system unknown.
-** 1:   Operating system is Win9x.
-** 2:   Operating system is WinNT.
-**
-** In order to facilitate testing on a WinNT system, the test fixture
-** can manually set this value to 1 to emulate Win98 behavior.
+** Acquire a lock on the handle h
 */
-#ifdef SQLITE_TEST
-LONG SQLITE_WIN32_VOLATILE sqlite3_os_type = 0;
-#else
-static LONG SQLITE_WIN32_VOLATILE sqlite3_os_type = 0;
-#endif
-
-#ifndef SYSCALL
-#  define SYSCALL sqlite3_syscall_ptr
-#endif
-
+static void winceMutexAcquire(HANDLE h){
+   DWORD dwErr;
+   do {
+     dwErr = WaitForSingleObject(h, INFINITE);
+   } while (dwErr != WAIT_OBJECT_0 && dwErr != WAIT_ABANDONED);
+}
 /*
-** This function is not available on Windows CE or WinRT.
- */
-
-#if SQLITE_OS_WINCE || SQLITE_OS_WINRT
-#  define osAreFileApisANSI()       1
-#endif
+** Release a lock acquired by winceMutexAcquire()
+*/
+#define winceMutexRelease(h) ReleaseMutex(h)
 
 /*
-** Many system calls are accessed through pointer-to-functions so that
-** they may be overridden at runtime to facilitate fault injection during
-** testing and sandboxing.  The following array holds the names and pointers
-** to all overrideable system calls.
-*/
-static struct win_syscall {
-  const char *zName;            /* Name of the system call */
-  sqlite3_syscall_ptr pCurrent; /* Current value of the system call */
-  sqlite3_syscall_ptr pDefault; /* Default value */
-} aSyscall[] = {
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
-  { "AreFileApisANSI",         (SYSCALL)AreFileApisANSI,         0 },
-#else
-  { "AreFileApisANSI",         (SYSCALL)0,                       0 },
-#endif
-
-#ifndef osAreFileApisANSI
-#define osAreFileApisANSI ((BOOL(WINAPI*)(VOID))aSyscall[0].pCurrent)
-#endif
+** Create the mutex and shared memory used for locking in the file
+** descriptor pFile
+*/
+static BOOL winceCreateLock(const char *zFilename, winFile *pFile){
+  WCHAR *zTok;
+  WCHAR *zName = utf8ToUnicode(zFilename);
+  BOOL bInit = TRUE;
 
-#if SQLITE_OS_WINCE && defined(SQLITE_WIN32_HAS_WIDE)
-  { "CharLowerW",              (SYSCALL)CharLowerW,              0 },
-#else
-  { "CharLowerW",              (SYSCALL)0,                       0 },
-#endif
+  /* Initialize the local lockdata */
+  ZeroMemory(&pFile->local, sizeof(pFile->local));
 
-#define osCharLowerW ((LPWSTR(WINAPI*)(LPWSTR))aSyscall[1].pCurrent)
+  /* Replace the backslashes from the filename and lowercase it
+  ** to derive a mutex name. */
+  zTok = CharLowerW(zName);
+  for (;*zTok;zTok++){
+    if (*zTok == '\\') *zTok = '_';
+  }
 
-#if SQLITE_OS_WINCE && defined(SQLITE_WIN32_HAS_WIDE)
-  { "CharUpperW",              (SYSCALL)CharUpperW,              0 },
-#else
-  { "CharUpperW",              (SYSCALL)0,                       0 },
-#endif
+  /* Create/open the named mutex */
+  pFile->hMutex = CreateMutexW(NULL, FALSE, zName);
+  if (!pFile->hMutex){
+    pFile->lastErrno = GetLastError();
+    free(zName);
+    return FALSE;
+  }
 
-#define osCharUpperW ((LPWSTR(WINAPI*)(LPWSTR))aSyscall[2].pCurrent)
-
-  { "CloseHandle",             (SYSCALL)CloseHandle,             0 },
-
-#define osCloseHandle ((BOOL(WINAPI*)(HANDLE))aSyscall[3].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "CreateFileA",             (SYSCALL)CreateFileA,             0 },
-#else
-  { "CreateFileA",             (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateFileA ((HANDLE(WINAPI*)(LPCSTR,DWORD,DWORD, \
-        LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE))aSyscall[4].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "CreateFileW",             (SYSCALL)CreateFileW,             0 },
-#else
-  { "CreateFileW",             (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateFileW ((HANDLE(WINAPI*)(LPCWSTR,DWORD,DWORD, \
-        LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE))aSyscall[5].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_ANSI) && \
-        (!defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0) && \
-        SQLITE_WIN32_CREATEFILEMAPPINGA
-  { "CreateFileMappingA",      (SYSCALL)CreateFileMappingA,      0 },
-#else
-  { "CreateFileMappingA",      (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateFileMappingA ((HANDLE(WINAPI*)(HANDLE,LPSECURITY_ATTRIBUTES, \
-        DWORD,DWORD,DWORD,LPCSTR))aSyscall[6].pCurrent)
-
-#if SQLITE_OS_WINCE || (!SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE) && \
-        (!defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0))
-  { "CreateFileMappingW",      (SYSCALL)CreateFileMappingW,      0 },
-#else
-  { "CreateFileMappingW",      (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateFileMappingW ((HANDLE(WINAPI*)(HANDLE,LPSECURITY_ATTRIBUTES, \
-        DWORD,DWORD,DWORD,LPCWSTR))aSyscall[7].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "CreateMutexW",            (SYSCALL)CreateMutexW,            0 },
-#else
-  { "CreateMutexW",            (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateMutexW ((HANDLE(WINAPI*)(LPSECURITY_ATTRIBUTES,BOOL, \
-        LPCWSTR))aSyscall[8].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "DeleteFileA",             (SYSCALL)DeleteFileA,             0 },
-#else
-  { "DeleteFileA",             (SYSCALL)0,                       0 },
-#endif
-
-#define osDeleteFileA ((BOOL(WINAPI*)(LPCSTR))aSyscall[9].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_WIDE)
-  { "DeleteFileW",             (SYSCALL)DeleteFileW,             0 },
-#else
-  { "DeleteFileW",             (SYSCALL)0,                       0 },
-#endif
-
-#define osDeleteFileW ((BOOL(WINAPI*)(LPCWSTR))aSyscall[10].pCurrent)
-
-#if SQLITE_OS_WINCE
-  { "FileTimeToLocalFileTime", (SYSCALL)FileTimeToLocalFileTime, 0 },
-#else
-  { "FileTimeToLocalFileTime", (SYSCALL)0,                       0 },
-#endif
-
-#define osFileTimeToLocalFileTime ((BOOL(WINAPI*)(CONST FILETIME*, \
-        LPFILETIME))aSyscall[11].pCurrent)
-
-#if SQLITE_OS_WINCE
-  { "FileTimeToSystemTime",    (SYSCALL)FileTimeToSystemTime,    0 },
-#else
-  { "FileTimeToSystemTime",    (SYSCALL)0,                       0 },
-#endif
-
-#define osFileTimeToSystemTime ((BOOL(WINAPI*)(CONST FILETIME*, \
-        LPSYSTEMTIME))aSyscall[12].pCurrent)
-
-  { "FlushFileBuffers",        (SYSCALL)FlushFileBuffers,        0 },
-
-#define osFlushFileBuffers ((BOOL(WINAPI*)(HANDLE))aSyscall[13].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "FormatMessageA",          (SYSCALL)FormatMessageA,          0 },
-#else
-  { "FormatMessageA",          (SYSCALL)0,                       0 },
-#endif
-
-#define osFormatMessageA ((DWORD(WINAPI*)(DWORD,LPCVOID,DWORD,DWORD,LPSTR, \
-        DWORD,va_list*))aSyscall[14].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_WIDE)
-  { "FormatMessageW",          (SYSCALL)FormatMessageW,          0 },
-#else
-  { "FormatMessageW",          (SYSCALL)0,                       0 },
-#endif
-
-#define osFormatMessageW ((DWORD(WINAPI*)(DWORD,LPCVOID,DWORD,DWORD,LPWSTR, \
-        DWORD,va_list*))aSyscall[15].pCurrent)
-
-#if !defined(SQLITE_OMIT_LOAD_EXTENSION)
-  { "FreeLibrary",             (SYSCALL)FreeLibrary,             0 },
-#else
-  { "FreeLibrary",             (SYSCALL)0,                       0 },
-#endif
-
-#define osFreeLibrary ((BOOL(WINAPI*)(HMODULE))aSyscall[16].pCurrent)
-
-  { "GetCurrentProcessId",     (SYSCALL)GetCurrentProcessId,     0 },
-
-#define osGetCurrentProcessId ((DWORD(WINAPI*)(VOID))aSyscall[17].pCurrent)
-
-#if !SQLITE_OS_WINCE && defined(SQLITE_WIN32_HAS_ANSI)
-  { "GetDiskFreeSpaceA",       (SYSCALL)GetDiskFreeSpaceA,       0 },
-#else
-  { "GetDiskFreeSpaceA",       (SYSCALL)0,                       0 },
-#endif
-
-#define osGetDiskFreeSpaceA ((BOOL(WINAPI*)(LPCSTR,LPDWORD,LPDWORD,LPDWORD, \
-        LPDWORD))aSyscall[18].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "GetDiskFreeSpaceW",       (SYSCALL)GetDiskFreeSpaceW,       0 },
-#else
-  { "GetDiskFreeSpaceW",       (SYSCALL)0,                       0 },
-#endif
-
-#define osGetDiskFreeSpaceW ((BOOL(WINAPI*)(LPCWSTR,LPDWORD,LPDWORD,LPDWORD, \
-        LPDWORD))aSyscall[19].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "GetFileAttributesA",      (SYSCALL)GetFileAttributesA,      0 },
-#else
-  { "GetFileAttributesA",      (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFileAttributesA ((DWORD(WINAPI*)(LPCSTR))aSyscall[20].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "GetFileAttributesW",      (SYSCALL)GetFileAttributesW,      0 },
-#else
-  { "GetFileAttributesW",      (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFileAttributesW ((DWORD(WINAPI*)(LPCWSTR))aSyscall[21].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_WIDE)
-  { "GetFileAttributesExW",    (SYSCALL)GetFileAttributesExW,    0 },
-#else
-  { "GetFileAttributesExW",    (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFileAttributesExW ((BOOL(WINAPI*)(LPCWSTR,GET_FILEEX_INFO_LEVELS, \
-        LPVOID))aSyscall[22].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "GetFileSize",             (SYSCALL)GetFileSize,             0 },
-#else
-  { "GetFileSize",             (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFileSize ((DWORD(WINAPI*)(HANDLE,LPDWORD))aSyscall[23].pCurrent)
-
-#if !SQLITE_OS_WINCE && defined(SQLITE_WIN32_HAS_ANSI)
-  { "GetFullPathNameA",        (SYSCALL)GetFullPathNameA,        0 },
-#else
-  { "GetFullPathNameA",        (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFullPathNameA ((DWORD(WINAPI*)(LPCSTR,DWORD,LPSTR, \
-        LPSTR*))aSyscall[24].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "GetFullPathNameW",        (SYSCALL)GetFullPathNameW,        0 },
-#else
-  { "GetFullPathNameW",        (SYSCALL)0,                       0 },
-#endif
-
-#define osGetFullPathNameW ((DWORD(WINAPI*)(LPCWSTR,DWORD,LPWSTR, \
-        LPWSTR*))aSyscall[25].pCurrent)
-
-  { "GetLastError",            (SYSCALL)GetLastError,            0 },
-
-#define osGetLastError ((DWORD(WINAPI*)(VOID))aSyscall[26].pCurrent)
-
-#if !defined(SQLITE_OMIT_LOAD_EXTENSION)
-#if SQLITE_OS_WINCE
-  /* The GetProcAddressA() routine is only available on Windows CE. */
-  { "GetProcAddressA",         (SYSCALL)GetProcAddressA,         0 },
-#else
-  /* All other Windows platforms expect GetProcAddress() to take
-  ** an ANSI string regardless of the _UNICODE setting */
-  { "GetProcAddressA",         (SYSCALL)GetProcAddress,          0 },
-#endif
-#else
-  { "GetProcAddressA",         (SYSCALL)0,                       0 },
-#endif
-
-#define osGetProcAddressA ((FARPROC(WINAPI*)(HMODULE, \
-        LPCSTR))aSyscall[27].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "GetSystemInfo",           (SYSCALL)GetSystemInfo,           0 },
-#else
-  { "GetSystemInfo",           (SYSCALL)0,                       0 },
-#endif
-
-#define osGetSystemInfo ((VOID(WINAPI*)(LPSYSTEM_INFO))aSyscall[28].pCurrent)
-
-  { "GetSystemTime",           (SYSCALL)GetSystemTime,           0 },
-
-#define osGetSystemTime ((VOID(WINAPI*)(LPSYSTEMTIME))aSyscall[29].pCurrent)
-
-#if !SQLITE_OS_WINCE
-  { "GetSystemTimeAsFileTime", (SYSCALL)GetSystemTimeAsFileTime, 0 },
-#else
-  { "GetSystemTimeAsFileTime", (SYSCALL)0,                       0 },
-#endif
-
-#define osGetSystemTimeAsFileTime ((VOID(WINAPI*)( \
-        LPFILETIME))aSyscall[30].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "GetTempPathA",            (SYSCALL)GetTempPathA,            0 },
-#else
-  { "GetTempPathA",            (SYSCALL)0,                       0 },
-#endif
-
-#define osGetTempPathA ((DWORD(WINAPI*)(DWORD,LPSTR))aSyscall[31].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE)
-  { "GetTempPathW",            (SYSCALL)GetTempPathW,            0 },
-#else
-  { "GetTempPathW",            (SYSCALL)0,                       0 },
-#endif
-
-#define osGetTempPathW ((DWORD(WINAPI*)(DWORD,LPWSTR))aSyscall[32].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "GetTickCount",            (SYSCALL)GetTickCount,            0 },
-#else
-  { "GetTickCount",            (SYSCALL)0,                       0 },
-#endif
-
-#define osGetTickCount ((DWORD(WINAPI*)(VOID))aSyscall[33].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI) && SQLITE_WIN32_GETVERSIONEX
-  { "GetVersionExA",           (SYSCALL)GetVersionExA,           0 },
-#else
-  { "GetVersionExA",           (SYSCALL)0,                       0 },
-#endif
-
-#define osGetVersionExA ((BOOL(WINAPI*)( \
-        LPOSVERSIONINFOA))aSyscall[34].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE) && \
-        SQLITE_WIN32_GETVERSIONEX
-  { "GetVersionExW",           (SYSCALL)GetVersionExW,           0 },
-#else
-  { "GetVersionExW",           (SYSCALL)0,                       0 },
-#endif
-
-#define osGetVersionExW ((BOOL(WINAPI*)( \
-        LPOSVERSIONINFOW))aSyscall[35].pCurrent)
-
-  { "HeapAlloc",               (SYSCALL)HeapAlloc,               0 },
-
-#define osHeapAlloc ((LPVOID(WINAPI*)(HANDLE,DWORD, \
-        SIZE_T))aSyscall[36].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "HeapCreate",              (SYSCALL)HeapCreate,              0 },
-#else
-  { "HeapCreate",              (SYSCALL)0,                       0 },
-#endif
-
-#define osHeapCreate ((HANDLE(WINAPI*)(DWORD,SIZE_T, \
-        SIZE_T))aSyscall[37].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "HeapDestroy",             (SYSCALL)HeapDestroy,             0 },
-#else
-  { "HeapDestroy",             (SYSCALL)0,                       0 },
-#endif
-
-#define osHeapDestroy ((BOOL(WINAPI*)(HANDLE))aSyscall[38].pCurrent)
-
-  { "HeapFree",                (SYSCALL)HeapFree,                0 },
-
-#define osHeapFree ((BOOL(WINAPI*)(HANDLE,DWORD,LPVOID))aSyscall[39].pCurrent)
-
-  { "HeapReAlloc",             (SYSCALL)HeapReAlloc,             0 },
-
-#define osHeapReAlloc ((LPVOID(WINAPI*)(HANDLE,DWORD,LPVOID, \
-        SIZE_T))aSyscall[40].pCurrent)
-
-  { "HeapSize",                (SYSCALL)HeapSize,                0 },
-
-#define osHeapSize ((SIZE_T(WINAPI*)(HANDLE,DWORD, \
-        LPCVOID))aSyscall[41].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "HeapValidate",            (SYSCALL)HeapValidate,            0 },
-#else
-  { "HeapValidate",            (SYSCALL)0,                       0 },
-#endif
-
-#define osHeapValidate ((BOOL(WINAPI*)(HANDLE,DWORD, \
-        LPCVOID))aSyscall[42].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
-  { "HeapCompact",             (SYSCALL)HeapCompact,             0 },
-#else
-  { "HeapCompact",             (SYSCALL)0,                       0 },
-#endif
-
-#define osHeapCompact ((UINT(WINAPI*)(HANDLE,DWORD))aSyscall[43].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI) && !defined(SQLITE_OMIT_LOAD_EXTENSION)
-  { "LoadLibraryA",            (SYSCALL)LoadLibraryA,            0 },
-#else
-  { "LoadLibraryA",            (SYSCALL)0,                       0 },
-#endif
-
-#define osLoadLibraryA ((HMODULE(WINAPI*)(LPCSTR))aSyscall[44].pCurrent)
-
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_HAS_WIDE) && \
-        !defined(SQLITE_OMIT_LOAD_EXTENSION)
-  { "LoadLibraryW",            (SYSCALL)LoadLibraryW,            0 },
-#else
-  { "LoadLibraryW",            (SYSCALL)0,                       0 },
-#endif
-
-#define osLoadLibraryW ((HMODULE(WINAPI*)(LPCWSTR))aSyscall[45].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "LocalFree",               (SYSCALL)LocalFree,               0 },
-#else
-  { "LocalFree",               (SYSCALL)0,                       0 },
-#endif
-
-#define osLocalFree ((HLOCAL(WINAPI*)(HLOCAL))aSyscall[46].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
-  { "LockFile",                (SYSCALL)LockFile,                0 },
-#else
-  { "LockFile",                (SYSCALL)0,                       0 },
-#endif
-
-#ifndef osLockFile
-#define osLockFile ((BOOL(WINAPI*)(HANDLE,DWORD,DWORD,DWORD, \
-        DWORD))aSyscall[47].pCurrent)
-#endif
-
-#if !SQLITE_OS_WINCE
-  { "LockFileEx",              (SYSCALL)LockFileEx,              0 },
-#else
-  { "LockFileEx",              (SYSCALL)0,                       0 },
-#endif
-
-#ifndef osLockFileEx
-#define osLockFileEx ((BOOL(WINAPI*)(HANDLE,DWORD,DWORD,DWORD,DWORD, \
-        LPOVERLAPPED))aSyscall[48].pCurrent)
-#endif
-
-#if SQLITE_OS_WINCE || (!SQLITE_OS_WINRT && \
-        (!defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0))
-  { "MapViewOfFile",           (SYSCALL)MapViewOfFile,           0 },
-#else
-  { "MapViewOfFile",           (SYSCALL)0,                       0 },
-#endif
-
-#define osMapViewOfFile ((LPVOID(WINAPI*)(HANDLE,DWORD,DWORD,DWORD, \
-        SIZE_T))aSyscall[49].pCurrent)
-
-  { "MultiByteToWideChar",     (SYSCALL)MultiByteToWideChar,     0 },
-
-#define osMultiByteToWideChar ((int(WINAPI*)(UINT,DWORD,LPCSTR,int,LPWSTR, \
-        int))aSyscall[50].pCurrent)
-
-  { "QueryPerformanceCounter", (SYSCALL)QueryPerformanceCounter, 0 },
-
-#define osQueryPerformanceCounter ((BOOL(WINAPI*)( \
-        LARGE_INTEGER*))aSyscall[51].pCurrent)
-
-  { "ReadFile",                (SYSCALL)ReadFile,                0 },
-
-#define osReadFile ((BOOL(WINAPI*)(HANDLE,LPVOID,DWORD,LPDWORD, \
-        LPOVERLAPPED))aSyscall[52].pCurrent)
-
-  { "SetEndOfFile",            (SYSCALL)SetEndOfFile,            0 },
-
-#define osSetEndOfFile ((BOOL(WINAPI*)(HANDLE))aSyscall[53].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "SetFilePointer",          (SYSCALL)SetFilePointer,          0 },
-#else
-  { "SetFilePointer",          (SYSCALL)0,                       0 },
-#endif
-
-#define osSetFilePointer ((DWORD(WINAPI*)(HANDLE,LONG,PLONG, \
-        DWORD))aSyscall[54].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "Sleep",                   (SYSCALL)Sleep,                   0 },
-#else
-  { "Sleep",                   (SYSCALL)0,                       0 },
-#endif
-
-#define osSleep ((VOID(WINAPI*)(DWORD))aSyscall[55].pCurrent)
-
-  { "SystemTimeToFileTime",    (SYSCALL)SystemTimeToFileTime,    0 },
-
-#define osSystemTimeToFileTime ((BOOL(WINAPI*)(CONST SYSTEMTIME*, \
-        LPFILETIME))aSyscall[56].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
-  { "UnlockFile",              (SYSCALL)UnlockFile,              0 },
-#else
-  { "UnlockFile",              (SYSCALL)0,                       0 },
-#endif
-
-#ifndef osUnlockFile
-#define osUnlockFile ((BOOL(WINAPI*)(HANDLE,DWORD,DWORD,DWORD, \
-        DWORD))aSyscall[57].pCurrent)
-#endif
-
-#if !SQLITE_OS_WINCE
-  { "UnlockFileEx",            (SYSCALL)UnlockFileEx,            0 },
-#else
-  { "UnlockFileEx",            (SYSCALL)0,                       0 },
-#endif
-
-#define osUnlockFileEx ((BOOL(WINAPI*)(HANDLE,DWORD,DWORD,DWORD, \
-        LPOVERLAPPED))aSyscall[58].pCurrent)
-
-#if SQLITE_OS_WINCE || !defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0
-  { "UnmapViewOfFile",         (SYSCALL)UnmapViewOfFile,         0 },
-#else
-  { "UnmapViewOfFile",         (SYSCALL)0,                       0 },
-#endif
-
-#define osUnmapViewOfFile ((BOOL(WINAPI*)(LPCVOID))aSyscall[59].pCurrent)
-
-  { "WideCharToMultiByte",     (SYSCALL)WideCharToMultiByte,     0 },
-
-#define osWideCharToMultiByte ((int(WINAPI*)(UINT,DWORD,LPCWSTR,int,LPSTR,int, \
-        LPCSTR,LPBOOL))aSyscall[60].pCurrent)
-
-  { "WriteFile",               (SYSCALL)WriteFile,               0 },
-
-#define osWriteFile ((BOOL(WINAPI*)(HANDLE,LPCVOID,DWORD,LPDWORD, \
-        LPOVERLAPPED))aSyscall[61].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "CreateEventExW",          (SYSCALL)CreateEventExW,          0 },
-#else
-  { "CreateEventExW",          (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateEventExW ((HANDLE(WINAPI*)(LPSECURITY_ATTRIBUTES,LPCWSTR, \
-        DWORD,DWORD))aSyscall[62].pCurrent)
-
-#if !SQLITE_OS_WINRT
-  { "WaitForSingleObject",     (SYSCALL)WaitForSingleObject,     0 },
-#else
-  { "WaitForSingleObject",     (SYSCALL)0,                       0 },
-#endif
-
-#define osWaitForSingleObject ((DWORD(WINAPI*)(HANDLE, \
-        DWORD))aSyscall[63].pCurrent)
-
-#if !SQLITE_OS_WINCE
-  { "WaitForSingleObjectEx",   (SYSCALL)WaitForSingleObjectEx,   0 },
-#else
-  { "WaitForSingleObjectEx",   (SYSCALL)0,                       0 },
-#endif
-
-#define osWaitForSingleObjectEx ((DWORD(WINAPI*)(HANDLE,DWORD, \
-        BOOL))aSyscall[64].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "SetFilePointerEx",        (SYSCALL)SetFilePointerEx,        0 },
-#else
-  { "SetFilePointerEx",        (SYSCALL)0,                       0 },
-#endif
-
-#define osSetFilePointerEx ((BOOL(WINAPI*)(HANDLE,LARGE_INTEGER, \
-        PLARGE_INTEGER,DWORD))aSyscall[65].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "GetFileInformationByHandleEx", (SYSCALL)GetFileInformationByHandleEx, 0 },
-#else
-  { "GetFileInformationByHandleEx", (SYSCALL)0,                  0 },
-#endif
-
-#define osGetFileInformationByHandleEx ((BOOL(WINAPI*)(HANDLE, \
-        FILE_INFO_BY_HANDLE_CLASS,LPVOID,DWORD))aSyscall[66].pCurrent)
-
-#if SQLITE_OS_WINRT && (!defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0)
-  { "MapViewOfFileFromApp",    (SYSCALL)MapViewOfFileFromApp,    0 },
-#else
-  { "MapViewOfFileFromApp",    (SYSCALL)0,                       0 },
-#endif
-
-#define osMapViewOfFileFromApp ((LPVOID(WINAPI*)(HANDLE,ULONG,ULONG64, \
-        SIZE_T))aSyscall[67].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "CreateFile2",             (SYSCALL)CreateFile2,             0 },
-#else
-  { "CreateFile2",             (SYSCALL)0,                       0 },
-#endif
-
-#define osCreateFile2 ((HANDLE(WINAPI*)(LPCWSTR,DWORD,DWORD,DWORD, \
-        LPCREATEFILE2_EXTENDED_PARAMETERS))aSyscall[68].pCurrent)
-
-#if SQLITE_OS_WINRT && !defined(SQLITE_OMIT_LOAD_EXTENSION)
-  { "LoadPackagedLibrary",     (SYSCALL)LoadPackagedLibrary,     0 },
-#else
-  { "LoadPackagedLibrary",     (SYSCALL)0,                       0 },
-#endif
-
-#define osLoadPackagedLibrary ((HMODULE(WINAPI*)(LPCWSTR, \
-        DWORD))aSyscall[69].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "GetTickCount64",          (SYSCALL)GetTickCount64,          0 },
-#else
-  { "GetTickCount64",          (SYSCALL)0,                       0 },
-#endif
-
-#define osGetTickCount64 ((ULONGLONG(WINAPI*)(VOID))aSyscall[70].pCurrent)
-
-#if SQLITE_OS_WINRT
-  { "GetNativeSystemInfo",     (SYSCALL)GetNativeSystemInfo,     0 },
-#else
-  { "GetNativeSystemInfo",     (SYSCALL)0,                       0 },
-#endif
-
-#define osGetNativeSystemInfo ((VOID(WINAPI*)( \
-        LPSYSTEM_INFO))aSyscall[71].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  { "OutputDebugStringA",      (SYSCALL)OutputDebugStringA,      0 },
-#else
-  { "OutputDebugStringA",      (SYSCALL)0,                       0 },
-#endif
-
-#define osOutputDebugStringA ((VOID(WINAPI*)(LPCSTR))aSyscall[72].pCurrent)
-
-#if defined(SQLITE_WIN32_HAS_WIDE)
-  { "OutputDebugStringW",      (SYSCALL)OutputDebugStringW,      0 },
-#else
-  { "OutputDebugStringW",      (SYSCALL)0,                       0 },
-#endif
-
-#define osOutputDebugStringW ((VOID(WINAPI*)(LPCWSTR))aSyscall[73].pCurrent)
-
-  { "GetProcessHeap",          (SYSCALL)GetProcessHeap,          0 },
-
-#define osGetProcessHeap ((HANDLE(WINAPI*)(VOID))aSyscall[74].pCurrent)
-
-#if SQLITE_OS_WINRT && (!defined(SQLITE_OMIT_WAL) || SQLITE_MAX_MMAP_SIZE>0)
-  { "CreateFileMappingFromApp", (SYSCALL)CreateFileMappingFromApp, 0 },
-#else
-  { "CreateFileMappingFromApp", (SYSCALL)0,                      0 },
-#endif
-
-#define osCreateFileMappingFromApp ((HANDLE(WINAPI*)(HANDLE, \
-        LPSECURITY_ATTRIBUTES,ULONG,ULONG64,LPCWSTR))aSyscall[75].pCurrent)
-
-/*
-** NOTE: On some sub-platforms, the InterlockedCompareExchange "function"
-**       is really just a macro that uses a compiler intrinsic (e.g. x64).
-**       So do not try to make this is into a redefinable interface.
-*/
-#if defined(InterlockedCompareExchange)
-  { "InterlockedCompareExchange", (SYSCALL)0,                    0 },
-
-#define osInterlockedCompareExchange InterlockedCompareExchange
-#else
-  { "InterlockedCompareExchange", (SYSCALL)InterlockedCompareExchange, 0 },
-
-#define osInterlockedCompareExchange ((LONG(WINAPI*)(LONG \
-        SQLITE_WIN32_VOLATILE*, LONG,LONG))aSyscall[76].pCurrent)
-#endif /* defined(InterlockedCompareExchange) */
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT && SQLITE_WIN32_USE_UUID
-  { "UuidCreate",               (SYSCALL)UuidCreate,             0 },
-#else
-  { "UuidCreate",               (SYSCALL)0,                      0 },
-#endif
-
-#define osUuidCreate ((RPC_STATUS(RPC_ENTRY*)(UUID*))aSyscall[77].pCurrent)
-
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT && SQLITE_WIN32_USE_UUID
-  { "UuidCreateSequential",     (SYSCALL)UuidCreateSequential,   0 },
-#else
-  { "UuidCreateSequential",     (SYSCALL)0,                      0 },
-#endif
-
-#define osUuidCreateSequential \
-        ((RPC_STATUS(RPC_ENTRY*)(UUID*))aSyscall[78].pCurrent)
-
-#if !defined(SQLITE_NO_SYNC) && SQLITE_MAX_MMAP_SIZE>0
-  { "FlushViewOfFile",          (SYSCALL)FlushViewOfFile,        0 },
-#else
-  { "FlushViewOfFile",          (SYSCALL)0,                      0 },
-#endif
-
-#define osFlushViewOfFile \
-        ((BOOL(WINAPI*)(LPCVOID,SIZE_T))aSyscall[79].pCurrent)
-
-}; /* End of the overrideable system calls */
-
-/*
-** This is the xSetSystemCall() method of sqlite3_vfs for all of the
-** "win32" VFSes.  Return SQLITE_OK opon successfully updating the
-** system call pointer, or SQLITE_NOTFOUND if there is no configurable
-** system call named zName.
-*/
-static int winSetSystemCall(
-  sqlite3_vfs *pNotUsed,        /* The VFS pointer.  Not used */
-  const char *zName,            /* Name of system call to override */
-  sqlite3_syscall_ptr pNewFunc  /* Pointer to new system call value */
-){
-  unsigned int i;
-  int rc = SQLITE_NOTFOUND;
-
-  UNUSED_PARAMETER(pNotUsed);
-  if( zName==0 ){
-    /* If no zName is given, restore all system calls to their default
-    ** settings and return NULL
-    */
-    rc = SQLITE_OK;
-    for(i=0; i<sizeof(aSyscall)/sizeof(aSyscall[0]); i++){
-      if( aSyscall[i].pDefault ){
-        aSyscall[i].pCurrent = aSyscall[i].pDefault;
-      }
-    }
-  }else{
-    /* If zName is specified, operate on only the one system call
-    ** specified.
-    */
-    for(i=0; i<sizeof(aSyscall)/sizeof(aSyscall[0]); i++){
-      if( strcmp(zName, aSyscall[i].zName)==0 ){
-        if( aSyscall[i].pDefault==0 ){
-          aSyscall[i].pDefault = aSyscall[i].pCurrent;
-        }
-        rc = SQLITE_OK;
-        if( pNewFunc==0 ) pNewFunc = aSyscall[i].pDefault;
-        aSyscall[i].pCurrent = pNewFunc;
-        break;
-      }
-    }
-  }
-  return rc;
-}
-
-/*
-** Return the value of a system call.  Return NULL if zName is not a
-** recognized system call name.  NULL is also returned if the system call
-** is currently undefined.
-*/
-static sqlite3_syscall_ptr winGetSystemCall(
-  sqlite3_vfs *pNotUsed,
-  const char *zName
-){
-  unsigned int i;
-
-  UNUSED_PARAMETER(pNotUsed);
-  for(i=0; i<sizeof(aSyscall)/sizeof(aSyscall[0]); i++){
-    if( strcmp(zName, aSyscall[i].zName)==0 ) return aSyscall[i].pCurrent;
-  }
-  return 0;
-}
-
-/*
-** Return the name of the first system call after zName.  If zName==NULL
-** then return the name of the first system call.  Return NULL if zName
-** is the last system call or if zName is not the name of a valid
-** system call.
-*/
-static const char *winNextSystemCall(sqlite3_vfs *p, const char *zName){
-  int i = -1;
-
-  UNUSED_PARAMETER(p);
-  if( zName ){
-    for(i=0; i<ArraySize(aSyscall)-1; i++){
-      if( strcmp(zName, aSyscall[i].zName)==0 ) break;
-    }
-  }
-  for(i++; i<ArraySize(aSyscall); i++){
-    if( aSyscall[i].pCurrent!=0 ) return aSyscall[i].zName;
-  }
-  return 0;
-}
-
-#ifdef SQLITE_WIN32_MALLOC
-/*
-** If a Win32 native heap has been configured, this function will attempt to
-** compact it.  Upon success, SQLITE_OK will be returned.  Upon failure, one
-** of SQLITE_NOMEM, SQLITE_ERROR, or SQLITE_NOTFOUND will be returned.  The
-** "pnLargest" argument, if non-zero, will be used to return the size of the
-** largest committed free block in the heap, in bytes.
-*/
-int sqlite3_win32_compact_heap(LPUINT pnLargest){
-  int rc = SQLITE_OK;
-  UINT nLargest = 0;
-  HANDLE hHeap;
-
-  winMemAssertMagic();
-  hHeap = winMemGetHeap();
-  assert( hHeap!=0 );
-  assert( hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, NULL) );
-#endif
-#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
-  if( (nLargest=osHeapCompact(hHeap, SQLITE_WIN32_HEAP_FLAGS))==0 ){
-    DWORD lastErrno = osGetLastError();
-    if( lastErrno==NO_ERROR ){
-      sqlite3_log(SQLITE_NOMEM, "failed to HeapCompact (no space), heap=%p",
-                  (void*)hHeap);
-      rc = SQLITE_NOMEM_BKPT;
-    }else{
-      sqlite3_log(SQLITE_ERROR, "failed to HeapCompact (%lu), heap=%p",
-                  osGetLastError(), (void*)hHeap);
-      rc = SQLITE_ERROR;
-    }
-  }
-#else
-  sqlite3_log(SQLITE_NOTFOUND, "failed to HeapCompact, heap=%p",
-              (void*)hHeap);
-  rc = SQLITE_NOTFOUND;
-#endif
-  if( pnLargest ) *pnLargest = nLargest;
-  return rc;
-}
-
-/*
-** If a Win32 native heap has been configured, this function will attempt to
-** destroy and recreate it.  If the Win32 native heap is not isolated and/or
-** the sqlite3_memory_used() function does not return zero, SQLITE_BUSY will
-** be returned and no changes will be made to the Win32 native heap.
-*/
-int sqlite3_win32_reset_heap(){
-  int rc;
-  MUTEX_LOGIC( sqlite3_mutex *pMaster; ) /* The main static mutex */
-  MUTEX_LOGIC( sqlite3_mutex *pMem; )    /* The memsys static mutex */
-  MUTEX_LOGIC( pMaster = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER); )
-  MUTEX_LOGIC( pMem = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MEM); )
-  sqlite3_mutex_enter(pMaster);
-  sqlite3_mutex_enter(pMem);
-  winMemAssertMagic();
-  if( winMemGetHeap()!=NULL && winMemGetOwned() && sqlite3_memory_used()==0 ){
-    /*
-    ** At this point, there should be no outstanding memory allocations on
-    ** the heap.  Also, since both the master and memsys locks are currently
-    ** being held by us, no other function (i.e. from another thread) should
-    ** be able to even access the heap.  Attempt to destroy and recreate our
-    ** isolated Win32 native heap now.
-    */
-    assert( winMemGetHeap()!=NULL );
-    assert( winMemGetOwned() );
-    assert( sqlite3_memory_used()==0 );
-    winMemShutdown(winMemGetDataPtr());
-    assert( winMemGetHeap()==NULL );
-    assert( !winMemGetOwned() );
-    assert( sqlite3_memory_used()==0 );
-    rc = winMemInit(winMemGetDataPtr());
-    assert( rc!=SQLITE_OK || winMemGetHeap()!=NULL );
-    assert( rc!=SQLITE_OK || winMemGetOwned() );
-    assert( rc!=SQLITE_OK || sqlite3_memory_used()==0 );
-  }else{
-    /*
-    ** The Win32 native heap cannot be modified because it may be in use.
-    */
-    rc = SQLITE_BUSY;
-  }
-  sqlite3_mutex_leave(pMem);
-  sqlite3_mutex_leave(pMaster);
-  return rc;
-}
-#endif /* SQLITE_WIN32_MALLOC */
-
-/*
-** This function outputs the specified (ANSI) string to the Win32 debugger
-** (if available).
-*/
-
-void sqlite3_win32_write_debug(const char *zBuf, int nBuf){
-  char zDbgBuf[SQLITE_WIN32_DBG_BUF_SIZE];
-  int nMin = MIN(nBuf, (SQLITE_WIN32_DBG_BUF_SIZE - 1)); /* may be negative. */
-  if( nMin<-1 ) nMin = -1; /* all negative values become -1. */
-  assert( nMin==-1 || nMin==0 || nMin<SQLITE_WIN32_DBG_BUF_SIZE );
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zBuf ){
-    (void)SQLITE_MISUSE_BKPT;
-    return;
-  }
-#endif
-#if defined(SQLITE_WIN32_HAS_ANSI)
-  if( nMin>0 ){
-    memset(zDbgBuf, 0, SQLITE_WIN32_DBG_BUF_SIZE);
-    memcpy(zDbgBuf, zBuf, nMin);
-    osOutputDebugStringA(zDbgBuf);
-  }else{
-    osOutputDebugStringA(zBuf);
-  }
-#elif defined(SQLITE_WIN32_HAS_WIDE)
-  memset(zDbgBuf, 0, SQLITE_WIN32_DBG_BUF_SIZE);
-  if ( osMultiByteToWideChar(
-          osAreFileApisANSI() ? CP_ACP : CP_OEMCP, 0, zBuf,
-          nMin, (LPWSTR)zDbgBuf, SQLITE_WIN32_DBG_BUF_SIZE/sizeof(WCHAR))<=0 ){
-    return;
-  }
-  osOutputDebugStringW((LPCWSTR)zDbgBuf);
-#else
-  if( nMin>0 ){
-    memset(zDbgBuf, 0, SQLITE_WIN32_DBG_BUF_SIZE);
-    memcpy(zDbgBuf, zBuf, nMin);
-    fprintf(stderr, "%s", zDbgBuf);
-  }else{
-    fprintf(stderr, "%s", zBuf);
-  }
-#endif
-}
-
-/*
-** The following routine suspends the current thread for at least ms
-** milliseconds.  This is equivalent to the Win32 Sleep() interface.
-*/
-#if SQLITE_OS_WINRT
-static HANDLE sleepObj = NULL;
-#endif
-
-void sqlite3_win32_sleep(DWORD milliseconds){
-#if SQLITE_OS_WINRT
-  if ( sleepObj==NULL ){
-    sleepObj = osCreateEventExW(NULL, NULL, CREATE_EVENT_MANUAL_RESET,
-                                SYNCHRONIZE);
-  }
-  assert( sleepObj!=NULL );
-  osWaitForSingleObjectEx(sleepObj, milliseconds, FALSE);
-#else
-  osSleep(milliseconds);
-#endif
-}
-
-#if SQLITE_MAX_WORKER_THREADS>0 && !SQLITE_OS_WINCE && !SQLITE_OS_WINRT && \
-        SQLITE_THREADSAFE>0
-DWORD sqlite3Win32Wait(HANDLE hObject){
-  DWORD rc;
-  while( (rc = osWaitForSingleObjectEx(hObject, INFINITE,
-                                       TRUE))==WAIT_IO_COMPLETION ){}
-  return rc;
-}
-#endif
-
-/*
-** Return true (non-zero) if we are running under WinNT, Win2K, WinXP,
-** or WinCE.  Return false (zero) for Win95, Win98, or WinME.
-**
-** Here is an interesting observation:  Win95, Win98, and WinME lack
-** the LockFileEx() API.  But we can still statically link against that
-** API as long as we don't call it when running Win95/98/ME.  A call to
-** this routine is used to determine if the host is Win95/98/ME or
-** WinNT/2K/XP so that we will know whether or not we can safely call
-** the LockFileEx() API.
-*/
-
-#if !SQLITE_WIN32_GETVERSIONEX
-# define osIsNT()  (1)
-#elif SQLITE_OS_WINCE || SQLITE_OS_WINRT || !defined(SQLITE_WIN32_HAS_ANSI)
-# define osIsNT()  (1)
-#elif !defined(SQLITE_WIN32_HAS_WIDE)
-# define osIsNT()  (0)
-#else
-# define osIsNT()  ((sqlite3_os_type==2) || sqlite3_win32_is_nt())
-#endif
-
-/*
-** This function determines if the machine is running a version of Windows
-** based on the NT kernel.
-*/
-int sqlite3_win32_is_nt(void){
-#if SQLITE_OS_WINRT
-  /*
-  ** NOTE: The WinRT sub-platform is always assumed to be based on the NT
-  **       kernel.
-  */
-  return 1;
-#elif SQLITE_WIN32_GETVERSIONEX
-  if( osInterlockedCompareExchange(&sqlite3_os_type, 0, 0)==0 ){
-#if defined(SQLITE_WIN32_HAS_ANSI)
-    OSVERSIONINFOA sInfo;
-    sInfo.dwOSVersionInfoSize = sizeof(sInfo);
-    osGetVersionExA(&sInfo);
-    osInterlockedCompareExchange(&sqlite3_os_type,
-        (sInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) ? 2 : 1, 0);
-#elif defined(SQLITE_WIN32_HAS_WIDE)
-    OSVERSIONINFOW sInfo;
-    sInfo.dwOSVersionInfoSize = sizeof(sInfo);
-    osGetVersionExW(&sInfo);
-    osInterlockedCompareExchange(&sqlite3_os_type,
-        (sInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) ? 2 : 1, 0);
-#endif
-  }
-  return osInterlockedCompareExchange(&sqlite3_os_type, 2, 2)==2;
-#elif SQLITE_TEST
-  return osInterlockedCompareExchange(&sqlite3_os_type, 2, 2)==2;
-#else
-  /*
-  ** NOTE: All sub-platforms where the GetVersionEx[AW] functions are
-  **       deprecated are always assumed to be based on the NT kernel.
-  */
-  return 1;
-#endif
-}
-
-#ifdef SQLITE_WIN32_MALLOC
-/*
-** Allocate nBytes of memory.
-*/
-static void *winMemMalloc(int nBytes){
-  HANDLE hHeap;
-  void *p;
-
-  winMemAssertMagic();
-  hHeap = winMemGetHeap();
-  assert( hHeap!=0 );
-  assert( hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, NULL) );
-#endif
-  assert( nBytes>=0 );
-  p = osHeapAlloc(hHeap, SQLITE_WIN32_HEAP_FLAGS, (SIZE_T)nBytes);
-  if( !p ){
-    sqlite3_log(SQLITE_NOMEM, "failed to HeapAlloc %u bytes (%lu), heap=%p",
-                nBytes, osGetLastError(), (void*)hHeap);
-  }
-  return p;
-}
-
-/*
-** Free memory.
-*/
-static void winMemFree(void *pPrior){
-  HANDLE hHeap;
-
-  winMemAssertMagic();
-  hHeap = winMemGetHeap();
-  assert( hHeap!=0 );
-  assert( hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, pPrior) );
-#endif
-  if( !pPrior ) return; /* Passing NULL to HeapFree is undefined. */
-  if( !osHeapFree(hHeap, SQLITE_WIN32_HEAP_FLAGS, pPrior) ){
-    sqlite3_log(SQLITE_NOMEM, "failed to HeapFree block %p (%lu), heap=%p",
-                pPrior, osGetLastError(), (void*)hHeap);
-  }
-}
-
-/*
-** Change the size of an existing memory allocation
-*/
-static void *winMemRealloc(void *pPrior, int nBytes){
-  HANDLE hHeap;
-  void *p;
-
-  winMemAssertMagic();
-  hHeap = winMemGetHeap();
-  assert( hHeap!=0 );
-  assert( hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, pPrior) );
-#endif
-  assert( nBytes>=0 );
-  if( !pPrior ){
-    p = osHeapAlloc(hHeap, SQLITE_WIN32_HEAP_FLAGS, (SIZE_T)nBytes);
-  }else{
-    p = osHeapReAlloc(hHeap, SQLITE_WIN32_HEAP_FLAGS, pPrior, (SIZE_T)nBytes);
-  }
-  if( !p ){
-    sqlite3_log(SQLITE_NOMEM, "failed to %s %u bytes (%lu), heap=%p",
-                pPrior ? "HeapReAlloc" : "HeapAlloc", nBytes, osGetLastError(),
-                (void*)hHeap);
-  }
-  return p;
-}
-
-/*
-** Return the size of an outstanding allocation, in bytes.
-*/
-static int winMemSize(void *p){
-  HANDLE hHeap;
-  SIZE_T n;
-
-  winMemAssertMagic();
-  hHeap = winMemGetHeap();
-  assert( hHeap!=0 );
-  assert( hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, p) );
-#endif
-  if( !p ) return 0;
-  n = osHeapSize(hHeap, SQLITE_WIN32_HEAP_FLAGS, p);
-  if( n==(SIZE_T)-1 ){
-    sqlite3_log(SQLITE_NOMEM, "failed to HeapSize block %p (%lu), heap=%p",
-                p, osGetLastError(), (void*)hHeap);
-    return 0;
-  }
-  return (int)n;
-}
-
-/*
-** Round up a request size to the next valid allocation size.
-*/
-static int winMemRoundup(int n){
-  return n;
-}
-
-/*
-** Initialize this module.
-*/
-static int winMemInit(void *pAppData){
-  winMemData *pWinMemData = (winMemData *)pAppData;
-
-  if( !pWinMemData ) return SQLITE_ERROR;
-  assert( pWinMemData->magic1==WINMEM_MAGIC1 );
-  assert( pWinMemData->magic2==WINMEM_MAGIC2 );
-
-#if !SQLITE_OS_WINRT && SQLITE_WIN32_HEAP_CREATE
-  if( !pWinMemData->hHeap ){
-    DWORD dwInitialSize = SQLITE_WIN32_HEAP_INIT_SIZE;
-    DWORD dwMaximumSize = (DWORD)sqlite3GlobalConfig.nHeap;
-    if( dwMaximumSize==0 ){
-      dwMaximumSize = SQLITE_WIN32_HEAP_MAX_SIZE;
-    }else if( dwInitialSize>dwMaximumSize ){
-      dwInitialSize = dwMaximumSize;
-    }
-    pWinMemData->hHeap = osHeapCreate(SQLITE_WIN32_HEAP_FLAGS,
-                                      dwInitialSize, dwMaximumSize);
-    if( !pWinMemData->hHeap ){
-      sqlite3_log(SQLITE_NOMEM,
-          "failed to HeapCreate (%lu), flags=%u, initSize=%lu, maxSize=%lu",
-          osGetLastError(), SQLITE_WIN32_HEAP_FLAGS, dwInitialSize,
-          dwMaximumSize);
-      return SQLITE_NOMEM_BKPT;
-    }
-    pWinMemData->bOwned = TRUE;
-    assert( pWinMemData->bOwned );
-  }
-#else
-  pWinMemData->hHeap = osGetProcessHeap();
-  if( !pWinMemData->hHeap ){
-    sqlite3_log(SQLITE_NOMEM,
-        "failed to GetProcessHeap (%lu)", osGetLastError());
-    return SQLITE_NOMEM_BKPT;
-  }
-  pWinMemData->bOwned = FALSE;
-  assert( !pWinMemData->bOwned );
-#endif
-  assert( pWinMemData->hHeap!=0 );
-  assert( pWinMemData->hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-  assert( osHeapValidate(pWinMemData->hHeap, SQLITE_WIN32_HEAP_FLAGS, NULL) );
-#endif
-  return SQLITE_OK;
-}
-
-/*
-** Deinitialize this module.
-*/
-static void winMemShutdown(void *pAppData){
-  winMemData *pWinMemData = (winMemData *)pAppData;
-
-  if( !pWinMemData ) return;
-  assert( pWinMemData->magic1==WINMEM_MAGIC1 );
-  assert( pWinMemData->magic2==WINMEM_MAGIC2 );
-
-  if( pWinMemData->hHeap ){
-    assert( pWinMemData->hHeap!=INVALID_HANDLE_VALUE );
-#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
-    assert( osHeapValidate(pWinMemData->hHeap, SQLITE_WIN32_HEAP_FLAGS, NULL) );
-#endif
-    if( pWinMemData->bOwned ){
-      if( !osHeapDestroy(pWinMemData->hHeap) ){
-        sqlite3_log(SQLITE_NOMEM, "failed to HeapDestroy (%lu), heap=%p",
-                    osGetLastError(), (void*)pWinMemData->hHeap);
-      }
-      pWinMemData->bOwned = FALSE;
-    }
-    pWinMemData->hHeap = NULL;
-  }
-}
-
-/*
-** Populate the low-level memory allocation function pointers in
-** sqlite3GlobalConfig.m with pointers to the routines in this file. The
-** arguments specify the block of memory to manage.
-**
-** This routine is only called by sqlite3_config(), and therefore
-** is not required to be threadsafe (it is not).
-*/
-const sqlite3_mem_methods *sqlite3MemGetWin32(void){
-  static const sqlite3_mem_methods winMemMethods = {
-    winMemMalloc,
-    winMemFree,
-    winMemRealloc,
-    winMemSize,
-    winMemRoundup,
-    winMemInit,
-    winMemShutdown,
-    &win_mem_data
-  };
-  return &winMemMethods;
-}
-
-void sqlite3MemSetDefault(void){
-  sqlite3_config(SQLITE_CONFIG_MALLOC, sqlite3MemGetWin32());
-}
-#endif /* SQLITE_WIN32_MALLOC */
-
-/*
-** Convert a UTF-8 string to Microsoft Unicode.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static LPWSTR winUtf8ToUnicode(const char *zText){
-  int nChar;
-  LPWSTR zWideText;
-
-  nChar = osMultiByteToWideChar(CP_UTF8, 0, zText, -1, NULL, 0);
-  if( nChar==0 ){
-    return 0;
-  }
-  zWideText = sqlite3MallocZero( nChar*sizeof(WCHAR) );
-  if( zWideText==0 ){
-    return 0;
-  }
-  nChar = osMultiByteToWideChar(CP_UTF8, 0, zText, -1, zWideText,
-                                nChar);
-  if( nChar==0 ){
-    sqlite3_free(zWideText);
-    zWideText = 0;
-  }
-  return zWideText;
-}
-
-/*
-** Convert a Microsoft Unicode string to UTF-8.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static char *winUnicodeToUtf8(LPCWSTR zWideText){
-  int nByte;
-  char *zText;
-
-  nByte = osWideCharToMultiByte(CP_UTF8, 0, zWideText, -1, 0, 0, 0, 0);
-  if( nByte == 0 ){
-    return 0;
-  }
-  zText = sqlite3MallocZero( nByte );
-  if( zText==0 ){
-    return 0;
-  }
-  nByte = osWideCharToMultiByte(CP_UTF8, 0, zWideText, -1, zText, nByte,
-                                0, 0);
-  if( nByte == 0 ){
-    sqlite3_free(zText);
-    zText = 0;
-  }
-  return zText;
-}
-
-/*
-** Convert an ANSI string to Microsoft Unicode, using the ANSI or OEM
-** code page.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static LPWSTR winMbcsToUnicode(const char *zText, int useAnsi){
-  int nByte;
-  LPWSTR zMbcsText;
-  int codepage = useAnsi ? CP_ACP : CP_OEMCP;
-
-  nByte = osMultiByteToWideChar(codepage, 0, zText, -1, NULL,
-                                0)*sizeof(WCHAR);
-  if( nByte==0 ){
-    return 0;
-  }
-  zMbcsText = sqlite3MallocZero( nByte*sizeof(WCHAR) );
-  if( zMbcsText==0 ){
-    return 0;
-  }
-  nByte = osMultiByteToWideChar(codepage, 0, zText, -1, zMbcsText,
-                                nByte);
-  if( nByte==0 ){
-    sqlite3_free(zMbcsText);
-    zMbcsText = 0;
-  }
-  return zMbcsText;
-}
-
-/*
-** Convert a Microsoft Unicode string to a multi-byte character string,
-** using the ANSI or OEM code page.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static char *winUnicodeToMbcs(LPCWSTR zWideText, int useAnsi){
-  int nByte;
-  char *zText;
-  int codepage = useAnsi ? CP_ACP : CP_OEMCP;
-
-  nByte = osWideCharToMultiByte(codepage, 0, zWideText, -1, 0, 0, 0, 0);
-  if( nByte == 0 ){
-    return 0;
-  }
-  zText = sqlite3MallocZero( nByte );
-  if( zText==0 ){
-    return 0;
-  }
-  nByte = osWideCharToMultiByte(codepage, 0, zWideText, -1, zText,
-                                nByte, 0, 0);
-  if( nByte == 0 ){
-    sqlite3_free(zText);
-    zText = 0;
-  }
-  return zText;
-}
-
-/*
-** Convert a multi-byte character string to UTF-8.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static char *winMbcsToUtf8(const char *zText, int useAnsi){
-  char *zTextUtf8;
-  LPWSTR zTmpWide;
-
-  zTmpWide = winMbcsToUnicode(zText, useAnsi);
-  if( zTmpWide==0 ){
-    return 0;
-  }
-  zTextUtf8 = winUnicodeToUtf8(zTmpWide);
-  sqlite3_free(zTmpWide);
-  return zTextUtf8;
-}
-
-/*
-** Convert a UTF-8 string to a multi-byte character string.
-**
-** Space to hold the returned string is obtained from sqlite3_malloc().
-*/
-static char *winUtf8ToMbcs(const char *zText, int useAnsi){
-  char *zTextMbcs;
-  LPWSTR zTmpWide;
-
-  zTmpWide = winUtf8ToUnicode(zText);
-  if( zTmpWide==0 ){
-    return 0;
-  }
-  zTextMbcs = winUnicodeToMbcs(zTmpWide, useAnsi);
-  sqlite3_free(zTmpWide);
-  return zTextMbcs;
-}
-
-/*
-** This is a public wrapper for the winUtf8ToUnicode() function.
-*/
-LPWSTR sqlite3_win32_utf8_to_unicode(const char *zText){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winUtf8ToUnicode(zText);
-}
-
-/*
-** This is a public wrapper for the winUnicodeToUtf8() function.
-*/
-char *sqlite3_win32_unicode_to_utf8(LPCWSTR zWideText){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zWideText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winUnicodeToUtf8(zWideText);
-}
-
-/*
-** This is a public wrapper for the winMbcsToUtf8() function.
-*/
-char *sqlite3_win32_mbcs_to_utf8(const char *zText){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winMbcsToUtf8(zText, osAreFileApisANSI());
-}
-
-/*
-** This is a public wrapper for the winMbcsToUtf8() function.
-*/
-char *sqlite3_win32_mbcs_to_utf8_v2(const char *zText, int useAnsi){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winMbcsToUtf8(zText, useAnsi);
-}
-
-/*
-** This is a public wrapper for the winUtf8ToMbcs() function.
-*/
-char *sqlite3_win32_utf8_to_mbcs(const char *zText){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winUtf8ToMbcs(zText, osAreFileApisANSI());
-}
-
-/*
-** This is a public wrapper for the winUtf8ToMbcs() function.
-*/
-char *sqlite3_win32_utf8_to_mbcs_v2(const char *zText, int useAnsi){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !zText ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
-#ifndef SQLITE_OMIT_AUTOINIT
-  if( sqlite3_initialize() ) return 0;
-#endif
-  return winUtf8ToMbcs(zText, useAnsi);
-}
-
-/*
-** This function sets the data directory or the temporary directory based on
-** the provided arguments.  The type argument must be 1 in order to set the
-** data directory or 2 in order to set the temporary directory.  The zValue
-** argument is the name of the directory to use.  The return value will be
-** SQLITE_OK if successful.
-*/
-int sqlite3_win32_set_directory(DWORD type, LPCWSTR zValue){
-  char **ppDirectory = 0;
-#ifndef SQLITE_OMIT_AUTOINIT
-  int rc = sqlite3_initialize();
-  if( rc ) return rc;
-#endif
-  if( type==SQLITE_WIN32_DATA_DIRECTORY_TYPE ){
-    ppDirectory = &sqlite3_data_directory;
-  }else if( type==SQLITE_WIN32_TEMP_DIRECTORY_TYPE ){
-    ppDirectory = &sqlite3_temp_directory;
-  }
-  assert( !ppDirectory || type==SQLITE_WIN32_DATA_DIRECTORY_TYPE
-          || type==SQLITE_WIN32_TEMP_DIRECTORY_TYPE
-  );
-  assert( !ppDirectory || sqlite3MemdebugHasType(*ppDirectory, MEMTYPE_HEAP) );
-  if( ppDirectory ){
-    char *zValueUtf8 = 0;
-    if( zValue && zValue[0] ){
-      zValueUtf8 = winUnicodeToUtf8(zValue);
-      if ( zValueUtf8==0 ){
-        return SQLITE_NOMEM_BKPT;
-      }
-    }
-    sqlite3_free(*ppDirectory);
-    *ppDirectory = zValueUtf8;
-    return SQLITE_OK;
-  }
-  return SQLITE_ERROR;
-}
-
-/*
-** The return value of winGetLastErrorMsg
-** is zero if the error message fits in the buffer, or non-zero
-** otherwise (if the message was truncated).
-*/
-static int winGetLastErrorMsg(DWORD lastErrno, int nBuf, char *zBuf){
-  /* FormatMessage returns 0 on failure.  Otherwise it
-  ** returns the number of TCHARs written to the output
-  ** buffer, excluding the terminating null char.
-  */
-  DWORD dwLen = 0;
-  char *zOut = 0;
-
-  if( osIsNT() ){
-#if SQLITE_OS_WINRT
-    WCHAR zTempWide[SQLITE_WIN32_MAX_ERRMSG_CHARS+1];
-    dwLen = osFormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
-                             FORMAT_MESSAGE_IGNORE_INSERTS,
-                             NULL,
-                             lastErrno,
-                             0,
-                             zTempWide,
-                             SQLITE_WIN32_MAX_ERRMSG_CHARS,
-                             0);
-#else
-    LPWSTR zTempWide = NULL;
-    dwLen = osFormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
-                             FORMAT_MESSAGE_FROM_SYSTEM |
-                             FORMAT_MESSAGE_IGNORE_INSERTS,
-                             NULL,
-                             lastErrno,
-                             0,
-                             (LPWSTR) &zTempWide,
-                             0,
-                             0);
-#endif
-    if( dwLen > 0 ){
-      /* allocate a buffer and convert to UTF8 */
-      sqlite3BeginBenignMalloc();
-      zOut = winUnicodeToUtf8(zTempWide);
-      sqlite3EndBenignMalloc();
-#if !SQLITE_OS_WINRT
-      /* free the system buffer allocated by FormatMessage */
-      osLocalFree(zTempWide);
-#endif
-    }
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
-    char *zTemp = NULL;
-    dwLen = osFormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
-                             FORMAT_MESSAGE_FROM_SYSTEM |
-                             FORMAT_MESSAGE_IGNORE_INSERTS,
-                             NULL,
-                             lastErrno,
-                             0,
-                             (LPSTR) &zTemp,
-                             0,
-                             0);
-    if( dwLen > 0 ){
-      /* allocate a buffer and convert to UTF8 */
-      sqlite3BeginBenignMalloc();
-      zOut = winMbcsToUtf8(zTemp, osAreFileApisANSI());
-      sqlite3EndBenignMalloc();
-      /* free the system buffer allocated by FormatMessage */
-      osLocalFree(zTemp);
-    }
-  }
-#endif
-  if( 0 == dwLen ){
-    sqlite3_snprintf(nBuf, zBuf, "OsError 0x%lx (%lu)", lastErrno, lastErrno);
-  }else{
-    /* copy a maximum of nBuf chars to output buffer */
-    sqlite3_snprintf(nBuf, zBuf, "%s", zOut);
-    /* free the UTF8 buffer */
-    sqlite3_free(zOut);
-  }
-  return 0;
-}
-
-/*
-**
-** This function - winLogErrorAtLine() - is only ever called via the macro
-** winLogError().
-**
-** This routine is invoked after an error occurs in an OS function.
-** It logs a message using sqlite3_log() containing the current value of
-** error code and, if possible, the human-readable equivalent from
-** FormatMessage.
-**
-** The first argument passed to the macro should be the error code that
-** will be returned to SQLite (e.g. SQLITE_IOERR_DELETE, SQLITE_CANTOPEN).
-** The two subsequent arguments should be the name of the OS function that
-** failed and the associated file-system path, if any.
-*/
-#define winLogError(a,b,c,d)   winLogErrorAtLine(a,b,c,d,__LINE__)
-static int winLogErrorAtLine(
-  int errcode,                    /* SQLite error code */
-  DWORD lastErrno,                /* Win32 last error */
-  const char *zFunc,              /* Name of OS function that failed */
-  const char *zPath,              /* File path associated with error */
-  int iLine                       /* Source line number where error occurred */
-){
-  char zMsg[500];                 /* Human readable error text */
-  int i;                          /* Loop counter */
-
-  zMsg[0] = 0;
-  winGetLastErrorMsg(lastErrno, sizeof(zMsg), zMsg);
-  assert( errcode!=SQLITE_OK );
-  if( zPath==0 ) zPath = "";
-  for(i=0; zMsg[i] && zMsg[i]!='\r' && zMsg[i]!='\n'; i++){}
-  zMsg[i] = 0;
-  sqlite3_log(errcode,
-      "os_win.c:%d: (%lu) %s(%s) - %s",
-      iLine, lastErrno, zFunc, zPath, zMsg
-  );
-
-  return errcode;
-}
-
-/*
-** The number of times that a ReadFile(), WriteFile(), and DeleteFile()
-** will be retried following a locking error - probably caused by
-** antivirus software.  Also the initial delay before the first retry.
-** The delay increases linearly with each retry.
-*/
-#ifndef SQLITE_WIN32_IOERR_RETRY
-# define SQLITE_WIN32_IOERR_RETRY 10
-#endif
-#ifndef SQLITE_WIN32_IOERR_RETRY_DELAY
-# define SQLITE_WIN32_IOERR_RETRY_DELAY 25
-#endif
-static int winIoerrRetry = SQLITE_WIN32_IOERR_RETRY;
-static int winIoerrRetryDelay = SQLITE_WIN32_IOERR_RETRY_DELAY;
-
-/*
-** The "winIoerrCanRetry1" macro is used to determine if a particular I/O
-** error code obtained via GetLastError() is eligible to be retried.  It
-** must accept the error code DWORD as its only argument and should return
-** non-zero if the error code is transient in nature and the operation
-** responsible for generating the original error might succeed upon being
-** retried.  The argument to this macro should be a variable.
-**
-** Additionally, a macro named "winIoerrCanRetry2" may be defined.  If it
-** is defined, it will be consulted only when the macro "winIoerrCanRetry1"
-** returns zero.  The "winIoerrCanRetry2" macro is completely optional and
-** may be used to include additional error codes in the set that should
-** result in the failing I/O operation being retried by the caller.  If
-** defined, the "winIoerrCanRetry2" macro must exhibit external semantics
-** identical to those of the "winIoerrCanRetry1" macro.
-*/
-#if !defined(winIoerrCanRetry1)
-#define winIoerrCanRetry1(a) (((a)==ERROR_ACCESS_DENIED)        || \
-                              ((a)==ERROR_SHARING_VIOLATION)    || \
-                              ((a)==ERROR_LOCK_VIOLATION)       || \
-                              ((a)==ERROR_DEV_NOT_EXIST)        || \
-                              ((a)==ERROR_NETNAME_DELETED)      || \
-                              ((a)==ERROR_SEM_TIMEOUT)          || \
-                              ((a)==ERROR_NETWORK_UNREACHABLE))
-#endif
-
-/*
-** If a ReadFile() or WriteFile() error occurs, invoke this routine
-** to see if it should be retried.  Return TRUE to retry.  Return FALSE
-** to give up with an error.
-*/
-static int winRetryIoerr(int *pnRetry, DWORD *pError){
-  DWORD e = osGetLastError();
-  if( *pnRetry>=winIoerrRetry ){
-    if( pError ){
-      *pError = e;
-    }
-    return 0;
-  }
-  if( winIoerrCanRetry1(e) ){
-    sqlite3_win32_sleep(winIoerrRetryDelay*(1+*pnRetry));
-    ++*pnRetry;
-    return 1;
-  }
-#if defined(winIoerrCanRetry2)
-  else if( winIoerrCanRetry2(e) ){
-    sqlite3_win32_sleep(winIoerrRetryDelay*(1+*pnRetry));
-    ++*pnRetry;
-    return 1;
-  }
-#endif
-  if( pError ){
-    *pError = e;
-  }
-  return 0;
-}
-
-/*
-** Log a I/O error retry episode.
-*/
-static void winLogIoerr(int nRetry, int lineno){
-  if( nRetry ){
-    sqlite3_log(SQLITE_NOTICE,
-      "delayed %dms for lock/sharing conflict at line %d",
-      winIoerrRetryDelay*nRetry*(nRetry+1)/2, lineno
-    );
-  }
-}
-
-/*
-** This #if does not rely on the SQLITE_OS_WINCE define because the
-** corresponding section in "date.c" cannot use it.
-*/
-#if !defined(SQLITE_OMIT_LOCALTIME) && defined(_WIN32_WCE) && \
-    (!defined(SQLITE_MSVC_LOCALTIME_API) || !SQLITE_MSVC_LOCALTIME_API)
-/*
-** The MSVC CRT on Windows CE may not have a localtime() function.
-** So define a substitute.
-*/
-#  include <time.h>
-struct tm *__cdecl localtime(const time_t *t)
-{
-  static struct tm y;
-  FILETIME uTm, lTm;
-  SYSTEMTIME pTm;
-  sqlite3_int64 t64;
-  t64 = *t;
-  t64 = (t64 + 11644473600)*10000000;
-  uTm.dwLowDateTime = (DWORD)(t64 & 0xFFFFFFFF);
-  uTm.dwHighDateTime= (DWORD)(t64 >> 32);
-  osFileTimeToLocalFileTime(&uTm,&lTm);
-  osFileTimeToSystemTime(&lTm,&pTm);
-  y.tm_year = pTm.wYear - 1900;
-  y.tm_mon = pTm.wMonth - 1;
-  y.tm_wday = pTm.wDayOfWeek;
-  y.tm_mday = pTm.wDay;
-  y.tm_hour = pTm.wHour;
-  y.tm_min = pTm.wMinute;
-  y.tm_sec = pTm.wSecond;
-  return &y;
-}
-#endif
-
-#if SQLITE_OS_WINCE
-/*************************************************************************
-** This section contains code for WinCE only.
-*/
-#define HANDLE_TO_WINFILE(a) (winFile*)&((char*)a)[-(int)offsetof(winFile,h)]
-
-/*
-** Acquire a lock on the handle h
-*/
-static void winceMutexAcquire(HANDLE h){
-   DWORD dwErr;
-   do {
-     dwErr = osWaitForSingleObject(h, INFINITE);
-   } while (dwErr != WAIT_OBJECT_0 && dwErr != WAIT_ABANDONED);
-}
-/*
-** Release a lock acquired by winceMutexAcquire()
-*/
-#define winceMutexRelease(h) ReleaseMutex(h)
-
-/*
-** Create the mutex and shared memory used for locking in the file
-** descriptor pFile
-*/
-static int winceCreateLock(const char *zFilename, winFile *pFile){
-  LPWSTR zTok;
-  LPWSTR zName;
-  DWORD lastErrno;
-  BOOL bLogged = FALSE;
-  BOOL bInit = TRUE;
-
-  zName = winUtf8ToUnicode(zFilename);
-  if( zName==0 ){
-    /* out of memory */
-    return SQLITE_IOERR_NOMEM_BKPT;
-  }
-
-  /* Initialize the local lockdata */
-  memset(&pFile->local, 0, sizeof(pFile->local));
-
-  /* Replace the backslashes from the filename and lowercase it
-  ** to derive a mutex name. */
-  zTok = osCharLowerW(zName);
-  for (;*zTok;zTok++){
-    if (*zTok == '\\') *zTok = '_';
-  }
-
-  /* Create/open the named mutex */
-  pFile->hMutex = osCreateMutexW(NULL, FALSE, zName);
-  if (!pFile->hMutex){
-    pFile->lastErrno = osGetLastError();
-    sqlite3_free(zName);
-    return winLogError(SQLITE_IOERR, pFile->lastErrno,
-                       "winceCreateLock1", zFilename);
-  }
-
-  /* Acquire the mutex before continuing */
-  winceMutexAcquire(pFile->hMutex);
-
-  /* Since the names of named mutexes, semaphores, file mappings etc are
-  ** case-sensitive, take advantage of that by uppercasing the mutex name
-  ** and using that as the shared filemapping name.
-  */
-  osCharUpperW(zName);
-  pFile->hShared = osCreateFileMappingW(INVALID_HANDLE_VALUE, NULL,
-                                        PAGE_READWRITE, 0, sizeof(winceLock),
-                                        zName);
-
-  /* Set a flag that indicates we're the first to create the memory so it
-  ** must be zero-initialized */
-  lastErrno = osGetLastError();
-  if (lastErrno == ERROR_ALREADY_EXISTS){
-    bInit = FALSE;
-  }
-
-  sqlite3_free(zName);
-
-  /* If we succeeded in making the shared memory handle, map it. */
-  if( pFile->hShared ){
-    pFile->shared = (winceLock*)osMapViewOfFile(pFile->hShared,
-             FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, sizeof(winceLock));
-    /* If mapping failed, close the shared memory handle and erase it */
-    if( !pFile->shared ){
-      pFile->lastErrno = osGetLastError();
-      winLogError(SQLITE_IOERR, pFile->lastErrno,
-                  "winceCreateLock2", zFilename);
-      bLogged = TRUE;
-      osCloseHandle(pFile->hShared);
-      pFile->hShared = NULL;
-    }
-  }
-
-  /* If shared memory could not be created, then close the mutex and fail */
-  if( pFile->hShared==NULL ){
-    if( !bLogged ){
-      pFile->lastErrno = lastErrno;
-      winLogError(SQLITE_IOERR, pFile->lastErrno,
-                  "winceCreateLock3", zFilename);
-      bLogged = TRUE;
-    }
-    winceMutexRelease(pFile->hMutex);
-    osCloseHandle(pFile->hMutex);
-    pFile->hMutex = NULL;
-    return SQLITE_IOERR;
-  }
-
-  /* Initialize the shared memory if we're supposed to */
-  if( bInit ){
-    memset(pFile->shared, 0, sizeof(winceLock));
-  }
-
-  winceMutexRelease(pFile->hMutex);
-  return SQLITE_OK;
-}
-
-/*
-** Destroy the part of winFile that deals with wince locks
-*/
-static void winceDestroyLock(winFile *pFile){
-  if (pFile->hMutex){
-    /* Acquire the mutex */
-    winceMutexAcquire(pFile->hMutex);
-
-    /* The following blocks should probably assert in debug mode, but they
-       are to cleanup in case any locks remained open */
-    if (pFile->local.nReaders){
-      pFile->shared->nReaders --;
-    }
-    if (pFile->local.bReserved){
-      pFile->shared->bReserved = FALSE;
-    }
-    if (pFile->local.bPending){
-      pFile->shared->bPending = FALSE;
-    }
-    if (pFile->local.bExclusive){
-      pFile->shared->bExclusive = FALSE;
-    }
-
-    /* De-reference and close our copy of the shared memory handle */
-    osUnmapViewOfFile(pFile->shared);
-    osCloseHandle(pFile->hShared);
-
-    /* Done with the mutex */
-    winceMutexRelease(pFile->hMutex);
-    osCloseHandle(pFile->hMutex);
-    pFile->hMutex = NULL;
-  }
-}
-
-/*
-** An implementation of the LockFile() API of Windows for CE
-*/
-static BOOL winceLockFile(
-  LPHANDLE phFile,
-  DWORD dwFileOffsetLow,
-  DWORD dwFileOffsetHigh,
-  DWORD nNumberOfBytesToLockLow,
-  DWORD nNumberOfBytesToLockHigh
-){
-  winFile *pFile = HANDLE_TO_WINFILE(phFile);
-  BOOL bReturn = FALSE;
-
-  UNUSED_PARAMETER(dwFileOffsetHigh);
-  UNUSED_PARAMETER(nNumberOfBytesToLockHigh);
-
-  if (!pFile->hMutex) return TRUE;
-  winceMutexAcquire(pFile->hMutex);
-
-  /* Wanting an exclusive lock? */
-  if (dwFileOffsetLow == (DWORD)SHARED_FIRST
-       && nNumberOfBytesToLockLow == (DWORD)SHARED_SIZE){
-    if (pFile->shared->nReaders == 0 && pFile->shared->bExclusive == 0){
-       pFile->shared->bExclusive = TRUE;
-       pFile->local.bExclusive = TRUE;
-       bReturn = TRUE;
-    }
-  }
-
-  /* Want a read-only lock? */
-  else if (dwFileOffsetLow == (DWORD)SHARED_FIRST &&
-           nNumberOfBytesToLockLow == 1){
-    if (pFile->shared->bExclusive == 0){
-      pFile->local.nReaders ++;
-      if (pFile->local.nReaders == 1){
-        pFile->shared->nReaders ++;
-      }
-      bReturn = TRUE;
-    }
-  }
-
-  /* Want a pending lock? */
-  else if (dwFileOffsetLow == (DWORD)PENDING_BYTE
-           && nNumberOfBytesToLockLow == 1){
-    /* If no pending lock has been acquired, then acquire it */
-    if (pFile->shared->bPending == 0) {
-      pFile->shared->bPending = TRUE;
-      pFile->local.bPending = TRUE;
-      bReturn = TRUE;
-    }
-  }
-
-  /* Want a reserved lock? */
-  else if (dwFileOffsetLow == (DWORD)RESERVED_BYTE
-           && nNumberOfBytesToLockLow == 1){
-    if (pFile->shared->bReserved == 0) {
-      pFile->shared->bReserved = TRUE;
-      pFile->local.bReserved = TRUE;
-      bReturn = TRUE;
-    }
-  }
-
-  winceMutexRelease(pFile->hMutex);
-  return bReturn;
-}
-
-/*
-** An implementation of the UnlockFile API of Windows for CE
-*/
-static BOOL winceUnlockFile(
-  LPHANDLE phFile,
-  DWORD dwFileOffsetLow,
-  DWORD dwFileOffsetHigh,
-  DWORD nNumberOfBytesToUnlockLow,
-  DWORD nNumberOfBytesToUnlockHigh
-){
-  winFile *pFile = HANDLE_TO_WINFILE(phFile);
-  BOOL bReturn = FALSE;
-
-  UNUSED_PARAMETER(dwFileOffsetHigh);
-  UNUSED_PARAMETER(nNumberOfBytesToUnlockHigh);
-
-  if (!pFile->hMutex) return TRUE;
+  /* Acquire the mutex before continuing */
   winceMutexAcquire(pFile->hMutex);
+  
+  /* Since the names of named mutexes, semaphores, file mappings etc are 
+  ** case-sensitive, take advantage of that by uppercasing the mutex name
+  ** and using that as the shared filemapping name.
+  */
+  CharUpperW(zName);
+  pFile->hShared = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL,
+                                       PAGE_READWRITE, 0, sizeof(winceLock),
+                                       zName);  
 
-  /* Releasing a reader lock or an exclusive lock */
-  if (dwFileOffsetLow == (DWORD)SHARED_FIRST){
-    /* Did we have an exclusive lock? */
-    if (pFile->local.bExclusive){
-      assert(nNumberOfBytesToUnlockLow == (DWORD)SHARED_SIZE);
-      pFile->local.bExclusive = FALSE;
-      pFile->shared->bExclusive = FALSE;
-      bReturn = TRUE;
-    }
-
-    /* Did we just have a reader lock? */
-    else if (pFile->local.nReaders){
-      assert(nNumberOfBytesToUnlockLow == (DWORD)SHARED_SIZE
-             || nNumberOfBytesToUnlockLow == 1);
-      pFile->local.nReaders --;
-      if (pFile->local.nReaders == 0)
-      {
-        pFile->shared->nReaders --;
-      }
-      bReturn = TRUE;
-    }
-  }
-
-  /* Releasing a pending lock */
-  else if (dwFileOffsetLow == (DWORD)PENDING_BYTE
-           && nNumberOfBytesToUnlockLow == 1){
-    if (pFile->local.bPending){
-      pFile->local.bPending = FALSE;
-      pFile->shared->bPending = FALSE;
-      bReturn = TRUE;
-    }
-  }
-  /* Releasing a reserved lock */
-  else if (dwFileOffsetLow == (DWORD)RESERVED_BYTE
-           && nNumberOfBytesToUnlockLow == 1){
-    if (pFile->local.bReserved) {
-      pFile->local.bReserved = FALSE;
-      pFile->shared->bReserved = FALSE;
-      bReturn = TRUE;
-    }
-  }
-
-  winceMutexRelease(pFile->hMutex);
-  return bReturn;
-}
-/*
-** End of the special code for wince
-*****************************************************************************/
-#endif /* SQLITE_OS_WINCE */
-
-/*
-** Lock a file region.
-*/
-static BOOL winLockFile(
-  LPHANDLE phFile,
-  DWORD flags,
-  DWORD offsetLow,
-  DWORD offsetHigh,
-  DWORD numBytesLow,
-  DWORD numBytesHigh
-){
-#if SQLITE_OS_WINCE
-  /*
-  ** NOTE: Windows CE is handled differently here due its lack of the Win32
-  **       API LockFile.
-  */
-  return winceLockFile(phFile, offsetLow, offsetHigh,
-                       numBytesLow, numBytesHigh);
-#else
-  if( osIsNT() ){
-    OVERLAPPED ovlp;
-    memset(&ovlp, 0, sizeof(OVERLAPPED));
-    ovlp.Offset = offsetLow;
-    ovlp.OffsetHigh = offsetHigh;
-    return osLockFileEx(*phFile, flags, 0, numBytesLow, numBytesHigh, &ovlp);
-  }else{
-    return osLockFile(*phFile, offsetLow, offsetHigh, numBytesLow,
-                      numBytesHigh);
-  }
-#endif
-}
-
-/*
-** Unlock a file region.
- */
-static BOOL winUnlockFile(
-  LPHANDLE phFile,
-  DWORD offsetLow,
-  DWORD offsetHigh,
-  DWORD numBytesLow,
-  DWORD numBytesHigh
-){
-#if SQLITE_OS_WINCE
-  /*
-  ** NOTE: Windows CE is handled differently here due its lack of the Win32
-  **       API UnlockFile.
-  */
-  return winceUnlockFile(phFile, offsetLow, offsetHigh,
-                         numBytesLow, numBytesHigh);
-#else
-  if( osIsNT() ){
-    OVERLAPPED ovlp;
-    memset(&ovlp, 0, sizeof(OVERLAPPED));
-    ovlp.Offset = offsetLow;
-    ovlp.OffsetHigh = offsetHigh;
-    return osUnlockFileEx(*phFile, 0, numBytesLow, numBytesHigh, &ovlp);
-  }else{
-    return osUnlockFile(*phFile, offsetLow, offsetHigh, numBytesLow,
-                        numBytesHigh);
-  }
-#endif
-}
-
-/*****************************************************************************
-** The next group of routines implement the I/O methods specified
-** by the sqlite3_io_methods object.
-******************************************************************************/
-
-/*
-** Some Microsoft compilers lack this definition.
-*/
-#ifndef INVALID_SET_FILE_POINTER
-# define INVALID_SET_FILE_POINTER ((DWORD)-1)
-#endif
-
-/*
-** Move the current position of the file handle passed as the first
-** argument to offset iOffset within the file. If successful, return 0.
-** Otherwise, set pFile->lastErrno and return non-zero.
-*/
-static int winSeekFile(winFile *pFile, sqlite3_int64 iOffset){
-#if !SQLITE_OS_WINRT
-  LONG upperBits;                 /* Most sig. 32 bits of new offset */
-  LONG lowerBits;                 /* Least sig. 32 bits of new offset */
-  DWORD dwRet;                    /* Value returned by SetFilePointer() */
-  DWORD lastErrno;                /* Value returned by GetLastError() */
-
-  OSTRACE(("SEEK file=%p, offset=%lld\n", pFile->h, iOffset));
-
-  upperBits = (LONG)((iOffset>>32) & 0x7fffffff);
-  lowerBits = (LONG)(iOffset & 0xffffffff);
-
-  /* API oddity: If successful, SetFilePointer() returns a dword
-  ** containing the lower 32-bits of the new file-offset. Or, if it fails,
-  ** it returns INVALID_SET_FILE_POINTER. However according to MSDN,
-  ** INVALID_SET_FILE_POINTER may also be a valid new offset. So to determine
-  ** whether an error has actually occurred, it is also necessary to call
-  ** GetLastError().
-  */
-  dwRet = osSetFilePointer(pFile->h, lowerBits, &upperBits, FILE_BEGIN);
-
-  if( (dwRet==INVALID_SET_FILE_POINTER
-      && ((lastErrno = osGetLastError())!=NO_ERROR)) ){
-    pFile->lastErrno = lastErrno;
-    winLogError(SQLITE_IOERR_SEEK, pFile->lastErrno,
-                "winSeekFile", pFile->zPath);
-    OSTRACE(("SEEK file=%p, rc=SQLITE_IOERR_SEEK\n", pFile->h));
-    return 1;
-  }
-
-  OSTRACE(("SEEK file=%p, rc=SQLITE_OK\n", pFile->h));
-  return 0;
-#else
-  /*
-  ** Same as above, except that this implementation works for WinRT.
-  */
-
-  LARGE_INTEGER x;                /* The new offset */
-  BOOL bRet;                      /* Value returned by SetFilePointerEx() */
-
-  x.QuadPart = iOffset;
-  bRet = osSetFilePointerEx(pFile->h, x, 0, FILE_BEGIN);
-
-  if(!bRet){
-    pFile->lastErrno = osGetLastError();
-    winLogError(SQLITE_IOERR_SEEK, pFile->lastErrno,
-                "winSeekFile", pFile->zPath);
-    OSTRACE(("SEEK file=%p, rc=SQLITE_IOERR_SEEK\n", pFile->h));
-    return 1;
-  }
-
-  OSTRACE(("SEEK file=%p, rc=SQLITE_OK\n", pFile->h));
-  return 0;
-#endif
-}
-
-#if SQLITE_MAX_MMAP_SIZE>0
-/* Forward references to VFS helper methods used for memory mapped files */
-static int winMapfile(winFile*, sqlite3_int64);
-static int winUnmapfile(winFile*);
-#endif
-
-/*
-** Close a file.
-**
-** It is reported that an attempt to close a handle might sometimes
-** fail.  This is a very unreasonable result, but Windows is notorious
-** for being unreasonable so I do not doubt that it might happen.  If
-** the close fails, we pause for 100 milliseconds and try again.  As
-** many as MX_CLOSE_ATTEMPT attempts to close the handle are made before
-** giving up and returning an error.
-*/
-#define MX_CLOSE_ATTEMPT 3
-static int winClose(sqlite3_file *id){
-  int rc, cnt = 0;
-  winFile *pFile = (winFile*)id;
-
-  assert( id!=0 );
-#ifndef SQLITE_OMIT_WAL
-  assert( pFile->pShm==0 );
-#endif
-  assert( pFile->h!=NULL && pFile->h!=INVALID_HANDLE_VALUE );
-  OSTRACE(("CLOSE pid=%lu, pFile=%p, file=%p\n",
-           osGetCurrentProcessId(), pFile, pFile->h));
-
-#if SQLITE_MAX_MMAP_SIZE>0
-  winUnmapfile(pFile);
-#endif
-
-  do{
-    rc = osCloseHandle(pFile->h);
-    /* SimulateIOError( rc=0; cnt=MX_CLOSE_ATTEMPT; ); */
-  }while( rc==0 && ++cnt < MX_CLOSE_ATTEMPT && (sqlite3_win32_sleep(100), 1) );
-#if SQLITE_OS_WINCE
-#define WINCE_DELETION_ATTEMPTS 3
-  {
-    winVfsAppData *pAppData = (winVfsAppData*)pFile->pVfs->pAppData;
-    if( pAppData==NULL || !pAppData->bNoLock ){
-      winceDestroyLock(pFile);
-    }
-  }
-  if( pFile->zDeleteOnClose ){
-    int cnt = 0;
-    while(
-           osDeleteFileW(pFile->zDeleteOnClose)==0
-        && osGetFileAttributesW(pFile->zDeleteOnClose)!=0xffffffff
-        && cnt++ < WINCE_DELETION_ATTEMPTS
-    ){
-       sqlite3_win32_sleep(100);  /* Wait a little before trying again */
-    }
-    sqlite3_free(pFile->zDeleteOnClose);
-  }
-#endif
-  if( rc ){
-    pFile->h = NULL;
-  }
-  OpenCounter(-1);
-  OSTRACE(("CLOSE pid=%lu, pFile=%p, file=%p, rc=%s\n",
-           osGetCurrentProcessId(), pFile, pFile->h, rc ? "ok" : "failed"));
-  return rc ? SQLITE_OK
-            : winLogError(SQLITE_IOERR_CLOSE, osGetLastError(),
-                          "winClose", pFile->zPath);
-}
-
-/*
-** Read data from a file into a buffer.  Return SQLITE_OK if all
-** bytes were read successfully and SQLITE_IOERR if anything goes
-** wrong.
-*/
-static int winRead(
-  sqlite3_file *id,          /* File to read from */
-  void *pBuf,                /* Write content into this buffer */
-  int amt,                   /* Number of bytes to read */
-  sqlite3_int64 offset       /* Begin reading at this offset */
-){
-#if !SQLITE_OS_WINCE && !defined(SQLITE_WIN32_NO_OVERLAPPED)
-  OVERLAPPED overlapped;          /* The offset for ReadFile. */
-#endif
-  winFile *pFile = (winFile*)id;  /* file handle */
-  DWORD nRead;                    /* Number of bytes actually read from file */
-  int nRetry = 0;                 /* Number of retrys */
-
-  assert( id!=0 );
-  assert( amt>0 );
-  assert( offset>=0 );
-  SimulateIOError(return SQLITE_IOERR_READ);
-  OSTRACE(("READ pid=%lu, pFile=%p, file=%p, buffer=%p, amount=%d, "
-           "offset=%lld, lock=%d\n", osGetCurrentProcessId(), pFile,
-           pFile->h, pBuf, amt, offset, pFile->locktype));
-
-#if SQLITE_MAX_MMAP_SIZE>0
-  /* Deal with as much of this read request as possible by transfering
-  ** data from the memory mapping using memcpy().  */
-  if( offset<pFile->mmapSize ){
-    if( offset+amt <= pFile->mmapSize ){
-      memcpy(pBuf, &((u8 *)(pFile->pMapRegion))[offset], amt);
-      OSTRACE(("READ-MMAP pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-               osGetCurrentProcessId(), pFile, pFile->h));
-      return SQLITE_OK;
-    }else{
-      int nCopy = (int)(pFile->mmapSize - offset);
-      memcpy(pBuf, &((u8 *)(pFile->pMapRegion))[offset], nCopy);
-      pBuf = &((u8 *)pBuf)[nCopy];
-      amt -= nCopy;
-      offset += nCopy;
-    }
-  }
-#endif
-
-#if SQLITE_OS_WINCE || defined(SQLITE_WIN32_NO_OVERLAPPED)
-  if( winSeekFile(pFile, offset) ){
-    OSTRACE(("READ pid=%lu, pFile=%p, file=%p, rc=SQLITE_FULL\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return SQLITE_FULL;
-  }
-  while( !osReadFile(pFile->h, pBuf, amt, &nRead, 0) ){
-#else
-  memset(&overlapped, 0, sizeof(OVERLAPPED));
-  overlapped.Offset = (LONG)(offset & 0xffffffff);
-  overlapped.OffsetHigh = (LONG)((offset>>32) & 0x7fffffff);
-  while( !osReadFile(pFile->h, pBuf, amt, &nRead, &overlapped) &&
-         osGetLastError()!=ERROR_HANDLE_EOF ){
-#endif
-    DWORD lastErrno;
-    if( winRetryIoerr(&nRetry, &lastErrno) ) continue;
-    pFile->lastErrno = lastErrno;
-    OSTRACE(("READ pid=%lu, pFile=%p, file=%p, rc=SQLITE_IOERR_READ\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return winLogError(SQLITE_IOERR_READ, pFile->lastErrno,
-                       "winRead", pFile->zPath);
-  }
-  winLogIoerr(nRetry, __LINE__);
-  if( nRead<(DWORD)amt ){
-    /* Unread parts of the buffer must be zero-filled */
-    memset(&((char*)pBuf)[nRead], 0, amt-nRead);
-    OSTRACE(("READ pid=%lu, pFile=%p, file=%p, rc=SQLITE_IOERR_SHORT_READ\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return SQLITE_IOERR_SHORT_READ;
-  }
-
-  OSTRACE(("READ pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), pFile, pFile->h));
-  return SQLITE_OK;
-}
-
-/*
-** Write data from a buffer into a file.  Return SQLITE_OK on success
-** or some other error code on failure.
-*/
-static int winWrite(
-  sqlite3_file *id,               /* File to write into */
-  const void *pBuf,               /* The bytes to be written */
-  int amt,                        /* Number of bytes to write */
-  sqlite3_int64 offset            /* Offset into the file to begin writing at */
-){
-  int rc = 0;                     /* True if error has occurred, else false */
-  winFile *pFile = (winFile*)id;  /* File handle */
-  int nRetry = 0;                 /* Number of retries */
-
-  assert( amt>0 );
-  assert( pFile );
-  SimulateIOError(return SQLITE_IOERR_WRITE);
-  SimulateDiskfullError(return SQLITE_FULL);
-
-  OSTRACE(("WRITE pid=%lu, pFile=%p, file=%p, buffer=%p, amount=%d, "
-           "offset=%lld, lock=%d\n", osGetCurrentProcessId(), pFile,
-           pFile->h, pBuf, amt, offset, pFile->locktype));
-
-#if defined(SQLITE_MMAP_READWRITE) && SQLITE_MAX_MMAP_SIZE>0
-  /* Deal with as much of this write request as possible by transfering
-  ** data from the memory mapping using memcpy().  */
-  if( offset<pFile->mmapSize ){
-    if( offset+amt <= pFile->mmapSize ){
-      memcpy(&((u8 *)(pFile->pMapRegion))[offset], pBuf, amt);
-      OSTRACE(("WRITE-MMAP pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-               osGetCurrentProcessId(), pFile, pFile->h));
-      return SQLITE_OK;
-    }else{
-      int nCopy = (int)(pFile->mmapSize - offset);
-      memcpy(&((u8 *)(pFile->pMapRegion))[offset], pBuf, nCopy);
-      pBuf = &((u8 *)pBuf)[nCopy];
-      amt -= nCopy;
-      offset += nCopy;
-    }
-  }
-#endif
-
-#if SQLITE_OS_WINCE || defined(SQLITE_WIN32_NO_OVERLAPPED)
-  rc = winSeekFile(pFile, offset);
-  if( rc==0 ){
-#else
-  {
-#endif
-#if !SQLITE_OS_WINCE && !defined(SQLITE_WIN32_NO_OVERLAPPED)
-    OVERLAPPED overlapped;        /* The offset for WriteFile. */
-#endif
-    u8 *aRem = (u8 *)pBuf;        /* Data yet to be written */
-    int nRem = amt;               /* Number of bytes yet to be written */
-    DWORD nWrite;                 /* Bytes written by each WriteFile() call */
-    DWORD lastErrno = NO_ERROR;   /* Value returned by GetLastError() */
-
-#if !SQLITE_OS_WINCE && !defined(SQLITE_WIN32_NO_OVERLAPPED)
-    memset(&overlapped, 0, sizeof(OVERLAPPED));
-    overlapped.Offset = (LONG)(offset & 0xffffffff);
-    overlapped.OffsetHigh = (LONG)((offset>>32) & 0x7fffffff);
-#endif
-
-    while( nRem>0 ){
-#if SQLITE_OS_WINCE || defined(SQLITE_WIN32_NO_OVERLAPPED)
-      if( !osWriteFile(pFile->h, aRem, nRem, &nWrite, 0) ){
-#else
-      if( !osWriteFile(pFile->h, aRem, nRem, &nWrite, &overlapped) ){
-#endif
-        if( winRetryIoerr(&nRetry, &lastErrno) ) continue;
-        break;
-      }
-      assert( nWrite==0 || nWrite<=(DWORD)nRem );
-      if( nWrite==0 || nWrite>(DWORD)nRem ){
-        lastErrno = osGetLastError();
-        break;
-      }
-#if !SQLITE_OS_WINCE && !defined(SQLITE_WIN32_NO_OVERLAPPED)
-      offset += nWrite;
-      overlapped.Offset = (LONG)(offset & 0xffffffff);
-      overlapped.OffsetHigh = (LONG)((offset>>32) & 0x7fffffff);
-#endif
-      aRem += nWrite;
-      nRem -= nWrite;
-    }
-    if( nRem>0 ){
-      pFile->lastErrno = lastErrno;
-      rc = 1;
-    }
+  /* Set a flag that indicates we're the first to create the memory so it 
+  ** must be zero-initialized */
+  if (GetLastError() == ERROR_ALREADY_EXISTS){
+    bInit = FALSE;
   }
 
-  if( rc ){
-    if(   ( pFile->lastErrno==ERROR_HANDLE_DISK_FULL )
-       || ( pFile->lastErrno==ERROR_DISK_FULL )){
-      OSTRACE(("WRITE pid=%lu, pFile=%p, file=%p, rc=SQLITE_FULL\n",
-               osGetCurrentProcessId(), pFile, pFile->h));
-      return winLogError(SQLITE_FULL, pFile->lastErrno,
-                         "winWrite1", pFile->zPath);
+  free(zName);
+
+  /* If we succeeded in making the shared memory handle, map it. */
+  if (pFile->hShared){
+    pFile->shared = (winceLock*)MapViewOfFile(pFile->hShared, 
+             FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, sizeof(winceLock));
+    /* If mapping failed, close the shared memory handle and erase it */
+    if (!pFile->shared){
+      pFile->lastErrno = GetLastError();
+      CloseHandle(pFile->hShared);
+      pFile->hShared = NULL;
     }
-    OSTRACE(("WRITE pid=%lu, pFile=%p, file=%p, rc=SQLITE_IOERR_WRITE\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return winLogError(SQLITE_IOERR_WRITE, pFile->lastErrno,
-                       "winWrite2", pFile->zPath);
-  }else{
-    winLogIoerr(nRetry, __LINE__);
   }
-  OSTRACE(("WRITE pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), pFile, pFile->h));
-  return SQLITE_OK;
-}
-
-/*
-** Truncate an open file to a specified size
-*/
-static int winTruncate(sqlite3_file *id, sqlite3_int64 nByte){
-  winFile *pFile = (winFile*)id;  /* File handle object */
-  int rc = SQLITE_OK;             /* Return code for this function */
-  DWORD lastErrno;
-
-  assert( pFile );
-  SimulateIOError(return SQLITE_IOERR_TRUNCATE);
-  OSTRACE(("TRUNCATE pid=%lu, pFile=%p, file=%p, size=%lld, lock=%d\n",
-           osGetCurrentProcessId(), pFile, pFile->h, nByte, pFile->locktype));
 
-  /* If the user has configured a chunk-size for this file, truncate the
-  ** file so that it consists of an integer number of chunks (i.e. the
-  ** actual file size after the operation may be larger than the requested
-  ** size).
-  */
-  if( pFile->szChunk>0 ){
-    nByte = ((nByte + pFile->szChunk - 1)/pFile->szChunk) * pFile->szChunk;
+  /* If shared memory could not be created, then close the mutex and fail */
+  if (pFile->hShared == NULL){
+    winceMutexRelease(pFile->hMutex);
+    CloseHandle(pFile->hMutex);
+    pFile->hMutex = NULL;
+    return FALSE;
   }
-
-  /* SetEndOfFile() returns non-zero when successful, or zero when it fails. */
-  if( winSeekFile(pFile, nByte) ){
-    rc = winLogError(SQLITE_IOERR_TRUNCATE, pFile->lastErrno,
-                     "winTruncate1", pFile->zPath);
-  }else if( 0==osSetEndOfFile(pFile->h) &&
-            ((lastErrno = osGetLastError())!=ERROR_USER_MAPPED_FILE) ){
-    pFile->lastErrno = lastErrno;
-    rc = winLogError(SQLITE_IOERR_TRUNCATE, pFile->lastErrno,
-                     "winTruncate2", pFile->zPath);
-  }
-
-#if SQLITE_MAX_MMAP_SIZE>0
-  /* If the file was truncated to a size smaller than the currently
-  ** mapped region, reduce the effective mapping size as well. SQLite will
-  ** use read() and write() to access data beyond this point from now on.
-  */
-  if( pFile->pMapRegion && nByte<pFile->mmapSize ){
-    pFile->mmapSize = nByte;
+  
+  /* Initialize the shared memory if we're supposed to */
+  if (bInit) {
+    ZeroMemory(pFile->shared, sizeof(winceLock));
   }
-#endif
 
-  OSTRACE(("TRUNCATE pid=%lu, pFile=%p, file=%p, rc=%s\n",
-           osGetCurrentProcessId(), pFile, pFile->h, sqlite3ErrName(rc)));
-  return rc;
+  winceMutexRelease(pFile->hMutex);
+  return TRUE;
 }
 
-#ifdef SQLITE_TEST
-/*
-** Count the number of fullsyncs and normal syncs.  This is used to test
-** that syncs and fullsyncs are occuring at the right times.
-*/
-int sqlite3_sync_count = 0;
-int sqlite3_fullsync_count = 0;
-#endif
-
 /*
-** Make sure all writes to a particular file are committed to disk.
+** Destroy the part of winFile that deals with wince locks
 */
-static int winSync(sqlite3_file *id, int flags){
-#ifndef SQLITE_NO_SYNC
-  /*
-  ** Used only when SQLITE_NO_SYNC is not defined.
-   */
-  BOOL rc;
-#endif
-#if !defined(NDEBUG) || !defined(SQLITE_NO_SYNC) || \
-    defined(SQLITE_HAVE_OS_TRACE)
-  /*
-  ** Used when SQLITE_NO_SYNC is not defined and by the assert() and/or
-  ** OSTRACE() macros.
-   */
-  winFile *pFile = (winFile*)id;
-#else
-  UNUSED_PARAMETER(id);
-#endif
-
-  assert( pFile );
-  /* Check that one of SQLITE_SYNC_NORMAL or FULL was passed */
-  assert((flags&0x0F)==SQLITE_SYNC_NORMAL
-      || (flags&0x0F)==SQLITE_SYNC_FULL
-  );
-
-  /* Unix cannot, but some systems may return SQLITE_FULL from here. This
-  ** line is to test that doing so does not cause any problems.
-  */
-  SimulateDiskfullError( return SQLITE_FULL );
-
-  OSTRACE(("SYNC pid=%lu, pFile=%p, file=%p, flags=%x, lock=%d\n",
-           osGetCurrentProcessId(), pFile, pFile->h, flags,
-           pFile->locktype));
-
-#ifndef SQLITE_TEST
-  UNUSED_PARAMETER(flags);
-#else
-  if( (flags&0x0F)==SQLITE_SYNC_FULL ){
-    sqlite3_fullsync_count++;
-  }
-  sqlite3_sync_count++;
-#endif
+static void winceDestroyLock(winFile *pFile){
+  if (pFile->hMutex){
+    /* Acquire the mutex */
+    winceMutexAcquire(pFile->hMutex);
 
-  /* If we compiled with the SQLITE_NO_SYNC flag, then syncing is a
-  ** no-op
-  */
-#ifdef SQLITE_NO_SYNC
-  OSTRACE(("SYNC-NOP pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), pFile, pFile->h));
-  return SQLITE_OK;
-#else
-#if SQLITE_MAX_MMAP_SIZE>0
-  if( pFile->pMapRegion ){
-    if( osFlushViewOfFile(pFile->pMapRegion, 0) ){
-      OSTRACE(("SYNC-MMAP pid=%lu, pFile=%p, pMapRegion=%p, "
-               "rc=SQLITE_OK\n", osGetCurrentProcessId(),
-               pFile, pFile->pMapRegion));
-    }else{
-      pFile->lastErrno = osGetLastError();
-      OSTRACE(("SYNC-MMAP pid=%lu, pFile=%p, pMapRegion=%p, "
-               "rc=SQLITE_IOERR_MMAP\n", osGetCurrentProcessId(),
-               pFile, pFile->pMapRegion));
-      return winLogError(SQLITE_IOERR_MMAP, pFile->lastErrno,
-                         "winSync1", pFile->zPath);
+    /* The following blocks should probably assert in debug mode, but they
+       are to cleanup in case any locks remained open */
+    if (pFile->local.nReaders){
+      pFile->shared->nReaders --;
     }
-  }
-#endif
-  rc = osFlushFileBuffers(pFile->h);
-  SimulateIOError( rc=FALSE );
-  if( rc ){
-    OSTRACE(("SYNC pid=%lu, pFile=%p, file=%p, rc=SQLITE_OK\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return SQLITE_OK;
-  }else{
-    pFile->lastErrno = osGetLastError();
-    OSTRACE(("SYNC pid=%lu, pFile=%p, file=%p, rc=SQLITE_IOERR_FSYNC\n",
-             osGetCurrentProcessId(), pFile, pFile->h));
-    return winLogError(SQLITE_IOERR_FSYNC, pFile->lastErrno,
-                       "winSync2", pFile->zPath);
-  }
-#endif
-}
-
-/*
-** Determine the current size of a file in bytes
-*/
-static int winFileSize(sqlite3_file *id, sqlite3_int64 *pSize){
-  winFile *pFile = (winFile*)id;
-  int rc = SQLITE_OK;
-
-  assert( id!=0 );
-  assert( pSize!=0 );
-  SimulateIOError(return SQLITE_IOERR_FSTAT);
-  OSTRACE(("SIZE file=%p, pSize=%p\n", pFile->h, pSize));
-
-#if SQLITE_OS_WINRT
-  {
-    FILE_STANDARD_INFO info;
-    if( osGetFileInformationByHandleEx(pFile->h, FileStandardInfo,
-                                     &info, sizeof(info)) ){
-      *pSize = info.EndOfFile.QuadPart;
-    }else{
-      pFile->lastErrno = osGetLastError();
-      rc = winLogError(SQLITE_IOERR_FSTAT, pFile->lastErrno,
-                       "winFileSize", pFile->zPath);
+    if (pFile->local.bReserved){
+      pFile->shared->bReserved = FALSE;
     }
-  }
-#else
-  {
-    DWORD upperBits;
-    DWORD lowerBits;
-    DWORD lastErrno;
-
-    lowerBits = osGetFileSize(pFile->h, &upperBits);
-    *pSize = (((sqlite3_int64)upperBits)<<32) + lowerBits;
-    if(   (lowerBits == INVALID_FILE_SIZE)
-       && ((lastErrno = osGetLastError())!=NO_ERROR) ){
-      pFile->lastErrno = lastErrno;
-      rc = winLogError(SQLITE_IOERR_FSTAT, pFile->lastErrno,
-                       "winFileSize", pFile->zPath);
+    if (pFile->local.bPending){
+      pFile->shared->bPending = FALSE;
+    }
+    if (pFile->local.bExclusive){
+      pFile->shared->bExclusive = FALSE;
     }
-  }
-#endif
-  OSTRACE(("SIZE file=%p, pSize=%p, *pSize=%lld, rc=%s\n",
-           pFile->h, pSize, *pSize, sqlite3ErrName(rc)));
-  return rc;
-}
-
-/*
-** LOCKFILE_FAIL_IMMEDIATELY is undefined on some Windows systems.
-*/
-#ifndef LOCKFILE_FAIL_IMMEDIATELY
-# define LOCKFILE_FAIL_IMMEDIATELY 1
-#endif
-
-#ifndef LOCKFILE_EXCLUSIVE_LOCK
-# define LOCKFILE_EXCLUSIVE_LOCK 2
-#endif
-
-/*
-** Historically, SQLite has used both the LockFile and LockFileEx functions.
-** When the LockFile function was used, it was always expected to fail
-** immediately if the lock could not be obtained.  Also, it always expected to
-** obtain an exclusive lock.  These flags are used with the LockFileEx function
-** and reflect those expectations; therefore, they should not be changed.
-*/
-#ifndef SQLITE_LOCKFILE_FLAGS
-# define SQLITE_LOCKFILE_FLAGS   (LOCKFILE_FAIL_IMMEDIATELY | \
-                                  LOCKFILE_EXCLUSIVE_LOCK)
-#endif
-
-/*
-** Currently, SQLite never calls the LockFileEx function without wanting the
-** call to fail immediately if the lock cannot be obtained.
-*/
-#ifndef SQLITE_LOCKFILEEX_FLAGS
-# define SQLITE_LOCKFILEEX_FLAGS (LOCKFILE_FAIL_IMMEDIATELY)
-#endif
 
-/*
-** Acquire a reader lock.
-** Different API routines are called depending on whether or not this
-** is Win9x or WinNT.
-*/
-static int winGetReadLock(winFile *pFile){
-  int res;
-  OSTRACE(("READ-LOCK file=%p, lock=%d\n", pFile->h, pFile->locktype));
-  if( osIsNT() ){
-#if SQLITE_OS_WINCE
-    /*
-    ** NOTE: Windows CE is handled differently here due its lack of the Win32
-    **       API LockFileEx.
-    */
-    res = winceLockFile(&pFile->h, SHARED_FIRST, 0, 1, 0);
-#else
-    res = winLockFile(&pFile->h, SQLITE_LOCKFILEEX_FLAGS, SHARED_FIRST, 0,
-                      SHARED_SIZE, 0);
-#endif
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
-    int lk;
-    sqlite3_randomness(sizeof(lk), &lk);
-    pFile->sharedLockByte = (short)((lk & 0x7fffffff)%(SHARED_SIZE - 1));
-    res = winLockFile(&pFile->h, SQLITE_LOCKFILE_FLAGS,
-                      SHARED_FIRST+pFile->sharedLockByte, 0, 1, 0);
-  }
-#endif
-  if( res == 0 ){
-    pFile->lastErrno = osGetLastError();
-    /* No need to log a failure to lock */
-  }
-  OSTRACE(("READ-LOCK file=%p, result=%d\n", pFile->h, res));
-  return res;
-}
+    /* De-reference and close our copy of the shared memory handle */
+    UnmapViewOfFile(pFile->shared);
+    CloseHandle(pFile->hShared);
 
-/*
-** Undo a readlock
-*/
-static int winUnlockReadLock(winFile *pFile){
-  int res;
-  DWORD lastErrno;
-  OSTRACE(("READ-UNLOCK file=%p, lock=%d\n", pFile->h, pFile->locktype));
-  if( osIsNT() ){
-    res = winUnlockFile(&pFile->h, SHARED_FIRST, 0, SHARED_SIZE, 0);
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
-    res = winUnlockFile(&pFile->h, SHARED_FIRST+pFile->sharedLockByte, 0, 1, 0);
-  }
-#endif
-  if( res==0 && ((lastErrno = osGetLastError())!=ERROR_NOT_LOCKED) ){
-    pFile->lastErrno = lastErrno;
-    winLogError(SQLITE_IOERR_UNLOCK, pFile->lastErrno,
-                "winUnlockReadLock", pFile->zPath);
+    /* Done with the mutex */
+    winceMutexRelease(pFile->hMutex);    
+    CloseHandle(pFile->hMutex);
+    pFile->hMutex = NULL;
   }
-  OSTRACE(("READ-UNLOCK file=%p, result=%d\n", pFile->h, res));
-  return res;
 }
 
-/*
-** Lock the file with the lock specified by parameter locktype - one
-** of the following:
-**
-**     (1) SHARED_LOCK
-**     (2) RESERVED_LOCK
-**     (3) PENDING_LOCK
-**     (4) EXCLUSIVE_LOCK
-**
-** Sometimes when requesting one lock state, additional lock states
-** are inserted in between.  The locking might fail on one of the later
-** transitions leaving the lock state different from what it started but
-** still short of its goal.  The following chart shows the allowed
-** transitions and the inserted intermediate states:
-**
-**    UNLOCKED -> SHARED
-**    SHARED -> RESERVED
-**    SHARED -> (PENDING) -> EXCLUSIVE
-**    RESERVED -> (PENDING) -> EXCLUSIVE
-**    PENDING -> EXCLUSIVE
-**
-** This routine will only increase a lock.  The winUnlock() routine
-** erases all locks at once and returns us immediately to locking level 0.
-** It is not possible to lower the locking level one step at a time.  You
-** must go straight to locking level 0.
+/* 
+** An implementation of the LockFile() API of windows for wince
 */
-static int winLock(sqlite3_file *id, int locktype){
-  int rc = SQLITE_OK;    /* Return code from subroutines */
-  int res = 1;           /* Result of a Windows lock call */
-  int newLocktype;       /* Set pFile->locktype to this value before exiting */
-  int gotPendingLock = 0;/* True if we acquired a PENDING lock this time */
-  winFile *pFile = (winFile*)id;
-  DWORD lastErrno = NO_ERROR;
-
-  assert( id!=0 );
-  OSTRACE(("LOCK file=%p, oldLock=%d(%d), newLock=%d\n",
-           pFile->h, pFile->locktype, pFile->sharedLockByte, locktype));
-
-  /* If there is already a lock of this type or more restrictive on the
-  ** OsFile, do nothing. Don't use the end_lock: exit path, as
-  ** sqlite3OsEnterMutex() hasn't been called yet.
-  */
-  if( pFile->locktype>=locktype ){
-    OSTRACE(("LOCK-HELD file=%p, rc=SQLITE_OK\n", pFile->h));
-    return SQLITE_OK;
-  }
-
-  /* Do not allow any kind of write-lock on a read-only database
-  */
-  if( (pFile->ctrlFlags & WINFILE_RDONLY)!=0 && locktype>=RESERVED_LOCK ){
-    return SQLITE_IOERR_LOCK;
-  }
-
-  /* Make sure the locking sequence is correct
-  */
-  assert( pFile->locktype!=NO_LOCK || locktype==SHARED_LOCK );
-  assert( locktype!=PENDING_LOCK );
-  assert( locktype!=RESERVED_LOCK || pFile->locktype==SHARED_LOCK );
-
-  /* Lock the PENDING_LOCK byte if we need to acquire a PENDING lock or
-  ** a SHARED lock.  If we are acquiring a SHARED lock, the acquisition of
-  ** the PENDING_LOCK byte is temporary.
-  */
-  newLocktype = pFile->locktype;
-  if( pFile->locktype==NO_LOCK
-   || (locktype==EXCLUSIVE_LOCK && pFile->locktype<=RESERVED_LOCK)
-  ){
-    int cnt = 3;
-    while( cnt-->0 && (res = winLockFile(&pFile->h, SQLITE_LOCKFILE_FLAGS,
-                                         PENDING_BYTE, 0, 1, 0))==0 ){
-      /* Try 3 times to get the pending lock.  This is needed to work
-      ** around problems caused by indexing and/or anti-virus software on
-      ** Windows systems.
-      ** If you are using this code as a model for alternative VFSes, do not
-      ** copy this retry logic.  It is a hack intended for Windows only.
-      */
-      lastErrno = osGetLastError();
-      OSTRACE(("LOCK-PENDING-FAIL file=%p, count=%d, result=%d\n",
-               pFile->h, cnt, res));
-      if( lastErrno==ERROR_INVALID_HANDLE ){
-        pFile->lastErrno = lastErrno;
-        rc = SQLITE_IOERR_LOCK;
-        OSTRACE(("LOCK-FAIL file=%p, count=%d, rc=%s\n",
-                 pFile->h, cnt, sqlite3ErrName(rc)));
-        return rc;
-      }
-      if( cnt ) sqlite3_win32_sleep(1);
-    }
-    gotPendingLock = res;
-    if( !res ){
-      lastErrno = osGetLastError();
-    }
-  }
+static BOOL winceLockFile(
+  HANDLE *phFile,
+  DWORD dwFileOffsetLow,
+  DWORD dwFileOffsetHigh,
+  DWORD nNumberOfBytesToLockLow,
+  DWORD nNumberOfBytesToLockHigh
+){
+  winFile *pFile = HANDLE_TO_WINFILE(phFile);
+  BOOL bReturn = FALSE;
 
-  /* Acquire a shared lock
-  */
-  if( locktype==SHARED_LOCK && res ){
-    assert( pFile->locktype==NO_LOCK );
-    res = winGetReadLock(pFile);
-    if( res ){
-      newLocktype = SHARED_LOCK;
-    }else{
-      lastErrno = osGetLastError();
-    }
-  }
+  if (!pFile->hMutex) return TRUE;
+  winceMutexAcquire(pFile->hMutex);
 
-  /* Acquire a RESERVED lock
-  */
-  if( locktype==RESERVED_LOCK && res ){
-    assert( pFile->locktype==SHARED_LOCK );
-    res = winLockFile(&pFile->h, SQLITE_LOCKFILE_FLAGS, RESERVED_BYTE, 0, 1, 0);
-    if( res ){
-      newLocktype = RESERVED_LOCK;
-    }else{
-      lastErrno = osGetLastError();
+  /* Wanting an exclusive lock? */
+  if (dwFileOffsetLow == SHARED_FIRST
+       && nNumberOfBytesToLockLow == SHARED_SIZE){
+    if (pFile->shared->nReaders == 0 && pFile->shared->bExclusive == 0){
+       pFile->shared->bExclusive = TRUE;
+       pFile->local.bExclusive = TRUE;
+       bReturn = TRUE;
     }
   }
 
-  /* Acquire a PENDING lock
-  */
-  if( locktype==EXCLUSIVE_LOCK && res ){
-    newLocktype = PENDING_LOCK;
-    gotPendingLock = 0;
+  /* Want a read-only lock? */
+  else if ((dwFileOffsetLow >= SHARED_FIRST &&
+            dwFileOffsetLow < SHARED_FIRST + SHARED_SIZE) &&
+            nNumberOfBytesToLockLow == 1){
+    if (pFile->shared->bExclusive == 0){
+      pFile->local.nReaders ++;
+      if (pFile->local.nReaders == 1){
+        pFile->shared->nReaders ++;
+      }
+      bReturn = TRUE;
+    }
   }
 
-  /* Acquire an EXCLUSIVE lock
-  */
-  if( locktype==EXCLUSIVE_LOCK && res ){
-    assert( pFile->locktype>=SHARED_LOCK );
-    res = winUnlockReadLock(pFile);
-    res = winLockFile(&pFile->h, SQLITE_LOCKFILE_FLAGS, SHARED_FIRST, 0,
-                      SHARED_SIZE, 0);
-    if( res ){
-      newLocktype = EXCLUSIVE_LOCK;
-    }else{
-      lastErrno = osGetLastError();
-      winGetReadLock(pFile);
+  /* Want a pending lock? */
+  else if (dwFileOffsetLow == PENDING_BYTE && nNumberOfBytesToLockLow == 1){
+    /* If no pending lock has been acquired, then acquire it */
+    if (pFile->shared->bPending == 0) {
+      pFile->shared->bPending = TRUE;
+      pFile->local.bPending = TRUE;
+      bReturn = TRUE;
     }
   }
-
-  /* If we are holding a PENDING lock that ought to be released, then
-  ** release it now.
-  */
-  if( gotPendingLock && locktype==SHARED_LOCK ){
-    winUnlockFile(&pFile->h, PENDING_BYTE, 0, 1, 0);
+  /* Want a reserved lock? */
+  else if (dwFileOffsetLow == RESERVED_BYTE && nNumberOfBytesToLockLow == 1){
+    if (pFile->shared->bReserved == 0) {
+      pFile->shared->bReserved = TRUE;
+      pFile->local.bReserved = TRUE;
+      bReturn = TRUE;
+    }
   }
 
-  /* Update the state of the lock has held in the file descriptor then
-  ** return the appropriate result code.
-  */
-  if( res ){
-    rc = SQLITE_OK;
-  }else{
-    pFile->lastErrno = lastErrno;
-    rc = SQLITE_BUSY;
-    OSTRACE(("LOCK-FAIL file=%p, wanted=%d, got=%d\n",
-             pFile->h, locktype, newLocktype));
-  }
-  pFile->locktype = (u8)newLocktype;
-  OSTRACE(("LOCK file=%p, lock=%d, rc=%s\n",
-           pFile->h, pFile->locktype, sqlite3ErrName(rc)));
-  return rc;
+  winceMutexRelease(pFile->hMutex);
+  return bReturn;
 }
 
 /*
-** This routine checks if there is a RESERVED lock held on the specified
-** file by this or any other process. If such a lock is held, return
-** non-zero, otherwise zero.
+** An implementation of the UnlockFile API of windows for wince
 */
-static int winCheckReservedLock(sqlite3_file *id, int *pResOut){
-  int res;
-  winFile *pFile = (winFile*)id;
+static BOOL winceUnlockFile(
+  HANDLE *phFile,
+  DWORD dwFileOffsetLow,
+  DWORD dwFileOffsetHigh,
+  DWORD nNumberOfBytesToUnlockLow,
+  DWORD nNumberOfBytesToUnlockHigh
+){
+  winFile *pFile = HANDLE_TO_WINFILE(phFile);
+  BOOL bReturn = FALSE;
 
-  SimulateIOError( return SQLITE_IOERR_CHECKRESERVEDLOCK; );
-  OSTRACE(("TEST-WR-LOCK file=%p, pResOut=%p\n", pFile->h, pResOut));
+  if (!pFile->hMutex) return TRUE;
+  winceMutexAcquire(pFile->hMutex);
 
-  assert( id!=0 );
-  if( pFile->locktype>=RESERVED_LOCK ){
-    res = 1;
-    OSTRACE(("TEST-WR-LOCK file=%p, result=%d (local)\n", pFile->h, res));
-  }else{
-    res = winLockFile(&pFile->h, SQLITE_LOCKFILEEX_FLAGS,RESERVED_BYTE,0,1,0);
-    if( res ){
-      winUnlockFile(&pFile->h, RESERVED_BYTE, 0, 1, 0);
+  /* Releasing a reader lock or an exclusive lock */
+  if (dwFileOffsetLow >= SHARED_FIRST &&
+       dwFileOffsetLow < SHARED_FIRST + SHARED_SIZE){
+    /* Did we have an exclusive lock? */
+    if (pFile->local.bExclusive){
+      pFile->local.bExclusive = FALSE;
+      pFile->shared->bExclusive = FALSE;
+      bReturn = TRUE;
     }
-    res = !res;
-    OSTRACE(("TEST-WR-LOCK file=%p, result=%d (remote)\n", pFile->h, res));
-  }
-  *pResOut = res;
-  OSTRACE(("TEST-WR-LOCK file=%p, pResOut=%p, *pResOut=%d, rc=SQLITE_OK\n",
-           pFile->h, pResOut, *pResOut));
-  return SQLITE_OK;
-}
 
-/*
-** Lower the locking level on file descriptor id to locktype.  locktype
-** must be either NO_LOCK or SHARED_LOCK.
-**
-** If the locking level of the file descriptor is already at or below
-** the requested locking level, this routine is a no-op.
-**
-** It is not possible for this routine to fail if the second argument
-** is NO_LOCK.  If the second argument is SHARED_LOCK then this routine
-** might return SQLITE_IOERR;
-*/
-static int winUnlock(sqlite3_file *id, int locktype){
-  int type;
-  winFile *pFile = (winFile*)id;
-  int rc = SQLITE_OK;
-  assert( pFile!=0 );
-  assert( locktype<=SHARED_LOCK );
-  OSTRACE(("UNLOCK file=%p, oldLock=%d(%d), newLock=%d\n",
-           pFile->h, pFile->locktype, pFile->sharedLockByte, locktype));
-  type = pFile->locktype;
-  if( type>=EXCLUSIVE_LOCK ){
-    winUnlockFile(&pFile->h, SHARED_FIRST, 0, SHARED_SIZE, 0);
-    if( locktype==SHARED_LOCK && !winGetReadLock(pFile) ){
-      /* This should never happen.  We should always be able to
-      ** reacquire the read lock */
-      rc = winLogError(SQLITE_IOERR_UNLOCK, osGetLastError(),
-                       "winUnlock", pFile->zPath);
+    /* Did we just have a reader lock? */
+    else if (pFile->local.nReaders){
+      pFile->local.nReaders --;
+      if (pFile->local.nReaders == 0)
+      {
+        pFile->shared->nReaders --;
+      }
+      bReturn = TRUE;
     }
   }
-  if( type>=RESERVED_LOCK ){
-    winUnlockFile(&pFile->h, RESERVED_BYTE, 0, 1, 0);
-  }
-  if( locktype==NO_LOCK && type>=SHARED_LOCK ){
-    winUnlockReadLock(pFile);
+
+  /* Releasing a pending lock */
+  else if (dwFileOffsetLow == PENDING_BYTE && nNumberOfBytesToUnlockLow == 1){
+    if (pFile->local.bPending){
+      pFile->local.bPending = FALSE;
+      pFile->shared->bPending = FALSE;
+      bReturn = TRUE;
+    }
   }
-  if( type>=PENDING_LOCK ){
-    winUnlockFile(&pFile->h, PENDING_BYTE, 0, 1, 0);
+  /* Releasing a reserved lock */
+  else if (dwFileOffsetLow == RESERVED_BYTE && nNumberOfBytesToUnlockLow == 1){
+    if (pFile->local.bReserved) {
+      pFile->local.bReserved = FALSE;
+      pFile->shared->bReserved = FALSE;
+      bReturn = TRUE;
+    }
   }
-  pFile->locktype = (u8)locktype;
-  OSTRACE(("UNLOCK file=%p, lock=%d, rc=%s\n",
-           pFile->h, pFile->locktype, sqlite3ErrName(rc)));
-  return rc;
-}
 
-/******************************************************************************
-****************************** No-op Locking **********************************
-**
-** Of the various locking implementations available, this is by far the
-** simplest:  locking is ignored.  No attempt is made to lock the database
-** file for reading or writing.
-**
-** This locking mode is appropriate for use on read-only databases
-** (ex: databases that are burned into CD-ROM, for example.)  It can
-** also be used if the application employs some external mechanism to
-** prevent simultaneous access of the same database by two or more
-** database connections.  But there is a serious risk of database
-** corruption if this locking mode is used in situations where multiple
-** database connections are accessing the same database file at the same
-** time and one or more of those connections are writing.
-*/
-
-static int winNolockLock(sqlite3_file *id, int locktype){
-  UNUSED_PARAMETER(id);
-  UNUSED_PARAMETER(locktype);
-  return SQLITE_OK;
-}
-
-static int winNolockCheckReservedLock(sqlite3_file *id, int *pResOut){
-  UNUSED_PARAMETER(id);
-  UNUSED_PARAMETER(pResOut);
-  return SQLITE_OK;
-}
-
-static int winNolockUnlock(sqlite3_file *id, int locktype){
-  UNUSED_PARAMETER(id);
-  UNUSED_PARAMETER(locktype);
-  return SQLITE_OK;
+  winceMutexRelease(pFile->hMutex);
+  return bReturn;
 }
 
-/******************* End of the no-op lock implementation *********************
-******************************************************************************/
-
 /*
-** If *pArg is initially negative then this is a query.  Set *pArg to
-** 1 or 0 depending on whether or not bit mask of pFile->ctrlFlags is set.
-**
-** If *pArg is 0 or 1, then clear or set the mask bit of pFile->ctrlFlags.
+** An implementation of the LockFileEx() API of windows for wince
 */
-static void winModeBit(winFile *pFile, unsigned char mask, int *pArg){
-  if( *pArg<0 ){
-    *pArg = (pFile->ctrlFlags & mask)!=0;
-  }else if( (*pArg)==0 ){
-    pFile->ctrlFlags &= ~mask;
-  }else{
-    pFile->ctrlFlags |= mask;
+static BOOL winceLockFileEx(
+  HANDLE *phFile,
+  DWORD dwFlags,
+  DWORD dwReserved,
+  DWORD nNumberOfBytesToLockLow,
+  DWORD nNumberOfBytesToLockHigh,
+  LPOVERLAPPED lpOverlapped
+){
+  /* If the caller wants a shared read lock, forward this call
+  ** to winceLockFile */
+  if (lpOverlapped->Offset == SHARED_FIRST &&
+      dwFlags == 1 &&
+      nNumberOfBytesToLockLow == SHARED_SIZE){
+    return winceLockFile(phFile, SHARED_FIRST, 0, 1, 0);
   }
+  return FALSE;
 }
+/*
+** End of the special code for wince
+*****************************************************************************/
+#endif /* SQLITE_OS_WINCE */
 
-/* Forward references to VFS helper methods used for temporary files */
-static int winGetTempname(sqlite3_vfs *, char **);
-static int winIsDir(const void *);
-static BOOL winIsDriveLetterAndColon(const char *);
+/*****************************************************************************
+** The next group of routines implement the I/O methods specified
+** by the sqlite3_io_methods object.
+******************************************************************************/
 
 /*
-** Control and query of the open file handle.
+** Close a file.
+**
+** It is reported that an attempt to close a handle might sometimes
+** fail.  This is a very unreasonable result, but windows is notorious
+** for being unreasonable so I do not doubt that it might happen.  If
+** the close fails, we pause for 100 milliseconds and try again.  As
+** many as MX_CLOSE_ATTEMPT attempts to close the handle are made before
+** giving up and returning an error.
 */
-static int winFileControl(sqlite3_file *id, int op, void *pArg){
+#define MX_CLOSE_ATTEMPT 3
+static int winClose(sqlite3_file *id){
+  int rc, cnt = 0;
   winFile *pFile = (winFile*)id;
-  OSTRACE(("FCNTL file=%p, op=%d, pArg=%p\n", pFile->h, op, pArg));
-  switch( op ){
-    case SQLITE_FCNTL_LOCKSTATE: {
-      *(int*)pArg = pFile->locktype;
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_LAST_ERRNO: {
-      *(int*)pArg = (int)pFile->lastErrno;
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_CHUNK_SIZE: {
-      pFile->szChunk = *(int *)pArg;
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_SIZE_HINT: {
-      if( pFile->szChunk>0 ){
-        sqlite3_int64 oldSz;
-        int rc = winFileSize(id, &oldSz);
-        if( rc==SQLITE_OK ){
-          sqlite3_int64 newSz = *(sqlite3_int64*)pArg;
-          if( newSz>oldSz ){
-            SimulateIOErrorBenign(1);
-            rc = winTruncate(id, newSz);
-            SimulateIOErrorBenign(0);
-          }
-        }
-        OSTRACE(("FCNTL file=%p, rc=%s\n", pFile->h, sqlite3ErrName(rc)));
-        return rc;
-      }
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_PERSIST_WAL: {
-      winModeBit(pFile, WINFILE_PERSIST_WAL, (int*)pArg);
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_POWERSAFE_OVERWRITE: {
-      winModeBit(pFile, WINFILE_PSOW, (int*)pArg);
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_VFSNAME: {
-      *(char**)pArg = sqlite3_mprintf("%s", pFile->pVfs->zName);
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_WIN32_AV_RETRY: {
-      int *a = (int*)pArg;
-      if( a[0]>0 ){
-        winIoerrRetry = a[0];
-      }else{
-        a[0] = winIoerrRetry;
-      }
-      if( a[1]>0 ){
-        winIoerrRetryDelay = a[1];
-      }else{
-        a[1] = winIoerrRetryDelay;
-      }
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-    case SQLITE_FCNTL_WIN32_GET_HANDLE: {
-      LPHANDLE phFile = (LPHANDLE)pArg;
-      *phFile = pFile->h;
-      OSTRACE(("FCNTL file=%p, rc=SQLITE_OK\n", pFile->h));
-      return SQLITE_OK;
-    }
-#ifdef SQLITE_TEST
-    case SQLITE_FCNTL_WIN32_SET_HANDLE: {
-      LPHANDLE phFile = (LPHANDLE)pArg;
-      HANDLE hOldFile = pFile->h;
-      pFile->h = *phFile;
-      *phFile = hOldFile;
-      OSTRACE(("FCNTL oldFile=%p, newFile=%p, rc=SQLITE_OK\n",
-               hOldFile, pFile->h));
-      return SQLITE_OK;
-    }
-#endif
-    case SQLITE_FCNTL_TEMPFILENAME: {
-      char *zTFile = 0;
-      int rc = winGetTempname(pFile->pVfs, &zTFile);
-      if( rc==SQLITE_OK ){
-        *(char**)pArg = zTFile;
-      }
-      OSTRACE(("FCNTL file=%p, rc=%s\n", pFile->h, sqlite3ErrName(rc)));
-      return rc;
-    }
-#if SQLITE_MAX_MMAP_SIZE>0
-    case SQLITE_FCNTL_MMAP_SIZE: {
-      i64 newLimit = *(i64*)pArg;
-      int rc = SQLITE_OK;
-      if( newLimit>sqlite3GlobalConfig.mxMmap ){
-        newLimit = sqlite3GlobalConfig.mxMmap;
-      }
-
-      /* The value of newLimit may be eventually cast to (SIZE_T) and passed
-      ** to MapViewOfFile(). Restrict its value to 2GB if (SIZE_T) is not at
-      ** least a 64-bit type. */
-      if( newLimit>0 && sizeof(SIZE_T)<8 ){
-        newLimit = (newLimit & 0x7FFFFFFF);
-      }
 
-      *(i64*)pArg = pFile->mmapSizeMax;
-      if( newLimit>=0 && newLimit!=pFile->mmapSizeMax && pFile->nFetchOut==0 ){
-        pFile->mmapSizeMax = newLimit;
-        if( pFile->mmapSize>0 ){
-          winUnmapfile(pFile);
-          rc = winMapfile(pFile, -1);
-        }
-      }
-      OSTRACE(("FCNTL file=%p, rc=%s\n", pFile->h, sqlite3ErrName(rc)));
-      return rc;
+  assert( id!=0 );
+  OSTRACE2("CLOSE %d\n", pFile->h);
+  do{
+    rc = CloseHandle(pFile->h);
+  }while( rc==0 && ++cnt < MX_CLOSE_ATTEMPT && (Sleep(100), 1) );
+#if SQLITE_OS_WINCE
+#define WINCE_DELETION_ATTEMPTS 3
+  winceDestroyLock(pFile);
+  if( pFile->zDeleteOnClose ){
+    int cnt = 0;
+    while(
+           DeleteFileW(pFile->zDeleteOnClose)==0
+        && GetFileAttributesW(pFile->zDeleteOnClose)!=0xffffffff 
+        && cnt++ < WINCE_DELETION_ATTEMPTS
+    ){
+       Sleep(100);  /* Wait a little before trying again */
     }
-#endif
+    free(pFile->zDeleteOnClose);
   }
-  OSTRACE(("FCNTL file=%p, rc=SQLITE_NOTFOUND\n", pFile->h));
-  return SQLITE_NOTFOUND;
+#endif
+  OpenCounter(-1);
+  return rc ? SQLITE_OK : SQLITE_IOERR;
 }
 
 /*
-** Return the sector size in bytes of the underlying block device for
-** the specified file. This is almost always 512 bytes, but may be
-** larger for some devices.
-**
-** SQLite code assumes this function cannot fail. It also assumes that
-** if two files are created in the same file-system directory (i.e.
-** a database and its journal file) that the sector size will be the
-** same for both.
+** Some microsoft compilers lack this definition.
 */
-static int winSectorSize(sqlite3_file *id){
-  (void)id;
-  return SQLITE_DEFAULT_SECTOR_SIZE;
+#ifndef INVALID_SET_FILE_POINTER
+# define INVALID_SET_FILE_POINTER ((DWORD)-1)
+#endif
+
+/*
+** Read data from a file into a buffer.  Return SQLITE_OK if all
+** bytes were read successfully and SQLITE_IOERR if anything goes
+** wrong.
+*/
+static int winRead(
+  sqlite3_file *id,          /* File to read from */
+  void *pBuf,                /* Write content into this buffer */
+  int amt,                   /* Number of bytes to read */
+  sqlite3_int64 offset       /* Begin reading at this offset */
+){
+  LONG upperBits = (LONG)((offset>>32) & 0x7fffffff);
+  LONG lowerBits = (LONG)(offset & 0xffffffff);
+  DWORD rc;
+  winFile *pFile = (winFile*)id;
+  DWORD error;
+  DWORD got;
+
+  assert( id!=0 );
+  SimulateIOError(return SQLITE_IOERR_READ);
+  OSTRACE3("READ %d lock=%d\n", pFile->h, pFile->locktype);
+  rc = SetFilePointer(pFile->h, lowerBits, &upperBits, FILE_BEGIN);
+  if( rc==INVALID_SET_FILE_POINTER && (error=GetLastError())!=NO_ERROR ){
+    pFile->lastErrno = error;
+    return SQLITE_FULL;
+  }
+  if( !ReadFile(pFile->h, pBuf, amt, &got, 0) ){
+    pFile->lastErrno = GetLastError();
+    return SQLITE_IOERR_READ;
+  }
+  if( got==(DWORD)amt ){
+    return SQLITE_OK;
+  }else{
+    /* Unread parts of the buffer must be zero-filled */
+    memset(&((char*)pBuf)[got], 0, amt-got);
+    return SQLITE_IOERR_SHORT_READ;
+  }
 }
 
 /*
-** Return a vector of device characteristics.
+** Write data from a buffer into a file.  Return SQLITE_OK on success
+** or some other error code on failure.
 */
-static int winDeviceCharacteristics(sqlite3_file *id){
-  winFile *p = (winFile*)id;
-  return SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN |
-         ((p->ctrlFlags & WINFILE_PSOW)?SQLITE_IOCAP_POWERSAFE_OVERWRITE:0);
+static int winWrite(
+  sqlite3_file *id,         /* File to write into */
+  const void *pBuf,         /* The bytes to be written */
+  int amt,                  /* Number of bytes to write */
+  sqlite3_int64 offset      /* Offset into the file to begin writing at */
+){
+  LONG upperBits = (LONG)((offset>>32) & 0x7fffffff);
+  LONG lowerBits = (LONG)(offset & 0xffffffff);
+  DWORD rc;
+  winFile *pFile = (winFile*)id;
+  DWORD error;
+  DWORD wrote = 0;
+
+  assert( id!=0 );
+  SimulateIOError(return SQLITE_IOERR_WRITE);
+  SimulateDiskfullError(return SQLITE_FULL);
+  OSTRACE3("WRITE %d lock=%d\n", pFile->h, pFile->locktype);
+  rc = SetFilePointer(pFile->h, lowerBits, &upperBits, FILE_BEGIN);
+  if( rc==INVALID_SET_FILE_POINTER && (error=GetLastError())!=NO_ERROR ){
+    pFile->lastErrno = error;
+    return SQLITE_FULL;
+  }
+  assert( amt>0 );
+  while(
+     amt>0
+     && (rc = WriteFile(pFile->h, pBuf, amt, &wrote, 0))!=0
+     && wrote>0
+  ){
+    amt -= wrote;
+    pBuf = &((char*)pBuf)[wrote];
+  }
+  if( !rc || amt>(int)wrote ){
+    pFile->lastErrno = GetLastError();
+    return SQLITE_FULL;
+  }
+  return SQLITE_OK;
 }
 
 /*
-** Windows will only let you create file view mappings
-** on allocation size granularity boundaries.
-** During sqlite3_os_init() we do a GetSystemInfo()
-** to get the granularity size.
+** Truncate an open file to a specified size
 */
-static SYSTEM_INFO winSysInfo;
+static int winTruncate(sqlite3_file *id, sqlite3_int64 nByte){
+  LONG upperBits = (LONG)((nByte>>32) & 0x7fffffff);
+  LONG lowerBits = (LONG)(nByte & 0xffffffff);
+  DWORD rc;
+  winFile *pFile = (winFile*)id;
+  DWORD error;
 
-#ifndef SQLITE_OMIT_WAL
+  assert( id!=0 );
+  OSTRACE3("TRUNCATE %d %lld\n", pFile->h, nByte);
+  SimulateIOError(return SQLITE_IOERR_TRUNCATE);
+  rc = SetFilePointer(pFile->h, lowerBits, &upperBits, FILE_BEGIN);
+  if( rc==INVALID_SET_FILE_POINTER && (error=GetLastError())!=NO_ERROR ){
+    pFile->lastErrno = error;
+    return SQLITE_IOERR_TRUNCATE;
+  }
+  /* SetEndOfFile will fail if nByte is negative */
+  if( !SetEndOfFile(pFile->h) ){
+    pFile->lastErrno = GetLastError();
+    return SQLITE_IOERR_TRUNCATE;
+  }
+  return SQLITE_OK;
+}
 
+#ifdef SQLITE_TEST
 /*
-** Helper functions to obtain and relinquish the global mutex. The
-** global mutex is used to protect the winLockInfo objects used by
-** this file, all of which may be shared by multiple threads.
-**
-** Function winShmMutexHeld() is used to assert() that the global mutex
-** is held when required. This function is only used as part of assert()
-** statements. e.g.
-**
-**   winShmEnterMutex()
-**     assert( winShmMutexHeld() );
-**   winShmLeaveMutex()
-*/
-static void winShmEnterMutex(void){
-  sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_VFS1));
-}
-static void winShmLeaveMutex(void){
-  sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_VFS1));
-}
-#ifndef NDEBUG
-static int winShmMutexHeld(void) {
-  return sqlite3_mutex_held(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_VFS1));
-}
+** Count the number of fullsyncs and normal syncs.  This is used to test
+** that syncs and fullsyncs are occuring at the right times.
+*/
+int sqlite3_sync_count = 0;
+int sqlite3_fullsync_count = 0;
 #endif
 
 /*
-** Object used to represent a single file opened and mmapped to provide
-** shared memory.  When multiple threads all reference the same
-** log-summary, each thread has its own winFile object, but they all
-** point to a single instance of this object.  In other words, each
-** log-summary is opened only once per process.
-**
-** winShmMutexHeld() must be true when creating or destroying
-** this object or while reading or writing the following fields:
-**
-**      nRef
-**      pNext
-**
-** The following fields are read-only after the object is created:
-**
-**      fid
-**      zFilename
-**
-** Either winShmNode.mutex must be held or winShmNode.nRef==0 and
-** winShmMutexHeld() is true when reading or writing any other field
-** in this structure.
-**
+** Make sure all writes to a particular file are committed to disk.
 */
-struct winShmNode {
-  sqlite3_mutex *mutex;      /* Mutex to access this object */
-  char *zFilename;           /* Name of the file */
-  winFile hFile;             /* File handle from winOpen */
-
-  int szRegion;              /* Size of shared-memory regions */
-  int nRegion;               /* Size of array apRegion */
-  struct ShmRegion {
-    HANDLE hMap;             /* File handle from CreateFileMapping */
-    void *pMap;
-  } *aRegion;
-  DWORD lastErrno;           /* The Windows errno from the last I/O error */
-
-  int nRef;                  /* Number of winShm objects pointing to this */
-  winShm *pFirst;            /* All winShm objects pointing to this */
-  winShmNode *pNext;         /* Next in list of all winShmNode objects */
-#if defined(SQLITE_DEBUG) || defined(SQLITE_HAVE_OS_TRACE)
-  u8 nextShmId;              /* Next available winShm.id value */
+static int winSync(sqlite3_file *id, int flags){
+#ifndef SQLITE_NO_SYNC
+  winFile *pFile = (winFile*)id;
+
+  assert( id!=0 );
+  OSTRACE3("SYNC %d lock=%d\n", pFile->h, pFile->locktype);
+#else
+  UNUSED_PARAMETER(id);
 #endif
-};
+#ifndef SQLITE_TEST
+  UNUSED_PARAMETER(flags);
+#else
+  if( flags & SQLITE_SYNC_FULL ){
+    sqlite3_fullsync_count++;
+  }
+  sqlite3_sync_count++;
+#endif
+  /* If we compiled with the SQLITE_NO_SYNC flag, then syncing is a
+  ** no-op
+  */
+#ifdef SQLITE_NO_SYNC
+    return SQLITE_OK;
+#else
+  if( FlushFileBuffers(pFile->h) ){
+    return SQLITE_OK;
+  }else{
+    pFile->lastErrno = GetLastError();
+    return SQLITE_IOERR;
+  }
+#endif
+}
 
 /*
-** A global array of all winShmNode objects.
-**
-** The winShmMutexHeld() must be true while reading or writing this list.
+** Determine the current size of a file in bytes
 */
-static winShmNode *winShmNodeList = 0;
+static int winFileSize(sqlite3_file *id, sqlite3_int64 *pSize){
+  DWORD upperBits;
+  DWORD lowerBits;
+  winFile *pFile = (winFile*)id;
+  DWORD error;
+
+  assert( id!=0 );
+  SimulateIOError(return SQLITE_IOERR_FSTAT);
+  lowerBits = GetFileSize(pFile->h, &upperBits);
+  if(   (lowerBits == INVALID_FILE_SIZE)
+     && ((error = GetLastError()) != NO_ERROR) )
+  {
+    pFile->lastErrno = error;
+    return SQLITE_IOERR_FSTAT;
+  }
+  *pSize = (((sqlite3_int64)upperBits)<<32) + lowerBits;
+  return SQLITE_OK;
+}
 
 /*
-** Structure used internally by this VFS to record the state of an
-** open shared memory connection.
-**
-** The following fields are initialized when this object is created and
-** are read-only thereafter:
-**
-**    winShm.pShmNode
-**    winShm.id
-**
-** All other fields are read/write.  The winShm.pShmNode->mutex must be held
-** while accessing any read/write fields.
+** LOCKFILE_FAIL_IMMEDIATELY is undefined on some Windows systems.
 */
-struct winShm {
-  winShmNode *pShmNode;      /* The underlying winShmNode object */
-  winShm *pNext;             /* Next winShm with the same winShmNode */
-  u8 hasMutex;               /* True if holding the winShmNode mutex */
-  u16 sharedMask;            /* Mask of shared locks held */
-  u16 exclMask;              /* Mask of exclusive locks held */
-#if defined(SQLITE_DEBUG) || defined(SQLITE_HAVE_OS_TRACE)
-  u8 id;                     /* Id of this connection with its winShmNode */
+#ifndef LOCKFILE_FAIL_IMMEDIATELY
+# define LOCKFILE_FAIL_IMMEDIATELY 1
 #endif
-};
 
 /*
-** Constants used for locking
+** Acquire a reader lock.
+** Different API routines are called depending on whether or not this
+** is Win95 or WinNT.
 */
-#define WIN_SHM_BASE   ((22+SQLITE_SHM_NLOCK)*4)        /* first lock byte */
-#define WIN_SHM_DMS    (WIN_SHM_BASE+SQLITE_SHM_NLOCK)  /* deadman switch */
-
-/*
-** Apply advisory locks for all n bytes beginning at ofst.
+static int getReadLock(winFile *pFile){
+  int res;
+  if( isNT() ){
+    OVERLAPPED ovlp;
+    ovlp.Offset = SHARED_FIRST;
+    ovlp.OffsetHigh = 0;
+    ovlp.hEvent = 0;
+    res = LockFileEx(pFile->h, LOCKFILE_FAIL_IMMEDIATELY,
+                     0, SHARED_SIZE, 0, &ovlp);
+/* isNT() is 1 if SQLITE_OS_WINCE==1, so this else is never executed. 
 */
-#define WINSHM_UNLCK  1
-#define WINSHM_RDLCK  2
-#define WINSHM_WRLCK  3
-static int winShmSystemLock(
-  winShmNode *pFile,    /* Apply locks to this open shared-memory segment */
-  int lockType,         /* WINSHM_UNLCK, WINSHM_RDLCK, or WINSHM_WRLCK */
-  int ofst,             /* Offset to first byte to be locked/unlocked */
-  int nByte             /* Number of bytes to lock or unlock */
-){
-  int rc = 0;           /* Result code form Lock/UnlockFileEx() */
-
-  /* Access to the winShmNode object is serialized by the caller */
-  assert( sqlite3_mutex_held(pFile->mutex) || pFile->nRef==0 );
-
-  OSTRACE(("SHM-LOCK file=%p, lock=%d, offset=%d, size=%d\n",
-           pFile->hFile.h, lockType, ofst, nByte));
-
-  /* Release/Acquire the system-level lock */
-  if( lockType==WINSHM_UNLCK ){
-    rc = winUnlockFile(&pFile->hFile.h, ofst, 0, nByte, 0);
+#if SQLITE_OS_WINCE==0
   }else{
-    /* Initialize the locking parameters */
-    DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY;
-    if( lockType == WINSHM_WRLCK ) dwFlags |= LOCKFILE_EXCLUSIVE_LOCK;
-    rc = winLockFile(&pFile->hFile.h, dwFlags, ofst, 0, nByte, 0);
+    int lk;
+    sqlite3_randomness(sizeof(lk), &lk);
+    pFile->sharedLockByte = (short)((lk & 0x7fffffff)%(SHARED_SIZE - 1));
+    res = LockFile(pFile->h, SHARED_FIRST+pFile->sharedLockByte, 0, 1, 0);
+#endif
   }
-
-  if( rc!= 0 ){
-    rc = SQLITE_OK;
-  }else{
-    pFile->lastErrno =  osGetLastError();
-    rc = SQLITE_BUSY;
+  if( res == 0 ){
+    pFile->lastErrno = GetLastError();
   }
-
-  OSTRACE(("SHM-LOCK file=%p, func=%s, errno=%lu, rc=%s\n",
-           pFile->hFile.h, (lockType == WINSHM_UNLCK) ? "winUnlockFile" :
-           "winLockFile", pFile->lastErrno, sqlite3ErrName(rc)));
-
-  return rc;
+  return res;
 }
 
-/* Forward references to VFS methods */
-static int winOpen(sqlite3_vfs*,const char*,sqlite3_file*,int,int*);
-static int winDelete(sqlite3_vfs *,const char*,int);
-
 /*
-** Purge the winShmNodeList list of all entries with winShmNode.nRef==0.
-**
-** This is not a VFS shared-memory method; it is a utility function called
-** by VFS shared-memory methods.
+** Undo a readlock
 */
-static void winShmPurge(sqlite3_vfs *pVfs, int deleteFlag){
-  winShmNode **pp;
-  winShmNode *p;
-  assert( winShmMutexHeld() );
-  OSTRACE(("SHM-PURGE pid=%lu, deleteFlag=%d\n",
-           osGetCurrentProcessId(), deleteFlag));
-  pp = &winShmNodeList;
-  while( (p = *pp)!=0 ){
-    if( p->nRef==0 ){
-      int i;
-      if( p->mutex ){ sqlite3_mutex_free(p->mutex); }
-      for(i=0; i<p->nRegion; i++){
-        BOOL bRc = osUnmapViewOfFile(p->aRegion[i].pMap);
-        OSTRACE(("SHM-PURGE-UNMAP pid=%lu, region=%d, rc=%s\n",
-                 osGetCurrentProcessId(), i, bRc ? "ok" : "failed"));
-        UNUSED_VARIABLE_VALUE(bRc);
-        bRc = osCloseHandle(p->aRegion[i].hMap);
-        OSTRACE(("SHM-PURGE-CLOSE pid=%lu, region=%d, rc=%s\n",
-                 osGetCurrentProcessId(), i, bRc ? "ok" : "failed"));
-        UNUSED_VARIABLE_VALUE(bRc);
-      }
-      if( p->hFile.h!=NULL && p->hFile.h!=INVALID_HANDLE_VALUE ){
-        SimulateIOErrorBenign(1);
-        winClose((sqlite3_file *)&p->hFile);
-        SimulateIOErrorBenign(0);
-      }
-      if( deleteFlag ){
-        SimulateIOErrorBenign(1);
-        sqlite3BeginBenignMalloc();
-        winDelete(pVfs, p->zFilename, 0);
-        sqlite3EndBenignMalloc();
-        SimulateIOErrorBenign(0);
-      }
-      *pp = p->pNext;
-      sqlite3_free(p->aRegion);
-      sqlite3_free(p);
-    }else{
-      pp = &p->pNext;
-    }
+static int unlockReadLock(winFile *pFile){
+  int res;
+  if( isNT() ){
+    res = UnlockFile(pFile->h, SHARED_FIRST, 0, SHARED_SIZE, 0);
+/* isNT() is 1 if SQLITE_OS_WINCE==1, so this else is never executed. 
+*/
+#if SQLITE_OS_WINCE==0
+  }else{
+    res = UnlockFile(pFile->h, SHARED_FIRST + pFile->sharedLockByte, 0, 1, 0);
+#endif
+  }
+  if( res == 0 ){
+    pFile->lastErrno = GetLastError();
   }
+  return res;
 }
 
 /*
-** Open the shared-memory area associated with database file pDbFd.
+** Lock the file with the lock specified by parameter locktype - one
+** of the following:
 **
-** When opening a new shared-memory file, if no other instances of that
-** file are currently open, in this process or in other processes, then
-** the file must be truncated to zero length or have its header cleared.
-*/
-static int winOpenSharedMemory(winFile *pDbFd){
-  struct winShm *p;                  /* The connection to be opened */
-  struct winShmNode *pShmNode = 0;   /* The underlying mmapped file */
-  int rc;                            /* Result code */
-  struct winShmNode *pNew;           /* Newly allocated winShmNode */
-  int nName;                         /* Size of zName in bytes */
-
-  assert( pDbFd->pShm==0 );    /* Not previously opened */
+**     (1) SHARED_LOCK
+**     (2) RESERVED_LOCK
+**     (3) PENDING_LOCK
+**     (4) EXCLUSIVE_LOCK
+**
+** Sometimes when requesting one lock state, additional lock states
+** are inserted in between.  The locking might fail on one of the later
+** transitions leaving the lock state different from what it started but
+** still short of its goal.  The following chart shows the allowed
+** transitions and the inserted intermediate states:
+**
+**    UNLOCKED -> SHARED
+**    SHARED -> RESERVED
+**    SHARED -> (PENDING) -> EXCLUSIVE
+**    RESERVED -> (PENDING) -> EXCLUSIVE
+**    PENDING -> EXCLUSIVE
+**
+** This routine will only increase a lock.  The winUnlock() routine
+** erases all locks at once and returns us immediately to locking level 0.
+** It is not possible to lower the locking level one step at a time.  You
+** must go straight to locking level 0.
+*/
+static int winLock(sqlite3_file *id, int locktype){
+  int rc = SQLITE_OK;    /* Return code from subroutines */
+  int res = 1;           /* Result of a windows lock call */
+  int newLocktype;       /* Set pFile->locktype to this value before exiting */
+  int gotPendingLock = 0;/* True if we acquired a PENDING lock this time */
+  winFile *pFile = (winFile*)id;
+  DWORD error = NO_ERROR;
 
-  /* Allocate space for the new sqlite3_shm object.  Also speculatively
-  ** allocate space for a new winShmNode and filename.
-  */
-  p = sqlite3MallocZero( sizeof(*p) );
-  if( p==0 ) return SQLITE_IOERR_NOMEM_BKPT;
-  nName = sqlite3Strlen30(pDbFd->zPath);
-  pNew = sqlite3MallocZero( sizeof(*pShmNode) + nName + 17 );
-  if( pNew==0 ){
-    sqlite3_free(p);
-    return SQLITE_IOERR_NOMEM_BKPT;
-  }
-  pNew->zFilename = (char*)&pNew[1];
-  sqlite3_snprintf(nName+15, pNew->zFilename, "%s-shm", pDbFd->zPath);
-  sqlite3FileSuffix3(pDbFd->zPath, pNew->zFilename);
+  assert( id!=0 );
+  OSTRACE5("LOCK %d %d was %d(%d)\n",
+          pFile->h, locktype, pFile->locktype, pFile->sharedLockByte);
 
-  /* Look to see if there is an existing winShmNode that can be used.
-  ** If no matching winShmNode currently exists, create a new one.
+  /* If there is already a lock of this type or more restrictive on the
+  ** OsFile, do nothing. Don't use the end_lock: exit path, as
+  ** sqlite3OsEnterMutex() hasn't been called yet.
   */
-  winShmEnterMutex();
-  for(pShmNode = winShmNodeList; pShmNode; pShmNode=pShmNode->pNext){
-    /* TBD need to come up with better match here.  Perhaps
-    ** use FILE_ID_BOTH_DIR_INFO Structure.
-    */
-    if( sqlite3StrICmp(pShmNode->zFilename, pNew->zFilename)==0 ) break;
+  if( pFile->locktype>=locktype ){
+    return SQLITE_OK;
   }
-  if( pShmNode ){
-    sqlite3_free(pNew);
-  }else{
-    pShmNode = pNew;
-    pNew = 0;
-    ((winFile*)(&pShmNode->hFile))->h = INVALID_HANDLE_VALUE;
-    pShmNode->pNext = winShmNodeList;
-    winShmNodeList = pShmNode;
-
-    if( sqlite3GlobalConfig.bCoreMutex ){
-      pShmNode->mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
-      if( pShmNode->mutex==0 ){
-        rc = SQLITE_IOERR_NOMEM_BKPT;
-        goto shm_open_err;
-      }
-    }
 
-    rc = winOpen(pDbFd->pVfs,
-                 pShmNode->zFilename,             /* Name of the file (UTF-8) */
-                 (sqlite3_file*)&pShmNode->hFile,  /* File handle here */
-                 SQLITE_OPEN_WAL | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
-                 0);
-    if( SQLITE_OK!=rc ){
-      goto shm_open_err;
-    }
+  /* Make sure the locking sequence is correct
+  */
+  assert( pFile->locktype!=NO_LOCK || locktype==SHARED_LOCK );
+  assert( locktype!=PENDING_LOCK );
+  assert( locktype!=RESERVED_LOCK || pFile->locktype==SHARED_LOCK );
 
-    /* Check to see if another process is holding the dead-man switch.
-    ** If not, truncate the file to zero length.
-    */
-    if( winShmSystemLock(pShmNode, WINSHM_WRLCK, WIN_SHM_DMS, 1)==SQLITE_OK ){
-      rc = winTruncate((sqlite3_file *)&pShmNode->hFile, 0);
-      if( rc!=SQLITE_OK ){
-        rc = winLogError(SQLITE_IOERR_SHMOPEN, osGetLastError(),
-                         "winOpenShm", pDbFd->zPath);
-      }
+  /* Lock the PENDING_LOCK byte if we need to acquire a PENDING lock or
+  ** a SHARED lock.  If we are acquiring a SHARED lock, the acquisition of
+  ** the PENDING_LOCK byte is temporary.
+  */
+  newLocktype = pFile->locktype;
+  if(   (pFile->locktype==NO_LOCK)
+     || (   (locktype==EXCLUSIVE_LOCK)
+         && (pFile->locktype==RESERVED_LOCK))
+  ){
+    int cnt = 3;
+    while( cnt-->0 && (res = LockFile(pFile->h, PENDING_BYTE, 0, 1, 0))==0 ){
+      /* Try 3 times to get the pending lock.  The pending lock might be
+      ** held by another reader process who will release it momentarily.
+      */
+      OSTRACE2("could not get a PENDING lock. cnt=%d\n", cnt);
+      Sleep(1);
     }
-    if( rc==SQLITE_OK ){
-      winShmSystemLock(pShmNode, WINSHM_UNLCK, WIN_SHM_DMS, 1);
-      rc = winShmSystemLock(pShmNode, WINSHM_RDLCK, WIN_SHM_DMS, 1);
+    gotPendingLock = res;
+    if( !res ){
+      error = GetLastError();
     }
-    if( rc ) goto shm_open_err;
   }
 
-  /* Make the new connection a child of the winShmNode */
-  p->pShmNode = pShmNode;
-#if defined(SQLITE_DEBUG) || defined(SQLITE_HAVE_OS_TRACE)
-  p->id = pShmNode->nextShmId++;
-#endif
-  pShmNode->nRef++;
-  pDbFd->pShm = p;
-  winShmLeaveMutex();
-
-  /* The reference count on pShmNode has already been incremented under
-  ** the cover of the winShmEnterMutex() mutex and the pointer from the
-  ** new (struct winShm) object to the pShmNode has been set. All that is
-  ** left to do is to link the new object into the linked list starting
-  ** at pShmNode->pFirst. This must be done while holding the pShmNode->mutex
-  ** mutex.
+  /* Acquire a shared lock
   */
-  sqlite3_mutex_enter(pShmNode->mutex);
-  p->pNext = pShmNode->pFirst;
-  pShmNode->pFirst = p;
-  sqlite3_mutex_leave(pShmNode->mutex);
-  return SQLITE_OK;
-
-  /* Jump here on any error */
-shm_open_err:
-  winShmSystemLock(pShmNode, WINSHM_UNLCK, WIN_SHM_DMS, 1);
-  winShmPurge(pDbFd->pVfs, 0);      /* This call frees pShmNode if required */
-  sqlite3_free(p);
-  sqlite3_free(pNew);
-  winShmLeaveMutex();
-  return rc;
-}
-
-/*
-** Close a connection to shared-memory.  Delete the underlying
-** storage if deleteFlag is true.
-*/
-static int winShmUnmap(
-  sqlite3_file *fd,          /* Database holding shared memory */
-  int deleteFlag             /* Delete after closing if true */
-){
-  winFile *pDbFd;       /* Database holding shared-memory */
-  winShm *p;            /* The connection to be closed */
-  winShmNode *pShmNode; /* The underlying shared-memory file */
-  winShm **pp;          /* For looping over sibling connections */
-
-  pDbFd = (winFile*)fd;
-  p = pDbFd->pShm;
-  if( p==0 ) return SQLITE_OK;
-  pShmNode = p->pShmNode;
-
-  /* Remove connection p from the set of connections associated
-  ** with pShmNode */
-  sqlite3_mutex_enter(pShmNode->mutex);
-  for(pp=&pShmNode->pFirst; (*pp)!=p; pp = &(*pp)->pNext){}
-  *pp = p->pNext;
-
-  /* Free the connection p */
-  sqlite3_free(p);
-  pDbFd->pShm = 0;
-  sqlite3_mutex_leave(pShmNode->mutex);
-
-  /* If pShmNode->nRef has reached 0, then close the underlying
-  ** shared-memory file, too */
-  winShmEnterMutex();
-  assert( pShmNode->nRef>0 );
-  pShmNode->nRef--;
-  if( pShmNode->nRef==0 ){
-    winShmPurge(pDbFd->pVfs, deleteFlag);
-  }
-  winShmLeaveMutex();
-
-  return SQLITE_OK;
-}
-
-/*
-** Change the lock state for a shared-memory segment.
-*/
-static int winShmLock(
-  sqlite3_file *fd,          /* Database file holding the shared memory */
-  int ofst,                  /* First lock to acquire or release */
-  int n,                     /* Number of locks to acquire or release */
-  int flags                  /* What to do with the lock */
-){
-  winFile *pDbFd = (winFile*)fd;        /* Connection holding shared memory */
-  winShm *p = pDbFd->pShm;              /* The shared memory being locked */
-  winShm *pX;                           /* For looping over all siblings */
-  winShmNode *pShmNode = p->pShmNode;
-  int rc = SQLITE_OK;                   /* Result code */
-  u16 mask;                             /* Mask of locks to take or release */
-
-  assert( ofst>=0 && ofst+n<=SQLITE_SHM_NLOCK );
-  assert( n>=1 );
-  assert( flags==(SQLITE_SHM_LOCK | SQLITE_SHM_SHARED)
-       || flags==(SQLITE_SHM_LOCK | SQLITE_SHM_EXCLUSIVE)
-       || flags==(SQLITE_SHM_UNLOCK | SQLITE_SHM_SHARED)
-       || flags==(SQLITE_SHM_UNLOCK | SQLITE_SHM_EXCLUSIVE) );
-  assert( n==1 || (flags & SQLITE_SHM_EXCLUSIVE)!=0 );
-
-  mask = (u16)((1U<<(ofst+n)) - (1U<<ofst));
-  assert( n>1 || mask==(1<<ofst) );
-  sqlite3_mutex_enter(pShmNode->mutex);
-  if( flags & SQLITE_SHM_UNLOCK ){
-    u16 allMask = 0; /* Mask of locks held by siblings */
-
-    /* See if any siblings hold this same lock */
-    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
-      if( pX==p ) continue;
-      assert( (pX->exclMask & (p->exclMask|p->sharedMask))==0 );
-      allMask |= pX->sharedMask;
-    }
-
-    /* Unlock the system-level locks */
-    if( (mask & allMask)==0 ){
-      rc = winShmSystemLock(pShmNode, WINSHM_UNLCK, ofst+WIN_SHM_BASE, n);
+  if( locktype==SHARED_LOCK && res ){
+    assert( pFile->locktype==NO_LOCK );
+    res = getReadLock(pFile);
+    if( res ){
+      newLocktype = SHARED_LOCK;
     }else{
-      rc = SQLITE_OK;
-    }
-
-    /* Undo the local locks */
-    if( rc==SQLITE_OK ){
-      p->exclMask &= ~mask;
-      p->sharedMask &= ~mask;
-    }
-  }else if( flags & SQLITE_SHM_SHARED ){
-    u16 allShared = 0;  /* Union of locks held by connections other than "p" */
-
-    /* Find out which shared locks are already held by sibling connections.
-    ** If any sibling already holds an exclusive lock, go ahead and return
-    ** SQLITE_BUSY.
-    */
-    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
-      if( (pX->exclMask & mask)!=0 ){
-        rc = SQLITE_BUSY;
-        break;
-      }
-      allShared |= pX->sharedMask;
-    }
-
-    /* Get shared locks at the system level, if necessary */
-    if( rc==SQLITE_OK ){
-      if( (allShared & mask)==0 ){
-        rc = winShmSystemLock(pShmNode, WINSHM_RDLCK, ofst+WIN_SHM_BASE, n);
-      }else{
-        rc = SQLITE_OK;
-      }
-    }
-
-    /* Get the local shared locks */
-    if( rc==SQLITE_OK ){
-      p->sharedMask |= mask;
-    }
-  }else{
-    /* Make sure no sibling connections hold locks that will block this
-    ** lock.  If any do, return SQLITE_BUSY right away.
-    */
-    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
-      if( (pX->exclMask & mask)!=0 || (pX->sharedMask & mask)!=0 ){
-        rc = SQLITE_BUSY;
-        break;
-      }
-    }
-
-    /* Get the exclusive locks at the system level.  Then if successful
-    ** also mark the local connection as being locked.
-    */
-    if( rc==SQLITE_OK ){
-      rc = winShmSystemLock(pShmNode, WINSHM_WRLCK, ofst+WIN_SHM_BASE, n);
-      if( rc==SQLITE_OK ){
-        assert( (p->sharedMask & mask)==0 );
-        p->exclMask |= mask;
-      }
+      error = GetLastError();
     }
   }
-  sqlite3_mutex_leave(pShmNode->mutex);
-  OSTRACE(("SHM-LOCK pid=%lu, id=%d, sharedMask=%03x, exclMask=%03x, rc=%s\n",
-           osGetCurrentProcessId(), p->id, p->sharedMask, p->exclMask,
-           sqlite3ErrName(rc)));
-  return rc;
-}
-
-/*
-** Implement a memory barrier or memory fence on shared memory.
-**
-** All loads and stores begun before the barrier must complete before
-** any load or store begun after the barrier.
-*/
-static void winShmBarrier(
-  sqlite3_file *fd          /* Database holding the shared memory */
-){
-  UNUSED_PARAMETER(fd);
-  sqlite3MemoryBarrier();   /* compiler-defined memory barrier */
-  winShmEnterMutex();       /* Also mutex, for redundancy */
-  winShmLeaveMutex();
-}
 
-/*
-** This function is called to obtain a pointer to region iRegion of the
-** shared-memory associated with the database file fd. Shared-memory regions
-** are numbered starting from zero. Each shared-memory region is szRegion
-** bytes in size.
-**
-** If an error occurs, an error code is returned and *pp is set to NULL.
-**
-** Otherwise, if the isWrite parameter is 0 and the requested shared-memory
-** region has not been allocated (by any client, including one running in a
-** separate process), then *pp is set to NULL and SQLITE_OK returned. If
-** isWrite is non-zero and the requested shared-memory region has not yet
-** been allocated, it is allocated by this function.
-**
-** If the shared-memory region has already been allocated or is allocated by
-** this call as described above, then it is mapped into this processes
-** address space (if it is not already), *pp is set to point to the mapped
-** memory and SQLITE_OK returned.
-*/
-static int winShmMap(
-  sqlite3_file *fd,               /* Handle open on database file */
-  int iRegion,                    /* Region to retrieve */
-  int szRegion,                   /* Size of regions */
-  int isWrite,                    /* True to extend file if necessary */
-  void volatile **pp              /* OUT: Mapped memory */
-){
-  winFile *pDbFd = (winFile*)fd;
-  winShm *pShm = pDbFd->pShm;
-  winShmNode *pShmNode;
-  int rc = SQLITE_OK;
-
-  if( !pShm ){
-    rc = winOpenSharedMemory(pDbFd);
-    if( rc!=SQLITE_OK ) return rc;
-    pShm = pDbFd->pShm;
-  }
-  pShmNode = pShm->pShmNode;
-
-  sqlite3_mutex_enter(pShmNode->mutex);
-  assert( szRegion==pShmNode->szRegion || pShmNode->nRegion==0 );
-
-  if( pShmNode->nRegion<=iRegion ){
-    struct ShmRegion *apNew;           /* New aRegion[] array */
-    int nByte = (iRegion+1)*szRegion;  /* Minimum required file size */
-    sqlite3_int64 sz;                  /* Current size of wal-index file */
-
-    pShmNode->szRegion = szRegion;
-
-    /* The requested region is not mapped into this processes address space.
-    ** Check to see if it has been allocated (i.e. if the wal-index file is
-    ** large enough to contain the requested region).
-    */
-    rc = winFileSize((sqlite3_file *)&pShmNode->hFile, &sz);
-    if( rc!=SQLITE_OK ){
-      rc = winLogError(SQLITE_IOERR_SHMSIZE, osGetLastError(),
-                       "winShmMap1", pDbFd->zPath);
-      goto shmpage_out;
+  /* Acquire a RESERVED lock
+  */
+  if( locktype==RESERVED_LOCK && res ){
+    assert( pFile->locktype==SHARED_LOCK );
+    res = LockFile(pFile->h, RESERVED_BYTE, 0, 1, 0);
+    if( res ){
+      newLocktype = RESERVED_LOCK;
+    }else{
+      error = GetLastError();
     }
+  }
 
-    if( sz<nByte ){
-      /* The requested memory region does not exist. If isWrite is set to
-      ** zero, exit early. *pp will be set to NULL and SQLITE_OK returned.
-      **
-      ** Alternatively, if isWrite is non-zero, use ftruncate() to allocate
-      ** the requested memory region.
-      */
-      if( !isWrite ) goto shmpage_out;
-      rc = winTruncate((sqlite3_file *)&pShmNode->hFile, nByte);
-      if( rc!=SQLITE_OK ){
-        rc = winLogError(SQLITE_IOERR_SHMSIZE, osGetLastError(),
-                         "winShmMap2", pDbFd->zPath);
-        goto shmpage_out;
-      }
-    }
+  /* Acquire a PENDING lock
+  */
+  if( locktype==EXCLUSIVE_LOCK && res ){
+    newLocktype = PENDING_LOCK;
+    gotPendingLock = 0;
+  }
 
-    /* Map the requested memory region into this processes address space. */
-    apNew = (struct ShmRegion *)sqlite3_realloc64(
-        pShmNode->aRegion, (iRegion+1)*sizeof(apNew[0])
-    );
-    if( !apNew ){
-      rc = SQLITE_IOERR_NOMEM_BKPT;
-      goto shmpage_out;
+  /* Acquire an EXCLUSIVE lock
+  */
+  if( locktype==EXCLUSIVE_LOCK && res ){
+    assert( pFile->locktype>=SHARED_LOCK );
+    res = unlockReadLock(pFile);
+    OSTRACE2("unreadlock = %d\n", res);
+    res = LockFile(pFile->h, SHARED_FIRST, 0, SHARED_SIZE, 0);
+    if( res ){
+      newLocktype = EXCLUSIVE_LOCK;
+    }else{
+      error = GetLastError();
+      OSTRACE2("error-code = %d\n", error);
+      getReadLock(pFile);
     }
-    pShmNode->aRegion = apNew;
-
-    while( pShmNode->nRegion<=iRegion ){
-      HANDLE hMap = NULL;         /* file-mapping handle */
-      void *pMap = 0;             /* Mapped memory region */
-
-#if SQLITE_OS_WINRT
-      hMap = osCreateFileMappingFromApp(pShmNode->hFile.h,
-          NULL, PAGE_READWRITE, nByte, NULL
-      );
-#elif defined(SQLITE_WIN32_HAS_WIDE)
-      hMap = osCreateFileMappingW(pShmNode->hFile.h,
-          NULL, PAGE_READWRITE, 0, nByte, NULL
-      );
-#elif defined(SQLITE_WIN32_HAS_ANSI) && SQLITE_WIN32_CREATEFILEMAPPINGA
-      hMap = osCreateFileMappingA(pShmNode->hFile.h,
-          NULL, PAGE_READWRITE, 0, nByte, NULL
-      );
-#endif
-      OSTRACE(("SHM-MAP-CREATE pid=%lu, region=%d, size=%d, rc=%s\n",
-               osGetCurrentProcessId(), pShmNode->nRegion, nByte,
-               hMap ? "ok" : "failed"));
-      if( hMap ){
-        int iOffset = pShmNode->nRegion*szRegion;
-        int iOffsetShift = iOffset % winSysInfo.dwAllocationGranularity;
-#if SQLITE_OS_WINRT
-        pMap = osMapViewOfFileFromApp(hMap, FILE_MAP_WRITE | FILE_MAP_READ,
-            iOffset - iOffsetShift, szRegion + iOffsetShift
-        );
-#else
-        pMap = osMapViewOfFile(hMap, FILE_MAP_WRITE | FILE_MAP_READ,
-            0, iOffset - iOffsetShift, szRegion + iOffsetShift
-        );
-#endif
-        OSTRACE(("SHM-MAP-MAP pid=%lu, region=%d, offset=%d, size=%d, rc=%s\n",
-                 osGetCurrentProcessId(), pShmNode->nRegion, iOffset,
-                 szRegion, pMap ? "ok" : "failed"));
-      }
-      if( !pMap ){
-        pShmNode->lastErrno = osGetLastError();
-        rc = winLogError(SQLITE_IOERR_SHMMAP, pShmNode->lastErrno,
-                         "winShmMap3", pDbFd->zPath);
-        if( hMap ) osCloseHandle(hMap);
-        goto shmpage_out;
-      }
+  }
 
-      pShmNode->aRegion[pShmNode->nRegion].pMap = pMap;
-      pShmNode->aRegion[pShmNode->nRegion].hMap = hMap;
-      pShmNode->nRegion++;
-    }
+  /* If we are holding a PENDING lock that ought to be released, then
+  ** release it now.
+  */
+  if( gotPendingLock && locktype==SHARED_LOCK ){
+    UnlockFile(pFile->h, PENDING_BYTE, 0, 1, 0);
   }
 
-shmpage_out:
-  if( pShmNode->nRegion>iRegion ){
-    int iOffset = iRegion*szRegion;
-    int iOffsetShift = iOffset % winSysInfo.dwAllocationGranularity;
-    char *p = (char *)pShmNode->aRegion[iRegion].pMap;
-    *pp = (void *)&p[iOffsetShift];
+  /* Update the state of the lock has held in the file descriptor then
+  ** return the appropriate result code.
+  */
+  if( res ){
+    rc = SQLITE_OK;
   }else{
-    *pp = 0;
+    OSTRACE4("LOCK FAILED %d trying for %d but got %d\n", pFile->h,
+           locktype, newLocktype);
+    pFile->lastErrno = error;
+    rc = SQLITE_BUSY;
   }
-  sqlite3_mutex_leave(pShmNode->mutex);
+  pFile->locktype = (u8)newLocktype;
   return rc;
 }
 
-#else
-# define winShmMap     0
-# define winShmLock    0
-# define winShmBarrier 0
-# define winShmUnmap   0
-#endif /* #ifndef SQLITE_OMIT_WAL */
-
 /*
-** Cleans up the mapped region of the specified file, if any.
+** This routine checks if there is a RESERVED lock held on the specified
+** file by this or any other process. If such a lock is held, return
+** non-zero, otherwise zero.
 */
-#if SQLITE_MAX_MMAP_SIZE>0
-static int winUnmapfile(winFile *pFile){
-  assert( pFile!=0 );
-  OSTRACE(("UNMAP-FILE pid=%lu, pFile=%p, hMap=%p, pMapRegion=%p, "
-           "mmapSize=%lld, mmapSizeActual=%lld, mmapSizeMax=%lld\n",
-           osGetCurrentProcessId(), pFile, pFile->hMap, pFile->pMapRegion,
-           pFile->mmapSize, pFile->mmapSizeActual, pFile->mmapSizeMax));
-  if( pFile->pMapRegion ){
-    if( !osUnmapViewOfFile(pFile->pMapRegion) ){
-      pFile->lastErrno = osGetLastError();
-      OSTRACE(("UNMAP-FILE pid=%lu, pFile=%p, pMapRegion=%p, "
-               "rc=SQLITE_IOERR_MMAP\n", osGetCurrentProcessId(), pFile,
-               pFile->pMapRegion));
-      return winLogError(SQLITE_IOERR_MMAP, pFile->lastErrno,
-                         "winUnmapfile1", pFile->zPath);
-    }
-    pFile->pMapRegion = 0;
-    pFile->mmapSize = 0;
-    pFile->mmapSizeActual = 0;
-  }
-  if( pFile->hMap!=NULL ){
-    if( !osCloseHandle(pFile->hMap) ){
-      pFile->lastErrno = osGetLastError();
-      OSTRACE(("UNMAP-FILE pid=%lu, pFile=%p, hMap=%p, rc=SQLITE_IOERR_MMAP\n",
-               osGetCurrentProcessId(), pFile, pFile->hMap));
-      return winLogError(SQLITE_IOERR_MMAP, pFile->lastErrno,
-                         "winUnmapfile2", pFile->zPath);
+static int winCheckReservedLock(sqlite3_file *id, int *pResOut){
+  int rc;
+  winFile *pFile = (winFile*)id;
+
+  assert( id!=0 );
+  if( pFile->locktype>=RESERVED_LOCK ){
+    rc = 1;
+    OSTRACE3("TEST WR-LOCK %d %d (local)\n", pFile->h, rc);
+  }else{
+    rc = LockFile(pFile->h, RESERVED_BYTE, 0, 1, 0);
+    if( rc ){
+      UnlockFile(pFile->h, RESERVED_BYTE, 0, 1, 0);
     }
-    pFile->hMap = NULL;
+    rc = !rc;
+    OSTRACE3("TEST WR-LOCK %d %d (remote)\n", pFile->h, rc);
   }
-  OSTRACE(("UNMAP-FILE pid=%lu, pFile=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), pFile));
+  *pResOut = rc;
   return SQLITE_OK;
 }
 
 /*
-** Memory map or remap the file opened by file-descriptor pFd (if the file
-** is already mapped, the existing mapping is replaced by the new). Or, if
-** there already exists a mapping for this file, and there are still
-** outstanding xFetch() references to it, this function is a no-op.
+** Lower the locking level on file descriptor id to locktype.  locktype
+** must be either NO_LOCK or SHARED_LOCK.
 **
-** If parameter nByte is non-negative, then it is the requested size of
-** the mapping to create. Otherwise, if nByte is less than zero, then the
-** requested size is the size of the file on disk. The actual size of the
-** created mapping is either the requested size or the value configured
-** using SQLITE_FCNTL_MMAP_SIZE, whichever is smaller.
+** If the locking level of the file descriptor is already at or below
+** the requested locking level, this routine is a no-op.
 **
-** SQLITE_OK is returned if no error occurs (even if the mapping is not
-** recreated as a result of outstanding references) or an SQLite error
-** code otherwise.
+** It is not possible for this routine to fail if the second argument
+** is NO_LOCK.  If the second argument is SHARED_LOCK then this routine
+** might return SQLITE_IOERR;
 */
-static int winMapfile(winFile *pFd, sqlite3_int64 nByte){
-  sqlite3_int64 nMap = nByte;
-  int rc;
-
-  assert( nMap>=0 || pFd->nFetchOut==0 );
-  OSTRACE(("MAP-FILE pid=%lu, pFile=%p, size=%lld\n",
-           osGetCurrentProcessId(), pFd, nByte));
-
-  if( pFd->nFetchOut>0 ) return SQLITE_OK;
-
-  if( nMap<0 ){
-    rc = winFileSize((sqlite3_file*)pFd, &nMap);
-    if( rc ){
-      OSTRACE(("MAP-FILE pid=%lu, pFile=%p, rc=SQLITE_IOERR_FSTAT\n",
-               osGetCurrentProcessId(), pFd));
-      return SQLITE_IOERR_FSTAT;
+static int winUnlock(sqlite3_file *id, int locktype){
+  int type;
+  winFile *pFile = (winFile*)id;
+  int rc = SQLITE_OK;
+  assert( pFile!=0 );
+  assert( locktype<=SHARED_LOCK );
+  OSTRACE5("UNLOCK %d to %d was %d(%d)\n", pFile->h, locktype,
+          pFile->locktype, pFile->sharedLockByte);
+  type = pFile->locktype;
+  if( type>=EXCLUSIVE_LOCK ){
+    UnlockFile(pFile->h, SHARED_FIRST, 0, SHARED_SIZE, 0);
+    if( locktype==SHARED_LOCK && !getReadLock(pFile) ){
+      /* This should never happen.  We should always be able to
+      ** reacquire the read lock */
+      rc = SQLITE_IOERR_UNLOCK;
     }
   }
-  if( nMap>pFd->mmapSizeMax ){
-    nMap = pFd->mmapSizeMax;
+  if( type>=RESERVED_LOCK ){
+    UnlockFile(pFile->h, RESERVED_BYTE, 0, 1, 0);
   }
-  nMap &= ~(sqlite3_int64)(winSysInfo.dwPageSize - 1);
-
-  if( nMap==0 && pFd->mmapSize>0 ){
-    winUnmapfile(pFd);
+  if( locktype==NO_LOCK && type>=SHARED_LOCK ){
+    unlockReadLock(pFile);
   }
-  if( nMap!=pFd->mmapSize ){
-    void *pNew = 0;
-    DWORD protect = PAGE_READONLY;
-    DWORD flags = FILE_MAP_READ;
-
-    winUnmapfile(pFd);
-#ifdef SQLITE_MMAP_READWRITE
-    if( (pFd->ctrlFlags & WINFILE_RDONLY)==0 ){
-      protect = PAGE_READWRITE;
-      flags |= FILE_MAP_WRITE;
-    }
-#endif
-#if SQLITE_OS_WINRT
-    pFd->hMap = osCreateFileMappingFromApp(pFd->h, NULL, protect, nMap, NULL);
-#elif defined(SQLITE_WIN32_HAS_WIDE)
-    pFd->hMap = osCreateFileMappingW(pFd->h, NULL, protect,
-                                (DWORD)((nMap>>32) & 0xffffffff),
-                                (DWORD)(nMap & 0xffffffff), NULL);
-#elif defined(SQLITE_WIN32_HAS_ANSI) && SQLITE_WIN32_CREATEFILEMAPPINGA
-    pFd->hMap = osCreateFileMappingA(pFd->h, NULL, protect,
-                                (DWORD)((nMap>>32) & 0xffffffff),
-                                (DWORD)(nMap & 0xffffffff), NULL);
-#endif
-    if( pFd->hMap==NULL ){
-      pFd->lastErrno = osGetLastError();
-      rc = winLogError(SQLITE_IOERR_MMAP, pFd->lastErrno,
-                       "winMapfile1", pFd->zPath);
-      /* Log the error, but continue normal operation using xRead/xWrite */
-      OSTRACE(("MAP-FILE-CREATE pid=%lu, pFile=%p, rc=%s\n",
-               osGetCurrentProcessId(), pFd, sqlite3ErrName(rc)));
-      return SQLITE_OK;
-    }
-    assert( (nMap % winSysInfo.dwPageSize)==0 );
-    assert( sizeof(SIZE_T)==sizeof(sqlite3_int64) || nMap<=0xffffffff );
-#if SQLITE_OS_WINRT
-    pNew = osMapViewOfFileFromApp(pFd->hMap, flags, 0, (SIZE_T)nMap);
-#else
-    pNew = osMapViewOfFile(pFd->hMap, flags, 0, 0, (SIZE_T)nMap);
-#endif
-    if( pNew==NULL ){
-      osCloseHandle(pFd->hMap);
-      pFd->hMap = NULL;
-      pFd->lastErrno = osGetLastError();
-      rc = winLogError(SQLITE_IOERR_MMAP, pFd->lastErrno,
-                       "winMapfile2", pFd->zPath);
-      /* Log the error, but continue normal operation using xRead/xWrite */
-      OSTRACE(("MAP-FILE-MAP pid=%lu, pFile=%p, rc=%s\n",
-               osGetCurrentProcessId(), pFd, sqlite3ErrName(rc)));
-      return SQLITE_OK;
-    }
-    pFd->pMapRegion = pNew;
-    pFd->mmapSize = nMap;
-    pFd->mmapSizeActual = nMap;
+  if( type>=PENDING_LOCK ){
+    UnlockFile(pFile->h, PENDING_BYTE, 0, 1, 0);
   }
-
-  OSTRACE(("MAP-FILE pid=%lu, pFile=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), pFd));
-  return SQLITE_OK;
+  pFile->locktype = (u8)locktype;
+  return rc;
 }
-#endif /* SQLITE_MAX_MMAP_SIZE>0 */
 
 /*
-** If possible, return a pointer to a mapping of file fd starting at offset
-** iOff. The mapping must be valid for at least nAmt bytes.
-**
-** If such a pointer can be obtained, store it in *pp and return SQLITE_OK.
-** Or, if one cannot but no error occurs, set *pp to 0 and return SQLITE_OK.
-** Finally, if an error does occur, return an SQLite error code. The final
-** value of *pp is undefined in this case.
-**
-** If this function does return a pointer, the caller must eventually
-** release the reference by calling winUnfetch().
+** Control and query of the open file handle.
 */
-static int winFetch(sqlite3_file *fd, i64 iOff, int nAmt, void **pp){
-#if SQLITE_MAX_MMAP_SIZE>0
-  winFile *pFd = (winFile*)fd;   /* The underlying database file */
-#endif
-  *pp = 0;
-
-  OSTRACE(("FETCH pid=%lu, pFile=%p, offset=%lld, amount=%d, pp=%p\n",
-           osGetCurrentProcessId(), fd, iOff, nAmt, pp));
-
-#if SQLITE_MAX_MMAP_SIZE>0
-  if( pFd->mmapSizeMax>0 ){
-    if( pFd->pMapRegion==0 ){
-      int rc = winMapfile(pFd, -1);
-      if( rc!=SQLITE_OK ){
-        OSTRACE(("FETCH pid=%lu, pFile=%p, rc=%s\n",
-                 osGetCurrentProcessId(), pFd, sqlite3ErrName(rc)));
-        return rc;
-      }
+static int winFileControl(sqlite3_file *id, int op, void *pArg){
+  switch( op ){
+    case SQLITE_FCNTL_LOCKSTATE: {
+      *(int*)pArg = ((winFile*)id)->locktype;
+      return SQLITE_OK;
     }
-    if( pFd->mmapSize >= iOff+nAmt ){
-      *pp = &((u8 *)pFd->pMapRegion)[iOff];
-      pFd->nFetchOut++;
+    case SQLITE_LAST_ERRNO: {
+      *(int*)pArg = (int)((winFile*)id)->lastErrno;
+      return SQLITE_OK;
     }
   }
-#endif
-
-  OSTRACE(("FETCH pid=%lu, pFile=%p, pp=%p, *pp=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), fd, pp, *pp));
-  return SQLITE_OK;
+  return SQLITE_ERROR;
 }
 
 /*
-** If the third argument is non-NULL, then this function releases a
-** reference obtained by an earlier call to winFetch(). The second
-** argument passed to this function must be the same as the corresponding
-** argument that was passed to the winFetch() invocation.
+** Return the sector size in bytes of the underlying block device for
+** the specified file. This is almost always 512 bytes, but may be
+** larger for some devices.
 **
-** Or, if the third argument is NULL, then this function is being called
-** to inform the VFS layer that, according to POSIX, any existing mapping
-** may now be invalid and should be unmapped.
-*/
-static int winUnfetch(sqlite3_file *fd, i64 iOff, void *p){
-#if SQLITE_MAX_MMAP_SIZE>0
-  winFile *pFd = (winFile*)fd;   /* The underlying database file */
-
-  /* If p==0 (unmap the entire file) then there must be no outstanding
-  ** xFetch references. Or, if p!=0 (meaning it is an xFetch reference),
-  ** then there must be at least one outstanding.  */
-  assert( (p==0)==(pFd->nFetchOut==0) );
-
-  /* If p!=0, it must match the iOff value. */
-  assert( p==0 || p==&((u8 *)pFd->pMapRegion)[iOff] );
-
-  OSTRACE(("UNFETCH pid=%lu, pFile=%p, offset=%lld, p=%p\n",
-           osGetCurrentProcessId(), pFd, iOff, p));
-
-  if( p ){
-    pFd->nFetchOut--;
-  }else{
-    /* FIXME:  If Windows truly always prevents truncating or deleting a
-    ** file while a mapping is held, then the following winUnmapfile() call
-    ** is unnecessary can be omitted - potentially improving
-    ** performance.  */
-    winUnmapfile(pFd);
-  }
-
-  assert( pFd->nFetchOut>=0 );
-#endif
-
-  OSTRACE(("UNFETCH pid=%lu, pFile=%p, rc=SQLITE_OK\n",
-           osGetCurrentProcessId(), fd));
-  return SQLITE_OK;
+** SQLite code assumes this function cannot fail. It also assumes that
+** if two files are created in the same file-system directory (i.e.
+** a database and its journal file) that the sector size will be the
+** same for both.
+*/
+static int winSectorSize(sqlite3_file *id){
+  assert( id!=0 );
+  return (int)(((winFile*)id)->sectorSize);
 }
 
 /*
-** Here ends the implementation of all sqlite3_file methods.
-**
-********************** End sqlite3_file Methods *******************************
-******************************************************************************/
+** Return a vector of device characteristics.
+*/
+static int winDeviceCharacteristics(sqlite3_file *id){
+  UNUSED_PARAMETER(id);
+  return 0;
+}
 
 /*
 ** This vector defines all the methods that can operate on an
 ** sqlite3_file for win32.
 */
 static const sqlite3_io_methods winIoMethod = {
-  3,                              /* iVersion */
-  winClose,                       /* xClose */
-  winRead,                        /* xRead */
-  winWrite,                       /* xWrite */
-  winTruncate,                    /* xTruncate */
-  winSync,                        /* xSync */
-  winFileSize,                    /* xFileSize */
-  winLock,                        /* xLock */
-  winUnlock,                      /* xUnlock */
-  winCheckReservedLock,           /* xCheckReservedLock */
-  winFileControl,                 /* xFileControl */
-  winSectorSize,                  /* xSectorSize */
-  winDeviceCharacteristics,       /* xDeviceCharacteristics */
-  winShmMap,                      /* xShmMap */
-  winShmLock,                     /* xShmLock */
-  winShmBarrier,                  /* xShmBarrier */
-  winShmUnmap,                    /* xShmUnmap */
-  winFetch,                       /* xFetch */
-  winUnfetch                      /* xUnfetch */
-};
-
-/*
-** This vector defines all the methods that can operate on an
-** sqlite3_file for win32 without performing any locking.
-*/
-static const sqlite3_io_methods winIoNolockMethod = {
-  3,                              /* iVersion */
-  winClose,                       /* xClose */
-  winRead,                        /* xRead */
-  winWrite,                       /* xWrite */
-  winTruncate,                    /* xTruncate */
-  winSync,                        /* xSync */
-  winFileSize,                    /* xFileSize */
-  winNolockLock,                  /* xLock */
-  winNolockUnlock,                /* xUnlock */
-  winNolockCheckReservedLock,     /* xCheckReservedLock */
-  winFileControl,                 /* xFileControl */
-  winSectorSize,                  /* xSectorSize */
-  winDeviceCharacteristics,       /* xDeviceCharacteristics */
-  winShmMap,                      /* xShmMap */
-  winShmLock,                     /* xShmLock */
-  winShmBarrier,                  /* xShmBarrier */
-  winShmUnmap,                    /* xShmUnmap */
-  winFetch,                       /* xFetch */
-  winUnfetch                      /* xUnfetch */
-};
-
-static winVfsAppData winAppData = {
-  &winIoMethod,       /* pMethod */
-  0,                  /* pAppData */
-  0                   /* bNoLock */
-};
-
-static winVfsAppData winNolockAppData = {
-  &winIoNolockMethod, /* pMethod */
-  0,                  /* pAppData */
-  1                   /* bNoLock */
+  1,                        /* iVersion */
+  winClose,
+  winRead,
+  winWrite,
+  winTruncate,
+  winSync,
+  winFileSize,
+  winLock,
+  winUnlock,
+  winCheckReservedLock,
+  winFileControl,
+  winSectorSize,
+  winDeviceCharacteristics
 };
 
-/****************************************************************************
-**************************** sqlite3_vfs methods ****************************
+/***************************************************************************
+** Here ends the I/O methods that form the sqlite3_io_methods object.
 **
-** This division contains the implementation of methods on the
-** sqlite3_vfs object.
-*/
-
-#if defined(__CYGWIN__)
-/*
-** Convert a filename from whatever the underlying operating system
-** supports for filenames into UTF-8.  Space to hold the result is
-** obtained from malloc and must be freed by the calling function.
-*/
-static char *winConvertToUtf8Filename(const void *zFilename){
-  char *zConverted = 0;
-  if( osIsNT() ){
-    zConverted = winUnicodeToUtf8(zFilename);
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
-    zConverted = winMbcsToUtf8(zFilename, osAreFileApisANSI());
-  }
-#endif
-  /* caller will handle out of memory */
-  return zConverted;
-}
-#endif
+** The next block of code implements the VFS methods.
+****************************************************************************/
 
 /*
 ** Convert a UTF-8 filename into whatever form the underlying
 ** operating system wants filenames in.  Space to hold the result
 ** is obtained from malloc and must be freed by the calling
 ** function.
 */
-static void *winConvertFromUtf8Filename(const char *zFilename){
+static void *convertUtf8Filename(const char *zFilename){
   void *zConverted = 0;
-  if( osIsNT() ){
-    zConverted = winUtf8ToUnicode(zFilename);
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
-    zConverted = winUtf8ToMbcs(zFilename, osAreFileApisANSI());
-  }
+  if( isNT() ){
+    zConverted = utf8ToUnicode(zFilename);
+/* isNT() is 1 if SQLITE_OS_WINCE==1, so this else is never executed. 
+*/
+#if SQLITE_OS_WINCE==0
+  }else{
+    zConverted = utf8ToMbcs(zFilename);
 #endif
+  }
   /* caller will handle out of memory */
   return zConverted;
 }
 
 /*
-** This function returns non-zero if the specified UTF-8 string buffer
-** ends with a directory separator character or one was successfully
-** added to it.
-*/
-static int winMakeEndInDirSep(int nBuf, char *zBuf){
-  if( zBuf ){
-    int nLen = sqlite3Strlen30(zBuf);
-    if( nLen>0 ){
-      if( winIsDirSep(zBuf[nLen-1]) ){
-        return 1;
-      }else if( nLen+1<nBuf ){
-        zBuf[nLen] = winGetDirSep();
-        zBuf[nLen+1] = '\0';
-        return 1;
-      }
-    }
-  }
-  return 0;
-}
-
-/*
-** Create a temporary file name and store the resulting pointer into pzBuf.
-** The pointer returned in pzBuf must be freed via sqlite3_free().
+** Create a temporary file name in zBuf.  zBuf must be big enough to
+** hold at pVfs->mxPathname characters.
 */
-static int winGetTempname(sqlite3_vfs *pVfs, char **pzBuf){
+static int getTempname(int nBuf, char *zBuf){
   static char zChars[] =
     "abcdefghijklmnopqrstuvwxyz"
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
     "0123456789";
   size_t i, j;
-  int nPre = sqlite3Strlen30(SQLITE_TEMP_FILE_PREFIX);
-  int nMax, nBuf, nDir, nLen;
-  char *zBuf;
-
-  /* It's odd to simulate an io-error here, but really this is just
-  ** using the io-error infrastructure to test that SQLite handles this
-  ** function failing.
-  */
-  SimulateIOError( return SQLITE_IOERR );
-
-  /* Allocate a temporary buffer to store the fully qualified file
-  ** name for the temporary file.  If this fails, we cannot continue.
-  */
-  nMax = pVfs->mxPathname; nBuf = nMax + 2;
-  zBuf = sqlite3MallocZero( nBuf );
-  if( !zBuf ){
-    OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-    return SQLITE_IOERR_NOMEM_BKPT;
-  }
-
-  /* Figure out the effective temporary directory.  First, check if one
-  ** has been explicitly set by the application; otherwise, use the one
-  ** configured by the operating system.
-  */
-  nDir = nMax - (nPre + 15);
-  assert( nDir>0 );
+  char zTempPath[MAX_PATH+1];
   if( sqlite3_temp_directory ){
-    int nDirLen = sqlite3Strlen30(sqlite3_temp_directory);
-    if( nDirLen>0 ){
-      if( !winIsDirSep(sqlite3_temp_directory[nDirLen-1]) ){
-        nDirLen++;
-      }
-      if( nDirLen>nDir ){
-        sqlite3_free(zBuf);
-        OSTRACE(("TEMP-FILENAME rc=SQLITE_ERROR\n"));
-        return winLogError(SQLITE_ERROR, 0, "winGetTempname1", 0);
-      }
-      sqlite3_snprintf(nMax, zBuf, "%s", sqlite3_temp_directory);
-    }
-  }
-#if defined(__CYGWIN__)
-  else{
-    static const char *azDirs[] = {
-       0, /* getenv("SQLITE_TMPDIR") */
-       0, /* getenv("TMPDIR") */
-       0, /* getenv("TMP") */
-       0, /* getenv("TEMP") */
-       0, /* getenv("USERPROFILE") */
-       "/var/tmp",
-       "/usr/tmp",
-       "/tmp",
-       ".",
-       0        /* List terminator */
-    };
-    unsigned int i;
-    const char *zDir = 0;
-
-    if( !azDirs[0] ) azDirs[0] = getenv("SQLITE_TMPDIR");
-    if( !azDirs[1] ) azDirs[1] = getenv("TMPDIR");
-    if( !azDirs[2] ) azDirs[2] = getenv("TMP");
-    if( !azDirs[3] ) azDirs[3] = getenv("TEMP");
-    if( !azDirs[4] ) azDirs[4] = getenv("USERPROFILE");
-    for(i=0; i<sizeof(azDirs)/sizeof(azDirs[0]); zDir=azDirs[i++]){
-      void *zConverted;
-      if( zDir==0 ) continue;
-      /* If the path starts with a drive letter followed by the colon
-      ** character, assume it is already a native Win32 path; otherwise,
-      ** it must be converted to a native Win32 path via the Cygwin API
-      ** prior to using it.
-      */
-      if( winIsDriveLetterAndColon(zDir) ){
-        zConverted = winConvertFromUtf8Filename(zDir);
-        if( !zConverted ){
-          sqlite3_free(zBuf);
-          OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-          return SQLITE_IOERR_NOMEM_BKPT;
-        }
-        if( winIsDir(zConverted) ){
-          sqlite3_snprintf(nMax, zBuf, "%s", zDir);
-          sqlite3_free(zConverted);
-          break;
-        }
-        sqlite3_free(zConverted);
-      }else{
-        zConverted = sqlite3MallocZero( nMax+1 );
-        if( !zConverted ){
-          sqlite3_free(zBuf);
-          OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-          return SQLITE_IOERR_NOMEM_BKPT;
-        }
-        if( cygwin_conv_path(
-                osIsNT() ? CCP_POSIX_TO_WIN_W : CCP_POSIX_TO_WIN_A, zDir,
-                zConverted, nMax+1)<0 ){
-          sqlite3_free(zConverted);
-          sqlite3_free(zBuf);
-          OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_CONVPATH\n"));
-          return winLogError(SQLITE_IOERR_CONVPATH, (DWORD)errno,
-                             "winGetTempname2", zDir);
-        }
-        if( winIsDir(zConverted) ){
-          /* At this point, we know the candidate directory exists and should
-          ** be used.  However, we may need to convert the string containing
-          ** its name into UTF-8 (i.e. if it is UTF-16 right now).
-          */
-          char *zUtf8 = winConvertToUtf8Filename(zConverted);
-          if( !zUtf8 ){
-            sqlite3_free(zConverted);
-            sqlite3_free(zBuf);
-            OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-            return SQLITE_IOERR_NOMEM_BKPT;
-          }
-          sqlite3_snprintf(nMax, zBuf, "%s", zUtf8);
-          sqlite3_free(zUtf8);
-          sqlite3_free(zConverted);
-          break;
-        }
-        sqlite3_free(zConverted);
-      }
-    }
-  }
-#elif !SQLITE_OS_WINRT && !defined(__CYGWIN__)
-  else if( osIsNT() ){
+    sqlite3_snprintf(MAX_PATH-30, zTempPath, "%s", sqlite3_temp_directory);
+  }else if( isNT() ){
     char *zMulti;
-    LPWSTR zWidePath = sqlite3MallocZero( nMax*sizeof(WCHAR) );
-    if( !zWidePath ){
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-      return SQLITE_IOERR_NOMEM_BKPT;
-    }
-    if( osGetTempPathW(nMax, zWidePath)==0 ){
-      sqlite3_free(zWidePath);
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_GETTEMPPATH\n"));
-      return winLogError(SQLITE_IOERR_GETTEMPPATH, osGetLastError(),
-                         "winGetTempname2", 0);
-    }
-    zMulti = winUnicodeToUtf8(zWidePath);
+    WCHAR zWidePath[MAX_PATH];
+    GetTempPathW(MAX_PATH-30, zWidePath);
+    zMulti = unicodeToUtf8(zWidePath);
     if( zMulti ){
-      sqlite3_snprintf(nMax, zBuf, "%s", zMulti);
-      sqlite3_free(zMulti);
-      sqlite3_free(zWidePath);
+      sqlite3_snprintf(MAX_PATH-30, zTempPath, "%s", zMulti);
+      free(zMulti);
     }else{
-      sqlite3_free(zWidePath);
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-      return SQLITE_IOERR_NOMEM_BKPT;
+      return SQLITE_NOMEM;
     }
-  }
-#ifdef SQLITE_WIN32_HAS_ANSI
-  else{
+/* isNT() is 1 if SQLITE_OS_WINCE==1, so this else is never executed. 
+** Since the ASCII version of these Windows API do not exist for WINCE,
+** it's important to not reference them for WINCE builds.
+*/
+#if SQLITE_OS_WINCE==0
+  }else{
     char *zUtf8;
-    char *zMbcsPath = sqlite3MallocZero( nMax );
-    if( !zMbcsPath ){
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-      return SQLITE_IOERR_NOMEM_BKPT;
-    }
-    if( osGetTempPathA(nMax, zMbcsPath)==0 ){
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_GETTEMPPATH\n"));
-      return winLogError(SQLITE_IOERR_GETTEMPPATH, osGetLastError(),
-                         "winGetTempname3", 0);
-    }
-    zUtf8 = winMbcsToUtf8(zMbcsPath, osAreFileApisANSI());
+    char zMbcsPath[MAX_PATH];
+    GetTempPathA(MAX_PATH-30, zMbcsPath);
+    zUtf8 = sqlite3_win32_mbcs_to_utf8(zMbcsPath);
     if( zUtf8 ){
-      sqlite3_snprintf(nMax, zBuf, "%s", zUtf8);
-      sqlite3_free(zUtf8);
+      sqlite3_snprintf(MAX_PATH-30, zTempPath, "%s", zUtf8);
+      free(zUtf8);
     }else{
-      sqlite3_free(zBuf);
-      OSTRACE(("TEMP-FILENAME rc=SQLITE_IOERR_NOMEM\n"));
-      return SQLITE_IOERR_NOMEM_BKPT;
+      return SQLITE_NOMEM;
     }
+#endif
   }
-#endif /* SQLITE_WIN32_HAS_ANSI */
-#endif /* !SQLITE_OS_WINRT */
-
-  /*
-  ** Check to make sure the temporary directory ends with an appropriate
-  ** separator.  If it does not and there is not enough space left to add
-  ** one, fail.
-  */
-  if( !winMakeEndInDirSep(nDir+1, zBuf) ){
-    sqlite3_free(zBuf);
-    OSTRACE(("TEMP-FILENAME rc=SQLITE_ERROR\n"));
-    return winLogError(SQLITE_ERROR, 0, "winGetTempname4", 0);
-  }
-
-  /*
-  ** Check that the output buffer is large enough for the temporary file
-  ** name in the following format:
-  **
-  **   "<temporary_directory>/etilqs_XXXXXXXXXXXXXXX\0\0"
-  **
-  ** If not, return SQLITE_ERROR.  The number 17 is used here in order to
-  ** account for the space used by the 15 character random suffix and the
-  ** two trailing NUL characters.  The final directory separator character
-  ** has already added if it was not already present.
-  */
-  nLen = sqlite3Strlen30(zBuf);
-  if( (nLen + nPre + 17) > nBuf ){
-    sqlite3_free(zBuf);
-    OSTRACE(("TEMP-FILENAME rc=SQLITE_ERROR\n"));
-    return winLogError(SQLITE_ERROR, 0, "winGetTempname5", 0);
-  }
-
-  sqlite3_snprintf(nBuf-16-nLen, zBuf+nLen, SQLITE_TEMP_FILE_PREFIX);
-
+  for(i=sqlite3Strlen30(zTempPath); i>0 && zTempPath[i-1]=='\\'; i--){}
+  zTempPath[i] = 0;
+  sqlite3_snprintf(nBuf-30, zBuf,
+                   "%s\\"SQLITE_TEMP_FILE_PREFIX, zTempPath);
   j = sqlite3Strlen30(zBuf);
-  sqlite3_randomness(15, &zBuf[j]);
-  for(i=0; i<15; i++, j++){
+  sqlite3_randomness(20, &zBuf[j]);
+  for(i=0; i<20; i++, j++){
     zBuf[j] = (char)zChars[ ((unsigned char)zBuf[j])%(sizeof(zChars)-1) ];
   }
   zBuf[j] = 0;
-  zBuf[j+1] = 0;
-  *pzBuf = zBuf;
-
-  OSTRACE(("TEMP-FILENAME name=%s, rc=SQLITE_OK\n", zBuf));
-  return SQLITE_OK;
+  OSTRACE2("TEMP FILENAME: %s\n", zBuf);
+  return SQLITE_OK; 
 }
 
 /*
-** Return TRUE if the named file is really a directory.  Return false if
-** it is something other than a directory, or if there is any kind of memory
-** allocation failure.
+** The return value of getLastErrorMsg
+** is zero if the error message fits in the buffer, or non-zero
+** otherwise (if the message was truncated).
 */
-static int winIsDir(const void *zConverted){
-  DWORD attr;
-  int rc = 0;
-  DWORD lastErrno;
+static int getLastErrorMsg(int nBuf, char *zBuf){
+  DWORD error = GetLastError();
 
-  if( osIsNT() ){
-    int cnt = 0;
-    WIN32_FILE_ATTRIBUTE_DATA sAttrData;
-    memset(&sAttrData, 0, sizeof(sAttrData));
-    while( !(rc = osGetFileAttributesExW((LPCWSTR)zConverted,
-                             GetFileExInfoStandard,
-                             &sAttrData)) && winRetryIoerr(&cnt, &lastErrno) ){}
-    if( !rc ){
-      return 0; /* Invalid name? */
-    }
-    attr = sAttrData.dwFileAttributes;
-#if SQLITE_OS_WINCE==0
-  }else{
-    attr = osGetFileAttributesA((char*)zConverted);
-#endif
+#if SQLITE_OS_WINCE
+  sqlite3_snprintf(nBuf, zBuf, "OsError 0x%x (%u)", error, error);
+#else
+  /* FormatMessage returns 0 on failure.  Otherwise it
+  ** returns the number of TCHARs written to the output
+  ** buffer, excluding the terminating null char.
+  */
+  if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
+                      NULL,
+                      error,
+                      0,
+                      zBuf,
+                      nBuf-1,
+                      0))
+  {
+    sqlite3_snprintf(nBuf, zBuf, "OsError 0x%x (%u)", error, error);
   }
-  return (attr!=INVALID_FILE_ATTRIBUTES) && (attr&FILE_ATTRIBUTE_DIRECTORY);
-}
+#endif
 
-/* forward reference */
-static int winAccess(
-  sqlite3_vfs *pVfs,         /* Not used on win32 */
-  const char *zFilename,     /* Name of file to check */
-  int flags,                 /* Type of test to make on this file */
-  int *pResOut               /* OUT: Result */
-);
+  return 0;
+}
 
 /*
 ** Open a file.
 */
 static int winOpen(
-  sqlite3_vfs *pVfs,        /* Used to get maximum path length and AppData */
+  sqlite3_vfs *pVfs,        /* Not used */
   const char *zName,        /* Name of the file (UTF-8) */
   sqlite3_file *id,         /* Write the SQLite file handle here */
   int flags,                /* Open mode flags */
   int *pOutFlags            /* Status return flags */
 ){
   HANDLE h;
-  DWORD lastErrno = 0;
   DWORD dwDesiredAccess;
   DWORD dwShareMode;
   DWORD dwCreationDisposition;
   DWORD dwFlagsAndAttributes = 0;
 #if SQLITE_OS_WINCE
   int isTemp = 0;
 #endif
-  winVfsAppData *pAppData;
   winFile *pFile = (winFile*)id;
-  void *zConverted;              /* Filename in OS encoding */
-  const char *zUtf8Name = zName; /* Filename in UTF-8 encoding */
-  int cnt = 0;
-
-  /* If argument zPath is a NULL pointer, this function is required to open
-  ** a temporary file. Use this buffer to store the file name in.
-  */
-  char *zTmpname = 0; /* For temporary filename, if necessary. */
-
-  int rc = SQLITE_OK;            /* Function Return Code */
-#if !defined(NDEBUG) || SQLITE_OS_WINCE
-  int eType = flags&0xFFFFFF00;  /* Type of file to open */
-#endif
-
-  int isExclusive  = (flags & SQLITE_OPEN_EXCLUSIVE);
-  int isDelete     = (flags & SQLITE_OPEN_DELETEONCLOSE);
-  int isCreate     = (flags & SQLITE_OPEN_CREATE);
-  int isReadonly   = (flags & SQLITE_OPEN_READONLY);
-  int isReadWrite  = (flags & SQLITE_OPEN_READWRITE);
-
-#ifndef NDEBUG
-  int isOpenJournal = (isCreate && (
-        eType==SQLITE_OPEN_MASTER_JOURNAL
-     || eType==SQLITE_OPEN_MAIN_JOURNAL
-     || eType==SQLITE_OPEN_WAL
-  ));
-#endif
-
-  OSTRACE(("OPEN name=%s, pFile=%p, flags=%x, pOutFlags=%p\n",
-           zUtf8Name, id, flags, pOutFlags));
-
-  /* Check the following statements are true:
-  **
-  **   (a) Exactly one of the READWRITE and READONLY flags must be set, and
-  **   (b) if CREATE is set, then READWRITE must also be set, and
-  **   (c) if EXCLUSIVE is set, then CREATE must also be set.
-  **   (d) if DELETEONCLOSE is set, then CREATE must also be set.
-  */
-  assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
-  assert(isCreate==0 || isReadWrite);
-  assert(isExclusive==0 || isCreate);
-  assert(isDelete==0 || isCreate);
-
-  /* The main DB, main journal, WAL file and master journal are never
-  ** automatically deleted. Nor are they ever temporary files.  */
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_DB );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_JOURNAL );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MASTER_JOURNAL );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_WAL );
-
-  /* Assert that the upper layer has set one of the "file-type" flags. */
-  assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB
-       || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL
-       || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL
-       || eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL
-  );
-
-  assert( pFile!=0 );
-  memset(pFile, 0, sizeof(winFile));
-  pFile->h = INVALID_HANDLE_VALUE;
+  void *zConverted;                 /* Filename in OS encoding */
+  const char *zUtf8Name = zName;    /* Filename in UTF-8 encoding */
+  char zTmpname[MAX_PATH+1];        /* Buffer used to create temp filename */
 
-#if SQLITE_OS_WINRT
-  if( !zUtf8Name && !sqlite3_temp_directory ){
-    sqlite3_log(SQLITE_ERROR,
-        "sqlite3_temp_directory variable should be set for WinRT");
-  }
-#endif
+  assert( id!=0 );
+  UNUSED_PARAMETER(pVfs);
 
-  /* If the second argument to this function is NULL, generate a
-  ** temporary file name to use
+  /* If the second argument to this function is NULL, generate a 
+  ** temporary file name to use 
   */
   if( !zUtf8Name ){
-    assert( isDelete && !isOpenJournal );
-    rc = winGetTempname(pVfs, &zTmpname);
+    int rc = getTempname(MAX_PATH+1, zTmpname);
     if( rc!=SQLITE_OK ){
-      OSTRACE(("OPEN name=%s, rc=%s", zUtf8Name, sqlite3ErrName(rc)));
       return rc;
     }
     zUtf8Name = zTmpname;
   }
 
-  /* Database filenames are double-zero terminated if they are not
-  ** URIs with parameters.  Hence, they can always be passed into
-  ** sqlite3_uri_parameter().
-  */
-  assert( (eType!=SQLITE_OPEN_MAIN_DB) || (flags & SQLITE_OPEN_URI) ||
-       zUtf8Name[sqlite3Strlen30(zUtf8Name)+1]==0 );
-
   /* Convert the filename to the system encoding. */
-  zConverted = winConvertFromUtf8Filename(zUtf8Name);
+  zConverted = convertUtf8Filename(zUtf8Name);
   if( zConverted==0 ){
-    sqlite3_free(zTmpname);
-    OSTRACE(("OPEN name=%s, rc=SQLITE_IOERR_NOMEM", zUtf8Name));
-    return SQLITE_IOERR_NOMEM_BKPT;
-  }
-
-  if( winIsDir(zConverted) ){
-    sqlite3_free(zConverted);
-    sqlite3_free(zTmpname);
-    OSTRACE(("OPEN name=%s, rc=SQLITE_CANTOPEN_ISDIR", zUtf8Name));
-    return SQLITE_CANTOPEN_ISDIR;
+    return SQLITE_NOMEM;
   }
 
-  if( isReadWrite ){
+  if( flags & SQLITE_OPEN_READWRITE ){
     dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
   }else{
     dwDesiredAccess = GENERIC_READ;
   }
-
-  /* SQLITE_OPEN_EXCLUSIVE is used to make sure that a new file is
-  ** created. SQLite doesn't use it to indicate "exclusive access"
+  /* SQLITE_OPEN_EXCLUSIVE is used to make sure that a new file is 
+  ** created. SQLite doesn't use it to indicate "exclusive access" 
   ** as it is usually understood.
   */
-  if( isExclusive ){
+  assert(!(flags & SQLITE_OPEN_EXCLUSIVE) || (flags & SQLITE_OPEN_CREATE));
+  if( flags & SQLITE_OPEN_EXCLUSIVE ){
     /* Creates a new file, only if it does not already exist. */
     /* If the file exists, it fails. */
     dwCreationDisposition = CREATE_NEW;
-  }else if( isCreate ){
+  }else if( flags & SQLITE_OPEN_CREATE ){
     /* Open existing file, or create if it doesn't exist */
     dwCreationDisposition = OPEN_ALWAYS;
   }else{
     /* Opens a file, only if it exists. */
     dwCreationDisposition = OPEN_EXISTING;
   }
