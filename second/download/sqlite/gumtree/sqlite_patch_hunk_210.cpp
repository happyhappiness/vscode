   for(i=0; i<db->nDb; i++) {
     Btree *pBt = db->aDb[i].pBt;
     if( pBt ){
       assert( sqlite3BtreeHoldsMutex(pBt) );
       rc = sqlite3BtreeSchemaLocked(pBt);
       if( rc ){
-        const char *zDb = db->aDb[i].zName;
-        sqlite3Error(db, rc, "database schema is locked: %s", zDb);
-        (void)sqlite3SafetyOff(db);
-        testcase( db->flags & SQLITE_ReadUncommitted );
+        const char *zDb = db->aDb[i].zDbSName;
+        sqlite3ErrorWithMsg(db, rc, "database schema is locked: %s", zDb);
+        testcase( db->flags & SQLITE_ReadUncommit );
         goto end_prepare;
       }
     }
   }
 
+  sqlite3VtabUnlockList(db);
 
-  pParse->db = db;
+  sParse.db = db;
   if( nBytes>=0 && (nBytes==0 || zSql[nBytes-1]!=0) ){
     char *zSqlCopy;
     int mxLen = db->aLimit[SQLITE_LIMIT_SQL_LENGTH];
+    testcase( nBytes==mxLen );
+    testcase( nBytes==mxLen+1 );
     if( nBytes>mxLen ){
-      sqlite3Error(db, SQLITE_TOOBIG, "statement too long");
-      (void)sqlite3SafetyOff(db);
+      sqlite3ErrorWithMsg(db, SQLITE_TOOBIG, "statement too long");
       rc = sqlite3ApiExit(db, SQLITE_TOOBIG);
       goto end_prepare;
     }
     zSqlCopy = sqlite3DbStrNDup(db, zSql, nBytes);
     if( zSqlCopy ){
-      sqlite3RunParser(pParse, zSqlCopy, &zErrMsg);
+      sqlite3RunParser(&sParse, zSqlCopy, &zErrMsg);
+      sParse.zTail = &zSql[sParse.zTail-zSqlCopy];
       sqlite3DbFree(db, zSqlCopy);
-      pParse->zTail = &zSql[pParse->zTail-zSqlCopy];
     }else{
-      pParse->zTail = &zSql[nBytes];
+      sParse.zTail = &zSql[nBytes];
     }
   }else{
-    sqlite3RunParser(pParse, zSql, &zErrMsg);
+    sqlite3RunParser(&sParse, zSql, &zErrMsg);
   }
+  assert( 0==sParse.nQueryLoop );
 
