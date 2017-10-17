     "ALTER TABLE %Q.'%q_rowid'  RENAME TO \"%w_rowid\";"
     , pRtree->zDb, pRtree->zName, zNewName 
     , pRtree->zDb, pRtree->zName, zNewName 
     , pRtree->zDb, pRtree->zName, zNewName
   );
   if( zSql ){
+    nodeBlobReset(pRtree);
     rc = sqlite3_exec(pRtree->db, zSql, 0, 0, 0);
     sqlite3_free(zSql);
   }
   return rc;
 }
 
+/*
+** The xSavepoint method.
+**
+** This module does not need to do anything to support savepoints. However,
+** it uses this hook to close any open blob handle. This is done because a 
+** DROP TABLE command - which fortunately always opens a savepoint - cannot 
+** succeed if there are any open blob handles. i.e. if the blob handle were
+** not closed here, the following would fail:
+**
+**   BEGIN;
+**     INSERT INTO rtree...
+**     DROP TABLE <tablename>;    -- Would fail with SQLITE_LOCKED
+**   COMMIT;
+*/
+static int rtreeSavepoint(sqlite3_vtab *pVtab, int iSavepoint){
+  Rtree *pRtree = (Rtree *)pVtab;
+  int iwt = pRtree->inWrTrans;
+  UNUSED_PARAMETER(iSavepoint);
+  pRtree->inWrTrans = 0;
+  nodeBlobReset(pRtree);
+  pRtree->inWrTrans = iwt;
+  return SQLITE_OK;
+}
+
+/*
+** This function populates the pRtree->nRowEst variable with an estimate
+** of the number of rows in the virtual table. If possible, this is based
+** on sqlite_stat1 data. Otherwise, use RTREE_DEFAULT_ROWEST.
+*/
+static int rtreeQueryStat1(sqlite3 *db, Rtree *pRtree){
+  const char *zFmt = "SELECT stat FROM %Q.sqlite_stat1 WHERE tbl = '%q_rowid'";
+  char *zSql;
+  sqlite3_stmt *p;
+  int rc;
+  i64 nRow = 0;
+
+  rc = sqlite3_table_column_metadata(
+      db, pRtree->zDb, "sqlite_stat1",0,0,0,0,0,0
+  );
+  if( rc!=SQLITE_OK ){
+    pRtree->nRowEst = RTREE_DEFAULT_ROWEST;
+    return rc==SQLITE_ERROR ? SQLITE_OK : rc;
+  }
+  zSql = sqlite3_mprintf(zFmt, pRtree->zDb, pRtree->zName);
+  if( zSql==0 ){
+    rc = SQLITE_NOMEM;
+  }else{
+    rc = sqlite3_prepare_v2(db, zSql, -1, &p, 0);
+    if( rc==SQLITE_OK ){
+      if( sqlite3_step(p)==SQLITE_ROW ) nRow = sqlite3_column_int64(p, 0);
+      rc = sqlite3_finalize(p);
+    }else if( rc!=SQLITE_NOMEM ){
+      rc = SQLITE_OK;
+    }
+
+    if( rc==SQLITE_OK ){
+      if( nRow==0 ){
+        pRtree->nRowEst = RTREE_DEFAULT_ROWEST;
+      }else{
+        pRtree->nRowEst = MAX(nRow, RTREE_MIN_ROWEST);
+      }
+    }
+    sqlite3_free(zSql);
+  }
+
+  return rc;
+}
+
 static sqlite3_module rtreeModule = {
-  0,                         /* iVersion */
+  2,                          /* iVersion */
   rtreeCreate,                /* xCreate - create a table */
   rtreeConnect,               /* xConnect - connect to an existing table */
   rtreeBestIndex,             /* xBestIndex - Determine search strategy */
   rtreeDisconnect,            /* xDisconnect - Disconnect from a table */
   rtreeDestroy,               /* xDestroy - Drop a table */
   rtreeOpen,                  /* xOpen - open a cursor */
