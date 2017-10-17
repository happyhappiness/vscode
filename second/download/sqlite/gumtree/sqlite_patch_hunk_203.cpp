     zRight = sqlite3MPrintf(db, "-%T", pValue);
   }else{
     zRight = sqlite3NameFromToken(db, pValue);
   }
 
   assert( pId2 );
-  zDb = pId2->n>0 ? pDb->zName : 0;
+  zDb = pId2->n>0 ? pDb->zDbSName : 0;
   if( sqlite3AuthCheck(pParse, SQLITE_PRAGMA, zLeft, zRight, zDb) ){
     goto pragma_out;
   }
- 
-#ifndef SQLITE_OMIT_PAGER_PRAGMAS
+
+  /* Send an SQLITE_FCNTL_PRAGMA file-control to the underlying VFS
+  ** connection.  If it returns SQLITE_OK, then assume that the VFS
+  ** handled the pragma and generate a no-op prepared statement.
+  **
+  ** IMPLEMENTATION-OF: R-12238-55120 Whenever a PRAGMA statement is parsed,
+  ** an SQLITE_FCNTL_PRAGMA file control is sent to the open sqlite3_file
+  ** object corresponding to the database file to which the pragma
+  ** statement refers.
+  **
+  ** IMPLEMENTATION-OF: R-29875-31678 The argument to the SQLITE_FCNTL_PRAGMA
+  ** file control is an array of pointers to strings (char**) in which the
+  ** second element of the array is the name of the pragma and the third
+  ** element is the argument to the pragma or NULL if the pragma has no
+  ** argument.
+  */
+  aFcntl[0] = 0;
+  aFcntl[1] = zLeft;
+  aFcntl[2] = zRight;
+  aFcntl[3] = 0;
+  db->busyHandler.nBusy = 0;
+  rc = sqlite3_file_control(db, zDb, SQLITE_FCNTL_PRAGMA, (void*)aFcntl);
+  if( rc==SQLITE_OK ){
+    sqlite3VdbeSetNumCols(v, 1);
+    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, aFcntl[0], SQLITE_TRANSIENT);
+    returnSingleText(v, aFcntl[0]);
+    sqlite3_free(aFcntl[0]);
+    goto pragma_out;
+  }
+  if( rc!=SQLITE_NOTFOUND ){
+    if( aFcntl[0] ){
+      sqlite3ErrorMsg(pParse, "%s", aFcntl[0]);
+      sqlite3_free(aFcntl[0]);
+    }
+    pParse->nErr++;
+    pParse->rc = rc;
+    goto pragma_out;
+  }
+
+  /* Locate the pragma in the lookup table */
+  pPragma = pragmaLocate(zLeft);
+  if( pPragma==0 ) goto pragma_out;
+
+  /* Make sure the database schema is loaded if the pragma requires that */
+  if( (pPragma->mPragFlg & PragFlg_NeedSchema)!=0 ){
+    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
+  }
+
+  /* Register the result column names for pragmas that return results */
+  if( (pPragma->mPragFlg & PragFlg_NoColumns)==0 
+   && ((pPragma->mPragFlg & PragFlg_NoColumns1)==0 || zRight==0)
+  ){
+    setPragmaResultColumnNames(v, pPragma);
+  }
+
+  /* Jump to the appropriate pragma handler */
+  switch( pPragma->ePragTyp ){
+  
+#if !defined(SQLITE_OMIT_PAGER_PRAGMAS) && !defined(SQLITE_OMIT_DEPRECATED)
   /*
-  **  PRAGMA [database.]default_cache_size
-  **  PRAGMA [database.]default_cache_size=N
+  **  PRAGMA [schema.]default_cache_size
+  **  PRAGMA [schema.]default_cache_size=N
   **
   ** The first form reports the current persistent setting for the
   ** page cache size.  The value returned is the maximum number of
   ** pages in the page cache.  The second form sets both the current
   ** page cache size value and the persistent page cache size value
   ** stored in the database file.
   **
-  ** The default cache size is stored in meta-value 2 of page 1 of the
-  ** database file.  The cache size is actually the absolute value of
-  ** this memory location.  The sign of meta-value 2 determines the
-  ** synchronous setting.  A negative value means synchronous is off
-  ** and a positive value means synchronous is on.
+  ** Older versions of SQLite would set the default cache size to a
+  ** negative number to indicate synchronous=OFF.  These days, synchronous
+  ** is always on by default regardless of the sign of the default cache
+  ** size.  But continue to take the absolute value of the default cache
+  ** size of historical compatibility.
   */
-  if( sqlite3StrICmp(zLeft,"default_cache_size")==0 ){
+  case PragTyp_DEFAULT_CACHE_SIZE: {
+    static const int iLn = VDBE_OFFSET_LINENO(2);
     static const VdbeOpList getCacheSize[] = {
-      { OP_ReadCookie,  0, 1,        BTREE_DEFAULT_CACHE_SIZE},  /* 0 */
-      { OP_IfPos,       1, 6,        0},
+      { OP_Transaction, 0, 0,        0},                         /* 0 */
+      { OP_ReadCookie,  0, 1,        BTREE_DEFAULT_CACHE_SIZE},  /* 1 */
+      { OP_IfPos,       1, 8,        0},
       { OP_Integer,     0, 2,        0},
       { OP_Subtract,    1, 2,        1},
-      { OP_IfPos,       1, 6,        0},
-      { OP_Integer,     0, 1,        0},  /* 5 */
+      { OP_IfPos,       1, 8,        0},
+      { OP_Integer,     0, 1,        0},                         /* 6 */
+      { OP_Noop,        0, 0,        0},
       { OP_ResultRow,   1, 1,        0},
     };
-    int addr;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
+    VdbeOp *aOp;
     sqlite3VdbeUsesBtree(v, iDb);
     if( !zRight ){
-      sqlite3VdbeSetNumCols(v, 1);
-      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "cache_size", SQLITE_STATIC);
       pParse->nMem += 2;
-      addr = sqlite3VdbeAddOpList(v, ArraySize(getCacheSize), getCacheSize);
-      sqlite3VdbeChangeP1(v, addr, iDb);
-      sqlite3VdbeChangeP1(v, addr+5, SQLITE_DEFAULT_CACHE_SIZE);
+      sqlite3VdbeVerifyNoMallocRequired(v, ArraySize(getCacheSize));
+      aOp = sqlite3VdbeAddOpList(v, ArraySize(getCacheSize), getCacheSize, iLn);
+      if( ONLY_IF_REALLOC_STRESS(aOp==0) ) break;
+      aOp[0].p1 = iDb;
+      aOp[1].p1 = iDb;
+      aOp[6].p1 = SQLITE_DEFAULT_CACHE_SIZE;
     }else{
-      int size = atoi(zRight);
-      if( size<0 ) size = -size;
+      int size = sqlite3AbsInt32(sqlite3Atoi(zRight));
       sqlite3BeginWriteOperation(pParse, 0, iDb);
-      sqlite3VdbeAddOp2(v, OP_Integer, size, 1);
-      sqlite3VdbeAddOp3(v, OP_ReadCookie, iDb, 2, BTREE_DEFAULT_CACHE_SIZE);
-      addr = sqlite3VdbeAddOp2(v, OP_IfPos, 2, 0);
-      sqlite3VdbeAddOp2(v, OP_Integer, -size, 1);
-      sqlite3VdbeJumpHere(v, addr);
-      sqlite3VdbeAddOp3(v, OP_SetCookie, iDb, BTREE_DEFAULT_CACHE_SIZE, 1);
+      sqlite3VdbeAddOp3(v, OP_SetCookie, iDb, BTREE_DEFAULT_CACHE_SIZE, size);
+      assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
       pDb->pSchema->cache_size = size;
       sqlite3BtreeSetCacheSize(pDb->pBt, pDb->pSchema->cache_size);
     }
-  }else
+    break;
+  }
+#endif /* !SQLITE_OMIT_PAGER_PRAGMAS && !SQLITE_OMIT_DEPRECATED */
 
