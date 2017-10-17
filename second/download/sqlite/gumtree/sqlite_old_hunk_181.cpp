  const char *zFile,    /* Name of the shared library containing extension */
  const char *zProc,    /* Entry point.  Use "sqlite3_extension_init" if 0 */
  char **pzErrMsg       /* Put error message here if not 0 */
){
  sqlite3_vfs *pVfs = db->pVfs;
  void *handle;
  int (*xInit)(sqlite3*,char**,const sqlite3_api_routines*);
  char *zErrmsg = 0;
  void **aHandle;
  const int nMsg = 300;

  if( pzErrMsg ) *pzErrMsg = 0;

  /* Ticket #1863.  To avoid a creating security problems for older
  ** applications that relink against newer versions of SQLite, the
  ** ability to run load_extension is turned off by default.  One
  ** must call sqlite3_enable_load_extension() to turn on extension
  ** loading.  Otherwise you get the following error.
  */
  if( (db->flags & SQLITE_LoadExtension)==0 ){
    if( pzErrMsg ){
      *pzErrMsg = sqlite3_mprintf("not authorized");
    }
    return SQLITE_ERROR;
  }

  if( zProc==0 ){
    zProc = "sqlite3_extension_init";
  }

  handle = sqlite3OsDlOpen(pVfs, zFile);
  if( handle==0 ){
    if( pzErrMsg ){
      zErrmsg = sqlite3StackAllocZero(db, nMsg);
      if( zErrmsg ){
        sqlite3_snprintf(nMsg, zErrmsg, 
            "unable to open shared library [%s]", zFile);
        sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
        *pzErrMsg = sqlite3DbStrDup(0, zErrmsg);
        sqlite3StackFree(db, zErrmsg);
      }
    }
    return SQLITE_ERROR;
  }
  xInit = (int(*)(sqlite3*,char**,const sqlite3_api_routines*))
                   sqlite3OsDlSym(pVfs, handle, zProc);
  if( xInit==0 ){
    if( pzErrMsg ){
      zErrmsg = sqlite3StackAllocZero(db, nMsg);
      if( zErrmsg ){
        sqlite3_snprintf(nMsg, zErrmsg,
            "no entry point [%s] in shared library [%s]", zProc,zFile);
        sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
        *pzErrMsg = sqlite3DbStrDup(0, zErrmsg);
        sqlite3StackFree(db, zErrmsg);
      }
      sqlite3OsDlClose(pVfs, handle);
    }
    return SQLITE_ERROR;
  }else if( xInit(db, &zErrmsg, &sqlite3Apis) ){
    if( pzErrMsg ){
      *pzErrMsg = sqlite3_mprintf("error during initialization: %s", zErrmsg);
    }
    sqlite3_free(zErrmsg);
    sqlite3OsDlClose(pVfs, handle);
    return SQLITE_ERROR;
  }

  /* Append the new shared library handle to the db->aExtension array. */
  aHandle = sqlite3DbMallocZero(db, sizeof(handle)*(db->nExtension+1));
  if( aHandle==0 ){
    return SQLITE_NOMEM;
  }
  if( db->nExtension>0 ){
    memcpy(aHandle, db->aExtension, sizeof(handle)*db->nExtension);
  }
  sqlite3DbFree(db, db->aExtension);
  db->aExtension = aHandle;
