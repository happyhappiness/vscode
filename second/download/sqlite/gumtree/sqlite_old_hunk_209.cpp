    db->flags &= ~SQLITE_LegacyFileFmt;
  }

  /* Read the schema information out of the schema tables
  */
  assert( db->init.busy );
  if( rc==SQLITE_EMPTY ){
    /* For an empty database, there is nothing to read */
    rc = SQLITE_OK;
  }else{
    char *zSql;
    zSql = sqlite3MPrintf(db, 
        "SELECT name, rootpage, sql FROM '%q'.%s",
        db->aDb[iDb].zName, zMasterName);
    (void)sqlite3SafetyOff(db);
#ifndef SQLITE_OMIT_AUTHORIZATION
    {
      int (*xAuth)(void*,int,const char*,const char*,const char*,const char*);
      xAuth = db->xAuth;
      db->xAuth = 0;
#endif
      rc = sqlite3_exec(db, zSql, sqlite3InitCallback, &initData, 0);
#ifndef SQLITE_OMIT_AUTHORIZATION
      db->xAuth = xAuth;
    }
#endif
    if( rc==SQLITE_OK ) rc = initData.rc;
    (void)sqlite3SafetyOn(db);
    sqlite3DbFree(db, zSql);
#ifndef SQLITE_OMIT_ANALYZE
    if( rc==SQLITE_OK ){
      sqlite3AnalysisLoad(db, iDb);
    }
#endif
  }
  if( db->mallocFailed ){
    rc = SQLITE_NOMEM;
    sqlite3ResetInternalSchema(db, 0);
  }
  if( rc==SQLITE_OK || (db->flags&SQLITE_RecoveryMode)){
    /* Black magic: If the SQLITE_RecoveryMode flag is set, then consider
    ** the schema loaded, even if errors occurred. In this situation the 
    ** current sqlite3_prepare() operation will fail, but the following one
    ** will attempt to compile the supplied statement against whatever subset
    ** of the schema was loaded before the error occurred. The primary
    ** purpose of this is to allow access to the sqlite_master table
    ** even when its contents have been corrupted.
