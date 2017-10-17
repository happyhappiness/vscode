   sqlite3 *db, 
   Table *pTab,
   Module *pMod,
   int (*xConstruct)(sqlite3*,void*,int,const char*const*,sqlite3_vtab**,char**),
   char **pzErr
 ){
-  VtabCtx sCtx;
-  VTable *pVTable;
   int rc;
+  int rc2;
+  sqlite3_vtab *pVtab = 0;
   const char *const*azArg = (const char *const*)pTab->azModuleArg;
   int nArg = pTab->nModuleArg;
   char *zErr = 0;
-  char *zModuleName;
-  int iDb;
-  VtabCtx *pCtx;
-
-  /* Check that the virtual-table is not already being initialized */
-  for(pCtx=db->pVtabCtx; pCtx; pCtx=pCtx->pPrior){
-    if( pCtx->pTab==pTab ){
-      *pzErr = sqlite3MPrintf(db, 
-          "vtable constructor called recursively: %s", pTab->zName
-      );
-      return SQLITE_LOCKED;
-    }
-  }
+  char *zModuleName = sqlite3MPrintf(db, "%s", pTab->zName);
 
-  zModuleName = sqlite3DbStrDup(db, pTab->zName);
   if( !zModuleName ){
-    return SQLITE_NOMEM_BKPT;
+    return SQLITE_NOMEM;
   }
 
-  pVTable = sqlite3MallocZero(sizeof(VTable));
-  if( !pVTable ){
-    sqlite3OomFault(db);
-    sqlite3DbFree(db, zModuleName);
-    return SQLITE_NOMEM_BKPT;
-  }
-  pVTable->db = db;
-  pVTable->pMod = pMod;
-
-  iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
-  pTab->azModuleArg[1] = db->aDb[iDb].zDbSName;
-
-  /* Invoke the virtual table constructor */
-  assert( &db->pVtabCtx );
+  assert( !db->pVTab );
   assert( xConstruct );
-  sCtx.pTab = pTab;
-  sCtx.pVTable = pVTable;
-  sCtx.pPrior = db->pVtabCtx;
-  sCtx.bDeclared = 0;
-  db->pVtabCtx = &sCtx;
-  rc = xConstruct(db, pMod->pAux, nArg, azArg, &pVTable->pVtab, &zErr);
-  db->pVtabCtx = sCtx.pPrior;
-  if( rc==SQLITE_NOMEM ) sqlite3OomFault(db);
-  assert( sCtx.pTab==pTab );
+
+  db->pVTab = pTab;
+  rc = sqlite3SafetyOff(db);
+  assert( rc==SQLITE_OK );
+  rc = xConstruct(db, pMod->pAux, nArg, azArg, &pVtab, &zErr);
+  rc2 = sqlite3SafetyOn(db);
+  if( rc==SQLITE_NOMEM ) db->mallocFailed = 1;
+  /* Justification of ALWAYS():  A correct vtab constructor must allocate
+  ** the sqlite3_vtab object if successful. */
+  if( rc==SQLITE_OK && ALWAYS(pVtab) ){
+    pVtab->pModule = pMod->pModule;
+    pVtab->nRef = 1;
+    pTab->pVtab = pVtab;
+  }
 
   if( SQLITE_OK!=rc ){
     if( zErr==0 ){
       *pzErr = sqlite3MPrintf(db, "vtable constructor failed: %s", zModuleName);
     }else {
       *pzErr = sqlite3MPrintf(db, "%s", zErr);
-      sqlite3_free(zErr);
+      sqlite3DbFree(db, zErr);
     }
-    sqlite3DbFree(db, pVTable);
-  }else if( ALWAYS(pVTable->pVtab) ){
-    /* Justification of ALWAYS():  A correct vtab constructor must allocate
-    ** the sqlite3_vtab object if successful.  */
-    memset(pVTable->pVtab, 0, sizeof(pVTable->pVtab[0]));
-    pVTable->pVtab->pModule = pMod->pModule;
-    pVTable->nRef = 1;
-    if( sCtx.bDeclared==0 ){
-      const char *zFormat = "vtable constructor did not declare schema: %s";
-      *pzErr = sqlite3MPrintf(db, zFormat, pTab->zName);
-      sqlite3VtabUnlock(pVTable);
-      rc = SQLITE_ERROR;
-    }else{
-      int iCol;
-      u8 oooHidden = 0;
-      /* If everything went according to plan, link the new VTable structure
-      ** into the linked list headed by pTab->pVTable. Then loop through the 
-      ** columns of the table to see if any of them contain the token "hidden".
-      ** If so, set the Column COLFLAG_HIDDEN flag and remove the token from
-      ** the type string.  */
-      pVTable->pNext = pTab->pVTable;
-      pTab->pVTable = pVTable;
-
-      for(iCol=0; iCol<pTab->nCol; iCol++){
-        char *zType = sqlite3ColumnType(&pTab->aCol[iCol], "");
-        int nType;
-        int i = 0;
-        nType = sqlite3Strlen30(zType);
+  }else if( db->pVTab ){
+    const char *zFormat = "vtable constructor did not declare schema: %s";
+    *pzErr = sqlite3MPrintf(db, zFormat, pTab->zName);
+    rc = SQLITE_ERROR;
+  } 
+  if( rc==SQLITE_OK ){
+    rc = rc2;
+  }
+  db->pVTab = 0;
+  sqlite3DbFree(db, zModuleName);
+
+  /* If everything went according to plan, loop through the columns
+  ** of the table to see if any of them contain the token "hidden".
+  ** If so, set the Column.isHidden flag and remove the token from
+  ** the type string.
+  */
+  if( rc==SQLITE_OK ){
+    int iCol;
+    for(iCol=0; iCol<pTab->nCol; iCol++){
+      char *zType = pTab->aCol[iCol].zType;
+      int nType;
+      int i = 0;
+      if( !zType ) continue;
+      nType = sqlite3Strlen30(zType);
+      if( sqlite3StrNICmp("hidden", zType, 6) || (zType[6] && zType[6]!=' ') ){
         for(i=0; i<nType; i++){
-          if( 0==sqlite3StrNICmp("hidden", &zType[i], 6)
-           && (i==0 || zType[i-1]==' ')
-           && (zType[i+6]=='\0' || zType[i+6]==' ')
+          if( (0==sqlite3StrNICmp(" hidden", &zType[i], 7))
+           && (zType[i+7]=='\0' || zType[i+7]==' ')
           ){
+            i++;
             break;
           }
         }
-        if( i<nType ){
-          int j;
-          int nDel = 6 + (zType[i+6] ? 1 : 0);
-          for(j=i; (j+nDel)<=nType; j++){
-            zType[j] = zType[j+nDel];
-          }
-          if( zType[i]=='\0' && i>0 ){
-            assert(zType[i-1]==' ');
-            zType[i-1] = '\0';
-          }
-          pTab->aCol[iCol].colFlags |= COLFLAG_HIDDEN;
-          oooHidden = TF_OOOHidden;
-        }else{
-          pTab->tabFlags |= oooHidden;
+      }
+      if( i<nType ){
+        int j;
+        int nDel = 6 + (zType[i+6] ? 1 : 0);
+        for(j=i; (j+nDel)<=nType; j++){
+          zType[j] = zType[j+nDel];
+        }
+        if( zType[i]=='\0' && i>0 ){
+          assert(zType[i-1]==' ');
+          zType[i-1] = '\0';
         }
+        pTab->aCol[iCol].isHidden = 1;
       }
     }
   }
-
-  sqlite3DbFree(db, zModuleName);
   return rc;
 }
 
 /*
 ** This function is invoked by the parser to call the xConnect() method
 ** of the virtual table pTab. If an error occurs, an error code is returned 
 ** and an error left in pParse.
 **
 ** This call is a no-op if table pTab is not a virtual table.
 */
 int sqlite3VtabCallConnect(Parse *pParse, Table *pTab){
-  sqlite3 *db = pParse->db;
-  const char *zMod;
   Module *pMod;
-  int rc;
+  int rc = SQLITE_OK;
 
   assert( pTab );
-  if( !IsVirtual(pTab) || sqlite3GetVTable(db, pTab) ){
+  if( (pTab->tabFlags & TF_Virtual)==0 || pTab->pVtab ){
     return SQLITE_OK;
   }
 
-  /* Locate the required virtual table module */
-  zMod = pTab->azModuleArg[0];
-  pMod = (Module*)sqlite3HashFind(&db->aModule, zMod);
-
+  pMod = pTab->pMod;
   if( !pMod ){
     const char *zModule = pTab->azModuleArg[0];
     sqlite3ErrorMsg(pParse, "no such module: %s", zModule);
     rc = SQLITE_ERROR;
-  }else{
+  } else {
     char *zErr = 0;
+    sqlite3 *db = pParse->db;
     rc = vtabCallConstructor(db, pTab, pMod, pMod->pModule->xConnect, &zErr);
     if( rc!=SQLITE_OK ){
       sqlite3ErrorMsg(pParse, "%s", zErr);
-      pParse->rc = rc;
     }
     sqlite3DbFree(db, zErr);
   }
 
   return rc;
 }
