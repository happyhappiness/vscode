     if( (pIn1->flags & MEM_RowSet)==0 ) goto no_mem;
   }
 
   assert( pOp->p4type==P4_INT32 );
   assert( iSet==-1 || iSet>=0 );
   if( iSet ){
-    exists = sqlite3RowSetTest(pIn1->u.pRowSet, 
-                               (u8)(iSet>=0 ? iSet & 0xf : 0xff),
-                               pIn3->u.i);
-    if( exists ){
-      pc = pOp->p2 - 1;
-      break;
-    }
+    exists = sqlite3RowSetTest(pIn1->u.pRowSet, iSet, pIn3->u.i);
+    VdbeBranchTaken(exists!=0,2);
+    if( exists ) goto jump_to_p2;
   }
   if( iSet>=0 ){
     sqlite3RowSetInsert(pIn1->u.pRowSet, pIn3->u.i);
   }
   break;
 }
 
 
 #ifndef SQLITE_OMIT_TRIGGER
-/* Opcode: ContextPush * * * 
+
+/* Opcode: Program P1 P2 P3 P4 P5
 **
-** Save the current Vdbe context such that it can be restored by a ContextPop
-** opcode. The context stores the last insert row id, the last statement change
-** count, and the current statement change count.
-*/
-case OP_ContextPush: {
-  int i;
-  Context *pContext;
+** Execute the trigger program passed as P4 (type P4_SUBPROGRAM). 
+**
+** P1 contains the address of the memory cell that contains the first memory 
+** cell in an array of values used as arguments to the sub-program. P2 
+** contains the address to jump to if the sub-program throws an IGNORE 
+** exception using the RAISE() function. Register P3 contains the address 
+** of a memory cell in this (the parent) VM that is used to allocate the 
+** memory required by the sub-vdbe at runtime.
+**
+** P4 is a pointer to the VM containing the trigger program.
+**
+** If P5 is non-zero, then recursive program invocation is enabled.
+*/
+case OP_Program: {        /* jump */
+  int nMem;               /* Number of memory registers for sub-program */
+  int nByte;              /* Bytes of runtime space required for sub-program */
+  Mem *pRt;               /* Register to allocate runtime space */
+  Mem *pMem;              /* Used to iterate through memory cells */
+  Mem *pEnd;              /* Last memory cell in new array */
+  VdbeFrame *pFrame;      /* New vdbe frame to execute in */
+  SubProgram *pProgram;   /* Sub-program to execute */
+  void *t;                /* Token identifying trigger */
+
+  pProgram = pOp->p4.pProgram;
+  pRt = &aMem[pOp->p3];
+  assert( pProgram->nOp>0 );
+  
+  /* If the p5 flag is clear, then recursive invocation of triggers is 
+  ** disabled for backwards compatibility (p5 is set if this sub-program
+  ** is really a trigger, not a foreign key action, and the flag set
+  ** and cleared by the "PRAGMA recursive_triggers" command is clear).
+  ** 
+  ** It is recursive invocation of triggers, at the SQL level, that is 
+  ** disabled. In some cases a single trigger may generate more than one 
+  ** SubProgram (if the trigger may be executed with more than one different 
+  ** ON CONFLICT algorithm). SubProgram structures associated with a
+  ** single trigger all have the same value for the SubProgram.token 
+  ** variable.  */
+  if( pOp->p5 ){
+    t = pProgram->token;
+    for(pFrame=p->pFrame; pFrame && pFrame->token!=t; pFrame=pFrame->pParent);
+    if( pFrame ) break;
+  }
+
+  if( p->nFrame>=db->aLimit[SQLITE_LIMIT_TRIGGER_DEPTH] ){
+    rc = SQLITE_ERROR;
+    sqlite3VdbeError(p, "too many levels of trigger recursion");
+    goto abort_due_to_error;
+  }
+
+  /* Register pRt is used to store the memory required to save the state
+  ** of the current program, and the memory required at runtime to execute
+  ** the trigger program. If this trigger has been fired before, then pRt 
+  ** is already allocated. Otherwise, it must be initialized.  */
+  if( (pRt->flags&MEM_Frame)==0 ){
+    /* SubProgram.nMem is set to the number of memory cells used by the 
+    ** program stored in SubProgram.aOp. As well as these, one memory
+    ** cell is required for each cursor used by the program. Set local
+    ** variable nMem (and later, VdbeFrame.nChildMem) to this value.
+    */
+    nMem = pProgram->nMem + pProgram->nCsr;
+    assert( nMem>0 );
+    if( pProgram->nCsr==0 ) nMem++;
+    nByte = ROUND8(sizeof(VdbeFrame))
+              + nMem * sizeof(Mem)
+              + pProgram->nCsr * sizeof(VdbeCursor*)
+              + (pProgram->nOp + 7)/8;
+    pFrame = sqlite3DbMallocZero(db, nByte);
+    if( !pFrame ){
+      goto no_mem;
+    }
+    sqlite3VdbeMemRelease(pRt);
+    pRt->flags = MEM_Frame;
+    pRt->u.pFrame = pFrame;
+
+    pFrame->v = p;
+    pFrame->nChildMem = nMem;
+    pFrame->nChildCsr = pProgram->nCsr;
+    pFrame->pc = (int)(pOp - aOp);
+    pFrame->aMem = p->aMem;
+    pFrame->nMem = p->nMem;
+    pFrame->apCsr = p->apCsr;
+    pFrame->nCursor = p->nCursor;
+    pFrame->aOp = p->aOp;
+    pFrame->nOp = p->nOp;
+    pFrame->token = pProgram->token;
+#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
+    pFrame->anExec = p->anExec;
+#endif
+
+    pEnd = &VdbeFrameMem(pFrame)[pFrame->nChildMem];
+    for(pMem=VdbeFrameMem(pFrame); pMem!=pEnd; pMem++){
+      pMem->flags = MEM_Undefined;
+      pMem->db = db;
+    }
+  }else{
+    pFrame = pRt->u.pFrame;
+    assert( pProgram->nMem+pProgram->nCsr==pFrame->nChildMem 
+        || (pProgram->nCsr==0 && pProgram->nMem+1==pFrame->nChildMem) );
+    assert( pProgram->nCsr==pFrame->nChildCsr );
+    assert( (int)(pOp - aOp)==pFrame->pc );
+  }
+
+  p->nFrame++;
+  pFrame->pParent = p->pFrame;
+  pFrame->lastRowid = db->lastRowid;
+  pFrame->nChange = p->nChange;
+  pFrame->nDbChange = p->db->nChange;
+  assert( pFrame->pAuxData==0 );
+  pFrame->pAuxData = p->pAuxData;
+  p->pAuxData = 0;
+  p->nChange = 0;
+  p->pFrame = pFrame;
+  p->aMem = aMem = VdbeFrameMem(pFrame);
+  p->nMem = pFrame->nChildMem;
+  p->nCursor = (u16)pFrame->nChildCsr;
+  p->apCsr = (VdbeCursor **)&aMem[p->nMem];
+  pFrame->aOnce = (u8*)&p->apCsr[pProgram->nCsr];
+  memset(pFrame->aOnce, 0, (pProgram->nOp + 7)/8);
+  p->aOp = aOp = pProgram->aOp;
+  p->nOp = pProgram->nOp;
+#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
+  p->anExec = 0;
+#endif
+  pOp = &aOp[-1];
 
-  i = p->contextStackTop++;
-  assert( i>=0 );
-  /* FIX ME: This should be allocated as part of the vdbe at compile-time */
-  if( i>=p->contextStackDepth ){
-    p->contextStackDepth = i+1;
-    p->contextStack = sqlite3DbReallocOrFree(db, p->contextStack,
-                                          sizeof(Context)*(i+1));
-    if( p->contextStack==0 ) goto no_mem;
-  }
-  pContext = &p->contextStack[i];
-  pContext->lastRowid = db->lastRowid;
-  pContext->nChange = p->nChange;
   break;
 }
 
-/* Opcode: ContextPop * * * 
-**
-** Restore the Vdbe context to the state it was in when contextPush was last
-** executed. The context stores the last insert row id, the last statement
-** change count, and the current statement change count.
-*/
-case OP_ContextPop: {
-  Context *pContext;
-  pContext = &p->contextStack[--p->contextStackTop];
-  assert( p->contextStackTop>=0 );
-  db->lastRowid = pContext->lastRowid;
-  p->nChange = pContext->nChange;
+/* Opcode: Param P1 P2 * * *
+**
+** This opcode is only ever present in sub-programs called via the 
+** OP_Program instruction. Copy a value currently stored in a memory 
+** cell of the calling (parent) frame to cell P2 in the current frames 
+** address space. This is used by trigger programs to access the new.* 
+** and old.* values.
+**
+** The address of the cell in the parent frame is determined by adding
+** the value of the P1 argument to the value of the P1 argument to the
+** calling OP_Program instruction.
+*/
+case OP_Param: {           /* out2 */
+  VdbeFrame *pFrame;
+  Mem *pIn;
+  pOut = out2Prerelease(p, pOp);
+  pFrame = p->pFrame;
+  pIn = &pFrame->aMem[pOp->p1 + pFrame->aOp[pFrame->pc].p1];   
+  sqlite3VdbeMemShallowCopy(pOut, pIn, MEM_Ephem);
   break;
 }
+
 #endif /* #ifndef SQLITE_OMIT_TRIGGER */
 
+#ifndef SQLITE_OMIT_FOREIGN_KEY
+/* Opcode: FkCounter P1 P2 * * *
+** Synopsis: fkctr[P1]+=P2
+**
+** Increment a "constraint counter" by P2 (P2 may be negative or positive).
+** If P1 is non-zero, the database constraint counter is incremented 
+** (deferred foreign key constraints). Otherwise, if P1 is zero, the 
+** statement counter is incremented (immediate foreign key constraints).
+*/
+case OP_FkCounter: {
+  if( db->flags & SQLITE_DeferFKs ){
+    db->nDeferredImmCons += pOp->p2;
+  }else if( pOp->p1 ){
+    db->nDeferredCons += pOp->p2;
+  }else{
+    p->nFkConstraint += pOp->p2;
+  }
+  break;
+}
+
+/* Opcode: FkIfZero P1 P2 * * *
+** Synopsis: if fkctr[P1]==0 goto P2
+**
+** This opcode tests if a foreign key constraint-counter is currently zero.
+** If so, jump to instruction P2. Otherwise, fall through to the next 
+** instruction.
+**
+** If P1 is non-zero, then the jump is taken if the database constraint-counter
+** is zero (the one that counts deferred constraint violations). If P1 is
+** zero, the jump is taken if the statement constraint-counter is zero
+** (immediate foreign key constraint violations).
+*/
+case OP_FkIfZero: {         /* jump */
+  if( pOp->p1 ){
+    VdbeBranchTaken(db->nDeferredCons==0 && db->nDeferredImmCons==0, 2);
+    if( db->nDeferredCons==0 && db->nDeferredImmCons==0 ) goto jump_to_p2;
+  }else{
+    VdbeBranchTaken(p->nFkConstraint==0 && db->nDeferredImmCons==0, 2);
+    if( p->nFkConstraint==0 && db->nDeferredImmCons==0 ) goto jump_to_p2;
+  }
+  break;
+}
+#endif /* #ifndef SQLITE_OMIT_FOREIGN_KEY */
+
 #ifndef SQLITE_OMIT_AUTOINCREMENT
 /* Opcode: MemMax P1 P2 * * *
+** Synopsis: r[P1]=max(r[P1],r[P2])
 **
-** Set the value of register P1 to the maximum of its current value
-** and the value in register P2.
+** P1 is a register in the root frame of this VM (the root frame is
+** different from the current frame if this instruction is being executed
+** within a sub-program). Set the value of register P1 to the maximum of 
+** its current value and the value in register P2.
 **
 ** This instruction throws an error if the memory cell is not initially
 ** an integer.
 */
-case OP_MemMax: {        /* in1, in2 */
+case OP_MemMax: {        /* in2 */
+  VdbeFrame *pFrame;
+  if( p->pFrame ){
+    for(pFrame=p->pFrame; pFrame->pParent; pFrame=pFrame->pParent);
+    pIn1 = &pFrame->aMem[pOp->p1];
+  }else{
+    pIn1 = &aMem[pOp->p1];
+  }
+  assert( memIsValid(pIn1) );
   sqlite3VdbeMemIntegerify(pIn1);
+  pIn2 = &aMem[pOp->p2];
   sqlite3VdbeMemIntegerify(pIn2);
   if( pIn1->u.i<pIn2->u.i){
     pIn1->u.i = pIn2->u.i;
   }
   break;
 }
 #endif /* SQLITE_OMIT_AUTOINCREMENT */
 
-/* Opcode: IfPos P1 P2 * * *
+/* Opcode: IfPos P1 P2 P3 * *
+** Synopsis: if r[P1]>0 then r[P1]-=P3, goto P2
 **
-** If the value of register P1 is 1 or greater, jump to P2.
+** Register P1 must contain an integer.
+** If the value of register P1 is 1 or greater, subtract P3 from the
+** value in P1 and jump to P2.
 **
-** It is illegal to use this instruction on a register that does
-** not contain an integer.  An assertion fault will result if you try.
+** If the initial value of register P1 is less than 1, then the
+** value is unchanged and control passes through to the next instruction.
 */
 case OP_IfPos: {        /* jump, in1 */
+  pIn1 = &aMem[pOp->p1];
   assert( pIn1->flags&MEM_Int );
+  VdbeBranchTaken( pIn1->u.i>0, 2);
   if( pIn1->u.i>0 ){
-     pc = pOp->p2 - 1;
+    pIn1->u.i -= pOp->p3;
+    goto jump_to_p2;
+  }
+  break;
+}
+
+/* Opcode: OffsetLimit P1 P2 P3 * *
+** Synopsis: if r[P1]>0 then r[P2]=r[P1]+max(0,r[P3]) else r[P2]=(-1)
+**
+** This opcode performs a commonly used computation associated with
+** LIMIT and OFFSET process.  r[P1] holds the limit counter.  r[P3]
+** holds the offset counter.  The opcode computes the combined value
+** of the LIMIT and OFFSET and stores that value in r[P2].  The r[P2]
+** value computed is the total number of rows that will need to be
+** visited in order to complete the query.
+**
+** If r[P3] is zero or negative, that means there is no OFFSET
+** and r[P2] is set to be the value of the LIMIT, r[P1].
+**
+** if r[P1] is zero or negative, that means there is no LIMIT
+** and r[P2] is set to -1. 
+**
+** Otherwise, r[P2] is set to the sum of r[P1] and r[P3].
+*/
+case OP_OffsetLimit: {    /* in1, out2, in3 */
+  i64 x;
+  pIn1 = &aMem[pOp->p1];
+  pIn3 = &aMem[pOp->p3];
+  pOut = out2Prerelease(p, pOp);
+  assert( pIn1->flags & MEM_Int );
+  assert( pIn3->flags & MEM_Int );
+  x = pIn1->u.i;
+  if( x<=0 || sqlite3AddInt64(&x, pIn3->u.i>0?pIn3->u.i:0) ){
+    /* If the LIMIT is less than or equal to zero, loop forever.  This
+    ** is documented.  But also, if the LIMIT+OFFSET exceeds 2^63 then
+    ** also loop forever.  This is undocumented.  In fact, one could argue
+    ** that the loop should terminate.  But assuming 1 billion iterations
+    ** per second (far exceeding the capabilities of any current hardware)
+    ** it would take nearly 300 years to actually reach the limit.  So
+    ** looping forever is a reasonable approximation. */
+    pOut->u.i = -1;
+  }else{
+    pOut->u.i = x;
   }
   break;
 }
 
-/* Opcode: IfNeg P1 P2 * * *
-**
-** If the value of register P1 is less than zero, jump to P2. 
+/* Opcode: IfNotZero P1 P2 * * *
+** Synopsis: if r[P1]!=0 then r[P1]--, goto P2
 **
-** It is illegal to use this instruction on a register that does
-** not contain an integer.  An assertion fault will result if you try.
+** Register P1 must contain an integer.  If the content of register P1 is
+** initially greater than zero, then decrement the value in register P1.
+** If it is non-zero (negative or positive) and then also jump to P2.  
+** If register P1 is initially zero, leave it unchanged and fall through.
 */
-case OP_IfNeg: {        /* jump, in1 */
+case OP_IfNotZero: {        /* jump, in1 */
+  pIn1 = &aMem[pOp->p1];
   assert( pIn1->flags&MEM_Int );
-  if( pIn1->u.i<0 ){
-     pc = pOp->p2 - 1;
+  VdbeBranchTaken(pIn1->u.i<0, 2);
+  if( pIn1->u.i ){
+     if( pIn1->u.i>0 ) pIn1->u.i--;
+     goto jump_to_p2;
   }
   break;
 }
 
-/* Opcode: IfZero P1 P2 * * *
+/* Opcode: DecrJumpZero P1 P2 * * *
+** Synopsis: if (--r[P1])==0 goto P2
 **
-** If the value of register P1 is exactly 0, jump to P2. 
-**
-** It is illegal to use this instruction on a register that does
-** not contain an integer.  An assertion fault will result if you try.
+** Register P1 must hold an integer.  Decrement the value in P1
+** and jump to P2 if the new value is exactly zero.
 */
-case OP_IfZero: {        /* jump, in1 */
+case OP_DecrJumpZero: {      /* jump, in1 */
+  pIn1 = &aMem[pOp->p1];
   assert( pIn1->flags&MEM_Int );
-  if( pIn1->u.i==0 ){
-     pc = pOp->p2 - 1;
-  }
+  if( pIn1->u.i>SMALLEST_INT64 ) pIn1->u.i--;
+  VdbeBranchTaken(pIn1->u.i==0, 2);
+  if( pIn1->u.i==0 ) goto jump_to_p2;
   break;
 }
 
-/* Opcode: AggStep * P2 P3 P4 P5
+
+/* Opcode: AggStep0 * P2 P3 P4 P5
+** Synopsis: accum=r[P3] step(r[P2@P5])
 **
 ** Execute the step function for an aggregate.  The
 ** function has P5 arguments.   P4 is a pointer to the FuncDef
-** structure that specifies the function.  Use register
-** P3 as the accumulator.
+** structure that specifies the function.  Register P3 is the
+** accumulator.
 **
 ** The P5 arguments are taken from register P2 and its
 ** successors.
 */
-case OP_AggStep: {
+/* Opcode: AggStep * P2 P3 P4 P5
+** Synopsis: accum=r[P3] step(r[P2@P5])
+**
+** Execute the step function for an aggregate.  The
+** function has P5 arguments.   P4 is a pointer to an sqlite3_context
+** object that is used to run the function.  Register P3 is
+** as the accumulator.
+**
+** The P5 arguments are taken from register P2 and its
+** successors.
+**
+** This opcode is initially coded as OP_AggStep0.  On first evaluation,
+** the FuncDef stored in P4 is converted into an sqlite3_context and
+** the opcode is changed.  In this way, the initialization of the
+** sqlite3_context only happens once, instead of on each call to the
+** step function.
+*/
+case OP_AggStep0: {
   int n;
+  sqlite3_context *pCtx;
+
+  assert( pOp->p4type==P4_FUNCDEF );
+  n = pOp->p5;
+  assert( pOp->p3>0 && pOp->p3<=(p->nMem+1 - p->nCursor) );
+  assert( n==0 || (pOp->p2>0 && pOp->p2+n<=(p->nMem+1 - p->nCursor)+1) );
+  assert( pOp->p3<pOp->p2 || pOp->p3>=pOp->p2+n );
+  pCtx = sqlite3DbMallocRawNN(db, sizeof(*pCtx) + (n-1)*sizeof(sqlite3_value*));
+  if( pCtx==0 ) goto no_mem;
+  pCtx->pMem = 0;
+  pCtx->pFunc = pOp->p4.pFunc;
+  pCtx->iOp = (int)(pOp - aOp);
+  pCtx->pVdbe = p;
+  pCtx->argc = n;
+  pOp->p4type = P4_FUNCCTX;
+  pOp->p4.pCtx = pCtx;
+  pOp->opcode = OP_AggStep;
+  /* Fall through into OP_AggStep */
+}
+case OP_AggStep: {
   int i;
+  sqlite3_context *pCtx;
   Mem *pMem;
-  Mem *pRec;
-  sqlite3_context ctx;
-  sqlite3_value **apVal;
+  Mem t;
+
+  assert( pOp->p4type==P4_FUNCCTX );
+  pCtx = pOp->p4.pCtx;
+  pMem = &aMem[pOp->p3];
+
+  /* If this function is inside of a trigger, the register array in aMem[]
+  ** might change from one evaluation to the next.  The next block of code
+  ** checks to see if the register array has changed, and if so it
+  ** reinitializes the relavant parts of the sqlite3_context object */
+  if( pCtx->pMem != pMem ){
+    pCtx->pMem = pMem;
+    for(i=pCtx->argc-1; i>=0; i--) pCtx->argv[i] = &aMem[pOp->p2+i];
+  }
+
+#ifdef SQLITE_DEBUG
+  for(i=0; i<pCtx->argc; i++){
+    assert( memIsValid(pCtx->argv[i]) );
+    REGISTER_TRACE(pOp->p2+i, pCtx->argv[i]);
+  }
+#endif
 
-  n = pOp->p5;
-  assert( n>=0 );
-  pRec = &p->aMem[pOp->p2];
-  apVal = p->apArg;
-  assert( apVal || n==0 );
-  for(i=0; i<n; i++, pRec++){
-    apVal[i] = pRec;
-    storeTypeInfo(pRec, encoding);
-  }
-  ctx.pFunc = pOp->p4.pFunc;
-  assert( pOp->p3>0 && pOp->p3<=p->nMem );
-  ctx.pMem = pMem = &p->aMem[pOp->p3];
   pMem->n++;
-  ctx.s.flags = MEM_Null;
-  ctx.s.z = 0;
-  ctx.s.zMalloc = 0;
-  ctx.s.xDel = 0;
-  ctx.s.db = db;
-  ctx.isError = 0;
-  ctx.pColl = 0;
-  if( ctx.pFunc->flags & SQLITE_FUNC_NEEDCOLL ){
-    assert( pOp>p->aOp );
-    assert( pOp[-1].p4type==P4_COLLSEQ );
-    assert( pOp[-1].opcode==OP_CollSeq );
-    ctx.pColl = pOp[-1].p4.pColl;
+  sqlite3VdbeMemInit(&t, db, MEM_Null);
+  pCtx->pOut = &t;
+  pCtx->fErrorOrAux = 0;
+  pCtx->skipFlag = 0;
+  (pCtx->pFunc->xSFunc)(pCtx,pCtx->argc,pCtx->argv); /* IMP: R-24505-23230 */
+  if( pCtx->fErrorOrAux ){
+    if( pCtx->isError ){
+      sqlite3VdbeError(p, "%s", sqlite3_value_text(&t));
+      rc = pCtx->isError;
+    }
+    sqlite3VdbeMemRelease(&t);
+    if( rc ) goto abort_due_to_error;
+  }else{
+    assert( t.flags==MEM_Null );
   }
-  (ctx.pFunc->xStep)(&ctx, n, apVal);
-  if( ctx.isError ){
-    sqlite3SetString(&p->zErrMsg, db, "%s", sqlite3_value_text(&ctx.s));
-    rc = ctx.isError;
+  if( pCtx->skipFlag ){
+    assert( pOp[-1].opcode==OP_CollSeq );
+    i = pOp[-1].p1;
+    if( i ) sqlite3VdbeMemSetInt64(&aMem[i], 1);
   }
-  sqlite3VdbeMemRelease(&ctx.s);
   break;
 }
 
 /* Opcode: AggFinal P1 P2 * P4 *
+** Synopsis: accum=r[P1] N=P2
 **
 ** Execute the finalizer function for an aggregate.  P1 is
 ** the memory location that is the accumulator for the aggregate.
 **
 ** P2 is the number of arguments that the step function takes and
 ** P4 is a pointer to the FuncDef for this function.  The P2
