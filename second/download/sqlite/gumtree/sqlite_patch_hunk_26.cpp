 static void sqliteAuthBadReturnCode(Parse *pParse){
   sqlite3ErrorMsg(pParse, "authorizer malfunction");
   pParse->rc = SQLITE_ERROR;
 }
 
 /*
-** Invoke the authorization callback for permission to read column zCol from
-** table zTab in database zDb. This function assumes that an authorization
-** callback has been registered (i.e. that sqlite3.xAuth is not NULL).
-**
-** If SQLITE_IGNORE is returned and pExpr is not NULL, then pExpr is changed
-** to an SQL NULL expression. Otherwise, if pExpr is NULL, then SQLITE_IGNORE
-** is treated as SQLITE_DENY. In this case an error is left in pParse.
-*/
-int sqlite3AuthReadCol(
-  Parse *pParse,                  /* The parser context */
-  const char *zTab,               /* Table name */
-  const char *zCol,               /* Column name */
-  int iDb                         /* Index of containing database. */
-){
-  sqlite3 *db = pParse->db;          /* Database handle */
-  char *zDb = db->aDb[iDb].zDbSName; /* Schema name of attached database */
-  int rc;                            /* Auth callback return code */
-
-  if( db->init.busy ) return SQLITE_OK;
-  rc = db->xAuth(db->pAuthArg, SQLITE_READ, zTab,zCol,zDb,pParse->zAuthContext
-#ifdef SQLITE_USER_AUTHENTICATION
-                 ,db->auth.zAuthUser
-#endif
-                );
-  if( rc==SQLITE_DENY ){
-    char *z = sqlite3_mprintf("%s.%s", zTab, zCol);
-    if( db->nDb>2 || iDb!=0 ) z = sqlite3_mprintf("%s.%z", zDb, z);
-    sqlite3ErrorMsg(pParse, "access to %z is prohibited", z);
-    pParse->rc = SQLITE_AUTH;
-  }else if( rc!=SQLITE_IGNORE && rc!=SQLITE_OK ){
-    sqliteAuthBadReturnCode(pParse);
-  }
-  return rc;
-}
-
-/*
 ** The pExpr should be a TK_COLUMN expression.  The table referred to
 ** is in pTabList or else it is the NEW or OLD table of a trigger.  
 ** Check to see if it is OK to read this particular column.
 **
 ** If the auth function returns SQLITE_IGNORE, change the TK_COLUMN 
 ** instruction into a TK_NULL.  If the auth function returns SQLITE_DENY,
