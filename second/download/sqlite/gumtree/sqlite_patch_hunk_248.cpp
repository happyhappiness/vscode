 ** if P2==OE_Fail. Do the rollback if P2==OE_Rollback.  If P2==OE_Abort,
 ** then back out all changes that have occurred during this execution of the
 ** VDBE, but do not rollback the transaction. 
 **
 ** If P4 is not null then it is an error message string.
 **
+** P5 is a value between 0 and 4, inclusive, that modifies the P4 string.
+**
+**    0:  (no change)
+**    1:  NOT NULL contraint failed: P4
+**    2:  UNIQUE constraint failed: P4
+**    3:  CHECK constraint failed: P4
+**    4:  FOREIGN KEY constraint failed: P4
+**
+** If P5 is not zero and P4 is NULL, then everything after the ":" is
+** omitted.
+**
 ** There is an implied "Halt 0 0 0" instruction inserted at the very end of
 ** every program.  So a jump past the last instruction of the program
 ** is the same as executing Halt.
 */
 case OP_Halt: {
+  VdbeFrame *pFrame;
+  int pcx;
+
+  pcx = (int)(pOp - aOp);
+  if( pOp->p1==SQLITE_OK && p->pFrame ){
+    /* Halt the sub-program. Return control to the parent frame. */
+    pFrame = p->pFrame;
+    p->pFrame = pFrame->pParent;
+    p->nFrame--;
+    sqlite3VdbeSetChanges(db, p->nChange);
+    pcx = sqlite3VdbeFrameRestore(pFrame);
+    if( pOp->p2==OE_Ignore ){
+      /* Instruction pcx is the OP_Program that invoked the sub-program 
+      ** currently being halted. If the p2 instruction of this OP_Halt
+      ** instruction is set to OE_Ignore, then the sub-program is throwing
+      ** an IGNORE exception. In this case jump to the address specified
+      ** as the p2 of the calling OP_Program.  */
+      pcx = p->aOp[pcx].p2-1;
+    }
+    aOp = p->aOp;
+    aMem = p->aMem;
+    pOp = &aOp[pcx];
+    break;
+  }
   p->rc = pOp->p1;
-  p->pc = pc;
-  p->errorAction = pOp->p2;
-  if( pOp->p4.z ){
-    sqlite3SetString(&p->zErrMsg, db, "%s", pOp->p4.z);
+  p->errorAction = (u8)pOp->p2;
+  p->pc = pcx;
+  assert( pOp->p5<=4 );
+  if( p->rc ){
+    if( pOp->p5 ){
+      static const char * const azType[] = { "NOT NULL", "UNIQUE", "CHECK",
+                                             "FOREIGN KEY" };
+      testcase( pOp->p5==1 );
+      testcase( pOp->p5==2 );
+      testcase( pOp->p5==3 );
+      testcase( pOp->p5==4 );
+      sqlite3VdbeError(p, "%s constraint failed", azType[pOp->p5-1]);
+      if( pOp->p4.z ){
+        p->zErrMsg = sqlite3MPrintf(db, "%z: %s", p->zErrMsg, pOp->p4.z);
+      }
+    }else{
+      sqlite3VdbeError(p, "%s", pOp->p4.z);
+    }
+    sqlite3_log(pOp->p1, "abort at %d in [%s]: %s", pcx, p->zSql, p->zErrMsg);
   }
   rc = sqlite3VdbeHalt(p);
-  assert( rc==SQLITE_BUSY || rc==SQLITE_OK );
+  assert( rc==SQLITE_BUSY || rc==SQLITE_OK || rc==SQLITE_ERROR );
   if( rc==SQLITE_BUSY ){
-    p->rc = rc = SQLITE_BUSY;
+    p->rc = SQLITE_BUSY;
   }else{
+    assert( rc==SQLITE_OK || (p->rc&0xff)==SQLITE_CONSTRAINT );
+    assert( rc==SQLITE_OK || db->nDeferredCons>0 || db->nDeferredImmCons>0 );
     rc = p->rc ? SQLITE_ERROR : SQLITE_DONE;
   }
   goto vdbe_return;
 }
 
 /* Opcode: Integer P1 P2 * * *
+** Synopsis: r[P2]=P1
 **
 ** The 32-bit integer value P1 is written into register P2.
 */
-case OP_Integer: {         /* out2-prerelease */
-  pOut->flags = MEM_Int;
+case OP_Integer: {         /* out2 */
+  pOut = out2Prerelease(p, pOp);
   pOut->u.i = pOp->p1;
   break;
 }
 
 /* Opcode: Int64 * P2 * P4 *
+** Synopsis: r[P2]=P4
 **
 ** P4 is a pointer to a 64-bit integer value.
 ** Write that value into register P2.
 */
-case OP_Int64: {           /* out2-prerelease */
+case OP_Int64: {           /* out2 */
+  pOut = out2Prerelease(p, pOp);
   assert( pOp->p4.pI64!=0 );
-  pOut->flags = MEM_Int;
   pOut->u.i = *pOp->p4.pI64;
   break;
 }
 
+#ifndef SQLITE_OMIT_FLOATING_POINT
 /* Opcode: Real * P2 * P4 *
+** Synopsis: r[P2]=P4
 **
 ** P4 is a pointer to a 64-bit floating point value.
 ** Write that value into register P2.
 */
-case OP_Real: {            /* same as TK_FLOAT, out2-prerelease */
+case OP_Real: {            /* same as TK_FLOAT, out2 */
+  pOut = out2Prerelease(p, pOp);
   pOut->flags = MEM_Real;
   assert( !sqlite3IsNaN(*pOp->p4.pReal) );
-  pOut->r = *pOp->p4.pReal;
+  pOut->u.r = *pOp->p4.pReal;
   break;
 }
+#endif
 
 /* Opcode: String8 * P2 * P4 *
+** Synopsis: r[P2]='P4'
 **
 ** P4 points to a nul terminated UTF-8 string. This opcode is transformed 
-** into an OP_String before it is executed for the first time.
+** into a String opcode before it is executed for the first time.  During
+** this transformation, the length of string P4 is computed and stored
+** as the P1 parameter.
 */
-case OP_String8: {         /* same as TK_STRING, out2-prerelease */
+case OP_String8: {         /* same as TK_STRING, out2 */
   assert( pOp->p4.z!=0 );
+  pOut = out2Prerelease(p, pOp);
   pOp->opcode = OP_String;
   pOp->p1 = sqlite3Strlen30(pOp->p4.z);
 
 #ifndef SQLITE_OMIT_UTF16
   if( encoding!=SQLITE_UTF8 ){
-    sqlite3VdbeMemSetStr(pOut, pOp->p4.z, -1, SQLITE_UTF8, SQLITE_STATIC);
+    rc = sqlite3VdbeMemSetStr(pOut, pOp->p4.z, -1, SQLITE_UTF8, SQLITE_STATIC);
+    assert( rc==SQLITE_OK || rc==SQLITE_TOOBIG );
     if( SQLITE_OK!=sqlite3VdbeChangeEncoding(pOut, encoding) ) goto no_mem;
-    if( SQLITE_OK!=sqlite3VdbeMemMakeWriteable(pOut) ) goto no_mem;
-    pOut->zMalloc = 0;
+    assert( pOut->szMalloc>0 && pOut->zMalloc==pOut->z );
+    assert( VdbeMemDynamic(pOut)==0 );
+    pOut->szMalloc = 0;
     pOut->flags |= MEM_Static;
-    pOut->flags &= ~MEM_Dyn;
     if( pOp->p4type==P4_DYNAMIC ){
       sqlite3DbFree(db, pOp->p4.z);
     }
     pOp->p4type = P4_DYNAMIC;
     pOp->p4.z = pOut->z;
     pOp->p1 = pOut->n;
-    if( pOp->p1>db->aLimit[SQLITE_LIMIT_LENGTH] ){
-      goto too_big;
-    }
-    UPDATE_MAX_BLOBSIZE(pOut);
-    break;
   }
+  testcase( rc==SQLITE_TOOBIG );
 #endif
   if( pOp->p1>db->aLimit[SQLITE_LIMIT_LENGTH] ){
     goto too_big;
   }
+  assert( rc==SQLITE_OK );
   /* Fall through to the next case, OP_String */
 }
   
-/* Opcode: String P1 P2 * P4 *
+/* Opcode: String P1 P2 P3 P4 P5
+** Synopsis: r[P2]='P4' (len=P1)
 **
 ** The string value P4 of length P1 (bytes) is stored in register P2.
+**
+** If P3 is not zero and the content of register P3 is equal to P5, then
+** the datatype of the register P2 is converted to BLOB.  The content is
+** the same sequence of bytes, it is merely interpreted as a BLOB instead
+** of a string, as if it had been CAST.  In other words:
+**
+** if( P3!=0 and reg[P3]==P5 ) reg[P2] := CAST(reg[P2] as BLOB)
 */
-case OP_String: {          /* out2-prerelease */
+case OP_String: {          /* out2 */
   assert( pOp->p4.z!=0 );
+  pOut = out2Prerelease(p, pOp);
   pOut->flags = MEM_Str|MEM_Static|MEM_Term;
   pOut->z = pOp->p4.z;
   pOut->n = pOp->p1;
   pOut->enc = encoding;
   UPDATE_MAX_BLOBSIZE(pOut);
+#ifndef SQLITE_LIKE_DOESNT_MATCH_BLOBS
+  if( pOp->p3>0 ){
+    assert( pOp->p3<=(p->nMem+1 - p->nCursor) );
+    pIn3 = &aMem[pOp->p3];
+    assert( pIn3->flags & MEM_Int );
+    if( pIn3->u.i==pOp->p5 ) pOut->flags = MEM_Blob|MEM_Static|MEM_Term;
+  }
+#endif
   break;
 }
 
-/* Opcode: Null * P2 * * *
+/* Opcode: Null P1 P2 P3 * *
+** Synopsis: r[P2..P3]=NULL
 **
-** Write a NULL into register P2.
+** Write a NULL into registers P2.  If P3 greater than P2, then also write
+** NULL into register P3 and every register in between P2 and P3.  If P3
+** is less than P2 (typically P3 is zero) then only register P2 is
+** set to NULL.
+**
+** If the P1 value is non-zero, then also set the MEM_Cleared flag so that
+** NULL values will not compare equal even if SQLITE_NULLEQ is set on
+** OP_Ne or OP_Eq.
 */
-case OP_Null: {           /* out2-prerelease */
+case OP_Null: {           /* out2 */
+  int cnt;
+  u16 nullFlag;
+  pOut = out2Prerelease(p, pOp);
+  cnt = pOp->p3-pOp->p2;
+  assert( pOp->p3<=(p->nMem+1 - p->nCursor) );
+  pOut->flags = nullFlag = pOp->p1 ? (MEM_Null|MEM_Cleared) : MEM_Null;
+  pOut->n = 0;
+  while( cnt>0 ){
+    pOut++;
+    memAboutToChange(p, pOut);
+    sqlite3VdbeMemSetNull(pOut);
+    pOut->flags = nullFlag;
+    pOut->n = 0;
+    cnt--;
+  }
   break;
 }
 
+/* Opcode: SoftNull P1 * * * *
+** Synopsis: r[P1]=NULL
+**
+** Set register P1 to have the value NULL as seen by the OP_MakeRecord
+** instruction, but do not free any string or blob memory associated with
+** the register, so that if the value was a string or blob that was
+** previously copied using OP_SCopy, the copies will continue to be valid.
+*/
+case OP_SoftNull: {
+  assert( pOp->p1>0 && pOp->p1<=(p->nMem+1 - p->nCursor) );
+  pOut = &aMem[pOp->p1];
+  pOut->flags = (pOut->flags&~(MEM_Undefined|MEM_AffMask))|MEM_Null;
+  break;
+}
 
-/* Opcode: Blob P1 P2 * P4
+/* Opcode: Blob P1 P2 * P4 *
+** Synopsis: r[P2]=P4 (len=P1)
 **
 ** P4 points to a blob of data P1 bytes long.  Store this
-** blob in register P2. This instruction is not coded directly
-** by the compiler. Instead, the compiler layer specifies
-** an OP_HexBlob opcode, with the hex string representation of
-** the blob as P4. This opcode is transformed to an OP_Blob
-** the first time it is executed.
+** blob in register P2.
 */
-case OP_Blob: {                /* out2-prerelease */
+case OP_Blob: {                /* out2 */
   assert( pOp->p1 <= SQLITE_MAX_LENGTH );
+  pOut = out2Prerelease(p, pOp);
   sqlite3VdbeMemSetStr(pOut, pOp->p4.z, pOp->p1, 0, 0);
   pOut->enc = encoding;
   UPDATE_MAX_BLOBSIZE(pOut);
   break;
 }
 
-/* Opcode: Variable P1 P2 P3 P4 *
+/* Opcode: Variable P1 P2 * P4 *
+** Synopsis: r[P2]=parameter(P1,P4)
 **
-** Transfer the values of bound parameters P1..P1+P3-1 into registers
-** P2..P2+P3-1.
+** Transfer the values of bound parameter P1 into register P2
 **
-** If the parameter is named, then its name appears in P4 and P3==1.
+** If the parameter is named, then its name appears in P4.
 ** The P4 value is used by sqlite3_bind_parameter_name().
 */
-case OP_Variable: {
-  int p1;          /* Variable to copy from */
-  int p2;          /* Register to copy to */
-  int n;           /* Number of values left to copy */
+case OP_Variable: {            /* out2 */
   Mem *pVar;       /* Value being transferred */
 
-  p1 = pOp->p1 - 1;
-  p2 = pOp->p2;
-  n = pOp->p3;
-  assert( p1>=0 && p1+n<=p->nVar );
-  assert( p2>=1 && p2+n-1<=p->nMem );
-  assert( pOp->p4.z==0 || pOp->p3==1 );
-
-  while( n-- > 0 ){
-    pVar = &p->aVar[p1++];
-    if( sqlite3VdbeMemTooBig(pVar) ){
-      goto too_big;
-    }
-    pOut = &p->aMem[p2++];
-    sqlite3VdbeMemReleaseExternal(pOut);
-    pOut->flags = MEM_Null;
-    sqlite3VdbeMemShallowCopy(pOut, pVar, MEM_Static);
-    UPDATE_MAX_BLOBSIZE(pOut);
+  assert( pOp->p1>0 && pOp->p1<=p->nVar );
+  assert( pOp->p4.z==0 || pOp->p4.z==sqlite3VListNumToName(p->pVList,pOp->p1) );
+  pVar = &p->aVar[pOp->p1 - 1];
+  if( sqlite3VdbeMemTooBig(pVar) ){
+    goto too_big;
   }
+  pOut = &aMem[pOp->p2];
+  sqlite3VdbeMemShallowCopy(pOut, pVar, MEM_Static);
+  UPDATE_MAX_BLOBSIZE(pOut);
   break;
 }
 
 /* Opcode: Move P1 P2 P3 * *
+** Synopsis: r[P2@P3]=r[P1@P3]
 **
-** Move the values in register P1..P1+P3-1 over into
-** registers P2..P2+P3-1.  Registers P1..P1+P1-1 are
+** Move the P3 values in register P1..P1+P3-1 over into
+** registers P2..P2+P3-1.  Registers P1..P1+P3-1 are
 ** left holding a NULL.  It is an error for register ranges
-** P1..P1+P3-1 and P2..P2+P3-1 to overlap.
+** P1..P1+P3-1 and P2..P2+P3-1 to overlap.  It is an error
+** for P3 to be less than 1.
 */
 case OP_Move: {
-  char *zMalloc;   /* Holding variable for allocated memory */
   int n;           /* Number of registers left to copy */
   int p1;          /* Register to copy from */
   int p2;          /* Register to copy to */
 
   n = pOp->p3;
   p1 = pOp->p1;
   p2 = pOp->p2;
   assert( n>0 && p1>0 && p2>0 );
   assert( p1+n<=p2 || p2+n<=p1 );
 
-  pIn1 = &p->aMem[p1];
-  pOut = &p->aMem[p2];
-  while( n-- ){
-    assert( pOut<=&p->aMem[p->nMem] );
-    assert( pIn1<=&p->aMem[p->nMem] );
-    zMalloc = pOut->zMalloc;
-    pOut->zMalloc = 0;
+  pIn1 = &aMem[p1];
+  pOut = &aMem[p2];
+  do{
+    assert( pOut<=&aMem[(p->nMem+1 - p->nCursor)] );
+    assert( pIn1<=&aMem[(p->nMem+1 - p->nCursor)] );
+    assert( memIsValid(pIn1) );
+    memAboutToChange(p, pOut);
     sqlite3VdbeMemMove(pOut, pIn1);
-    pIn1->zMalloc = zMalloc;
+#ifdef SQLITE_DEBUG
+    if( pOut->pScopyFrom>=&aMem[p1] && pOut->pScopyFrom<pOut ){
+      pOut->pScopyFrom += pOp->p2 - p1;
+    }
+#endif
+    Deephemeralize(pOut);
     REGISTER_TRACE(p2++, pOut);
     pIn1++;
     pOut++;
-  }
+  }while( --n );
   break;
 }
 
-/* Opcode: Copy P1 P2 * * *
+/* Opcode: Copy P1 P2 P3 * *
+** Synopsis: r[P2@P3+1]=r[P1@P3+1]
 **
-** Make a copy of register P1 into register P2.
+** Make a copy of registers P1..P1+P3 into registers P2..P2+P3.
 **
 ** This instruction makes a deep copy of the value.  A duplicate
 ** is made of any string or blob constant.  See also OP_SCopy.
 */
-case OP_Copy: {             /* in1 */
-  assert( pOp->p2>0 );
-  assert( pOp->p2<=p->nMem );
-  pOut = &p->aMem[pOp->p2];
+case OP_Copy: {
+  int n;
+
+  n = pOp->p3;
+  pIn1 = &aMem[pOp->p1];
+  pOut = &aMem[pOp->p2];
   assert( pOut!=pIn1 );
-  sqlite3VdbeMemShallowCopy(pOut, pIn1, MEM_Ephem);
-  Deephemeralize(pOut);
-  REGISTER_TRACE(pOp->p2, pOut);
+  while( 1 ){
+    sqlite3VdbeMemShallowCopy(pOut, pIn1, MEM_Ephem);
+    Deephemeralize(pOut);
+#ifdef SQLITE_DEBUG
+    pOut->pScopyFrom = 0;
+#endif
+    REGISTER_TRACE(pOp->p2+pOp->p3-n, pOut);
+    if( (n--)==0 ) break;
+    pOut++;
+    pIn1++;
+  }
   break;
 }
 
 /* Opcode: SCopy P1 P2 * * *
+** Synopsis: r[P2]=r[P1]
 **
 ** Make a shallow copy of register P1 into register P2.
 **
 ** This instruction makes a shallow copy of the value.  If the value
 ** is a string or blob, then the copy is only a pointer to the
 ** original and hence if the original changes so will the copy.
 ** Worse, if the original is deallocated, the copy becomes invalid.
 ** Thus the program must guarantee that the original will not change
 ** during the lifetime of the copy.  Use OP_Copy to make a complete
 ** copy.
 */
-case OP_SCopy: {            /* in1 */
-  REGISTER_TRACE(pOp->p1, pIn1);
-  assert( pOp->p2>0 );
-  assert( pOp->p2<=p->nMem );
-  pOut = &p->aMem[pOp->p2];
+case OP_SCopy: {            /* out2 */
+  pIn1 = &aMem[pOp->p1];
+  pOut = &aMem[pOp->p2];
   assert( pOut!=pIn1 );
   sqlite3VdbeMemShallowCopy(pOut, pIn1, MEM_Ephem);
-  REGISTER_TRACE(pOp->p2, pOut);
+#ifdef SQLITE_DEBUG
+  if( pOut->pScopyFrom==0 ) pOut->pScopyFrom = pIn1;
+#endif
+  break;
+}
+
+/* Opcode: IntCopy P1 P2 * * *
+** Synopsis: r[P2]=r[P1]
+**
+** Transfer the integer value held in register P1 into register P2.
+**
+** This is an optimized version of SCopy that works only for integer
+** values.
+*/
+case OP_IntCopy: {            /* out2 */
+  pIn1 = &aMem[pOp->p1];
+  assert( (pIn1->flags & MEM_Int)!=0 );
+  pOut = &aMem[pOp->p2];
+  sqlite3VdbeMemSetInt64(pOut, pIn1->u.i);
   break;
 }
 
 /* Opcode: ResultRow P1 P2 * * *
+** Synopsis: output=r[P1@P2]
 **
 ** The registers P1 through P1+P2-1 contain a single row of
 ** results. This opcode causes the sqlite3_step() call to terminate
 ** with an SQLITE_ROW return code and it sets up the sqlite3_stmt
-** structure to provide access to the top P1 values as the result
-** row.
+** structure to provide access to the r(P1)..r(P1+P2-1) values as
+** the result row.
 */
 case OP_ResultRow: {
   Mem *pMem;
   int i;
   assert( p->nResColumn==pOp->p2 );
   assert( pOp->p1>0 );
-  assert( pOp->p1+pOp->p2<=p->nMem+1 );
+  assert( pOp->p1+pOp->p2<=(p->nMem+1 - p->nCursor)+1 );
 
-  /* If the SQLITE_CountRows flag is set in sqlite3.flags mask, then 
-  ** DML statements invoke this opcode to return the number of rows 
-  ** modified to the user. This is the only way that a VM that
-  ** opens a statement transaction may invoke this opcode.
+#ifndef SQLITE_OMIT_PROGRESS_CALLBACK
+  /* Run the progress counter just before returning.
+  */
+  if( db->xProgress!=0
+   && nVmStep>=nProgressLimit 
+   && db->xProgress(db->pProgressArg)!=0
+  ){
+    rc = SQLITE_INTERRUPT;
+    goto abort_due_to_error;
+  }
+#endif
+
+  /* If this statement has violated immediate foreign key constraints, do
+  ** not return the number of rows modified. And do not RELEASE the statement
+  ** transaction. It needs to be rolled back.  */
+  if( SQLITE_OK!=(rc = sqlite3VdbeCheckFk(p, 0)) ){
+    assert( db->flags&SQLITE_CountRows );
+    assert( p->usesStmtJournal );
+    goto abort_due_to_error;
+  }
+
+  /* If the SQLITE_CountRows flag is set in sqlite3.flags mask, then 
+  ** DML statements invoke this opcode to return the number of rows 
+  ** modified to the user. This is the only way that a VM that
+  ** opens a statement transaction may invoke this opcode.
   **
   ** In case this is such a statement, close any statement transaction
   ** opened by this VM before returning control to the user. This is to
   ** ensure that statement-transactions are always nested, not overlapping.
   ** If the open statement-transaction is not closed here, then the user
   ** may step another VM that opens its own statement transaction. This
   ** may lead to overlapping statement transactions.
+  **
+  ** The statement transaction is never a top-level transaction.  Hence
+  ** the RELEASE call below can never fail.
   */
   assert( p->iStatement==0 || db->flags&SQLITE_CountRows );
-  if( SQLITE_OK!=(rc = sqlite3VdbeCloseStatement(p, SAVEPOINT_RELEASE)) ){
-    break;
-  }
+  rc = sqlite3VdbeCloseStatement(p, SAVEPOINT_RELEASE);
+  assert( rc==SQLITE_OK );
 
   /* Invalidate all ephemeral cursor row caches */
   p->cacheCtr = (p->cacheCtr + 2)|1;
 
   /* Make sure the results of the current row are \000 terminated
   ** and have an assigned type.  The results are de-ephemeralized as
-  ** as side effect.
+  ** a side effect.
   */
-  pMem = p->pResultSet = &p->aMem[pOp->p1];
+  pMem = p->pResultSet = &aMem[pOp->p1];
   for(i=0; i<pOp->p2; i++){
+    assert( memIsValid(&pMem[i]) );
+    Deephemeralize(&pMem[i]);
+    assert( (pMem[i].flags & MEM_Ephem)==0
+            || (pMem[i].flags & (MEM_Str|MEM_Blob))==0 );
     sqlite3VdbeMemNulTerminate(&pMem[i]);
-    storeTypeInfo(&pMem[i], encoding);
     REGISTER_TRACE(pOp->p1+i, &pMem[i]);
   }
   if( db->mallocFailed ) goto no_mem;
 
+  if( db->mTrace & SQLITE_TRACE_ROW ){
+    db->xTrace(SQLITE_TRACE_ROW, db->pTraceArg, p, 0);
+  }
+
   /* Return SQLITE_ROW
   */
-  p->pc = pc + 1;
+  p->pc = (int)(pOp - aOp) + 1;
   rc = SQLITE_ROW;
   goto vdbe_return;
 }
 
 /* Opcode: Concat P1 P2 P3 * *
+** Synopsis: r[P3]=r[P2]+r[P1]
 **
 ** Add the text in register P1 onto the end of the text in
 ** register P2 and store the result in register P3.
 ** If either the P1 or P2 text are NULL then store NULL in P3.
 **
 **   P3 = P2 || P1
