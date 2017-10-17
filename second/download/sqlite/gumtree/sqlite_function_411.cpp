static int winOpen(
  sqlite3_vfs *pVfs,        /* Used to get maximum path length and AppData */
  const char *zName,        /* Name of the file (UTF-8) */
  sqlite3_file *id,         /* Write the SQLite file handle here */
  int flags,                /* Open mode flags */
  int *pOutFlags            /* Status return flags */
){
  HANDLE h;
  DWORD lastErrno = 0;
  DWORD dwDesiredAccess;
  DWORD dwShareMode;
  DWORD dwCreationDisposition;
  DWORD dwFlagsAndAttributes = 0;
#if SQLITE_OS_WINCE
  int isTemp = 0;
#endif
  winVfsAppData *pAppData;
  winFile *pFile = (winFile*)id;
  void *zConverted;              /* Filename in OS encoding */
  const char *zUtf8Name = zName; /* Filename in UTF-8 encoding */
  int cnt = 0;

  /* If argument zPath is a NULL pointer, this function is required to open
  ** a temporary file. Use this buffer to store the file name in.
  */
  char *zTmpname = 0; /* For temporary filename, if necessary. */

  int rc = SQLITE_OK;            /* Function Return Code */
#if !defined(NDEBUG) || SQLITE_OS_WINCE
  int eType = flags&0xFFFFFF00;  /* Type of file to open */
#endif

  int isExclusive  = (flags & SQLITE_OPEN_EXCLUSIVE);
  int isDelete     = (flags & SQLITE_OPEN_DELETEONCLOSE);
  int isCreate     = (flags & SQLITE_OPEN_CREATE);
  int isReadonly   = (flags & SQLITE_OPEN_READONLY);
  int isReadWrite  = (flags & SQLITE_OPEN_READWRITE);

#ifndef NDEBUG
  int isOpenJournal = (isCreate && (
        eType==SQLITE_OPEN_MASTER_JOURNAL
     || eType==SQLITE_OPEN_MAIN_JOURNAL
     || eType==SQLITE_OPEN_WAL
  ));
#endif

  OSTRACE(("OPEN name=%s, pFile=%p, flags=%x, pOutFlags=%p\n",
           zUtf8Name, id, flags, pOutFlags));

  /* Check the following statements are true:
  **
  **   (a) Exactly one of the READWRITE and READONLY flags must be set, and
  **   (b) if CREATE is set, then READWRITE must also be set, and
  **   (c) if EXCLUSIVE is set, then CREATE must also be set.
  **   (d) if DELETEONCLOSE is set, then CREATE must also be set.
  */
  assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
  assert(isCreate==0 || isReadWrite);
  assert(isExclusive==0 || isCreate);
  assert(isDelete==0 || isCreate);

  /* The main DB, main journal, WAL file and master journal are never
  ** automatically deleted. Nor are they ever temporary files.  */
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_DB );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_JOURNAL );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MASTER_JOURNAL );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_WAL );

  /* Assert that the upper layer has set one of the "file-type" flags. */
  assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB
       || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL
       || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL
       || eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL
  );

  assert( pFile!=0 );
  memset(pFile, 0, sizeof(winFile));
  pFile->h = INVALID_HANDLE_VALUE;

#if SQLITE_OS_WINRT
  if( !zUtf8Name && !sqlite3_temp_directory ){
    sqlite3_log(SQLITE_ERROR,
        "sqlite3_temp_directory variable should be set for WinRT");
  }
