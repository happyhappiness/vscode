static int SQLITE_TCLAPI DbMain(
  void *cd,
  Tcl_Interp *interp,
  int objc,
  Tcl_Obj *const*objv
){
  SqliteDb *p;
  const char *zArg;
  char *zErrMsg;
  int i;
  const char *zFile;
  const char *zVfs = 0;
  int flags;
  Tcl_DString translatedFilename;
#if defined(SQLITE_HAS_CODEC) && !defined(SQLITE_OMIT_CODEC_FROM_TCL)
  void *pKey = 0;
  int nKey = 0;
#endif
  int rc;

  /* In normal use, each TCL interpreter runs in a single thread.  So
  ** by default, we can turn of mutexing on SQLite database connections.
  ** However, for testing purposes it is useful to have mutexes turned
  ** on.  So, by default, mutexes default off.  But if compiled with
  ** SQLITE_TCL_DEFAULT_FULLMUTEX then mutexes default on.
  */
#ifdef SQLITE_TCL_DEFAULT_FULLMUTEX
  flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
#else
  flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX;
#endif

  if( objc==2 ){
    zArg = Tcl_GetStringFromObj(objv[1], 0);
    if( strcmp(zArg,"-version")==0 ){
      Tcl_AppendResult(interp,sqlite3_libversion(), (char*)0);
      return TCL_OK;
    }
    if( strcmp(zArg,"-sourceid")==0 ){
      Tcl_AppendResult(interp,sqlite3_sourceid(), (char*)0);
      return TCL_OK;
    }
    if( strcmp(zArg,"-has-codec")==0 ){
#if defined(SQLITE_HAS_CODEC) && !defined(SQLITE_OMIT_CODEC_FROM_TCL)
      Tcl_AppendResult(interp,"1",(char*)0);
#else
      Tcl_AppendResult(interp,"0",(char*)0);
#endif
      return TCL_OK;
    }
  }
  for(i=3; i+1<objc; i+=2){
    zArg = Tcl_GetString(objv[i]);
    if( strcmp(zArg,"-key")==0 ){
#if defined(SQLITE_HAS_CODEC) && !defined(SQLITE_OMIT_CODEC_FROM_TCL)
      pKey = Tcl_GetByteArrayFromObj(objv[i+1], &nKey);
#endif
    }else if( strcmp(zArg, "-vfs")==0 ){
      zVfs = Tcl_GetString(objv[i+1]);
    }else if( strcmp(zArg, "-readonly")==0 ){
      int b;
      if( Tcl_GetBooleanFromObj(interp, objv[i+1], &b) ) return TCL_ERROR;
      if( b ){
        flags &= ~(SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
        flags |= SQLITE_OPEN_READONLY;
      }else{
        flags &= ~SQLITE_OPEN_READONLY;
        flags |= SQLITE_OPEN_READWRITE;
      }
    }else if( strcmp(zArg, "-create")==0 ){
      int b;
      if( Tcl_GetBooleanFromObj(interp, objv[i+1], &b) ) return TCL_ERROR;
      if( b && (flags & SQLITE_OPEN_READONLY)==0 ){
        flags |= SQLITE_OPEN_CREATE;
      }else{
        flags &= ~SQLITE_OPEN_CREATE;
      }
    }else if( strcmp(zArg, "-nomutex")==0 ){
      int b;
      if( Tcl_GetBooleanFromObj(interp, objv[i+1], &b) ) return TCL_ERROR;
      if( b ){
        flags |= SQLITE_OPEN_NOMUTEX;
        flags &= ~SQLITE_OPEN_FULLMUTEX;
      }else{
        flags &= ~SQLITE_OPEN_NOMUTEX;
      }
    }else if( strcmp(zArg, "-fullmutex")==0 ){
      int b;
      if( Tcl_GetBooleanFromObj(interp, objv[i+1], &b) ) return TCL_ERROR;
      if( b ){
        flags |= SQLITE_OPEN_FULLMUTEX;
        flags &= ~SQLITE_OPEN_NOMUTEX;
      }else{
        flags &= ~SQLITE_OPEN_FULLMUTEX;
      }
    }else if( strcmp(zArg, "-uri")==0 ){
      int b;
      if( Tcl_GetBooleanFromObj(interp, objv[i+1], &b) ) return TCL_ERROR;
      if( b ){
        flags |= SQLITE_OPEN_URI;
      }else{
        flags &= ~SQLITE_OPEN_URI;
      }
    }else{
      Tcl_AppendResult(interp, "unknown option: ", zArg, (char*)0);
      return TCL_ERROR;
    }
  }
  if( objc<3 || (objc&1)!=1 ){
    Tcl_WrongNumArgs(interp, 1, objv,
      "HANDLE FILENAME ?-vfs VFSNAME? ?-readonly BOOLEAN? ?-create BOOLEAN?"
      " ?-nomutex BOOLEAN? ?-fullmutex BOOLEAN? ?-uri BOOLEAN?"
#if defined(SQLITE_HAS_CODEC) && !defined(SQLITE_OMIT_CODEC_FROM_TCL)
      " ?-key CODECKEY?"
#endif
    );
    return TCL_ERROR;
  }
  zErrMsg = 0;
  p = (SqliteDb*)Tcl_Alloc( sizeof(*p) );
  memset(p, 0, sizeof(*p));
  zFile = Tcl_GetStringFromObj(objv[2], 0);
  zFile = Tcl_TranslateFileName(interp, zFile, &translatedFilename);
  rc = sqlite3_open_v2(zFile, &p->db, flags, zVfs);
  Tcl_DStringFree(&translatedFilename);
  if( p->db ){
    if( SQLITE_OK!=sqlite3_errcode(p->db) ){
      zErrMsg = sqlite3_mprintf("%s", sqlite3_errmsg(p->db));
      sqlite3_close(p->db);
      p->db = 0;
    }
  }else{
    zErrMsg = sqlite3_mprintf("%s", sqlite3_errstr(rc));
  }
#if defined(SQLITE_HAS_CODEC) && !defined(SQLITE_OMIT_CODEC_FROM_TCL)
  if( p->db ){
    sqlite3_key(p->db, pKey, nKey);
  }
#endif
  if( p->db==0 ){
    Tcl_SetResult(interp, zErrMsg, TCL_VOLATILE);
    Tcl_Free((char*)p);
    sqlite3_free(zErrMsg);
    return TCL_ERROR;
  }
  p->maxStmt = NUM_PREPARED_STMTS;
  p->openFlags = flags & SQLITE_OPEN_URI;
  p->interp = interp;
  zArg = Tcl_GetStringFromObj(objv[1], 0);
  if( DbUseNre() ){
    Tcl_NRCreateCommand(interp, zArg, DbObjCmdAdaptor, DbObjCmd,
                        (char*)p, DbDeleteCmd);
  }else{
    Tcl_CreateObjCommand(interp, zArg, DbObjCmd, (char*)p, DbDeleteCmd);
  }
  return TCL_OK;
}