+#if !defined(SQLITE_OMIT_PAGER_PRAGMAS)
   /*
-  **  PRAGMA [database.]page_size
-  **  PRAGMA [database.]page_size=N
+  **  PRAGMA [schema.]page_size
+  **  PRAGMA [schema.]page_size=N
   **
   ** The first form reports the current setting for the
   ** database page size in bytes.  The second form sets the
   ** database page size value.  The value can only be set if
   ** the database has not yet been created.
   */
-  if( sqlite3StrICmp(zLeft,"page_size")==0 ){
+  case PragTyp_PAGE_SIZE: {
     Btree *pBt = pDb->pBt;
     assert( pBt!=0 );
     if( !zRight ){
       int size = ALWAYS(pBt) ? sqlite3BtreeGetPageSize(pBt) : 0;
-      returnSingleInt(pParse, "page_size", size);
+      returnSingleInt(v, size);
     }else{
       /* Malloc may fail when setting the page-size, as there is an internal
       ** buffer that the pager module resizes using sqlite3_realloc().
       */
-      db->nextPagesize = atoi(zRight);
-      if( SQLITE_NOMEM==sqlite3BtreeSetPageSize(pBt, db->nextPagesize, -1, 0) ){
-        db->mallocFailed = 1;
+      db->nextPagesize = sqlite3Atoi(zRight);
+      if( SQLITE_NOMEM==sqlite3BtreeSetPageSize(pBt, db->nextPagesize,-1,0) ){
+        sqlite3OomFault(db);
       }
     }
-  }else
+    break;
+  }
 
   /*
-  **  PRAGMA [database.]max_page_count
-  **  PRAGMA [database.]max_page_count=N
+  **  PRAGMA [schema.]secure_delete
+  **  PRAGMA [schema.]secure_delete=ON/OFF/FAST
   **
   ** The first form reports the current setting for the
-  ** maximum number of pages in the database file.  The 
-  ** second form attempts to change this setting.  Both
-  ** forms return the current setting.
+  ** secure_delete flag.  The second form changes the secure_delete
+  ** flag setting and reports the new value.
   */
-  if( sqlite3StrICmp(zLeft,"max_page_count")==0 ){
+  case PragTyp_SECURE_DELETE: {
     Btree *pBt = pDb->pBt;
-    int newMax = 0;
+    int b = -1;
     assert( pBt!=0 );
     if( zRight ){
-      newMax = atoi(zRight);
+      if( sqlite3_stricmp(zRight, "fast")==0 ){
+        b = 2;
+      }else{
+        b = sqlite3GetBoolean(zRight, 0);
+      }
     }
-    if( ALWAYS(pBt) ){
-      newMax = sqlite3BtreeMaxPageCount(pBt, newMax);
+    if( pId2->n==0 && b>=0 ){
+      int ii;
+      for(ii=0; ii<db->nDb; ii++){
+        sqlite3BtreeSecureDelete(db->aDb[ii].pBt, b);
+      }
     }
-    returnSingleInt(pParse, "max_page_count", newMax);
-  }else
+    b = sqlite3BtreeSecureDelete(pBt, b);
+    returnSingleInt(v, b);
+    break;
+  }
 
   /*
-  **  PRAGMA [database.]page_count
+  **  PRAGMA [schema.]max_page_count
+  **  PRAGMA [schema.]max_page_count=N
+  **
+  ** The first form reports the current setting for the
+  ** maximum number of pages in the database file.  The 
+  ** second form attempts to change this setting.  Both
+  ** forms return the current setting.
+  **
+  ** The absolute value of N is used.  This is undocumented and might
+  ** change.  The only purpose is to provide an easy way to test
+  ** the sqlite3AbsInt32() function.
+  **
+  **  PRAGMA [schema.]page_count
   **
   ** Return the number of pages in the specified database.
   */
-  if( sqlite3StrICmp(zLeft,"page_count")==0 ){
+  case PragTyp_PAGE_COUNT: {
     int iReg;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
     sqlite3CodeVerifySchema(pParse, iDb);
     iReg = ++pParse->nMem;
-    sqlite3VdbeAddOp2(v, OP_Pagecount, iDb, iReg);
+    if( sqlite3Tolower(zLeft[0])=='p' ){
+      sqlite3VdbeAddOp2(v, OP_Pagecount, iDb, iReg);
+    }else{
+      sqlite3VdbeAddOp3(v, OP_MaxPgcnt, iDb, iReg, 
+                        sqlite3AbsInt32(sqlite3Atoi(zRight)));
+    }
     sqlite3VdbeAddOp2(v, OP_ResultRow, iReg, 1);
-    sqlite3VdbeSetNumCols(v, 1);
-    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "page_count", SQLITE_STATIC);
-  }else
+    break;
+  }
 
   /*
-  **  PRAGMA [database.]locking_mode
-  **  PRAGMA [database.]locking_mode = (normal|exclusive)
+  **  PRAGMA [schema.]locking_mode
+  **  PRAGMA [schema.]locking_mode = (normal|exclusive)
   */
-  if( sqlite3StrICmp(zLeft,"locking_mode")==0 ){
+  case PragTyp_LOCKING_MODE: {
     const char *zRet = "normal";
     int eMode = getLockingMode(zRight);
 
     if( pId2->n==0 && eMode==PAGER_LOCKINGMODE_QUERY ){
       /* Simple "PRAGMA locking_mode;" statement. This is a query for
       ** the current default locking mode (which may be different to
