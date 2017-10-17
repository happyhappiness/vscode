     sqlite3_free(zCreate);
     if( rc!=SQLITE_OK ){
       return rc;
     }
   }
 
-  appStmt[0] = &pRtree->pReadNode;
-  appStmt[1] = &pRtree->pWriteNode;
-  appStmt[2] = &pRtree->pDeleteNode;
-  appStmt[3] = &pRtree->pReadRowid;
-  appStmt[4] = &pRtree->pWriteRowid;
-  appStmt[5] = &pRtree->pDeleteRowid;
-  appStmt[6] = &pRtree->pReadParent;
-  appStmt[7] = &pRtree->pWriteParent;
-  appStmt[8] = &pRtree->pDeleteParent;
+  appStmt[0] = &pRtree->pWriteNode;
+  appStmt[1] = &pRtree->pDeleteNode;
+  appStmt[2] = &pRtree->pReadRowid;
+  appStmt[3] = &pRtree->pWriteRowid;
+  appStmt[4] = &pRtree->pDeleteRowid;
+  appStmt[5] = &pRtree->pReadParent;
+  appStmt[6] = &pRtree->pWriteParent;
+  appStmt[7] = &pRtree->pDeleteParent;
 
+  rc = rtreeQueryStat1(db, pRtree);
   for(i=0; i<N_STATEMENT && rc==SQLITE_OK; i++){
     char *zSql = sqlite3_mprintf(azSql[i], zDb, zPrefix);
     if( zSql ){
-      rc = sqlite3_prepare_v2(db, zSql, -1, appStmt[i], 0); 
+      rc = sqlite3_prepare_v3(db, zSql, -1, SQLITE_PREPARE_PERSISTENT,
+                              appStmt[i], 0); 
     }else{
       rc = SQLITE_NOMEM;
     }
     sqlite3_free(zSql);
   }
 
   return rc;
 }
 
 /*
-** This routine queries database handle db for the page-size used by
-** database zDb. If successful, the page-size in bytes is written to
-** *piPageSize and SQLITE_OK returned. Otherwise, and an SQLite error 
-** code is returned.
+** The second argument to this function contains the text of an SQL statement
+** that returns a single integer value. The statement is compiled and executed
+** using database connection db. If successful, the integer value returned
+** is written to *piVal and SQLITE_OK returned. Otherwise, an SQLite error
+** code is returned and the value of *piVal after returning is not defined.
 */
-static int getPageSize(sqlite3 *db, const char *zDb, int *piPageSize){
+static int getIntFromStmt(sqlite3 *db, const char *zSql, int *piVal){
   int rc = SQLITE_NOMEM;
-  char *zSql;
-  sqlite3_stmt *pStmt = 0;
-
-  zSql = sqlite3_mprintf("PRAGMA %Q.page_size", zDb);
-  if( !zSql ){
-    return SQLITE_NOMEM;
+  if( zSql ){
+    sqlite3_stmt *pStmt = 0;
+    rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
+    if( rc==SQLITE_OK ){
+      if( SQLITE_ROW==sqlite3_step(pStmt) ){
+        *piVal = sqlite3_column_int(pStmt, 0);
+      }
+      rc = sqlite3_finalize(pStmt);
+    }
   }
+  return rc;
+}
 
-  rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
-  sqlite3_free(zSql);
-  if( rc!=SQLITE_OK ){
-    return rc;
+/*
+** This function is called from within the xConnect() or xCreate() method to
+** determine the node-size used by the rtree table being created or connected
+** to. If successful, pRtree->iNodeSize is populated and SQLITE_OK returned.
+** Otherwise, an SQLite error code is returned.
+**
+** If this function is being called as part of an xConnect(), then the rtree
+** table already exists. In this case the node-size is determined by inspecting
+** the root node of the tree.
+**
+** Otherwise, for an xCreate(), use 64 bytes less than the database page-size. 
+** This ensures that each node is stored on a single database page. If the 
+** database page-size is so large that more than RTREE_MAXCELLS entries 
+** would fit in a single node, use a smaller node-size.
+*/
+static int getNodeSize(
+  sqlite3 *db,                    /* Database handle */
+  Rtree *pRtree,                  /* Rtree handle */
+  int isCreate,                   /* True for xCreate, false for xConnect */
+  char **pzErr                    /* OUT: Error message, if any */
+){
+  int rc;
+  char *zSql;
+  if( isCreate ){
+    int iPageSize = 0;
+    zSql = sqlite3_mprintf("PRAGMA %Q.page_size", pRtree->zDb);
+    rc = getIntFromStmt(db, zSql, &iPageSize);
+    if( rc==SQLITE_OK ){
+      pRtree->iNodeSize = iPageSize-64;
+      if( (4+pRtree->nBytesPerCell*RTREE_MAXCELLS)<pRtree->iNodeSize ){
+        pRtree->iNodeSize = 4+pRtree->nBytesPerCell*RTREE_MAXCELLS;
+      }
+    }else{
+      *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(db));
+    }
+  }else{
+    zSql = sqlite3_mprintf(
+        "SELECT length(data) FROM '%q'.'%q_node' WHERE nodeno = 1",
+        pRtree->zDb, pRtree->zName
+    );
+    rc = getIntFromStmt(db, zSql, &pRtree->iNodeSize);
+    if( rc!=SQLITE_OK ){
+      *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(db));
+    }else if( pRtree->iNodeSize<(512-64) ){
+      rc = SQLITE_CORRUPT_VTAB;
+      *pzErr = sqlite3_mprintf("undersize RTree blobs in \"%q_node\"",
+                               pRtree->zName);
+    }
   }
 
-  if( SQLITE_ROW==sqlite3_step(pStmt) ){
-    *piPageSize = sqlite3_column_int(pStmt, 0);
-  }
-  return sqlite3_finalize(pStmt);
+  sqlite3_free(zSql);
+  return rc;
 }
 
 /* 
 ** This function is the implementation of both the xConnect and xCreate
 ** methods of the r-tree virtual table.
 **
