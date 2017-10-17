 ** error message to pErrorDb.
 */
 static Btree *findBtree(sqlite3 *pErrorDb, sqlite3 *pDb, const char *zDb){
   int i = sqlite3FindDbName(pDb, zDb);
 
   if( i==1 ){
-    Parse sParse;
+    Parse *pParse;
     int rc = 0;
-    memset(&sParse, 0, sizeof(sParse));
-    sParse.db = pDb;
-    if( sqlite3OpenTempDatabase(&sParse) ){
-      sqlite3ErrorWithMsg(pErrorDb, sParse.rc, "%s", sParse.zErrMsg);
-      rc = SQLITE_ERROR;
+    pParse = sqlite3StackAllocZero(pErrorDb, sizeof(*pParse));
+    if( pParse==0 ){
+      sqlite3Error(pErrorDb, SQLITE_NOMEM, "out of memory");
+      rc = SQLITE_NOMEM;
+    }else{
+      pParse->db = pDb;
+      if( sqlite3OpenTempDatabase(pParse) ){
+        sqlite3ErrorClear(pParse);
+        sqlite3Error(pErrorDb, pParse->rc, "%s", pParse->zErrMsg);
+        rc = SQLITE_ERROR;
+      }
+      sqlite3StackFree(pErrorDb, pParse);
     }
-    sqlite3DbFree(pErrorDb, sParse.zErrMsg);
-    sqlite3ParserReset(&sParse);
     if( rc ){
       return 0;
     }
   }
 
   if( i<0 ){
-    sqlite3ErrorWithMsg(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
+    sqlite3Error(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
     return 0;
   }
 
   return pDb->aDb[i].pBt;
 }
 
 /*
-** Attempt to set the page size of the destination to match the page size
-** of the source.
-*/
-static int setDestPgsz(sqlite3_backup *p){
-  int rc;
-  rc = sqlite3BtreeSetPageSize(p->pDest,sqlite3BtreeGetPageSize(p->pSrc),-1,0);
-  return rc;
-}
-
-/*
-** Check that there is no open read-transaction on the b-tree passed as the
-** second argument. If there is not, return SQLITE_OK. Otherwise, if there
-** is an open read-transaction, return SQLITE_ERROR and leave an error 
-** message in database handle db.
-*/
-static int checkReadTransaction(sqlite3 *db, Btree *p){
-  if( sqlite3BtreeIsInReadTrans(p) ){
-    sqlite3ErrorWithMsg(db, SQLITE_ERROR, "destination database is in use");
-    return SQLITE_ERROR;
-  }
-  return SQLITE_OK;
-}
-
-/*
 ** Create an sqlite3_backup process to copy the contents of zSrcDb from
 ** connection handle pSrcDb to zDestDb in pDestDb. If successful, return
 ** a pointer to the new sqlite3_backup object.
 **
 ** If an error occurs, NULL is returned and an error code and error message
 ** stored in database handle pDestDb.
