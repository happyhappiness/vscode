   */
   assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
   assert(isCreate==0 || isReadWrite);
   assert(isExclusive==0 || isCreate);
   assert(isDelete==0 || isCreate);
 
-  /* The main DB, main journal, WAL file and master journal are never 
-  ** automatically deleted. Nor are they ever temporary files.  */
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_DB );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_JOURNAL );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MASTER_JOURNAL );
-  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_WAL );
+  /* The main DB, main journal, and master journal are never automatically
+  ** deleted
+  */
+  assert( eType!=SQLITE_OPEN_MAIN_DB || !isDelete );
+  assert( eType!=SQLITE_OPEN_MAIN_JOURNAL || !isDelete );
+  assert( eType!=SQLITE_OPEN_MASTER_JOURNAL || !isDelete );
 
   /* Assert that the upper layer has set one of the "file-type" flags. */
   assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB 
        || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL 
        || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL 
-       || eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL
+       || eType==SQLITE_OPEN_TRANSIENT_DB
   );
 
-  /* Detect a pid change and reset the PRNG.  There is a race condition
-  ** here such that two or more threads all trying to open databases at
-  ** the same instant might all reset the PRNG.  But multiple resets
-  ** are harmless.
-  */
-  if( randomnessPid!=osGetpid(0) ){
-    randomnessPid = osGetpid(0);
-    sqlite3_randomness(0,0);
-  }
-
-  memset(p, 0, sizeof(unixFile));
-
-  if( eType==SQLITE_OPEN_MAIN_DB ){
-    UnixUnusedFd *pUnused;
-    pUnused = findReusableFd(zName, flags);
-    if( pUnused ){
-      fd = pUnused->fd;
-    }else{
-      pUnused = sqlite3_malloc64(sizeof(*pUnused));
-      if( !pUnused ){
-        return SQLITE_NOMEM_BKPT;
-      }
-    }
-    p->pPreallocatedUnused = pUnused;
-
-    /* Database filenames are double-zero terminated if they are not
-    ** URIs with parameters.  Hence, they can always be passed into
-    ** sqlite3_uri_parameter(). */
-    assert( (flags & SQLITE_OPEN_URI) || zName[strlen(zName)+1]==0 );
-
-  }else if( !zName ){
-    /* If zName is NULL, the upper layer is requesting a temp file. */
-    assert(isDelete && !syncDir);
-    rc = unixGetTempname(pVfs->mxPathname, zTmpname);
+  memset(pFile, 0, sizeof(unixFile));
+
+  if( !zName ){
+    assert(isDelete && !isOpenDirectory);
+    rc = getTempname(MAX_PATHNAME+1, zTmpname);
     if( rc!=SQLITE_OK ){
       return rc;
     }
     zName = zTmpname;
-
-    /* Generated temporary filenames are always double-zero terminated
-    ** for use by sqlite3_uri_parameter(). */
-    assert( zName[strlen(zName)+1]==0 );
   }
 
-  /* Determine the value of the flags parameter passed to POSIX function
-  ** open(). These must be calculated even if open() is not called, as
-  ** they may be stored as part of the file handle and used by the 
-  ** 'conch file' locking functions later on.  */
   if( isReadonly )  openFlags |= O_RDONLY;
   if( isReadWrite ) openFlags |= O_RDWR;
   if( isCreate )    openFlags |= O_CREAT;
   if( isExclusive ) openFlags |= (O_EXCL|O_NOFOLLOW);
   openFlags |= (O_LARGEFILE|O_BINARY);
 
-  if( fd<0 ){
-    mode_t openMode;              /* Permissions to create file with */
-    uid_t uid;                    /* Userid for the file */
-    gid_t gid;                    /* Groupid for the file */
-    rc = findCreateFileMode(zName, flags, &openMode, &uid, &gid);
-    if( rc!=SQLITE_OK ){
-      assert( !p->pPreallocatedUnused );
-      assert( eType==SQLITE_OPEN_WAL || eType==SQLITE_OPEN_MAIN_JOURNAL );
-      return rc;
-    }
-    fd = robust_open(zName, openFlags, openMode);
-    OSTRACE(("OPENX   %-3d %s 0%o\n", fd, zName, openFlags));
-    assert( !isExclusive || (openFlags & O_CREAT)!=0 );
-    if( fd<0 && errno!=EISDIR && isReadWrite ){
-      /* Failed to open the file for read/write access. Try read-only. */
-      flags &= ~(SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
-      openFlags &= ~(O_RDWR|O_CREAT);
-      flags |= SQLITE_OPEN_READONLY;
-      openFlags |= O_RDONLY;
-      isReadonly = 1;
-      fd = robust_open(zName, openFlags, openMode);
-    }
-    if( fd<0 ){
-      rc = unixLogError(SQLITE_CANTOPEN_BKPT, "open", zName);
-      goto open_finished;
-    }
-
-    /* If this process is running as root and if creating a new rollback
-    ** journal or WAL file, set the ownership of the journal or WAL to be
-    ** the same as the original database.
-    */
-    if( flags & (SQLITE_OPEN_WAL|SQLITE_OPEN_MAIN_JOURNAL) ){
-      robustFchown(fd, uid, gid);
-    }
-  }
-  assert( fd>=0 );
-  if( pOutFlags ){
-    *pOutFlags = flags;
+  fd = open(zName, openFlags, isDelete?0600:SQLITE_DEFAULT_FILE_PERMISSIONS);
+  OSTRACE4("OPENX   %-3d %s 0%o\n", fd, zName, openFlags);
+  if( fd<0 && errno!=EISDIR && isReadWrite && !isExclusive ){
+    /* Failed to open the file for read/write access. Try read-only. */
+    flags &= ~(SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
+    flags |= SQLITE_OPEN_READONLY;
+    return unixOpen(pVfs, zPath, pFile, flags, pOutFlags);
   }
-
-  if( p->pPreallocatedUnused ){
-    p->pPreallocatedUnused->fd = fd;
-    p->pPreallocatedUnused->flags = flags;
+  if( fd<0 ){
+    return SQLITE_CANTOPEN;
   }
-
   if( isDelete ){
 #if OS_VXWORKS
     zPath = zName;
-#elif defined(SQLITE_UNLINK_AFTER_CLOSE)
-    zPath = sqlite3_mprintf("%s", zName);
-    if( zPath==0 ){
-      robust_close(p, fd, __LINE__);
-      return SQLITE_NOMEM_BKPT;
-    }
 #else
-    osUnlink(zName);
+    unlink(zName);
 #endif
   }
 #if SQLITE_ENABLE_LOCKING_STYLE
   else{
-    p->openFlags = openFlags;
+    ((unixFile*)pFile)->openFlags = openFlags;
   }
 #endif
-  
-#if defined(__APPLE__) || SQLITE_ENABLE_LOCKING_STYLE
-  if( fstatfs(fd, &fsInfo) == -1 ){
-    storeLastErrno(p, errno);
-    robust_close(p, fd, __LINE__);
-    return SQLITE_IOERR_ACCESS;
+  if( pOutFlags ){
+    *pOutFlags = flags;
   }
-  if (0 == strncmp("msdos", fsInfo.f_fstypename, 5)) {
-    ((unixFile*)pFile)->fsFlags |= SQLITE_FSFLAGS_IS_MSDOS;
+
+#ifndef NDEBUG
+  if( (flags & SQLITE_OPEN_MAIN_DB)!=0 ){
+    ((unixFile*)pFile)->isLockable = 1;
   }
-  if (0 == strncmp("exfat", fsInfo.f_fstypename, 5)) {
-    ((unixFile*)pFile)->fsFlags |= SQLITE_FSFLAGS_IS_MSDOS;
+#endif
+
+  assert( fd>=0 );
+  if( isOpenDirectory ){
+    rc = openDirectory(zPath, &dirfd);
+    if( rc!=SQLITE_OK ){
+      close(fd); /* silently leak if fail, already in error */
+      return rc;
+    }
   }
+
+#ifdef FD_CLOEXEC
+  fcntl(fd, F_SETFD, fcntl(fd, F_GETFD, 0) | FD_CLOEXEC);
 #endif
 
-  /* Set up appropriate ctrlFlags */
-  if( isDelete )                ctrlFlags |= UNIXFILE_DELETE;
-  if( isReadonly )              ctrlFlags |= UNIXFILE_RDONLY;
   noLock = eType!=SQLITE_OPEN_MAIN_DB;
-  if( noLock )                  ctrlFlags |= UNIXFILE_NOLOCK;
-  if( syncDir )                 ctrlFlags |= UNIXFILE_DIRSYNC;
-  if( flags & SQLITE_OPEN_URI ) ctrlFlags |= UNIXFILE_URI;
 
-#if SQLITE_ENABLE_LOCKING_STYLE
 #if SQLITE_PREFER_PROXY_LOCKING
-  isAutoProxy = 1;
-#endif
-  if( isAutoProxy && (zPath!=NULL) && (!noLock) && pVfs->xOpen ){
+  if( zPath!=NULL && !noLock ){
     char *envforce = getenv("SQLITE_FORCE_PROXY_LOCKING");
     int useProxy = 0;
 
-    /* SQLITE_FORCE_PROXY_LOCKING==1 means force always use proxy, 0 means 
-    ** never use proxy, NULL means use proxy for non-local files only.  */
+    /* SQLITE_FORCE_PROXY_LOCKING==1 means force always use proxy, 
+    ** 0 means never use proxy, NULL means use proxy for non-local files only
+    */
     if( envforce!=NULL ){
       useProxy = atoi(envforce)>0;
     }else{
+      struct statfs fsInfo;
+
+      if( statfs(zPath, &fsInfo) == -1 ){
+				((unixFile*)pFile)->lastErrno = errno;
+        if( dirfd>=0 ) close(dirfd); /* silently leak if fail, in error */
+        close(fd); /* silently leak if fail, in error */
+        return SQLITE_IOERR_ACCESS;
+      }
       useProxy = !(fsInfo.f_flags&MNT_LOCAL);
     }
     if( useProxy ){
-      rc = fillInUnixFile(pVfs, fd, pFile, zPath, ctrlFlags);
+      rc = fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock, isDelete);
       if( rc==SQLITE_OK ){
         rc = proxyTransformUnixFile((unixFile*)pFile, ":auto:");
-        if( rc!=SQLITE_OK ){
-          /* Use unixClose to clean up the resources added in fillInUnixFile 
-          ** and clear all the structure's references.  Specifically, 
-          ** pFile->pMethods will be NULL so sqlite3OsClose will be a no-op 
-          */
-          unixClose(pFile);
-          return rc;
-        }
       }
-      goto open_finished;
+      return rc;
     }
   }
 #endif
   
-  assert( zPath==0 || zPath[0]=='/' 
-      || eType==SQLITE_OPEN_MASTER_JOURNAL || eType==SQLITE_OPEN_MAIN_JOURNAL 
-  );
-  rc = fillInUnixFile(pVfs, fd, pFile, zPath, ctrlFlags);
-
-open_finished:
-  if( rc!=SQLITE_OK ){
-    sqlite3_free(p->pPreallocatedUnused);
-  }
-  return rc;
+  return fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock, isDelete);
 }
 
-
 /*
 ** Delete the file at zPath. If the dirSync argument is true, fsync()
 ** the directory after deleting the file.
 */
 static int unixDelete(
   sqlite3_vfs *NotUsed,     /* VFS containing this as the xDelete method */
