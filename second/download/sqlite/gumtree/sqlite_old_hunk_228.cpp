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
    }else{
      Tcl_AppendResult(interp, "unknown option: ", zArg, (char*)0);
      return TCL_ERROR;
    }
  }
  if( objc<3 || (objc&1)!=1 ){
    Tcl_WrongNumArgs(interp, 1, objv, 
      "HANDLE FILENAME ?-vfs VFSNAME? ?-readonly BOOLEAN? ?-create BOOLEAN?"
      " ?-nomutex BOOLEAN? ?-fullmutex BOOLEAN?"
#ifdef SQLITE_HAS_CODEC
      " ?-key CODECKEY?"
#endif
    );
    return TCL_ERROR;
  }
  zErrMsg = 0;
  p = (SqliteDb*)Tcl_Alloc( sizeof(*p) );
  if( p==0 ){
    Tcl_SetResult(interp, "malloc failed", TCL_STATIC);
    return TCL_ERROR;
  }
  memset(p, 0, sizeof(*p));
  zFile = Tcl_GetStringFromObj(objv[2], 0);
  zFile = Tcl_TranslateFileName(interp, zFile, &translatedFilename);
  sqlite3_open_v2(zFile, &p->db, flags, zVfs);
  Tcl_DStringFree(&translatedFilename);
  if( SQLITE_OK!=sqlite3_errcode(p->db) ){
    zErrMsg = sqlite3_mprintf("%s", sqlite3_errmsg(p->db));
    sqlite3_close(p->db);
    p->db = 0;
  }
#ifdef SQLITE_HAS_CODEC
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
  p->interp = interp;
  zArg = Tcl_GetStringFromObj(objv[1], 0);
  Tcl_CreateObjCommand(interp, zArg, DbObjCmd, (char*)p, DbDeleteCmd);
  return TCL_OK;
}

/*
** Provide a dummy Tcl_InitStubs if we are using this as a static
** library.
*/
#ifndef USE_TCL_STUBS
# undef  Tcl_InitStubs
# define Tcl_InitStubs(a,b,c)
#endif

/*
** Make sure we have a PACKAGE_VERSION macro defined.  This will be
** defined automatically by the TEA makefile.  But other makefiles
** do not define it.
