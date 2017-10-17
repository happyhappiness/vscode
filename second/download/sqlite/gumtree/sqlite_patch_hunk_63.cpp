   ** prior to accessing the inode number.  The one byte written is
   ** an ASCII 'S' character which also happens to be the first byte
   ** in the header of every SQLite database.  In this way, if there
   ** is a race condition such that another thread has already populated
   ** the first page of the database, no damage is done.
   */
-  if( statbuf.st_size==0 && (pFile->fsFlags & SQLITE_FSFLAGS_IS_MSDOS)!=0 ){
-    do{ rc = osWrite(fd, "S", 1); }while( rc<0 && errno==EINTR );
+  if( statbuf.st_size==0 ){
+    rc = write(fd, "S", 1);
     if( rc!=1 ){
-      storeLastErrno(pFile, errno);
       return SQLITE_IOERR;
     }
-    rc = osFstat(fd, &statbuf);
+    rc = fstat(fd, &statbuf);
     if( rc!=0 ){
-      storeLastErrno(pFile, errno);
+      pFile->lastErrno = errno;
       return SQLITE_IOERR;
     }
   }
 #endif
 
-  memset(&fileId, 0, sizeof(fileId));
-  fileId.dev = statbuf.st_dev;
+  memset(&lockKey, 0, sizeof(lockKey));
+  lockKey.fid.dev = statbuf.st_dev;
 #if OS_VXWORKS
-  fileId.pId = pFile->pId;
+  lockKey.fid.pId = pFile->pId;
 #else
-  fileId.ino = (u64)statbuf.st_ino;
+  lockKey.fid.ino = statbuf.st_ino;
 #endif
-  assert( inodeList!=0 || nUnusedFd==0 );
-  pInode = inodeList;
-  while( pInode && memcmp(&fileId, &pInode->fileId, sizeof(fileId)) ){
-    pInode = pInode->pNext;
-  }
-  if( pInode==0 ){
-    pInode = sqlite3_malloc64( sizeof(*pInode) );
-    if( pInode==0 ){
-      return SQLITE_NOMEM_BKPT;
-    }
-    memset(pInode, 0, sizeof(*pInode));
-    memcpy(&pInode->fileId, &fileId, sizeof(fileId));
-    pInode->nRef = 1;
-    pInode->pNext = inodeList;
-    pInode->pPrev = 0;
-    if( inodeList ) inodeList->pPrev = pInode;
-    inodeList = pInode;
-  }else{
-    pInode->nRef++;
+#if SQLITE_THREADSAFE && defined(__linux__)
+  if( threadsOverrideEachOthersLocks<0 ){
+    testThreadLockingBehavior(fd);
+  }
+  lockKey.tid = threadsOverrideEachOthersLocks ? 0 : pthread_self();
+#endif
+  fileId = lockKey.fid;
+  if( ppLock!=0 ){
+    pLock = lockList;
+    while( pLock && memcmp(&lockKey, &pLock->lockKey, sizeof(lockKey)) ){
+      pLock = pLock->pNext;
+    }
+    if( pLock==0 ){
+      pLock = sqlite3_malloc( sizeof(*pLock) );
+      if( pLock==0 ){
+        rc = SQLITE_NOMEM;
+        goto exit_findlockinfo;
+      }
+      pLock->lockKey = lockKey;
+      pLock->nRef = 1;
+      pLock->cnt = 0;
+      pLock->locktype = 0;
+      pLock->pNext = lockList;
+      pLock->pPrev = 0;
+      if( lockList ) lockList->pPrev = pLock;
+      lockList = pLock;
+    }else{
+      pLock->nRef++;
+    }
+    *ppLock = pLock;
   }
-  *ppInode = pInode;
-  return SQLITE_OK;
-}
-
-/*
-** Return TRUE if pFile has been renamed or unlinked since it was first opened.
-*/
-static int fileHasMoved(unixFile *pFile){
+  if( ppOpen!=0 ){
+    pOpen = openList;
+    while( pOpen && memcmp(&fileId, &pOpen->fileId, sizeof(fileId)) ){
+      pOpen = pOpen->pNext;
+    }
+    if( pOpen==0 ){
+      pOpen = sqlite3_malloc( sizeof(*pOpen) );
+      if( pOpen==0 ){
+        releaseLockInfo(pLock);
+        rc = SQLITE_NOMEM;
+        goto exit_findlockinfo;
+      }
+      pOpen->fileId = fileId;
+      pOpen->nRef = 1;
+      pOpen->nLock = 0;
+      pOpen->nPending = 0;
+      pOpen->aPending = 0;
+      pOpen->pNext = openList;
+      pOpen->pPrev = 0;
+      if( openList ) openList->pPrev = pOpen;
+      openList = pOpen;
 #if OS_VXWORKS
-  return pFile->pInode!=0 && pFile->pId!=pFile->pInode->fileId.pId;
-#else
-  struct stat buf;
-  return pFile->pInode!=0 &&
-      (osStat(pFile->zPath, &buf)!=0 
-         || (u64)buf.st_ino!=pFile->pInode->fileId.ino);
+      pOpen->pSem = NULL;
+      pOpen->aSemName[0] = '\0';
 #endif
-}
+    }else{
+      pOpen->nRef++;
+    }
+    *ppOpen = pOpen;
+  }
 
+exit_findlockinfo:
+  return rc;
+}
 
 /*
-** Check a unixFile that is a database.  Verify the following:
+** If we are currently in a different thread than the thread that the
+** unixFile argument belongs to, then transfer ownership of the unixFile
+** over to the current thread.
 **
-** (1) There is exactly one hard link on the file
-** (2) The file is not a symbolic link
-** (3) The file has not been renamed or unlinked
+** A unixFile is only owned by a thread on systems that use LinuxThreads.
 **
-** Issue sqlite3_log(SQLITE_WARNING,...) messages if anything is not right.
+** Ownership transfer is only allowed if the unixFile is currently unlocked.
+** If the unixFile is locked and an ownership is wrong, then return
+** SQLITE_MISUSE.  SQLITE_OK is returned if everything works.
 */