#endif

  /* If the second argument to this function is NULL, generate a
  ** temporary file name to use
  */
  if( !zUtf8Name ){
    assert( isDelete && !isOpenJournal );
    rc = winGetTempname(pVfs, &zTmpname);
    if( rc!=SQLITE_OK ){
      OSTRACE(("OPEN name=%s, rc=%s", zUtf8Name, sqlite3ErrName(rc)));
      return rc;
    }
    zUtf8Name = zTmpname;
  }

  /* Database filenames are double-zero terminated if they are not
  ** URIs with parameters.  Hence, they can always be passed into
  ** sqlite3_uri_parameter().
  */
  assert( (eType!=SQLITE_OPEN_MAIN_DB) || (flags & SQLITE_OPEN_URI) ||
       zUtf8Name[sqlite3Strlen30(zUtf8Name)+1]==0 );

  /* Convert the filename to the system encoding. */
  zConverted = winConvertFromUtf8Filename(zUtf8Name);
  if( zConverted==0 ){
    sqlite3_free(zTmpname);
    OSTRACE(("OPEN name=%s, rc=SQLITE_IOERR_NOMEM", zUtf8Name));
    return SQLITE_IOERR_NOMEM_BKPT;
  }

  if( winIsDir(zConverted) ){
    sqlite3_free(zConverted);
    sqlite3_free(zTmpname);
    OSTRACE(("OPEN name=%s, rc=SQLITE_CANTOPEN_ISDIR", zUtf8Name));
    return SQLITE_CANTOPEN_ISDIR;
  }

  if( isReadWrite ){
    dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
  }else{
    dwDesiredAccess = GENERIC_READ;
  }

  /* SQLITE_OPEN_EXCLUSIVE is used to make sure that a new file is
  ** created. SQLite doesn't use it to indicate "exclusive access"
  ** as it is usually understood.
  */
  if( isExclusive ){
    /* Creates a new file, only if it does not already exist. */
    /* If the file exists, it fails. */
    dwCreationDisposition = CREATE_NEW;
  }else if( isCreate ){
    /* Open existing file, or create if it doesn't exist */
    dwCreationDisposition = OPEN_ALWAYS;
  }else{
    /* Opens a file, only if it exists. */
    dwCreationDisposition = OPEN_EXISTING;
  }

  dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

  if( isDelete ){
#if SQLITE_OS_WINCE
    dwFlagsAndAttributes = FILE_ATTRIBUTE_HIDDEN;
    isTemp = 1;
#else
    dwFlagsAndAttributes = FILE_ATTRIBUTE_TEMPORARY
                               | FILE_ATTRIBUTE_HIDDEN
                               | FILE_FLAG_DELETE_ON_CLOSE;
#endif
  }else{
    dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
  }
  /* Reports from the internet are that performance is always
  ** better if FILE_FLAG_RANDOM_ACCESS is used.  Ticket #2699. */
#if SQLITE_OS_WINCE
  dwFlagsAndAttributes |= FILE_FLAG_RANDOM_ACCESS;
#endif

  if( osIsNT() ){
#if SQLITE_OS_WINRT
    CREATEFILE2_EXTENDED_PARAMETERS extendedParameters;
    extendedParameters.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    extendedParameters.dwFileAttributes =
            dwFlagsAndAttributes & FILE_ATTRIBUTE_MASK;
    extendedParameters.dwFileFlags = dwFlagsAndAttributes & FILE_FLAG_MASK;
    extendedParameters.dwSecurityQosFlags = SECURITY_ANONYMOUS;
    extendedParameters.lpSecurityAttributes = NULL;
    extendedParameters.hTemplateFile = NULL;
    do{
      h = osCreateFile2((LPCWSTR)zConverted,
                        dwDesiredAccess,
                        dwShareMode,
                        dwCreationDisposition,
                        &extendedParameters);
      if( h!=INVALID_HANDLE_VALUE ) break;
      if( isReadWrite ){
        int isRO = 0;
        int rc2 = winAccess(pVfs, zName, SQLITE_ACCESS_READ, &isRO);
        if( rc2==SQLITE_OK && isRO ) break;
      }
    }while( winRetryIoerr(&cnt, &lastErrno) );
#else
    do{
      h = osCreateFileW((LPCWSTR)zConverted,
                        dwDesiredAccess,
                        dwShareMode, NULL,
                        dwCreationDisposition,
                        dwFlagsAndAttributes,
                        NULL);
      if( h!=INVALID_HANDLE_VALUE ) break;
      if( isReadWrite ){
        int isRO = 0;
        int rc2 = winAccess(pVfs, zName, SQLITE_ACCESS_READ, &isRO);
        if( rc2==SQLITE_OK && isRO ) break;
      }
    }while( winRetryIoerr(&cnt, &lastErrno) );
#endif
  }
