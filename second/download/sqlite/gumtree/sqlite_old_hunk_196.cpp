** Only thread A can modify the lock.  Locking behavior is correct
** if the appliation uses the newer Native Posix Thread Library (NPTL)
** on linux - with NPTL a lock created by thread A can override locks
** in thread B.  But there is no way to know at compile-time which
** threading library is being used.  So there is no way to know at
** compile-time whether or not thread A can override locks on thread B.
** We have to do a run-time check to discover the behavior of the
** current process.
**
** On systems where thread A is unable to modify locks created by
** thread B, we have to keep track of which thread created each
** lock.  Hence there is an extra field in the key to the unixLockInfo
** structure to record this information.  And on those systems it
** is illegal to begin a transaction in one thread and finish it
** in another.  For this latter restriction, there is no work-around.
** It is a limitation of LinuxThreads.
*/

/*
** Set or check the unixFile.tid field.  This field is set when an unixFile
** is first opened.  All subsequent uses of the unixFile verify that the
** same thread is operating on the unixFile.  Some operating systems do
** not allow locks to be overridden by other threads and that restriction
** means that sqlite3* database handles cannot be moved from one thread
** to another while locks are held.
**
** Version 3.3.1 (2006-01-15):  unixFile can be moved from one thread to
** another as long as we are running on a system that supports threads
** overriding each others locks (which is now the most common behavior)
** or if no locks are held.  But the unixFile.pLock field needs to be
** recomputed because its key includes the thread-id.  See the 
** transferOwnership() function below for additional information
*/
#if SQLITE_THREADSAFE && defined(__linux__)
# define SET_THREADID(X)   (X)->tid = pthread_self()
# define CHECK_THREADID(X) (threadsOverrideEachOthersLocks==0 && \
                            !pthread_equal((X)->tid, pthread_self()))
#else
# define SET_THREADID(X)
# define CHECK_THREADID(X) 0
#endif

/*
** An instance of the following structure serves as the key used
** to locate a particular unixOpenCnt structure given its inode.  This
** is the same as the unixLockKey except that the thread ID is omitted.
*/
struct unixFileId {
  dev_t dev;                  /* Device number */
#if OS_VXWORKS
  struct vxworksFileId *pId;  /* Unique file ID for vxworks. */
#else
  ino_t ino;                  /* Inode number */
#endif
};

