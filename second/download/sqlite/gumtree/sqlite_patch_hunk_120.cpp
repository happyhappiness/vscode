 ** functions that can take varying numbers of arguments.  The
 ** P4 argument is only needed for the degenerate case where
 ** the step function was not previously called.
 */
 case OP_AggFinal: {
   Mem *pMem;
-  assert( pOp->p1>0 && pOp->p1<=(p->nMem+1 - p->nCursor) );
-  pMem = &aMem[pOp->p1];
+  assert( pOp->p1>0 && pOp->p1<=p->nMem );
+  pMem = &p->aMem[pOp->p1];
   assert( (pMem->flags & ~(MEM_Null|MEM_Agg))==0 );
   rc = sqlite3VdbeMemFinalize(pMem, pOp->p4.pFunc);
-  if( rc ){
-    sqlite3VdbeError(p, "%s", sqlite3_value_text(pMem));
-    goto abort_due_to_error;
+  if( rc==SQLITE_ERROR ){
+    sqlite3SetString(&p->zErrMsg, db, "%s", sqlite3_value_text(pMem));
   }
   sqlite3VdbeChangeEncoding(pMem, encoding);
   UPDATE_MAX_BLOBSIZE(pMem);
   if( sqlite3VdbeMemTooBig(pMem) ){
     goto too_big;
   }
   break;
 }
 
-#ifndef SQLITE_OMIT_WAL
-/* Opcode: Checkpoint P1 P2 P3 * *
-**
-** Checkpoint database P1. This is a no-op if P1 is not currently in
-** WAL mode. Parameter P2 is one of SQLITE_CHECKPOINT_PASSIVE, FULL,
-** RESTART, or TRUNCATE.  Write 1 or 0 into mem[P3] if the checkpoint returns
-** SQLITE_BUSY or not, respectively.  Write the number of pages in the
-** WAL after the checkpoint into mem[P3+1] and the number of pages
-** in the WAL that have been checkpointed after the checkpoint
-** completes into mem[P3+2].  However on an error, mem[P3+1] and
-** mem[P3+2] are initialized to -1.
-*/
-case OP_Checkpoint: {
-  int i;                          /* Loop counter */
-  int aRes[3];                    /* Results */
-  Mem *pMem;                      /* Write results here */
-
-  assert( p->readOnly==0 );
-  aRes[0] = 0;
-  aRes[1] = aRes[2] = -1;
-  assert( pOp->p2==SQLITE_CHECKPOINT_PASSIVE
-       || pOp->p2==SQLITE_CHECKPOINT_FULL
-       || pOp->p2==SQLITE_CHECKPOINT_RESTART
-       || pOp->p2==SQLITE_CHECKPOINT_TRUNCATE
-  );
-  rc = sqlite3Checkpoint(db, pOp->p1, pOp->p2, &aRes[1], &aRes[2]);
-  if( rc ){
-    if( rc!=SQLITE_BUSY ) goto abort_due_to_error;
-    rc = SQLITE_OK;
-    aRes[0] = 1;
-  }
-  for(i=0, pMem = &aMem[pOp->p3]; i<3; i++, pMem++){
-    sqlite3VdbeMemSetInt64(pMem, (i64)aRes[i]);
-  }    
-  break;
-};  
-#endif
-
-#ifndef SQLITE_OMIT_PRAGMA
-/* Opcode: JournalMode P1 P2 P3 * *
-**
-** Change the journal mode of database P1 to P3. P3 must be one of the
-** PAGER_JOURNALMODE_XXX values. If changing between the various rollback
-** modes (delete, truncate, persist, off and memory), this is a simple
-** operation. No IO is required.
-**
-** If changing into or out of WAL mode the procedure is more complicated.
-**
-** Write a string containing the final journal-mode to register P2.
-*/
-case OP_JournalMode: {    /* out2 */
-  Btree *pBt;                     /* Btree to change journal mode of */
-  Pager *pPager;                  /* Pager associated with pBt */
-  int eNew;                       /* New journal mode */
-  int eOld;                       /* The old journal mode */
-#ifndef SQLITE_OMIT_WAL
-  const char *zFilename;          /* Name of database file for pPager */
-#endif
-
-  pOut = out2Prerelease(p, pOp);
-  eNew = pOp->p3;
-  assert( eNew==PAGER_JOURNALMODE_DELETE 
-       || eNew==PAGER_JOURNALMODE_TRUNCATE 
-       || eNew==PAGER_JOURNALMODE_PERSIST 
-       || eNew==PAGER_JOURNALMODE_OFF
-       || eNew==PAGER_JOURNALMODE_MEMORY
-       || eNew==PAGER_JOURNALMODE_WAL
-       || eNew==PAGER_JOURNALMODE_QUERY
-  );
-  assert( pOp->p1>=0 && pOp->p1<db->nDb );
-  assert( p->readOnly==0 );
-
-  pBt = db->aDb[pOp->p1].pBt;
-  pPager = sqlite3BtreePager(pBt);
-  eOld = sqlite3PagerGetJournalMode(pPager);
-  if( eNew==PAGER_JOURNALMODE_QUERY ) eNew = eOld;
-  if( !sqlite3PagerOkToChangeJournalMode(pPager) ) eNew = eOld;
-
-#ifndef SQLITE_OMIT_WAL
-  zFilename = sqlite3PagerFilename(pPager, 1);
-
-  /* Do not allow a transition to journal_mode=WAL for a database
-  ** in temporary storage or if the VFS does not support shared memory 
-  */
-  if( eNew==PAGER_JOURNALMODE_WAL
-   && (sqlite3Strlen30(zFilename)==0           /* Temp file */
-       || !sqlite3PagerWalSupported(pPager))   /* No shared-memory support */
-  ){
-    eNew = eOld;
-  }
-
-  if( (eNew!=eOld)
-   && (eOld==PAGER_JOURNALMODE_WAL || eNew==PAGER_JOURNALMODE_WAL)
-  ){
-    if( !db->autoCommit || db->nVdbeRead>1 ){
-      rc = SQLITE_ERROR;
-      sqlite3VdbeError(p,
-          "cannot change %s wal mode from within a transaction",
-          (eNew==PAGER_JOURNALMODE_WAL ? "into" : "out of")
-      );
-      goto abort_due_to_error;
-    }else{
- 
-      if( eOld==PAGER_JOURNALMODE_WAL ){
-        /* If leaving WAL mode, close the log file. If successful, the call
-        ** to PagerCloseWal() checkpoints and deletes the write-ahead-log 
-        ** file. An EXCLUSIVE lock may still be held on the database file 
-        ** after a successful return. 
-        */
-        rc = sqlite3PagerCloseWal(pPager, db);
-        if( rc==SQLITE_OK ){
-          sqlite3PagerSetJournalMode(pPager, eNew);
-        }
-      }else if( eOld==PAGER_JOURNALMODE_MEMORY ){
-        /* Cannot transition directly from MEMORY to WAL.  Use mode OFF
-        ** as an intermediate */
-        sqlite3PagerSetJournalMode(pPager, PAGER_JOURNALMODE_OFF);
-      }
-  
-      /* Open a transaction on the database file. Regardless of the journal
-      ** mode, this transaction always uses a rollback journal.
-      */
-      assert( sqlite3BtreeIsInTrans(pBt)==0 );
-      if( rc==SQLITE_OK ){
-        rc = sqlite3BtreeSetVersion(pBt, (eNew==PAGER_JOURNALMODE_WAL ? 2 : 1));
-      }
-    }
-  }
-#endif /* ifndef SQLITE_OMIT_WAL */
-
-  if( rc ) eNew = eOld;
-  eNew = sqlite3PagerSetJournalMode(pPager, eNew);
-
-  pOut->flags = MEM_Str|MEM_Static|MEM_Term;
-  pOut->z = (char *)sqlite3JournalModename(eNew);
-  pOut->n = sqlite3Strlen30(pOut->z);
-  pOut->enc = SQLITE_UTF8;
-  sqlite3VdbeChangeEncoding(pOut, encoding);
-  if( rc ) goto abort_due_to_error;
-  break;
-};
-#endif /* SQLITE_OMIT_PRAGMA */
 
 #if !defined(SQLITE_OMIT_VACUUM) && !defined(SQLITE_OMIT_ATTACH)
-/* Opcode: Vacuum P1 * * * *
+/* Opcode: Vacuum * * * * *
 **
-** Vacuum the entire database P1.  P1 is 0 for "main", and 2 or more
-** for an attached database.  The "temp" database may not be vacuumed.
+** Vacuum the entire database.  This opcode will cause other virtual
+** machines to be created and run.  It may not be called from within
+** a transaction.
 */
 case OP_Vacuum: {
-  assert( p->readOnly==0 );
-  rc = sqlite3RunVacuum(&p->zErrMsg, db, pOp->p1);
-  if( rc ) goto abort_due_to_error;
+  if( sqlite3SafetyOff(db) ) goto abort_due_to_misuse; 
+  rc = sqlite3RunVacuum(&p->zErrMsg, db);
+  if( sqlite3SafetyOn(db) ) goto abort_due_to_misuse;
   break;
 }
 #endif
 
 #if !defined(SQLITE_OMIT_AUTOVACUUM)
 /* Opcode: IncrVacuum P1 P2 * * *
