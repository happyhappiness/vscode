    sqlite3_free(zCreate);
    if( rc!=SQLITE_OK ){
      return rc;
    }
  }

  appStmt[0] = &pRtree->pReadNode;
  appStmt[1] = &pRtree->pWriteNode;
  appStmt[2] = &pRtree->pDeleteNode;
  appStmt[3] = &pRtree->pReadRowid;
  appStmt[4] = &pRtree->pWriteRowid;
  appStmt[5] = &pRtree->pDeleteRowid;
  appStmt[6] = &pRtree->pReadParent;
  appStmt[7] = &pRtree->pWriteParent;
  appStmt[8] = &pRtree->pDeleteParent;

  for(i=0; i<N_STATEMENT && rc==SQLITE_OK; i++){
    char *zSql = sqlite3_mprintf(azSql[i], zDb, zPrefix);
    if( zSql ){
      rc = sqlite3_prepare_v2(db, zSql, -1, appStmt[i], 0); 
    }else{
      rc = SQLITE_NOMEM;
    }
    sqlite3_free(zSql);
  }

  return rc;
}

/*
** This routine queries database handle db for the page-size used by
** database zDb. If successful, the page-size in bytes is written to
** *piPageSize and SQLITE_OK returned. Otherwise, and an SQLite error 
** code is returned.
*/
static int getPageSize(sqlite3 *db, const char *zDb, int *piPageSize){
  int rc = SQLITE_NOMEM;
  char *zSql;
  sqlite3_stmt *pStmt = 0;

  zSql = sqlite3_mprintf("PRAGMA %Q.page_size", zDb);
  if( !zSql ){
    return SQLITE_NOMEM;
  }

  rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
  sqlite3_free(zSql);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  if( SQLITE_ROW==sqlite3_step(pStmt) ){
    *piPageSize = sqlite3_column_int(pStmt, 0);
  }
  return sqlite3_finalize(pStmt);
}

/* 
** This function is the implementation of both the xConnect and xCreate
** methods of the r-tree virtual table.
**