-static void verifyDbFile(unixFile *pFile){
-  struct stat buf;
+#if SQLITE_THREADSAFE && defined(__linux__)
+static int transferOwnership(unixFile *pFile){
   int rc;
-
-  /* These verifications occurs for the main database only */
-  if( pFile->ctrlFlags & UNIXFILE_NOLOCK ) return;
-
-  rc = osFstat(pFile->h, &buf);
-  if( rc!=0 ){
-    sqlite3_log(SQLITE_WARNING, "cannot fstat db file %s", pFile->zPath);
-    return;
+  pthread_t hSelf;
+  if( threadsOverrideEachOthersLocks ){
+    /* Ownership transfers not needed on this system */
+    return SQLITE_OK;
+  }
+  hSelf = pthread_self();
+  if( pthread_equal(pFile->tid, hSelf) ){
+    /* We are still in the same thread */
+    OSTRACE1("No-transfer, same thread\n");
+    return SQLITE_OK;
   }
-  if( buf.st_nlink==0 ){
-    sqlite3_log(SQLITE_WARNING, "file unlinked while open: %s", pFile->zPath);
-    return;
-  }
-  if( buf.st_nlink>1 ){
-    sqlite3_log(SQLITE_WARNING, "multiple links to file: %s", pFile->zPath);
-    return;
-  }
-  if( fileHasMoved(pFile) ){
-    sqlite3_log(SQLITE_WARNING, "file renamed while open: %s", pFile->zPath);
-    return;
+  if( pFile->locktype!=NO_LOCK ){
+    /* We cannot change ownership while we are holding a lock! */
+    return SQLITE_MISUSE;
+  }
+  OSTRACE4("Transfer ownership of %d from %d to %d\n",
+            pFile->h, pFile->tid, hSelf);
+  pFile->tid = hSelf;
+  if (pFile->pLock != NULL) {
+    releaseLockInfo(pFile->pLock);
+    rc = findLockInfo(pFile, &pFile->pLock, 0);
+    OSTRACE5("LOCK    %d is now %s(%s,%d)\n", pFile->h,
+           locktypeName(pFile->locktype),
+           locktypeName(pFile->pLock->locktype), pFile->pLock->cnt);
+    return rc;
+  } else {
+    return SQLITE_OK;
   }
 }
+#else  /* if not SQLITE_THREADSAFE */
+  /* On single-threaded builds, ownership transfer is a no-op */
+# define transferOwnership(X) SQLITE_OK
+#endif /* SQLITE_THREADSAFE */
 
 
 /*
 ** This routine checks if there is a RESERVED lock held on the specified
 ** file by this or any other process. If such a lock is held, set *pResOut
 ** to a non-zero value otherwise *pResOut is set to zero.  The return value