#ifdef SQLITE_WIN32_HAS_ANSI
  else{
    do{
      h = osCreateFileA((LPCSTR)zConverted,
                        dwDesiredAccess,
                        dwShareMode, NULL,
                        dwCreationDisposition,
                        dwFlagsAndAttributes,
                        NULL);
      if( h!=INVALID_HANDLE_VALUE ) break;
      if( isReadWrite ){
        int isRO = 0;
        int rc2 = winAccess(pVfs, zName, SQLITE_ACCESS_READ, &isRO);
        if( rc2==SQLITE_OK && isRO ) break;
      }
    }while( winRetryIoerr(&cnt, &lastErrno) );
  }
#endif
  winLogIoerr(cnt, __LINE__);

  OSTRACE(("OPEN file=%p, name=%s, access=%lx, rc=%s\n", h, zUtf8Name,
           dwDesiredAccess, (h==INVALID_HANDLE_VALUE) ? "failed" : "ok"));

  if( h==INVALID_HANDLE_VALUE ){
    sqlite3_free(zConverted);
    sqlite3_free(zTmpname);
    if( isReadWrite && !isExclusive ){
      return winOpen(pVfs, zName, id,
         ((flags|SQLITE_OPEN_READONLY) &
                     ~(SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE)),
         pOutFlags);
    }else{
      pFile->lastErrno = lastErrno;
      winLogError(SQLITE_CANTOPEN, pFile->lastErrno, "winOpen", zUtf8Name);
      return SQLITE_CANTOPEN_BKPT;
    }
  }

  if( pOutFlags ){
    if( isReadWrite ){
      *pOutFlags = SQLITE_OPEN_READWRITE;
    }else{
      *pOutFlags = SQLITE_OPEN_READONLY;
    }
  }

  OSTRACE(("OPEN file=%p, name=%s, access=%lx, pOutFlags=%p, *pOutFlags=%d, "
           "rc=%s\n", h, zUtf8Name, dwDesiredAccess, pOutFlags, pOutFlags ?
           *pOutFlags : 0, (h==INVALID_HANDLE_VALUE) ? "failed" : "ok"));

  pAppData = (winVfsAppData*)pVfs->pAppData;

#if SQLITE_OS_WINCE
  {
    if( isReadWrite && eType==SQLITE_OPEN_MAIN_DB
         && ((pAppData==NULL) || !pAppData->bNoLock)
         && (rc = winceCreateLock(zName, pFile))!=SQLITE_OK
    ){
      osCloseHandle(h);
      sqlite3_free(zConverted);
      sqlite3_free(zTmpname);
      OSTRACE(("OPEN-CE-LOCK name=%s, rc=%s\n", zName, sqlite3ErrName(rc)));
      return rc;
    }
  }
  if( isTemp ){
    pFile->zDeleteOnClose = zConverted;
  }else
#endif
  {
    sqlite3_free(zConverted);
  }

  sqlite3_free(zTmpname);
  pFile->pMethod = pAppData ? pAppData->pMethod : &winIoMethod;
  pFile->pVfs = pVfs;
  pFile->h = h;
  if( isReadonly ){
    pFile->ctrlFlags |= WINFILE_RDONLY;
  }
  if( sqlite3_uri_boolean(zName, "psow", SQLITE_POWERSAFE_OVERWRITE) ){
    pFile->ctrlFlags |= WINFILE_PSOW;
  }
  pFile->lastErrno = NO_ERROR;
  pFile->zPath = zName;
#if SQLITE_MAX_MMAP_SIZE>0
  pFile->hMap = NULL;
  pFile->pMapRegion = 0;
  pFile->mmapSize = 0;
  pFile->mmapSizeActual = 0;
  pFile->mmapSizeMax = sqlite3GlobalConfig.szMmap;
#endif

  OpenCounter(+1);
  return rc;
}