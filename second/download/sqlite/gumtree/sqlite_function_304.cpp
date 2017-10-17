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