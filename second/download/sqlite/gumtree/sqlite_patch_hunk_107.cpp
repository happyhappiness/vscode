 ** This feature is used to implement "EXPLAIN".
 **
 ** When p->explain==1, each instruction is listed.  When
 ** p->explain==2, only OP_Explain instructions are listed and these
 ** are shown in a different format.  p->explain==2 is used to implement
 ** EXPLAIN QUERY PLAN.
-**
-** When p->explain==1, first the main program is listed, then each of
-** the trigger subprograms are listed one by one.
 */
 int sqlite3VdbeList(
   Vdbe *p                   /* The VDBE */
 ){
-  int nRow;                            /* Stop when row count reaches this */
-  int nSub = 0;                        /* Number of sub-vdbes seen so far */
-  SubProgram **apSub = 0;              /* Array of sub-vdbes */
-  Mem *pSub = 0;                       /* Memory cell hold array of subprogs */
-  sqlite3 *db = p->db;                 /* The database connection */
-  int i;                               /* Loop counter */
-  int rc = SQLITE_OK;                  /* Return code */
-  Mem *pMem = &p->aMem[1];             /* First Mem of result set */
+  sqlite3 *db = p->db;
+  int i;
+  int rc = SQLITE_OK;
+  Mem *pMem = p->pResultSet = &p->aMem[1];
 
   assert( p->explain );
-  assert( p->magic==VDBE_MAGIC_RUN );
+  if( p->magic!=VDBE_MAGIC_RUN ) return SQLITE_MISUSE;
+  assert( db->magic==SQLITE_MAGIC_BUSY );
   assert( p->rc==SQLITE_OK || p->rc==SQLITE_BUSY || p->rc==SQLITE_NOMEM );
 
   /* Even though this opcode does not use dynamic strings for
   ** the result, result columns may become dynamic if the user calls
   ** sqlite3_column_text16(), causing a translation to UTF-16 encoding.
   */
-  releaseMemArray(pMem, 8);
-  p->pResultSet = 0;
+  releaseMemArray(pMem, p->nMem);
 
-  if( p->rc==SQLITE_NOMEM_BKPT ){
+  if( p->rc==SQLITE_NOMEM ){
     /* This happens if a malloc() inside a call to sqlite3_column_text() or
     ** sqlite3_column_text16() failed.  */
-    sqlite3OomFault(db);
+    db->mallocFailed = 1;
     return SQLITE_ERROR;
   }
 
-  /* When the number of output rows reaches nRow, that means the
-  ** listing has finished and sqlite3_step() should return SQLITE_DONE.
-  ** nRow is the sum of the number of rows in the main program, plus
-  ** the sum of the number of rows in all trigger subprograms encountered
-  ** so far.  The nRow value will increase as new trigger subprograms are
-  ** encountered, but p->pc will eventually catch up to nRow.
-  */
-  nRow = p->nOp;
-  if( p->explain==1 ){
-    /* The first 8 memory cells are used for the result set.  So we will
-    ** commandeer the 9th cell to use as storage for an array of pointers
-    ** to trigger subprograms.  The VDBE is guaranteed to have at least 9
-    ** cells.  */
-    assert( p->nMem>9 );
-    pSub = &p->aMem[9];
-    if( pSub->flags&MEM_Blob ){
-      /* On the first call to sqlite3_step(), pSub will hold a NULL.  It is
-      ** initialized to a BLOB by the P4_SUBPROGRAM processing logic below */
-      nSub = pSub->n/sizeof(Vdbe*);
-      apSub = (SubProgram **)pSub->z;
-    }
-    for(i=0; i<nSub; i++){
-      nRow += apSub[i]->nOp;
-    }
-  }
-
   do{
     i = p->pc++;
-  }while( i<nRow && p->explain==2 && p->aOp[i].opcode!=OP_Explain );
-  if( i>=nRow ){
+  }while( i<p->nOp && p->explain==2 && p->aOp[i].opcode!=OP_Explain );
+  if( i>=p->nOp ){
     p->rc = SQLITE_OK;
     rc = SQLITE_DONE;
   }else if( db->u1.isInterrupted ){
     p->rc = SQLITE_INTERRUPT;
     rc = SQLITE_ERROR;
-    sqlite3VdbeError(p, sqlite3ErrStr(p->rc));
+    sqlite3SetString(&p->zErrMsg, db, "%s", sqlite3ErrStr(p->rc));
   }else{
-    char *zP4;
-    Op *pOp;
-    if( i<p->nOp ){
-      /* The output line number is small enough that we are still in the
-      ** main program. */
-      pOp = &p->aOp[i];
-    }else{
-      /* We are currently listing subprograms.  Figure out which one and
-      ** pick up the appropriate opcode. */
-      int j;
-      i -= p->nOp;
-      for(j=0; i>=apSub[j]->nOp; j++){
-        i -= apSub[j]->nOp;
-      }
-      pOp = &apSub[j]->aOp[i];
-    }
+    char *z;
+    Op *pOp = &p->aOp[i];
     if( p->explain==1 ){
       pMem->flags = MEM_Int;
+      pMem->type = SQLITE_INTEGER;
       pMem->u.i = i;                                /* Program counter */
       pMem++;
   
       pMem->flags = MEM_Static|MEM_Str|MEM_Term;
-      pMem->z = (char*)sqlite3OpcodeName(pOp->opcode); /* Opcode */
+      pMem->z = (char*)sqlite3OpcodeName(pOp->opcode);  /* Opcode */
       assert( pMem->z!=0 );
       pMem->n = sqlite3Strlen30(pMem->z);
+      pMem->type = SQLITE_TEXT;
       pMem->enc = SQLITE_UTF8;
       pMem++;
-
-      /* When an OP_Program opcode is encounter (the only opcode that has
-      ** a P4_SUBPROGRAM argument), expand the size of the array of subprograms
-      ** kept in p->aMem[9].z to hold the new program - assuming this subprogram
-      ** has not already been seen.
-      */
-      if( pOp->p4type==P4_SUBPROGRAM ){
-        int nByte = (nSub+1)*sizeof(SubProgram*);
-        int j;
-        for(j=0; j<nSub; j++){
-          if( apSub[j]==pOp->p4.pProgram ) break;
-        }
-        if( j==nSub && SQLITE_OK==sqlite3VdbeMemGrow(pSub, nByte, nSub!=0) ){
-          apSub = (SubProgram **)pSub->z;
-          apSub[nSub++] = pOp->p4.pProgram;
-          pSub->flags |= MEM_Blob;
-          pSub->n = nSub*sizeof(SubProgram*);
-        }
-      }
     }
 
     pMem->flags = MEM_Int;
     pMem->u.i = pOp->p1;                          /* P1 */
+    pMem->type = SQLITE_INTEGER;
     pMem++;
 
     pMem->flags = MEM_Int;
     pMem->u.i = pOp->p2;                          /* P2 */
+    pMem->type = SQLITE_INTEGER;
     pMem++;
 
-    pMem->flags = MEM_Int;
-    pMem->u.i = pOp->p3;                          /* P3 */
-    pMem++;
+    if( p->explain==1 ){
+      pMem->flags = MEM_Int;
+      pMem->u.i = pOp->p3;                          /* P3 */
+      pMem->type = SQLITE_INTEGER;
+      pMem++;
+    }
 
-    if( sqlite3VdbeMemClearAndResize(pMem, 100) ){ /* P4 */
+    if( sqlite3VdbeMemGrow(pMem, 32, 0) ){            /* P4 */
       assert( p->db->mallocFailed );
       return SQLITE_ERROR;
     }
-    pMem->flags = MEM_Str|MEM_Term;
-    zP4 = displayP4(pOp, pMem->z, pMem->szMalloc);
-    if( zP4!=pMem->z ){
-      pMem->n = 0;
-      sqlite3VdbeMemSetStr(pMem, zP4, -1, SQLITE_UTF8, 0);
+    pMem->flags = MEM_Dyn|MEM_Str|MEM_Term;
+    z = displayP4(pOp, pMem->z, 32);
+    if( z!=pMem->z ){
+      sqlite3VdbeMemSetStr(pMem, z, -1, SQLITE_UTF8, 0);
     }else{
       assert( pMem->z!=0 );
       pMem->n = sqlite3Strlen30(pMem->z);
       pMem->enc = SQLITE_UTF8;
     }
+    pMem->type = SQLITE_TEXT;
     pMem++;
 
     if( p->explain==1 ){
-      if( sqlite3VdbeMemClearAndResize(pMem, 4) ){
+      if( sqlite3VdbeMemGrow(pMem, 4, 0) ){
         assert( p->db->mallocFailed );
         return SQLITE_ERROR;
       }
-      pMem->flags = MEM_Str|MEM_Term;
+      pMem->flags = MEM_Dyn|MEM_Str|MEM_Term;
       pMem->n = 2;
       sqlite3_snprintf(3, pMem->z, "%.2x", pOp->p5);   /* P5 */
+      pMem->type = SQLITE_TEXT;
       pMem->enc = SQLITE_UTF8;
       pMem++;
   
-#ifdef SQLITE_ENABLE_EXPLAIN_COMMENTS
-      if( sqlite3VdbeMemClearAndResize(pMem, 500) ){
-        assert( p->db->mallocFailed );
-        return SQLITE_ERROR;
-      }
-      pMem->flags = MEM_Str|MEM_Term;
-      pMem->n = displayComment(pOp, zP4, pMem->z, 500);
-      pMem->enc = SQLITE_UTF8;
-#else
-      pMem->flags = MEM_Null;                       /* Comment */
+#ifdef SQLITE_DEBUG
+      if( pOp->zComment ){
+        pMem->flags = MEM_Str|MEM_Term;
+        pMem->z = pOp->zComment;
+        pMem->n = sqlite3Strlen30(pMem->z);
+        pMem->enc = SQLITE_UTF8;
+        pMem->type = SQLITE_TEXT;
+      }else
 #endif
+      {
+        pMem->flags = MEM_Null;                       /* Comment */
+        pMem->type = SQLITE_NULL;
+      }
     }
 
-    p->nResColumn = 8 - 4*(p->explain-1);
-    p->pResultSet = &p->aMem[1];
+    p->nResColumn = 8 - 5*(p->explain-1);
     p->rc = SQLITE_OK;
     rc = SQLITE_ROW;
   }
   return rc;
 }
 #endif /* SQLITE_OMIT_EXPLAIN */
 
 #ifdef SQLITE_DEBUG
 /*
 ** Print the SQL that was used to generate a VDBE program.
 */
 void sqlite3VdbePrintSql(Vdbe *p){
-  const char *z = 0;
-  if( p->zSql ){
-    z = p->zSql;
-  }else if( p->nOp>=1 ){
-    const VdbeOp *pOp = &p->aOp[0];
-    if( pOp->opcode==OP_Init && pOp->p4.z!=0 ){
-      z = pOp->p4.z;
-      while( sqlite3Isspace(*z) ) z++;
-    }
+  int nOp = p->nOp;
+  VdbeOp *pOp;
+  if( nOp<1 ) return;
+  pOp = &p->aOp[0];
+  if( pOp->opcode==OP_Trace && pOp->p4.z!=0 ){
+    const char *z = pOp->p4.z;
+    while( sqlite3Isspace(*z) ) z++;
+    printf("SQL: [%s]\n", z);
   }
-  if( z ) printf("SQL: [%s]\n", z);
 }
 #endif
 
 #if !defined(SQLITE_OMIT_TRACE) && defined(SQLITE_ENABLE_IOTRACE)
 /*
 ** Print an IOTRACE message showing SQL content.
