  */
  assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
  assert(isCreate==0 || isReadWrite);
  assert(isExclusive==0 || isCreate);
  assert(isDelete==0 || isCreate);

  /* The main DB, main journal, and master journal are never automatically
  ** deleted
  */
  assert( eType!=SQLITE_OPEN_MAIN_DB || !isDelete );
  assert( eType!=SQLITE_OPEN_MAIN_JOURNAL || !isDelete );
  assert( eType!=SQLITE_OPEN_MASTER_JOURNAL || !isDelete );

  /* Assert that the upper layer has set one of the "file-type" flags. */
  assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB 
       || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL 
       || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL 
       || eType==SQLITE_OPEN_TRANSIENT_DB
  );

  memset(pFile, 0, sizeof(unixFile));

  if( !zName ){
    assert(isDelete && !isOpenDirectory);
    rc = getTempname(MAX_PATHNAME+1, zTmpname);
    if( rc!=SQLITE_OK ){
      return rc;
    }
    zName = zTmpname;
  }

  if( isReadonly )  openFlags |= O_RDONLY;
  if( isReadWrite ) openFlags |= O_RDWR;
  if( isCreate )    openFlags |= O_CREAT;
  if( isExclusive ) openFlags |= (O_EXCL|O_NOFOLLOW);
  openFlags |= (O_LARGEFILE|O_BINARY);

  fd = open(zName, openFlags, isDelete?0600:SQLITE_DEFAULT_FILE_PERMISSIONS);
  OSTRACE4("OPENX   %-3d %s 0%o\n", fd, zName, openFlags);
  if( fd<0 && errno!=EISDIR && isReadWrite && !isExclusive ){
    /* Failed to open the file for read/write access. Try read-only. */
    flags &= ~(SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
    flags |= SQLITE_OPEN_READONLY;
    return unixOpen(pVfs, zPath, pFile, flags, pOutFlags);
  }
  if( fd<0 ){
    return SQLITE_CANTOPEN;
  }
  if( isDelete ){
#if OS_VXWORKS
    zPath = zName;
#else
    unlink(zName);
#endif
  }
#if SQLITE_ENABLE_LOCKING_STYLE
  else{
    ((unixFile*)pFile)->openFlags = openFlags;
  }
#endif
  if( pOutFlags ){
    *pOutFlags = flags;
  }

#ifndef NDEBUG
  if( (flags & SQLITE_OPEN_MAIN_DB)!=0 ){
    ((unixFile*)pFile)->isLockable = 1;
  }
#endif

  assert( fd>=0 );
  if( isOpenDirectory ){
    rc = openDirectory(zPath, &dirfd);
    if( rc!=SQLITE_OK ){
      close(fd); /* silently leak if fail, already in error */
      return rc;
    }
  }

#ifdef FD_CLOEXEC
  fcntl(fd, F_SETFD, fcntl(fd, F_GETFD, 0) | FD_CLOEXEC);
#endif

  noLock = eType!=SQLITE_OPEN_MAIN_DB;

#if SQLITE_PREFER_PROXY_LOCKING
  if( zPath!=NULL && !noLock ){
    char *envforce = getenv("SQLITE_FORCE_PROXY_LOCKING");
    int useProxy = 0;

    /* SQLITE_FORCE_PROXY_LOCKING==1 means force always use proxy, 
    ** 0 means never use proxy, NULL means use proxy for non-local files only
    */
    if( envforce!=NULL ){
      useProxy = atoi(envforce)>0;
    }else{
      struct statfs fsInfo;

      if( statfs(zPath, &fsInfo) == -1 ){
				((unixFile*)pFile)->lastErrno = errno;
        if( dirfd>=0 ) close(dirfd); /* silently leak if fail, in error */
        close(fd); /* silently leak if fail, in error */
        return SQLITE_IOERR_ACCESS;
      }
      useProxy = !(fsInfo.f_flags&MNT_LOCAL);
    }
    if( useProxy ){
      rc = fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock, isDelete);
      if( rc==SQLITE_OK ){
        rc = proxyTransformUnixFile((unixFile*)pFile, ":auto:");
      }
      return rc;
    }
  }
#endif
  
  return fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock, isDelete);
}

/*
** Delete the file at zPath. If the dirSync argument is true, fsync()
** the directory after deleting the file.
*/
static int unixDelete(
  sqlite3_vfs *NotUsed,     /* VFS containing this as the xDelete method */