/*
** An instance of the following structure serves as the key used
** to locate a particular unixLockInfo structure given its inode.
**
** If threads cannot override each others locks (LinuxThreads), then we
** set the unixLockKey.tid field to the thread ID.  If threads can override
** each others locks (Posix and NPTL) then tid is always set to zero.
** tid is omitted if we compile without threading support or on an OS
** other than linux.
*/
struct unixLockKey {
  struct unixFileId fid;  /* Unique identifier for the file */
#if SQLITE_THREADSAFE && defined(__linux__)
  pthread_t tid;  /* Thread ID of lock owner. Zero if not using LinuxThreads */
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
struct unixLockInfo {
  struct unixLockKey lockKey;     /* The lookup key */
  int cnt;                        /* Number of SHARED locks held */
  int locktype;                   /* One of SHARED_LOCK, RESERVED_LOCK etc. */
  int nRef;                       /* Number of pointers to this structure */
  struct unixLockInfo *pNext;     /* List of all unixLockInfo objects */
  struct unixLockInfo *pPrev;     /*    .... doubly linked */
};

/*
** An instance of the following structure is allocated for each open
** inode.  This structure keeps track of the number of locks on that
** inode.  If a close is attempted against an inode that is holding
** locks, the close is deferred until all locks clear by adding the
** file descriptor to be closed to the pending list.
**
** TODO:  Consider changing this so that there is only a single file
** descriptor for each open file, even when it is opened multiple times.
** The close() system call would only occur when the last database
** using the file closes.
*/
struct unixOpenCnt {
  struct unixFileId fileId;   /* The lookup key */
  int nRef;                   /* Number of pointers to this structure */
  int nLock;                  /* Number of outstanding locks */
  int nPending;               /* Number of pending close() operations */
  int *aPending;            /* Malloced space holding fd's awaiting a close() */
#if OS_VXWORKS
  sem_t *pSem;                     /* Named POSIX semaphore */
  char aSemName[MAX_PATHNAME+1];   /* Name of that semaphore */
#endif
  struct unixOpenCnt *pNext, *pPrev;   /* List of all unixOpenCnt objects */
};

/*
** Lists of all unixLockInfo and unixOpenCnt objects.  These used to be hash
** tables.  But the number of objects is rarely more than a dozen and
** never exceeds a few thousand.  And lookup is not on a critical
** path so a simple linked list will suffice.
*/
static struct unixLockInfo *lockList = 0;
static struct unixOpenCnt *openList = 0;

/*
** This variable remembers whether or not threads can override each others
** locks.
**
**    0:  No.  Threads cannot override each others locks.  (LinuxThreads)
**    1:  Yes.  Threads can override each others locks.  (Posix & NLPT)
**   -1:  We don't know yet.
**
** On some systems, we know at compile-time if threads can override each
** others locks.  On those systems, the SQLITE_THREAD_OVERRIDE_LOCK macro
** will be set appropriately.  On other systems, we have to check at
** runtime.  On these latter systems, SQLTIE_THREAD_OVERRIDE_LOCK is
** undefined.
**
** This variable normally has file scope only.  But during testing, we make
** it a global so that the test code can change its value in order to verify
** that the right stuff happens in either case.
*/
#if SQLITE_THREADSAFE && defined(__linux__)
#  ifndef SQLITE_THREAD_OVERRIDE_LOCK
#    define SQLITE_THREAD_OVERRIDE_LOCK -1
#  endif
#  ifdef SQLITE_TEST
int threadsOverrideEachOthersLocks = SQLITE_THREAD_OVERRIDE_LOCK;
#  else
static int threadsOverrideEachOthersLocks = SQLITE_THREAD_OVERRIDE_LOCK;
#  endif
#endif

/*
** This structure holds information passed into individual test
** threads by the testThreadLockingBehavior() routine.
*/
struct threadTestData {
  int fd;                /* File to be locked */
  struct flock lock;     /* The locking operation */
  int result;            /* Result of the locking operation */
};

#if SQLITE_THREADSAFE && defined(__linux__)
/*
** This function is used as the main routine for a thread launched by
** testThreadLockingBehavior(). It tests whether the shared-lock obtained
** by the main thread in testThreadLockingBehavior() conflicts with a
** hypothetical write-lock obtained by this thread on the same file.
**
** The write-lock is not actually acquired, as this is not possible if 
** the file is open in read-only mode (see ticket #3472).
*/ 
static void *threadLockingTest(void *pArg){
  struct threadTestData *pData = (struct threadTestData*)pArg;
  pData->result = fcntl(pData->fd, F_GETLK, &pData->lock);
  return pArg;
}
#endif /* SQLITE_THREADSAFE && defined(__linux__) */


#if SQLITE_THREADSAFE && defined(__linux__)
/*
** This procedure attempts to determine whether or not threads
** can override each others locks then sets the 
** threadsOverrideEachOthersLocks variable appropriately.
*/
static void testThreadLockingBehavior(int fd_orig){
  int fd;
  int rc;
  struct threadTestData d;
  struct flock l;
  pthread_t t;

  fd = dup(fd_orig);
  if( fd<0 ) return;
  memset(&l, 0, sizeof(l));
  l.l_type = F_RDLCK;
  l.l_len = 1;
  l.l_start = 0;
  l.l_whence = SEEK_SET;
  rc = fcntl(fd_orig, F_SETLK, &l);
  if( rc!=0 ) return;
  memset(&d, 0, sizeof(d));
  d.fd = fd;
  d.lock = l;
  d.lock.l_type = F_WRLCK;
  pthread_create(&t, 0, threadLockingTest, &d);
  pthread_join(t, 0);
  close(fd);
  if( d.result!=0 ) return;
  threadsOverrideEachOthersLocks = (d.lock.l_type==F_UNLCK);
}
#endif /* SQLITE_THERADSAFE && defined(__linux__) */

/*
** Release a unixLockInfo structure previously allocated by findLockInfo().
*/
static void releaseLockInfo(struct unixLockInfo *pLock){
  if( pLock ){
    pLock->nRef--;
    if( pLock->nRef==0 ){
      if( pLock->pPrev ){
        assert( pLock->pPrev->pNext==pLock );
        pLock->pPrev->pNext = pLock->pNext;
      }else{
        assert( lockList==pLock );
        lockList = pLock->pNext;
      }
      if( pLock->pNext ){
        assert( pLock->pNext->pPrev==pLock );
        pLock->pNext->pPrev = pLock->pPrev;
      }
      sqlite3_free(pLock);
    }
  }
}

/*
** Release a unixOpenCnt structure previously allocated by findLockInfo().
*/
static void releaseOpenCnt(struct unixOpenCnt *pOpen){
  if( pOpen ){
    pOpen->nRef--;
    if( pOpen->nRef==0 ){
      if( pOpen->pPrev ){
        assert( pOpen->pPrev->pNext==pOpen );
        pOpen->pPrev->pNext = pOpen->pNext;
      }else{
        assert( openList==pOpen );
        openList = pOpen->pNext;
      }
      if( pOpen->pNext ){
        assert( pOpen->pNext->pPrev==pOpen );
        pOpen->pNext->pPrev = pOpen->pPrev;
      }
      sqlite3_free(pOpen->aPending);
      sqlite3_free(pOpen);
    }
  }
}

/*
** Given a file descriptor, locate unixLockInfo and unixOpenCnt structures that
** describes that file descriptor.  Create new ones if necessary.  The
** return values might be uninitialized if an error occurs.
**
** Return an appropriate error code.
*/
static int findLockInfo(
  unixFile *pFile,               /* Unix file with file desc used in the key */
  struct unixLockInfo **ppLock,  /* Return the unixLockInfo structure here */
  struct unixOpenCnt **ppOpen    /* Return the unixOpenCnt structure here */
){
  int rc;                        /* System call return code */
  int fd;                        /* The file descriptor for pFile */
  struct unixLockKey lockKey;    /* Lookup key for the unixLockInfo structure */
  struct unixFileId fileId;      /* Lookup key for the unixOpenCnt struct */
  struct stat statbuf;           /* Low-level file information */
  struct unixLockInfo *pLock;    /* Candidate unixLockInfo object */
  struct unixOpenCnt *pOpen;     /* Candidate unixOpenCnt object */

  /* Get low-level information about the file that we can used to
  ** create a unique name for the file.
  */
  fd = pFile->h;
  rc = fstat(fd, &statbuf);
  if( rc!=0 ){
    pFile->lastErrno = errno;
#ifdef EOVERFLOW
    if( pFile->lastErrno==EOVERFLOW ) return SQLITE_NOLFS;
#endif
    return SQLITE_IOERR;
  }

#ifdef __APPLE__
