  ** prior to accessing the inode number.  The one byte written is
  ** an ASCII 'S' character which also happens to be the first byte
  ** in the header of every SQLite database.  In this way, if there
  ** is a race condition such that another thread has already populated
  ** the first page of the database, no damage is done.
  */
  if( statbuf.st_size==0 ){
    rc = write(fd, "S", 1);
    if( rc!=1 ){
      return SQLITE_IOERR;
    }
    rc = fstat(fd, &statbuf);
    if( rc!=0 ){
      pFile->lastErrno = errno;
      return SQLITE_IOERR;
    }
  }
#endif

  memset(&lockKey, 0, sizeof(lockKey));
  lockKey.fid.dev = statbuf.st_dev;
#if OS_VXWORKS
  lockKey.fid.pId = pFile->pId;
#else
  lockKey.fid.ino = statbuf.st_ino;
#endif
#if SQLITE_THREADSAFE && defined(__linux__)
  if( threadsOverrideEachOthersLocks<0 ){
    testThreadLockingBehavior(fd);
  }
  lockKey.tid = threadsOverrideEachOthersLocks ? 0 : pthread_self();
#endif
  fileId = lockKey.fid;
  if( ppLock!=0 ){
    pLock = lockList;
    while( pLock && memcmp(&lockKey, &pLock->lockKey, sizeof(lockKey)) ){
      pLock = pLock->pNext;
    }
    if( pLock==0 ){
      pLock = sqlite3_malloc( sizeof(*pLock) );
      if( pLock==0 ){
        rc = SQLITE_NOMEM;
        goto exit_findlockinfo;
      }
      pLock->lockKey = lockKey;
      pLock->nRef = 1;
      pLock->cnt = 0;
      pLock->locktype = 0;
      pLock->pNext = lockList;
      pLock->pPrev = 0;
      if( lockList ) lockList->pPrev = pLock;
      lockList = pLock;
    }else{
      pLock->nRef++;
    }
    *ppLock = pLock;
  }
  if( ppOpen!=0 ){
    pOpen = openList;
    while( pOpen && memcmp(&fileId, &pOpen->fileId, sizeof(fileId)) ){
      pOpen = pOpen->pNext;
    }
    if( pOpen==0 ){
      pOpen = sqlite3_malloc( sizeof(*pOpen) );
      if( pOpen==0 ){
        releaseLockInfo(pLock);
        rc = SQLITE_NOMEM;
        goto exit_findlockinfo;
      }
      pOpen->fileId = fileId;
      pOpen->nRef = 1;
      pOpen->nLock = 0;
      pOpen->nPending = 0;
      pOpen->aPending = 0;
      pOpen->pNext = openList;
      pOpen->pPrev = 0;
      if( openList ) openList->pPrev = pOpen;
      openList = pOpen;
#if OS_VXWORKS
      pOpen->pSem = NULL;
      pOpen->aSemName[0] = '\0';
#endif
    }else{
      pOpen->nRef++;
    }
    *ppOpen = pOpen;
  }

exit_findlockinfo:
  return rc;
}

/*
** If we are currently in a different thread than the thread that the
** unixFile argument belongs to, then transfer ownership of the unixFile
** over to the current thread.
**
** A unixFile is only owned by a thread on systems that use LinuxThreads.
**
** Ownership transfer is only allowed if the unixFile is currently unlocked.
** If the unixFile is locked and an ownership is wrong, then return
** SQLITE_MISUSE.  SQLITE_OK is returned if everything works.
*/
#if SQLITE_THREADSAFE && defined(__linux__)
static int transferOwnership(unixFile *pFile){
  int rc;
  pthread_t hSelf;
  if( threadsOverrideEachOthersLocks ){
    /* Ownership transfers not needed on this system */
    return SQLITE_OK;
  }
  hSelf = pthread_self();
  if( pthread_equal(pFile->tid, hSelf) ){
    /* We are still in the same thread */
    OSTRACE1("No-transfer, same thread\n");
    return SQLITE_OK;
  }
  if( pFile->locktype!=NO_LOCK ){
    /* We cannot change ownership while we are holding a lock! */
    return SQLITE_MISUSE;
  }
  OSTRACE4("Transfer ownership of %d from %d to %d\n",
            pFile->h, pFile->tid, hSelf);
  pFile->tid = hSelf;
  if (pFile->pLock != NULL) {
    releaseLockInfo(pFile->pLock);
    rc = findLockInfo(pFile, &pFile->pLock, 0);
    OSTRACE5("LOCK    %d is now %s(%s,%d)\n", pFile->h,
           locktypeName(pFile->locktype),
           locktypeName(pFile->pLock->locktype), pFile->pLock->cnt);
    return rc;
  } else {
    return SQLITE_OK;
  }
}
#else  /* if not SQLITE_THREADSAFE */
  /* On single-threaded builds, ownership transfer is a no-op */
# define transferOwnership(X) SQLITE_OK
#endif /* SQLITE_THREADSAFE */


/*
** This routine checks if there is a RESERVED lock held on the specified
** file by this or any other process. If such a lock is held, set *pResOut
** to a non-zero value otherwise *pResOut is set to zero.  The return value
