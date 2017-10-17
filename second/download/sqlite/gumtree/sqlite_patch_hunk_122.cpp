 ** If P2==1 then no insert is performed.  argv[0] is the rowid of
 ** a row to delete.
 **
 ** P1 is a boolean flag. If it is set to true and the xUpdate call
 ** is successful, then the value returned by sqlite3_last_insert_rowid() 
 ** is set to the value of the rowid for the row just inserted.
-**
-** P5 is the error actions (OE_Replace, OE_Fail, OE_Ignore, etc) to
-** apply in the case of a constraint failure on an insert or update.
 */
 case OP_VUpdate: {
   sqlite3_vtab *pVtab;
-  const sqlite3_module *pModule;
+  sqlite3_module *pModule;
   int nArg;
   int i;
   sqlite_int64 rowid;
   Mem **apArg;
   Mem *pX;
 
-  assert( pOp->p2==1        || pOp->p5==OE_Fail   || pOp->p5==OE_Rollback 
-       || pOp->p5==OE_Abort || pOp->p5==OE_Ignore || pOp->p5==OE_Replace
-  );
-  assert( p->readOnly==0 );
-  pVtab = pOp->p4.pVtab->pVtab;
-  if( pVtab==0 || NEVER(pVtab->pModule==0) ){
-    rc = SQLITE_LOCKED;
-    goto abort_due_to_error;
-  }
-  pModule = pVtab->pModule;
+  pVtab = pOp->p4.pVtab;
+  pModule = (sqlite3_module *)pVtab->pModule;
   nArg = pOp->p2;
   assert( pOp->p4type==P4_VTAB );
-  if( ALWAYS(pModule->xUpdate) ){
-    u8 vtabOnConflict = db->vtabOnConflict;
+  if( pModule->xUpdate==0 ){
+    sqlite3SetString(&p->zErrMsg, db, "read-only table");
+    rc = SQLITE_ERROR;
+  }else{
     apArg = p->apArg;
-    pX = &aMem[pOp->p3];
+    pX = &p->aMem[pOp->p3];
     for(i=0; i<nArg; i++){
-      assert( memIsValid(pX) );
-      memAboutToChange(p, pX);
+      storeTypeInfo(pX, 0);
       apArg[i] = pX;
       pX++;
     }
-    db->vtabOnConflict = pOp->p5;
+    if( sqlite3SafetyOff(db) ) goto abort_due_to_misuse;
+    sqlite3VtabLock(pVtab);
     rc = pModule->xUpdate(pVtab, nArg, apArg, &rowid);
-    db->vtabOnConflict = vtabOnConflict;
-    sqlite3VtabImportErrmsg(p, pVtab);
-    if( rc==SQLITE_OK && pOp->p1 ){
+    sqlite3DbFree(db, p->zErrMsg);
+    p->zErrMsg = pVtab->zErrMsg;
+    pVtab->zErrMsg = 0;
+    sqlite3VtabUnlock(db, pVtab);
+    if( sqlite3SafetyOn(db) ) goto abort_due_to_misuse;
+    if( pOp->p1 && rc==SQLITE_OK ){
       assert( nArg>1 && apArg[0] && (apArg[0]->flags&MEM_Null) );
       db->lastRowid = rowid;
     }
-    if( (rc&0xff)==SQLITE_CONSTRAINT && pOp->p4.pVtab->bConstraint ){
-      if( pOp->p5==OE_Ignore ){
-        rc = SQLITE_OK;
-      }else{
-        p->errorAction = ((pOp->p5==OE_Replace) ? OE_Abort : pOp->p5);
-      }
-    }else{
-      p->nChange++;
-    }
-    if( rc ) goto abort_due_to_error;
+    p->nChange++;
   }
   break;
 }
 #endif /* SQLITE_OMIT_VIRTUALTABLE */
 
 #ifndef  SQLITE_OMIT_PAGER_PRAGMAS
 /* Opcode: Pagecount P1 P2 * * *
 **
 ** Write the current number of pages in database P1 to memory cell P2.
 */
-case OP_Pagecount: {            /* out2 */
-  pOut = out2Prerelease(p, pOp);
-  pOut->u.i = sqlite3BtreeLastPage(db->aDb[pOp->p1].pBt);
-  break;
-}
-#endif
-
-
-#ifndef  SQLITE_OMIT_PAGER_PRAGMAS
-/* Opcode: MaxPgcnt P1 P2 P3 * *
-**
-** Try to set the maximum page count for database P1 to the value in P3.
-** Do not let the maximum page count fall below the current page count and
-** do not change the maximum page count value if P3==0.
-**
-** Store the maximum page count after the change in register P2.
-*/
-case OP_MaxPgcnt: {            /* out2 */
-  unsigned int newMax;
-  Btree *pBt;
+case OP_Pagecount: {            /* out2-prerelease */
+  int p1;
+  int nPage;
+  Pager *pPager;
 
-  pOut = out2Prerelease(p, pOp);
-  pBt = db->aDb[pOp->p1].pBt;
-  newMax = 0;
-  if( pOp->p3 ){
-    newMax = sqlite3BtreeLastPage(pBt);
-    if( newMax < (unsigned)pOp->p3 ) newMax = (unsigned)pOp->p3;
+  p1 = pOp->p1; 
+  pPager = sqlite3BtreePager(db->aDb[p1].pBt);
+  rc = sqlite3PagerPagecount(pPager, &nPage);
+  if( rc==SQLITE_OK ){
+    pOut->flags = MEM_Int;
+    pOut->u.i = nPage;
   }
-  pOut->u.i = sqlite3BtreeMaxPageCount(pBt, newMax);
   break;
 }
 #endif
 
-/* Opcode: Function0 P1 P2 P3 P4 P5
-** Synopsis: r[P3]=func(r[P2@P5])
-**
-** Invoke a user function (P4 is a pointer to a FuncDef object that
-** defines the function) with P5 arguments taken from register P2 and
-** successors.  The result of the function is stored in register P3.
-** Register P3 must not be one of the function inputs.
-**
-** P1 is a 32-bit bitmask indicating whether or not each argument to the 
-** function was determined to be constant at compile time. If the first
-** argument was constant then bit 0 of P1 is set. This is used to determine
-** whether meta data associated with a user function argument using the
-** sqlite3_set_auxdata() API may be safely retained until the next
-** invocation of this opcode.
-**
-** See also: Function, AggStep, AggFinal
-*/
-/* Opcode: Function P1 P2 P3 P4 P5
-** Synopsis: r[P3]=func(r[P2@P5])
-**
-** Invoke a user function (P4 is a pointer to an sqlite3_context object that
-** contains a pointer to the function to be run) with P5 arguments taken
-** from register P2 and successors.  The result of the function is stored
-** in register P3.  Register P3 must not be one of the function inputs.
-**
-** P1 is a 32-bit bitmask indicating whether or not each argument to the 
-** function was determined to be constant at compile time. If the first
-** argument was constant then bit 0 of P1 is set. This is used to determine
-** whether meta data associated with a user function argument using the
-** sqlite3_set_auxdata() API may be safely retained until the next
-** invocation of this opcode.
-**
-** SQL functions are initially coded as OP_Function0 with P4 pointing
-** to a FuncDef object.  But on first evaluation, the P4 operand is
-** automatically converted into an sqlite3_context object and the operation
-** changed to this OP_Function opcode.  In this way, the initialization of
-** the sqlite3_context object occurs only once, rather than once for each
-** evaluation of the function.
-**
-** See also: Function0, AggStep, AggFinal
-*/
-case OP_PureFunc0:
-case OP_Function0: {
-  int n;
-  sqlite3_context *pCtx;
-
-  assert( pOp->p4type==P4_FUNCDEF );
-  n = pOp->p5;
-  assert( pOp->p3>0 && pOp->p3<=(p->nMem+1 - p->nCursor) );
-  assert( n==0 || (pOp->p2>0 && pOp->p2+n<=(p->nMem+1 - p->nCursor)+1) );
-  assert( pOp->p3<pOp->p2 || pOp->p3>=pOp->p2+n );
-  pCtx = sqlite3DbMallocRawNN(db, sizeof(*pCtx) + (n-1)*sizeof(sqlite3_value*));
-  if( pCtx==0 ) goto no_mem;
-  pCtx->pOut = 0;
-  pCtx->pFunc = pOp->p4.pFunc;
-  pCtx->iOp = (int)(pOp - aOp);
-  pCtx->pVdbe = p;
-  pCtx->argc = n;
-  pOp->p4type = P4_FUNCCTX;
-  pOp->p4.pCtx = pCtx;
-  assert( OP_PureFunc == OP_PureFunc0+2 );
-  assert( OP_Function == OP_Function0+2 );
-  pOp->opcode += 2;
-  /* Fall through into OP_Function */
-}
-case OP_PureFunc:
-case OP_Function: {
-  int i;
-  sqlite3_context *pCtx;
-
-  assert( pOp->p4type==P4_FUNCCTX );
-  pCtx = pOp->p4.pCtx;
-
-  /* If this function is inside of a trigger, the register array in aMem[]
-  ** might change from one evaluation to the next.  The next block of code
-  ** checks to see if the register array has changed, and if so it
-  ** reinitializes the relavant parts of the sqlite3_context object */
-  pOut = &aMem[pOp->p3];
-  if( pCtx->pOut != pOut ){
-    pCtx->pOut = pOut;
-    for(i=pCtx->argc-1; i>=0; i--) pCtx->argv[i] = &aMem[pOp->p2+i];
-  }
-
-  memAboutToChange(p, pOut);
-#ifdef SQLITE_DEBUG
-  for(i=0; i<pCtx->argc; i++){
-    assert( memIsValid(pCtx->argv[i]) );
-    REGISTER_TRACE(pOp->p2+i, pCtx->argv[i]);
-  }
-#endif
-  MemSetTypeFlag(pOut, MEM_Null);
-  pCtx->fErrorOrAux = 0;
-  (*pCtx->pFunc->xSFunc)(pCtx, pCtx->argc, pCtx->argv);/* IMP: R-24505-23230 */
-
-  /* If the function returned an error, throw an exception */
-  if( pCtx->fErrorOrAux ){
-    if( pCtx->isError ){
-      sqlite3VdbeError(p, "%s", sqlite3_value_text(pOut));
-      rc = pCtx->isError;
-    }
-    sqlite3VdbeDeleteAuxData(db, &p->pAuxData, pCtx->iOp, pOp->p1);
-    if( rc ) goto abort_due_to_error;
-  }
-
-  /* Copy the result of the function into register P3 */
-  if( pOut->flags & (MEM_Str|MEM_Blob) ){
-    sqlite3VdbeChangeEncoding(pOut, encoding);
-    if( sqlite3VdbeMemTooBig(pOut) ) goto too_big;
-  }
-
-  REGISTER_TRACE(pOp->p3, pOut);
-  UPDATE_MAX_BLOBSIZE(pOut);
-  break;
-}
-
-
-/* Opcode: Init P1 P2 P3 P4 *
-** Synopsis: Start at P2
-**
-** Programs contain a single instance of this opcode as the very first
-** opcode.
+#ifndef SQLITE_OMIT_TRACE
+/* Opcode: Trace * * * P4 *
 **
 ** If tracing is enabled (by the sqlite3_trace()) interface, then
 ** the UTF-8 string contained in P4 is emitted on the trace callback.
-** Or if P4 is blank, use the string returned by sqlite3_sql().
-**
-** If P2 is not zero, jump to instruction P2.
-**
-** Increment the value of P1 so that OP_Once opcodes will jump the
-** first time they are evaluated for this run.
-**
-** If P3 is not zero, then it is an address to jump to if an SQLITE_CORRUPT
-** error is encountered.
 */
-case OP_Init: {          /* jump */
+case OP_Trace: {
   char *zTrace;
-  int i;
-
-  /* If the P4 argument is not NULL, then it must be an SQL comment string.
-  ** The "--" string is broken up to prevent false-positives with srcck1.c.
-  **
-  ** This assert() provides evidence for:
-  ** EVIDENCE-OF: R-50676-09860 The callback can compute the same text that
-  ** would have been returned by the legacy sqlite3_trace() interface by
-  ** using the X argument when X begins with "--" and invoking
-  ** sqlite3_expanded_sql(P) otherwise.
-  */
-  assert( pOp->p4.z==0 || strncmp(pOp->p4.z, "-" "- ", 3)==0 );
-  assert( pOp==p->aOp );  /* Always instruction 0 */
 
-#ifndef SQLITE_OMIT_TRACE
-  if( (db->mTrace & (SQLITE_TRACE_STMT|SQLITE_TRACE_LEGACY))!=0
-   && !p->doingRerun
-   && (zTrace = (pOp->p4.z ? pOp->p4.z : p->zSql))!=0
-  ){
-#ifndef SQLITE_OMIT_DEPRECATED
-    if( db->mTrace & SQLITE_TRACE_LEGACY ){
-      void (*x)(void*,const char*) = (void(*)(void*,const char*))db->xTrace;
-      char *z = sqlite3VdbeExpandSql(p, zTrace);
-      x(db->pTraceArg, z);
-      sqlite3_free(z);
-    }else
-#endif
-    if( db->nVdbeExec>1 ){
-      char *z = sqlite3MPrintf(db, "-- %s", zTrace);
-      (void)db->xTrace(SQLITE_TRACE_STMT, db->pTraceArg, p, z);
-      sqlite3DbFree(db, z);
-    }else{
-      (void)db->xTrace(SQLITE_TRACE_STMT, db->pTraceArg, p, zTrace);
-    }
-  }
-#ifdef SQLITE_USE_FCNTL_TRACE
   zTrace = (pOp->p4.z ? pOp->p4.z : p->zSql);
   if( zTrace ){
-    int j;
-    for(j=0; j<db->nDb; j++){
-      if( DbMaskTest(p->btreeMask, j)==0 ) continue;
-      sqlite3_file_control(db, db->aDb[j].zDbSName, SQLITE_FCNTL_TRACE, zTrace);
+    if( db->xTrace ){
+      db->xTrace(db->pTraceArg, zTrace);
     }
-  }
-#endif /* SQLITE_USE_FCNTL_TRACE */
 #ifdef SQLITE_DEBUG
-  if( (db->flags & SQLITE_SqlTrace)!=0
-   && (zTrace = (pOp->p4.z ? pOp->p4.z : p->zSql))!=0
-  ){
-    sqlite3DebugPrintf("SQL-trace: %s\n", zTrace);
-  }
-#endif /* SQLITE_DEBUG */
-#endif /* SQLITE_OMIT_TRACE */
-  assert( pOp->p2>0 );
-  if( pOp->p1>=sqlite3GlobalConfig.iOnceResetThreshold ){
-    for(i=1; i<p->nOp; i++){
-      if( p->aOp[i].opcode==OP_Once ) p->aOp[i].p1 = 0;
+    if( (db->flags & SQLITE_SqlTrace)!=0 ){
+      sqlite3DebugPrintf("SQL-trace: %s\n", zTrace);
     }
-    pOp->p1 = 0;
-  }
-  pOp->p1++;
-  p->aCounter[SQLITE_STMTSTATUS_RUN]++;
-  goto jump_to_p2;
-}
-
-#ifdef SQLITE_ENABLE_CURSOR_HINTS
-/* Opcode: CursorHint P1 * * P4 *
-**
-** Provide a hint to cursor P1 that it only needs to return rows that
-** satisfy the Expr in P4.  TK_REGISTER terms in the P4 expression refer
-** to values currently held in registers.  TK_COLUMN terms in the P4
-** expression refer to columns in the b-tree to which cursor P1 is pointing.
-*/
-case OP_CursorHint: {
-  VdbeCursor *pC;
-
-  assert( pOp->p1>=0 && pOp->p1<p->nCursor );
-  assert( pOp->p4type==P4_EXPR );
-  pC = p->apCsr[pOp->p1];
-  if( pC ){
-    assert( pC->eCurType==CURTYPE_BTREE );
-    sqlite3BtreeCursorHint(pC->uc.pCursor, BTREE_HINT_RANGE,
-                           pOp->p4.pExpr, aMem);
+#endif /* SQLITE_DEBUG */
   }
   break;
 }
-#endif /* SQLITE_ENABLE_CURSOR_HINTS */
+#endif
+
 
 /* Opcode: Noop * * * * *
 **
 ** Do nothing.  This instruction is often useful as a jump
 ** destination.
 */
