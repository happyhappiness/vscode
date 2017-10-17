  for(i=0; i<db->nDb; i++) {
    Btree *pBt = db->aDb[i].pBt;
    if( pBt ){
      assert( sqlite3BtreeHoldsMutex(pBt) );
      rc = sqlite3BtreeSchemaLocked(pBt);
      if( rc ){
        const char *zDb = db->aDb[i].zName;
        sqlite3Error(db, rc, "database schema is locked: %s", zDb);
        (void)sqlite3SafetyOff(db);
        testcase( db->flags & SQLITE_ReadUncommitted );
        goto end_prepare;
      }
    }
  }


  pParse->db = db;
  if( nBytes>=0 && (nBytes==0 || zSql[nBytes-1]!=0) ){
    char *zSqlCopy;
    int mxLen = db->aLimit[SQLITE_LIMIT_SQL_LENGTH];
    if( nBytes>mxLen ){
      sqlite3Error(db, SQLITE_TOOBIG, "statement too long");
      (void)sqlite3SafetyOff(db);
      rc = sqlite3ApiExit(db, SQLITE_TOOBIG);
      goto end_prepare;
    }
    zSqlCopy = sqlite3DbStrNDup(db, zSql, nBytes);
    if( zSqlCopy ){
      sqlite3RunParser(pParse, zSqlCopy, &zErrMsg);
      sqlite3DbFree(db, zSqlCopy);
      pParse->zTail = &zSql[pParse->zTail-zSqlCopy];
    }else{
      pParse->zTail = &zSql[nBytes];
    }
  }else{
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }

  if( db->mallocFailed ){
    pParse->rc = SQLITE_NOMEM;
  }
  if( pParse->rc==SQLITE_DONE ) pParse->rc = SQLITE_OK;
  if( pParse->checkSchema && !schemaIsValid(db) ){
    pParse->rc = SQLITE_SCHEMA;
  }
  if( pParse->rc==SQLITE_SCHEMA ){
    sqlite3ResetInternalSchema(db, 0);
  }
  if( db->mallocFailed ){
    pParse->rc = SQLITE_NOMEM;
  }
  if( pzTail ){
    *pzTail = pParse->zTail;
  }
  rc = pParse->rc;

#ifndef SQLITE_OMIT_EXPLAIN
  if( rc==SQLITE_OK && pParse->pVdbe && pParse->explain ){
    static const char * const azColName[] = {
       "addr", "opcode", "p1", "p2", "p3", "p4", "p5", "comment",
       "order", "from", "detail"
    };
    int iFirst, mx;
    if( pParse->explain==2 ){
      sqlite3VdbeSetNumCols(pParse->pVdbe, 3);
      iFirst = 8;
      mx = 11;
    }else{
      sqlite3VdbeSetNumCols(pParse->pVdbe, 8);
      iFirst = 0;
      mx = 8;
    }
    for(i=iFirst; i<mx; i++){
      sqlite3VdbeSetColName(pParse->pVdbe, i-iFirst, COLNAME_NAME,
                            azColName[i], SQLITE_STATIC);
    }
  }
#endif

  if( sqlite3SafetyOff(db) ){
    rc = SQLITE_MISUSE;
  }

  assert( db->init.busy==0 || saveSqlFlag==0 );
  if( db->init.busy==0 ){
    Vdbe *pVdbe = pParse->pVdbe;
    sqlite3VdbeSetSql(pVdbe, zSql, (int)(pParse->zTail-zSql), saveSqlFlag);
  }
  if( pParse->pVdbe && (rc!=SQLITE_OK || db->mallocFailed) ){
    sqlite3VdbeFinalize(pParse->pVdbe);
    assert(!(*ppStmt));
  }else{
    *ppStmt = (sqlite3_stmt*)pParse->pVdbe;
  }

  if( zErrMsg ){
    sqlite3Error(db, rc, "%s", zErrMsg);
    sqlite3DbFree(db, zErrMsg);
  }else{
    sqlite3Error(db, rc, 0);
  }

end_prepare:

  sqlite3StackFree(db, pParse);
  rc = sqlite3ApiExit(db, rc);
  assert( (rc&db->errMask)==rc );
  return rc;
}
static int sqlite3LockAndPrepare(
  sqlite3 *db,              /* Database handle. */
  const char *zSql,         /* UTF-8 encoded SQL statement. */
  int nBytes,               /* Length of zSql in bytes. */
  int saveSqlFlag,          /* True to copy SQL text into the sqlite3_stmt */
  sqlite3_stmt **ppStmt,    /* OUT: A pointer to the prepared statement */
  const char **pzTail       /* OUT: End of parsed string */
){
  int rc;
  assert( ppStmt!=0 );
  *ppStmt = 0;
  if( !sqlite3SafetyCheckOk(db) ){
    return SQLITE_MISUSE;
  }
  sqlite3_mutex_enter(db->mutex);
  sqlite3BtreeEnterAll(db);
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, ppStmt, pzTail);
  sqlite3BtreeLeaveAll(db);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}

/*
** Rerun the compilation of a statement after a schema change.
**
