  /* Unix cannot, but some systems may return SQLITE_FULL from here. This
  ** line is to test that doing so does not cause any problems.
  */
  SimulateDiskfullError( return SQLITE_FULL );

  assert( pFile );
  OSTRACE2("SYNC    %-3d\n", pFile->h);
  rc = full_fsync(pFile->h, isFullsync, isDataOnly);
  SimulateIOError( rc=1 );
  if( rc ){
    pFile->lastErrno = errno;
    return SQLITE_IOERR_FSYNC;
  }
  if( pFile->dirfd>=0 ){
    int err;
    OSTRACE4("DIRSYNC %-3d (have_fullfsync=%d fullsync=%d)\n", pFile->dirfd,
            HAVE_FULLFSYNC, isFullsync);
#ifndef SQLITE_DISABLE_DIRSYNC
    /* The directory sync is only attempted if full_fsync is
    ** turned off or unavailable.  If a full_fsync occurred above,
    ** then the directory sync is superfluous.
    */
    if( (!HAVE_FULLFSYNC || !isFullsync) && full_fsync(pFile->dirfd,0,0) ){
       /*
       ** We have received multiple reports of fsync() returning
       ** errors when applied to directories on certain file systems.
       ** A failed directory sync is not a big deal.  So it seems
       ** better to ignore the error.  Ticket #1657
       */
       /* pFile->lastErrno = errno; */
       /* return SQLITE_IOERR; */
    }
#endif
    err = close(pFile->dirfd); /* Only need to sync once, so close the */
    if( err==0 ){              /* directory when we are done */
      pFile->dirfd = -1;
    }else{
      pFile->lastErrno = errno;
      rc = SQLITE_IOERR_DIR_CLOSE;
    }
  }
  return rc;
}

/*
** Truncate an open file to a specified size
*/
static int unixTruncate(sqlite3_file *id, i64 nByte){
  int rc;
  assert( id );
  SimulateIOError( return SQLITE_IOERR_TRUNCATE );
  rc = ftruncate(((unixFile*)id)->h, (off_t)nByte);
  if( rc ){
    ((unixFile*)id)->lastErrno = errno;
    return SQLITE_IOERR_TRUNCATE;
  }else{
    return SQLITE_OK;
  }
}

/*
** Determine the current size of a file in bytes
*/
static int unixFileSize(sqlite3_file *id, i64 *pSize){
  int rc;
  struct stat buf;
  assert( id );
  rc = fstat(((unixFile*)id)->h, &buf);
  SimulateIOError( rc=1 );
  if( rc!=0 ){
    ((unixFile*)id)->lastErrno = errno;
    return SQLITE_IOERR_FSTAT;
  }
  *pSize = buf.st_size;

  /* When opening a zero-size database, the findLockInfo() procedure
  ** writes a single byte into that file in order to work around a bug
  ** in the OS-X msdos filesystem.  In order to avoid problems with upper
  ** layers, we need to report this file size as zero even though it is
  ** really 1.   Ticket #3260.
  */
  if( *pSize==1 ) *pSize = 0;


  return SQLITE_OK;
}

#if SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__)
/*
** Handler for proxy-locking file-control verbs.  Defined below in the
** proxying locking division.
*/
static int proxyFileControl(sqlite3_file*,int,void*);
#endif


/*
** Information and control of an open file handle.
*/
static int unixFileControl(sqlite3_file *id, int op, void *pArg){
  switch( op ){
    case SQLITE_FCNTL_LOCKSTATE: {
      *(int*)pArg = ((unixFile*)id)->locktype;
      return SQLITE_OK;
    }
    case SQLITE_LAST_ERRNO: {
      *(int*)pArg = ((unixFile*)id)->lastErrno;
      return SQLITE_OK;
    }
#ifndef NDEBUG
    /* The pager calls this method to signal that it has done
    ** a rollback and that the database is therefore unchanged and
    ** it hence it is OK for the transaction change counter to be
    ** unchanged.
    */
    case SQLITE_FCNTL_DB_UNCHANGED: {
      ((unixFile*)id)->dbUpdate = 0;
      return SQLITE_OK;
    }
#endif
#if SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__)
    case SQLITE_SET_LOCKPROXYFILE:
    case SQLITE_GET_LOCKPROXYFILE: {
      return proxyFileControl(id,op,pArg);
    }
#endif /* SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__) */
  }
  return SQLITE_ERROR;
}

/*
** Return the sector size in bytes of the underlying block device for
** the specified file. This is almost always 512 bytes, but may be
** larger for some devices.
**
** SQLite code assumes this function cannot fail. It also assumes that
** if two files are created in the same file-system directory (i.e.
** a database and its journal file) that the sector size will be the
** same for both.
*/
static int unixSectorSize(sqlite3_file *NotUsed){
  UNUSED_PARAMETER(NotUsed);
  return SQLITE_DEFAULT_SECTOR_SIZE;
}

/*
** Return the device characteristics for the file. This is always 0 for unix.
*/
static int unixDeviceCharacteristics(sqlite3_file *NotUsed){
  UNUSED_PARAMETER(NotUsed);
  return 0;
}

/*
** Here ends the implementation of all sqlite3_file methods.
**
********************** End sqlite3_file Methods *******************************