-  if( db->mallocFailed ){
-    pParse->rc = SQLITE_NOMEM;
-  }
-  if( pParse->rc==SQLITE_DONE ) pParse->rc = SQLITE_OK;
-  if( pParse->checkSchema && !schemaIsValid(db) ){
-    pParse->rc = SQLITE_SCHEMA;
-  }
-  if( pParse->rc==SQLITE_SCHEMA ){
-    sqlite3ResetInternalSchema(db, 0);
+  if( sParse.rc==SQLITE_DONE ) sParse.rc = SQLITE_OK;
+  if( sParse.checkSchema ){
+    schemaIsValid(&sParse);
   }
   if( db->mallocFailed ){
-    pParse->rc = SQLITE_NOMEM;
+    sParse.rc = SQLITE_NOMEM_BKPT;
   }
   if( pzTail ){
-    *pzTail = pParse->zTail;
+    *pzTail = sParse.zTail;
   }
-  rc = pParse->rc;
+  rc = sParse.rc;
 
 #ifndef SQLITE_OMIT_EXPLAIN
-  if( rc==SQLITE_OK && pParse->pVdbe && pParse->explain ){
+  if( rc==SQLITE_OK && sParse.pVdbe && sParse.explain ){
     static const char * const azColName[] = {
        "addr", "opcode", "p1", "p2", "p3", "p4", "p5", "comment",
-       "order", "from", "detail"
+       "selectid", "order", "from", "detail"
     };
     int iFirst, mx;
-    if( pParse->explain==2 ){
-      sqlite3VdbeSetNumCols(pParse->pVdbe, 3);
+    if( sParse.explain==2 ){
+      sqlite3VdbeSetNumCols(sParse.pVdbe, 4);
       iFirst = 8;
-      mx = 11;
+      mx = 12;
     }else{
-      sqlite3VdbeSetNumCols(pParse->pVdbe, 8);
+      sqlite3VdbeSetNumCols(sParse.pVdbe, 8);
       iFirst = 0;
       mx = 8;
     }
     for(i=iFirst; i<mx; i++){
-      sqlite3VdbeSetColName(pParse->pVdbe, i-iFirst, COLNAME_NAME,
+      sqlite3VdbeSetColName(sParse.pVdbe, i-iFirst, COLNAME_NAME,
                             azColName[i], SQLITE_STATIC);
     }
   }
 #endif
 
-  if( sqlite3SafetyOff(db) ){
-    rc = SQLITE_MISUSE;
-  }
-
-  assert( db->init.busy==0 || saveSqlFlag==0 );
   if( db->init.busy==0 ){
-    Vdbe *pVdbe = pParse->pVdbe;
-    sqlite3VdbeSetSql(pVdbe, zSql, (int)(pParse->zTail-zSql), saveSqlFlag);
+    sqlite3VdbeSetSql(sParse.pVdbe, zSql, (int)(sParse.zTail-zSql), prepFlags);
   }
-  if( pParse->pVdbe && (rc!=SQLITE_OK || db->mallocFailed) ){
-    sqlite3VdbeFinalize(pParse->pVdbe);
+  if( sParse.pVdbe && (rc!=SQLITE_OK || db->mallocFailed) ){
+    sqlite3VdbeFinalize(sParse.pVdbe);
     assert(!(*ppStmt));
   }else{
-    *ppStmt = (sqlite3_stmt*)pParse->pVdbe;
+    *ppStmt = (sqlite3_stmt*)sParse.pVdbe;
   }
 
   if( zErrMsg ){
-    sqlite3Error(db, rc, "%s", zErrMsg);
+    sqlite3ErrorWithMsg(db, rc, "%s", zErrMsg);
     sqlite3DbFree(db, zErrMsg);
   }else{
-    sqlite3Error(db, rc, 0);
+    sqlite3Error(db, rc);
+  }
+
+  /* Delete any TriggerPrg structures allocated while parsing this statement. */
+  while( sParse.pTriggerPrg ){
+    TriggerPrg *pT = sParse.pTriggerPrg;
+    sParse.pTriggerPrg = pT->pNext;
+    sqlite3DbFree(db, pT);
   }
 
 end_prepare:
 
-  sqlite3StackFree(db, pParse);
+  sqlite3ParserReset(&sParse);
   rc = sqlite3ApiExit(db, rc);
   assert( (rc&db->errMask)==rc );
   return rc;
 }
 static int sqlite3LockAndPrepare(
   sqlite3 *db,              /* Database handle. */
   const char *zSql,         /* UTF-8 encoded SQL statement. */
   int nBytes,               /* Length of zSql in bytes. */
-  int saveSqlFlag,          /* True to copy SQL text into the sqlite3_stmt */
+  u32 prepFlags,            /* Zero or more SQLITE_PREPARE_* flags */
+  Vdbe *pOld,               /* VM being reprepared */
   sqlite3_stmt **ppStmt,    /* OUT: A pointer to the prepared statement */
   const char **pzTail       /* OUT: End of parsed string */
 ){
   int rc;
-  assert( ppStmt!=0 );
+
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( ppStmt==0 ) return SQLITE_MISUSE_BKPT;
+#endif
   *ppStmt = 0;
-  if( !sqlite3SafetyCheckOk(db) ){
-    return SQLITE_MISUSE;
+  if( !sqlite3SafetyCheckOk(db)||zSql==0 ){
+    return SQLITE_MISUSE_BKPT;
   }
   sqlite3_mutex_enter(db->mutex);
   sqlite3BtreeEnterAll(db);
-  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, ppStmt, pzTail);
+  rc = sqlite3Prepare(db, zSql, nBytes, prepFlags, pOld, ppStmt, pzTail);
+  if( rc==SQLITE_SCHEMA ){
+    sqlite3ResetOneSchema(db, -1);
+    sqlite3_finalize(*ppStmt);
+    rc = sqlite3Prepare(db, zSql, nBytes, prepFlags, pOld, ppStmt, pzTail);
+  }
   sqlite3BtreeLeaveAll(db);
   sqlite3_mutex_leave(db->mutex);
+  assert( rc==SQLITE_OK || *ppStmt==0 );
   return rc;
 }
 
 /*
 ** Rerun the compilation of a statement after a schema change.
 **
