     }
     sqlite3DbFree(db, zErr);
   }
 
   return rc;
 }
+
 /*
-** Grow the db->aVTrans[] array so that there is room for at least one
-** more v-table. Return SQLITE_NOMEM if a malloc fails, or SQLITE_OK otherwise.
+** Add the virtual table pVtab to the array sqlite3.aVTrans[].
 */
-static int growVTrans(sqlite3 *db){
+static int addToVTrans(sqlite3 *db, sqlite3_vtab *pVtab){
   const int ARRAY_INCR = 5;
 
   /* Grow the sqlite3.aVTrans array if required */
   if( (db->nVTrans%ARRAY_INCR)==0 ){
-    VTable **aVTrans;
+    sqlite3_vtab **aVTrans;
     int nBytes = sizeof(sqlite3_vtab *) * (db->nVTrans + ARRAY_INCR);
     aVTrans = sqlite3DbRealloc(db, (void *)db->aVTrans, nBytes);
     if( !aVTrans ){
-      return SQLITE_NOMEM_BKPT;
+      return SQLITE_NOMEM;
     }
     memset(&aVTrans[db->nVTrans], 0, sizeof(sqlite3_vtab *)*ARRAY_INCR);
     db->aVTrans = aVTrans;
   }
 
-  return SQLITE_OK;
-}
-
-/*
-** Add the virtual table pVTab to the array sqlite3.aVTrans[]. Space should
-** have already been reserved using growVTrans().
-*/
-static void addToVTrans(sqlite3 *db, VTable *pVTab){
   /* Add pVtab to the end of sqlite3.aVTrans */
-  db->aVTrans[db->nVTrans++] = pVTab;
-  sqlite3VtabLock(pVTab);
+  db->aVTrans[db->nVTrans++] = pVtab;
+  sqlite3VtabLock(pVtab);
+  return SQLITE_OK;
 }
 
 /*
 ** This function is invoked by the vdbe to call the xCreate method
 ** of the virtual table named zTab in database iDb. 
 **
-** If an error occurs, *pzErr is set to point to an English language
+** If an error occurs, *pzErr is set to point an an English language
 ** description of the error and an SQLITE_XXX error code is returned.
 ** In this case the caller must call sqlite3DbFree(db, ) on *pzErr.
 */
 int sqlite3VtabCallCreate(sqlite3 *db, int iDb, const char *zTab, char **pzErr){
   int rc = SQLITE_OK;
   Table *pTab;
   Module *pMod;
-  const char *zMod;
-
-  pTab = sqlite3FindTable(db, zTab, db->aDb[iDb].zDbSName);
-  assert( pTab && IsVirtual(pTab) && !pTab->pVTable );
+  const char *zModule;
 
-  /* Locate the required virtual table module */
-  zMod = pTab->azModuleArg[0];
-  pMod = (Module*)sqlite3HashFind(&db->aModule, zMod);
+  pTab = sqlite3FindTable(db, zTab, db->aDb[iDb].zName);
+  assert(pTab && (pTab->tabFlags & TF_Virtual)!=0 && !pTab->pVtab);
+  pMod = pTab->pMod;
+  zModule = pTab->azModuleArg[0];
 
   /* If the module has been registered and includes a Create method, 
   ** invoke it now. If the module has not been registered, return an 
   ** error. Otherwise, do nothing.
   */
-  if( pMod==0 || pMod->pModule->xCreate==0 || pMod->pModule->xDestroy==0 ){
-    *pzErr = sqlite3MPrintf(db, "no such module: %s", zMod);
+  if( !pMod ){
+    *pzErr = sqlite3MPrintf(db, "no such module: %s", zModule);
     rc = SQLITE_ERROR;
   }else{
     rc = vtabCallConstructor(db, pTab, pMod, pMod->pModule->xCreate, pzErr);
   }
 
   /* Justification of ALWAYS():  The xConstructor method is required to
   ** create a valid sqlite3_vtab if it returns SQLITE_OK. */
-  if( rc==SQLITE_OK && ALWAYS(sqlite3GetVTable(db, pTab)) ){
-    rc = growVTrans(db);
-    if( rc==SQLITE_OK ){
-      addToVTrans(db, sqlite3GetVTable(db, pTab));
-    }
+  if( rc==SQLITE_OK && ALWAYS(pTab->pVtab) ){
+      rc = addToVTrans(db, pTab->pVtab);
   }
 
   return rc;
 }
 
 /*
 ** This function is used to set the schema of a virtual table.  It is only
 ** valid to call this function from within the xCreate() or xConnect() of a
 ** virtual table module.
 */
 int sqlite3_declare_vtab(sqlite3 *db, const char *zCreateTable){
-  VtabCtx *pCtx;
+  Parse *pParse;
+
   int rc = SQLITE_OK;
   Table *pTab;
   char *zErr = 0;
-  Parse sParse;
 
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !sqlite3SafetyCheckOk(db) || zCreateTable==0 ){
-    return SQLITE_MISUSE_BKPT;
-  }
-#endif
   sqlite3_mutex_enter(db->mutex);
-  pCtx = db->pVtabCtx;
-  if( !pCtx || pCtx->bDeclared ){
-    sqlite3Error(db, SQLITE_MISUSE);
+  pTab = db->pVTab;
+  if( !pTab ){
+    sqlite3Error(db, SQLITE_MISUSE, 0);
     sqlite3_mutex_leave(db->mutex);
-    return SQLITE_MISUSE_BKPT;
+    return SQLITE_MISUSE;
   }
-  pTab = pCtx->pTab;
-  assert( IsVirtual(pTab) );
+  assert((pTab->tabFlags & TF_Virtual)!=0 && pTab->nCol==0 && pTab->aCol==0);
 
-  memset(&sParse, 0, sizeof(sParse));
-  sParse.declareVtab = 1;
-  sParse.db = db;
-  sParse.nQueryLoop = 1;
-  if( SQLITE_OK==sqlite3RunParser(&sParse, zCreateTable, &zErr) 
-   && sParse.pNewTable
-   && !db->mallocFailed
-   && !sParse.pNewTable->pSelect
-   && !IsVirtual(sParse.pNewTable)
-  ){
-    if( !pTab->aCol ){
-      Table *pNew = sParse.pNewTable;
-      Index *pIdx;
-      pTab->aCol = pNew->aCol;
-      pTab->nCol = pNew->nCol;
-      pTab->tabFlags |= pNew->tabFlags & (TF_WithoutRowid|TF_NoVisibleRowid);
-      pNew->nCol = 0;
-      pNew->aCol = 0;
-      assert( pTab->pIndex==0 );
-      assert( HasRowid(pNew) || sqlite3PrimaryKeyIndex(pNew)!=0 );
-      if( !HasRowid(pNew)
-       && pCtx->pVTable->pMod->pModule->xUpdate!=0
-       && sqlite3PrimaryKeyIndex(pNew)->nKeyCol!=1
-      ){
-        /* WITHOUT ROWID virtual tables must either be read-only (xUpdate==0)
-        ** or else must have a single-column PRIMARY KEY */
-        rc = SQLITE_ERROR;
-      }
-      pIdx = pNew->pIndex;
-      if( pIdx ){
-        assert( pIdx->pNext==0 );
-        pTab->pIndex = pIdx;
-        pNew->pIndex = 0;
-        pIdx->pTable = pTab;
-      }
-    }
-    pCtx->bDeclared = 1;
+  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
+  if( pParse==0 ){
+    rc = SQLITE_NOMEM;
   }else{
-    sqlite3ErrorWithMsg(db, SQLITE_ERROR, (zErr ? "%s" : 0), zErr);
-    sqlite3DbFree(db, zErr);
-    rc = SQLITE_ERROR;
-  }
-  sParse.declareVtab = 0;
-
-  if( sParse.pVdbe ){
-    sqlite3VdbeFinalize(sParse.pVdbe);
+    pParse->declareVtab = 1;
+    pParse->db = db;
+  
+    if( 
+        SQLITE_OK == sqlite3RunParser(pParse, zCreateTable, &zErr) && 
+        pParse->pNewTable && 
+        !pParse->pNewTable->pSelect && 
+        (pParse->pNewTable->tabFlags & TF_Virtual)==0
+    ){
+      pTab->aCol = pParse->pNewTable->aCol;
+      pTab->nCol = pParse->pNewTable->nCol;
+      pParse->pNewTable->nCol = 0;
+      pParse->pNewTable->aCol = 0;
+      db->pVTab = 0;
+    } else {
+      sqlite3Error(db, SQLITE_ERROR, zErr);
+      sqlite3DbFree(db, zErr);
+      rc = SQLITE_ERROR;
+    }
+    pParse->declareVtab = 0;
+  
+    if( pParse->pVdbe ){
+      sqlite3VdbeFinalize(pParse->pVdbe);
+    }
+    sqlite3DeleteTable(pParse->pNewTable);
+    sqlite3StackFree(db, pParse);
   }
-  sqlite3DeleteTable(db, sParse.pNewTable);
-  sqlite3ParserReset(&sParse);
 
   assert( (rc&0xff)==rc );
   rc = sqlite3ApiExit(db, rc);
   sqlite3_mutex_leave(db->mutex);
   return rc;
 }
