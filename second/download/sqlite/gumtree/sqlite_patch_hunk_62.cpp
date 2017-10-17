 ** Only thread A can modify the lock.  Locking behavior is correct
 ** if the appliation uses the newer Native Posix Thread Library (NPTL)
 ** on linux - with NPTL a lock created by thread A can override locks
 ** in thread B.  But there is no way to know at compile-time which
 ** threading library is being used.  So there is no way to know at
 ** compile-time whether or not thread A can override locks on thread B.
-** One has to do a run-time check to discover the behavior of the
+** We have to do a run-time check to discover the behavior of the
 ** current process.
 **
-** SQLite used to support LinuxThreads.  But support for LinuxThreads
-** was dropped beginning with version 3.7.0.  SQLite will still work with
-** LinuxThreads provided that (1) there is no more than one connection 
-** per database file in the same process and (2) database connections
-** do not move across threads.
+** On systems where thread A is unable to modify locks created by
+** thread B, we have to keep track of which thread created each
+** lock.  Hence there is an extra field in the key to the unixLockInfo
+** structure to record this information.  And on those systems it
+** is illegal to begin a transaction in one thread and finish it
+** in another.  For this latter restriction, there is no work-around.
+** It is a limitation of LinuxThreads.
 */
 
 /*
+** Set or check the unixFile.tid field.  This field is set when an unixFile
+** is first opened.  All subsequent uses of the unixFile verify that the
+** same thread is operating on the unixFile.  Some operating systems do
+** not allow locks to be overridden by other threads and that restriction
+** means that sqlite3* database handles cannot be moved from one thread
+** to another while locks are held.
+**
+** Version 3.3.1 (2006-01-15):  unixFile can be moved from one thread to
+** another as long as we are running on a system that supports threads
+** overriding each others locks (which is now the most common behavior)
+** or if no locks are held.  But the unixFile.pLock field needs to be
+** recomputed because its key includes the thread-id.  See the 
+** transferOwnership() function below for additional information
+*/
+#if SQLITE_THREADSAFE && defined(__linux__)
+# define SET_THREADID(X)   (X)->tid = pthread_self()
+# define CHECK_THREADID(X) (threadsOverrideEachOthersLocks==0 && \
+                            !pthread_equal((X)->tid, pthread_self()))
+#else
+# define SET_THREADID(X)
+# define CHECK_THREADID(X) 0
+#endif
+
+/*
 ** An instance of the following structure serves as the key used
-** to locate a particular unixInodeInfo object.
+** to locate a particular unixOpenCnt structure given its inode.  This
+** is the same as the unixLockKey except that the thread ID is omitted.
 */
 struct unixFileId {
   dev_t dev;                  /* Device number */
 #if OS_VXWORKS
   struct vxworksFileId *pId;  /* Unique file ID for vxworks. */
 #else
-  /* We are told that some versions of Android contain a bug that
-  ** sizes ino_t at only 32-bits instead of 64-bits. (See
-  ** https://android-review.googlesource.com/#/c/115351/3/dist/sqlite3.c)
-  ** To work around this, always allocate 64-bits for the inode number.  
-  ** On small machines that only have 32-bit inodes, this wastes 4 bytes,
-  ** but that should not be a big deal. */
-  /* WAS:  ino_t ino;   */
-  u64 ino;                   /* Inode number */
+  ino_t ino;                  /* Inode number */
+#endif
+};
+
+/*
+** An instance of the following structure serves as the key used
+** to locate a particular unixLockInfo structure given its inode.
+**
+** If threads cannot override each others locks (LinuxThreads), then we
+** set the unixLockKey.tid field to the thread ID.  If threads can override
+** each others locks (Posix and NPTL) then tid is always set to zero.
+** tid is omitted if we compile without threading support or on an OS
+** other than linux.
+*/
+struct unixLockKey {
+  struct unixFileId fid;  /* Unique identifier for the file */
+#if SQLITE_THREADSAFE && defined(__linux__)
+  pthread_t tid;  /* Thread ID of lock owner. Zero if not using LinuxThreads */
 #endif
 };
 
 /*
 ** An instance of the following structure is allocated for each open
 ** inode.  Or, on LinuxThreads, there is one of these structures for
 ** each inode opened by each thread.
 **
 ** A single inode can have multiple file descriptors, so each unixFile
 ** structure contains a pointer to an instance of this object and this
 ** object keeps a count of the number of unixFile pointing to it.
 */
