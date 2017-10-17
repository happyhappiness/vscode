 /*
 ** Return the database associated with the Vdbe.
 */
 sqlite3 *sqlite3VdbeDb(Vdbe *v){
   return v->db;
 }
+
+/*
+** Return the SQLITE_PREPARE flags for a Vdbe.
+*/
+u8 sqlite3VdbePrepareFlags(Vdbe *v){
+  return v->prepFlags;
+}
+
+/*
+** Return a pointer to an sqlite3_value structure containing the value bound
+** parameter iVar of VM v. Except, if the value is an SQL NULL, return 
+** 0 instead. Unless it is NULL, apply affinity aff (one of the SQLITE_AFF_*
+** constants) to the value before returning it.
+**
+** The returned value must be freed by the caller using sqlite3ValueFree().
+*/
+sqlite3_value *sqlite3VdbeGetBoundValue(Vdbe *v, int iVar, u8 aff){
+  assert( iVar>0 );
+  if( v ){
+    Mem *pMem = &v->aVar[iVar-1];
+    assert( (v->db->flags & SQLITE_EnableQPSG)==0 );
+    if( 0==(pMem->flags & MEM_Null) ){
+      sqlite3_value *pRet = sqlite3ValueNew(v->db);
+      if( pRet ){
+        sqlite3VdbeMemCopy((Mem *)pRet, pMem);
+        sqlite3ValueApplyAffinity(pRet, aff, SQLITE_UTF8);
+      }
+      return pRet;
+    }
+  }
+  return 0;
+}
+
+/*
+** Configure SQL variable iVar so that binding a new value to it signals
+** to sqlite3_reoptimize() that re-preparing the statement may result
+** in a better query plan.
+*/
+void sqlite3VdbeSetVarmask(Vdbe *v, int iVar){
+  assert( iVar>0 );
+  assert( (v->db->flags & SQLITE_EnableQPSG)==0 );
+  if( iVar>=32 ){
+    v->expmask |= 0x80000000;
+  }else{
+    v->expmask |= ((u32)1 << (iVar-1));
+  }
+}
+
+/*
+** Cause a function to throw an error if it was call from OP_PureFunc
+** rather than OP_Function.
+**
+** OP_PureFunc means that the function must be deterministic, and should
+** throw an error if it is given inputs that would make it non-deterministic.
+** This routine is invoked by date/time functions that use non-deterministic
+** features such as 'now'.
+*/
+int sqlite3NotPureFunc(sqlite3_context *pCtx){
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( pCtx->pVdbe==0 ) return 1;
+#endif
+  if( pCtx->pVdbe->aOp[pCtx->iOp].opcode==OP_PureFunc ){
+    sqlite3_result_error(pCtx, 
+       "non-deterministic function in index expression or CHECK constraint",
+       -1);
+    return 0;
+  }
+  return 1;
+}
+
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+/*
+** Transfer error message text from an sqlite3_vtab.zErrMsg (text stored
+** in memory obtained from sqlite3_malloc) into a Vdbe.zErrMsg (text stored
+** in memory obtained from sqlite3DbMalloc).
+*/
+void sqlite3VtabImportErrmsg(Vdbe *p, sqlite3_vtab *pVtab){
+  if( pVtab->zErrMsg ){
+    sqlite3 *db = p->db;
+    sqlite3DbFree(db, p->zErrMsg);
+    p->zErrMsg = sqlite3DbStrDup(db, pVtab->zErrMsg);
+    sqlite3_free(pVtab->zErrMsg);
+    pVtab->zErrMsg = 0;
+  }
+}
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
+
+#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
+
+/*
+** If the second argument is not NULL, release any allocations associated 
+** with the memory cells in the p->aMem[] array. Also free the UnpackedRecord
+** structure itself, using sqlite3DbFree().
+**
+** This function is used to free UnpackedRecord structures allocated by
+** the vdbeUnpackRecord() function found in vdbeapi.c.
+*/
+static void vdbeFreeUnpacked(sqlite3 *db, int nField, UnpackedRecord *p){
+  if( p ){
+    int i;
+    for(i=0; i<nField; i++){
+      Mem *pMem = &p->aMem[i];
+      if( pMem->zMalloc ) sqlite3VdbeMemRelease(pMem);
+    }
+    sqlite3DbFreeNN(db, p);
+  }
+}
+#endif /* SQLITE_ENABLE_PREUPDATE_HOOK */
+
+#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
+/*
+** Invoke the pre-update hook. If this is an UPDATE or DELETE pre-update call,
+** then cursor passed as the second argument should point to the row about
+** to be update or deleted. If the application calls sqlite3_preupdate_old(),
+** the required value will be read from the row the cursor points to.
+*/
+void sqlite3VdbePreUpdateHook(
+  Vdbe *v,                        /* Vdbe pre-update hook is invoked by */
+  VdbeCursor *pCsr,               /* Cursor to grab old.* values from */
+  int op,                         /* SQLITE_INSERT, UPDATE or DELETE */
+  const char *zDb,                /* Database name */
+  Table *pTab,                    /* Modified table */
+  i64 iKey1,                      /* Initial key value */
+  int iReg                        /* Register for new.* record */
+){
+  sqlite3 *db = v->db;
+  i64 iKey2;
+  PreUpdate preupdate;
+  const char *zTbl = pTab->zName;
+  static const u8 fakeSortOrder = 0;
+
+  assert( db->pPreUpdate==0 );
+  memset(&preupdate, 0, sizeof(PreUpdate));
+  if( HasRowid(pTab)==0 ){
+    iKey1 = iKey2 = 0;
+    preupdate.pPk = sqlite3PrimaryKeyIndex(pTab);
+  }else{
+    if( op==SQLITE_UPDATE ){
+      iKey2 = v->aMem[iReg].u.i;
+    }else{
+      iKey2 = iKey1;
+    }
+  }
+
+  assert( pCsr->nField==pTab->nCol 
+       || (pCsr->nField==pTab->nCol+1 && op==SQLITE_DELETE && iReg==-1)
+  );
+
+  preupdate.v = v;
+  preupdate.pCsr = pCsr;
+  preupdate.op = op;
+  preupdate.iNewReg = iReg;
+  preupdate.keyinfo.db = db;
+  preupdate.keyinfo.enc = ENC(db);
+  preupdate.keyinfo.nKeyField = pTab->nCol;
+  preupdate.keyinfo.aSortOrder = (u8*)&fakeSortOrder;
+  preupdate.iKey1 = iKey1;
+  preupdate.iKey2 = iKey2;
+  preupdate.pTab = pTab;
+
+  db->pPreUpdate = &preupdate;
+  db->xPreUpdateCallback(db->pPreUpdateArg, db, op, zDb, zTbl, iKey1, iKey2);
+  db->pPreUpdate = 0;
+  sqlite3DbFree(db, preupdate.aRecord);
+  vdbeFreeUnpacked(db, preupdate.keyinfo.nKeyField+1, preupdate.pUnpacked);
+  vdbeFreeUnpacked(db, preupdate.keyinfo.nKeyField+1, preupdate.pNewUnpacked);
+  if( preupdate.aNew ){
+    int i;
+    for(i=0; i<pCsr->nField; i++){
+      sqlite3VdbeMemRelease(&preupdate.aNew[i]);
+    }
+    sqlite3DbFreeNN(db, preupdate.aNew);
+  }
+}
+#endif /* SQLITE_ENABLE_PREUPDATE_HOOK */
