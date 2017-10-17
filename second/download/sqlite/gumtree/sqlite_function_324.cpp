int sqlite3AuthReadCol(
  Parse *pParse,                  /* The parser context */
  const char *zTab,               /* Table name */
  const char *zCol,               /* Column name */
  int iDb                         /* Index of containing database. */
){
  sqlite3 *db = pParse->db;          /* Database handle */
  char *zDb = db->aDb[iDb].zDbSName; /* Schema name of attached database */
  int rc;                            /* Auth callback return code */

  if( db->init.busy ) return SQLITE_OK;
  rc = db->xAuth(db->pAuthArg, SQLITE_READ, zTab,zCol,zDb,pParse->zAuthContext
#ifdef SQLITE_USER_AUTHENTICATION
                 ,db->auth.zAuthUser
#endif
                );
  if( rc==SQLITE_DENY ){
    char *z = sqlite3_mprintf("%s.%s", zTab, zCol);
    if( db->nDb>2 || iDb!=0 ) z = sqlite3_mprintf("%s.%z", zDb, z);
    sqlite3ErrorMsg(pParse, "access to %z is prohibited", z);
    pParse->rc = SQLITE_AUTH;
  }else if( rc!=SQLITE_IGNORE && rc!=SQLITE_OK ){
    sqliteAuthBadReturnCode(pParse);
  }
  return rc;
}