-struct unixInodeInfo {
-  struct unixFileId fileId;       /* The lookup key */
-  int nShared;                    /* Number of SHARED locks held */
-  unsigned char eFileLock;        /* One of SHARED_LOCK, RESERVED_LOCK etc. */
-  unsigned char bProcessLock;     /* An exclusive process lock is held */
+struct unixLockInfo {
+  struct unixLockKey lockKey;     /* The lookup key */
+  int cnt;                        /* Number of SHARED locks held */
+  int locktype;                   /* One of SHARED_LOCK, RESERVED_LOCK etc. */
   int nRef;                       /* Number of pointers to this structure */
-  unixShmNode *pShmNode;          /* Shared memory associated with this inode */
-  int nLock;                      /* Number of outstanding file locks */
-  UnixUnusedFd *pUnused;          /* Unused file descriptors to close */
-  unixInodeInfo *pNext;           /* List of all unixInodeInfo objects */
-  unixInodeInfo *pPrev;           /*    .... doubly linked */
-#if SQLITE_ENABLE_LOCKING_STYLE
-  unsigned long long sharedByte;  /* for AFP simulated shared lock */
-#endif
+  struct unixLockInfo *pNext;     /* List of all unixLockInfo objects */
+  struct unixLockInfo *pPrev;     /*    .... doubly linked */
+};
+
+/*
+** An instance of the following structure is allocated for each open
+** inode.  This structure keeps track of the number of locks on that
+** inode.  If a close is attempted against an inode that is holding
+** locks, the close is deferred until all locks clear by adding the
+** file descriptor to be closed to the pending list.
+**
+** TODO:  Consider changing this so that there is only a single file
+** descriptor for each open file, even when it is opened multiple times.
+** The close() system call would only occur when the last database
+** using the file closes.
+*/
+struct unixOpenCnt {
+  struct unixFileId fileId;   /* The lookup key */
+  int nRef;                   /* Number of pointers to this structure */
+  int nLock;                  /* Number of outstanding locks */
+  int nPending;               /* Number of pending close() operations */
+  int *aPending;            /* Malloced space holding fd's awaiting a close() */
 #if OS_VXWORKS
-  sem_t *pSem;                    /* Named POSIX semaphore */
-  char aSemName[MAX_PATHNAME+2];  /* Name of that semaphore */
+  sem_t *pSem;                     /* Named POSIX semaphore */
+  char aSemName[MAX_PATHNAME+1];   /* Name of that semaphore */
 #endif
+  struct unixOpenCnt *pNext, *pPrev;   /* List of all unixOpenCnt objects */
 };
 
 /*
-** A lists of all unixInodeInfo objects.
-*/
-static unixInodeInfo *inodeList = 0;  /* All unixInodeInfo objects */
-static unsigned int nUnusedFd = 0;    /* Total unused file descriptors */
+** Lists of all unixLockInfo and unixOpenCnt objects.  These used to be hash
+** tables.  But the number of objects is rarely more than a dozen and
+** never exceeds a few thousand.  And lookup is not on a critical
+** path so a simple linked list will suffice.
+*/
+static struct unixLockInfo *lockList = 0;
+static struct unixOpenCnt *openList = 0;
+
+/*
+** This variable remembers whether or not threads can override each others
+** locks.
+**
+**    0:  No.  Threads cannot override each others locks.  (LinuxThreads)
+**    1:  Yes.  Threads can override each others locks.  (Posix & NLPT)
+**   -1:  We don't know yet.
+**
+** On some systems, we know at compile-time if threads can override each
+** others locks.  On those systems, the SQLITE_THREAD_OVERRIDE_LOCK macro
+** will be set appropriately.  On other systems, we have to check at
+** runtime.  On these latter systems, SQLTIE_THREAD_OVERRIDE_LOCK is
+** undefined.
+**
+** This variable normally has file scope only.  But during testing, we make
+** it a global so that the test code can change its value in order to verify
+** that the right stuff happens in either case.
+*/
+#if SQLITE_THREADSAFE && defined(__linux__)
+#  ifndef SQLITE_THREAD_OVERRIDE_LOCK
+#    define SQLITE_THREAD_OVERRIDE_LOCK -1
+#  endif
+#  ifdef SQLITE_TEST
+int threadsOverrideEachOthersLocks = SQLITE_THREAD_OVERRIDE_LOCK;
+#  else
+static int threadsOverrideEachOthersLocks = SQLITE_THREAD_OVERRIDE_LOCK;
+#  endif
+#endif
 
 /*
-**
-** This function - unixLogErrorAtLine(), is only ever called via the macro
-** unixLogError().
-**
-** It is invoked after an error occurs in an OS function and errno has been
-** set. It logs a message using sqlite3_log() containing the current value of
-** errno and, if possible, the human-readable equivalent from strerror() or
-** strerror_r().
-**
-** The first argument passed to the macro should be the error code that
-** will be returned to SQLite (e.g. SQLITE_IOERR_DELETE, SQLITE_CANTOPEN). 
-** The two subsequent arguments should be the name of the OS function that
-** failed (e.g. "unlink", "open") and the associated file-system path,
-** if any.
+** This structure holds information passed into individual test
+** threads by the testThreadLockingBehavior() routine.
 */
-#define unixLogError(a,b,c)     unixLogErrorAtLine(a,b,c,__LINE__)
-static int unixLogErrorAtLine(
-  int errcode,                    /* SQLite error code */
-  const char *zFunc,              /* Name of OS function that failed */
-  const char *zPath,              /* File path associated with error */
-  int iLine                       /* Source line number where error occurred */
-){
-  char *zErr;                     /* Message from strerror() or equivalent */
-  int iErrno = errno;             /* Saved syscall error number */
-
-  /* If this is not a threadsafe build (SQLITE_THREADSAFE==0), then use
-  ** the strerror() function to obtain the human-readable error message
-  ** equivalent to errno. Otherwise, use strerror_r().
-  */ 
-#if SQLITE_THREADSAFE && defined(HAVE_STRERROR_R)
-  char aErr[80];
-  memset(aErr, 0, sizeof(aErr));
-  zErr = aErr;
-
-  /* If STRERROR_R_CHAR_P (set by autoconf scripts) or __USE_GNU is defined,
-  ** assume that the system provides the GNU version of strerror_r() that
-  ** returns a pointer to a buffer containing the error message. That pointer 
-  ** may point to aErr[], or it may point to some static storage somewhere. 
-  ** Otherwise, assume that the system provides the POSIX version of 
-  ** strerror_r(), which always writes an error message into aErr[].
-  **
-  ** If the code incorrectly assumes that it is the POSIX version that is
-  ** available, the error message will often be an empty string. Not a
-  ** huge problem. Incorrectly concluding that the GNU version is available 
-  ** could lead to a segfault though.
-  */
-#if defined(STRERROR_R_CHAR_P) || defined(__USE_GNU)
-  zErr = 
-# endif
-  strerror_r(iErrno, aErr, sizeof(aErr)-1);
-
-#elif SQLITE_THREADSAFE
-  /* This is a threadsafe build, but strerror_r() is not available. */
-  zErr = "";
-#else
-  /* Non-threadsafe build, use strerror(). */
-  zErr = strerror(iErrno);
-#endif
-
-  if( zPath==0 ) zPath = "";
-  sqlite3_log(errcode,
-      "os_unix.c:%d: (%d) %s(%s) - %s",
-      iLine, iErrno, zFunc, zPath, zErr
-  );
-
-  return errcode;
-}
+struct threadTestData {
+  int fd;                /* File to be locked */
+  struct flock lock;     /* The locking operation */
+  int result;            /* Result of the locking operation */
+};
 
+#if SQLITE_THREADSAFE && defined(__linux__)
 /*
-** Close a file descriptor.
-**
-** We assume that close() almost always works, since it is only in a
-** very sick application or on a very sick platform that it might fail.
-** If it does fail, simply leak the file descriptor, but do log the
-** error.
+** This function is used as the main routine for a thread launched by
+** testThreadLockingBehavior(). It tests whether the shared-lock obtained
+** by the main thread in testThreadLockingBehavior() conflicts with a
+** hypothetical write-lock obtained by this thread on the same file.
 **
-** Note that it is not safe to retry close() after EINTR since the
-** file descriptor might have already been reused by another thread.
-** So we don't even try to recover from an EINTR.  Just log the error
-** and move on.
-*/
-static void robust_close(unixFile *pFile, int h, int lineno){
-  if( osClose(h) ){
-    unixLogErrorAtLine(SQLITE_IOERR_CLOSE, "close",
-                       pFile ? pFile->zPath : 0, lineno);
-  }
+** The write-lock is not actually acquired, as this is not possible if 
+** the file is open in read-only mode (see ticket #3472).
+*/ 
+static void *threadLockingTest(void *pArg){
+  struct threadTestData *pData = (struct threadTestData*)pArg;
+  pData->result = fcntl(pData->fd, F_GETLK, &pData->lock);
+  return pArg;
 }
+#endif /* SQLITE_THREADSAFE && defined(__linux__) */
 
-/*
-** Set the pFile->lastErrno.  Do this in a subroutine as that provides
-** a convenient place to set a breakpoint.
-*/
-static void storeLastErrno(unixFile *pFile, int error){
-  pFile->lastErrno = error;
-}
 
+#if SQLITE_THREADSAFE && defined(__linux__)
 /*
-** Close all file descriptors accumuated in the unixInodeInfo->pUnused list.
-*/ 
-static void closePendingFds(unixFile *pFile){
-  unixInodeInfo *pInode = pFile->pInode;
-  UnixUnusedFd *p;
-  UnixUnusedFd *pNext;
-  for(p=pInode->pUnused; p; p=pNext){
-    pNext = p->pNext;
-    robust_close(pFile, p->fd, __LINE__);
-    sqlite3_free(p);
-    nUnusedFd--;
-  }
-  pInode->pUnused = 0;
+** This procedure attempts to determine whether or not threads
+** can override each others locks then sets the 
+** threadsOverrideEachOthersLocks variable appropriately.
+*/
+static void testThreadLockingBehavior(int fd_orig){
+  int fd;
+  int rc;
+  struct threadTestData d;
+  struct flock l;
+  pthread_t t;
+
+  fd = dup(fd_orig);
+  if( fd<0 ) return;
+  memset(&l, 0, sizeof(l));
+  l.l_type = F_RDLCK;
+  l.l_len = 1;
+  l.l_start = 0;
+  l.l_whence = SEEK_SET;
+  rc = fcntl(fd_orig, F_SETLK, &l);
+  if( rc!=0 ) return;
+  memset(&d, 0, sizeof(d));
+  d.fd = fd;
+  d.lock = l;
+  d.lock.l_type = F_WRLCK;
+  pthread_create(&t, 0, threadLockingTest, &d);
+  pthread_join(t, 0);
+  close(fd);
+  if( d.result!=0 ) return;
+  threadsOverrideEachOthersLocks = (d.lock.l_type==F_UNLCK);
+}
+#endif /* SQLITE_THERADSAFE && defined(__linux__) */
+
+/*
+** Release a unixLockInfo structure previously allocated by findLockInfo().
+*/
+static void releaseLockInfo(struct unixLockInfo *pLock){
+  if( pLock ){
+    pLock->nRef--;
+    if( pLock->nRef==0 ){
+      if( pLock->pPrev ){
+        assert( pLock->pPrev->pNext==pLock );
+        pLock->pPrev->pNext = pLock->pNext;
+      }else{
+        assert( lockList==pLock );
+        lockList = pLock->pNext;
+      }
+      if( pLock->pNext ){
+        assert( pLock->pNext->pPrev==pLock );
+        pLock->pNext->pPrev = pLock->pPrev;
+      }
+      sqlite3_free(pLock);
+    }
+  }
 }
 
 /*
-** Release a unixInodeInfo structure previously allocated by findInodeInfo().
-**
-** The mutex entered using the unixEnterMutex() function must be held
-** when this function is called.
-*/
-static void releaseInodeInfo(unixFile *pFile){
-  unixInodeInfo *pInode = pFile->pInode;
-  assert( unixMutexHeld() );
-  if( ALWAYS(pInode) ){
-    pInode->nRef--;
-    if( pInode->nRef==0 ){
-      assert( pInode->pShmNode==0 );
-      closePendingFds(pFile);
-      if( pInode->pPrev ){
-        assert( pInode->pPrev->pNext==pInode );
-        pInode->pPrev->pNext = pInode->pNext;
+** Release a unixOpenCnt structure previously allocated by findLockInfo().
+*/
+static void releaseOpenCnt(struct unixOpenCnt *pOpen){
+  if( pOpen ){
+    pOpen->nRef--;
+    if( pOpen->nRef==0 ){
+      if( pOpen->pPrev ){
+        assert( pOpen->pPrev->pNext==pOpen );
+        pOpen->pPrev->pNext = pOpen->pNext;
       }else{
-        assert( inodeList==pInode );
-        inodeList = pInode->pNext;
+        assert( openList==pOpen );
+        openList = pOpen->pNext;
       }
-      if( pInode->pNext ){
-        assert( pInode->pNext->pPrev==pInode );
-        pInode->pNext->pPrev = pInode->pPrev;
+      if( pOpen->pNext ){
+        assert( pOpen->pNext->pPrev==pOpen );
+        pOpen->pNext->pPrev = pOpen->pPrev;
       }
-      sqlite3_free(pInode);
+      sqlite3_free(pOpen->aPending);
+      sqlite3_free(pOpen);
     }
   }
-  assert( inodeList!=0 || nUnusedFd==0 );
 }
 
 /*
-** Given a file descriptor, locate the unixInodeInfo object that
-** describes that file descriptor.  Create a new one if necessary.  The
-** return value might be uninitialized if an error occurs.
-**
-** The mutex entered using the unixEnterMutex() function must be held
-** when this function is called.
+** Given a file descriptor, locate unixLockInfo and unixOpenCnt structures that
+** describes that file descriptor.  Create new ones if necessary.  The
+** return values might be uninitialized if an error occurs.
 **
 ** Return an appropriate error code.
 */
-static int findInodeInfo(
+static int findLockInfo(
   unixFile *pFile,               /* Unix file with file desc used in the key */
-  unixInodeInfo **ppInode        /* Return the unixInodeInfo object here */
+  struct unixLockInfo **ppLock,  /* Return the unixLockInfo structure here */
+  struct unixOpenCnt **ppOpen    /* Return the unixOpenCnt structure here */
 ){
   int rc;                        /* System call return code */
   int fd;                        /* The file descriptor for pFile */
-  struct unixFileId fileId;      /* Lookup key for the unixInodeInfo */
+  struct unixLockKey lockKey;    /* Lookup key for the unixLockInfo structure */
+  struct unixFileId fileId;      /* Lookup key for the unixOpenCnt struct */
   struct stat statbuf;           /* Low-level file information */
-  unixInodeInfo *pInode = 0;     /* Candidate unixInodeInfo object */
-
-  assert( unixMutexHeld() );
+  struct unixLockInfo *pLock;    /* Candidate unixLockInfo object */
+  struct unixOpenCnt *pOpen;     /* Candidate unixOpenCnt object */
 
   /* Get low-level information about the file that we can used to
   ** create a unique name for the file.
   */
   fd = pFile->h;
-  rc = osFstat(fd, &statbuf);
+  rc = fstat(fd, &statbuf);
   if( rc!=0 ){
-    storeLastErrno(pFile, errno);
-#if defined(EOVERFLOW) && defined(SQLITE_DISABLE_LFS)
+    pFile->lastErrno = errno;
+#ifdef EOVERFLOW
     if( pFile->lastErrno==EOVERFLOW ) return SQLITE_NOLFS;
 #endif
     return SQLITE_IOERR;
   }
 
 #ifdef __APPLE__
