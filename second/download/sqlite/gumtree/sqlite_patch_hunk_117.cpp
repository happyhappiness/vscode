 **
 ** This instruction causes the VM to halt.
 */
 case OP_AutoCommit: {
   int desiredAutoCommit;
   int iRollback;
+  int turnOnAC;
 
   desiredAutoCommit = pOp->p1;
   iRollback = pOp->p2;
+  turnOnAC = desiredAutoCommit && !db->autoCommit;
   assert( desiredAutoCommit==1 || desiredAutoCommit==0 );
   assert( desiredAutoCommit==1 || iRollback==0 );
-  assert( db->nVdbeActive>0 );  /* At least this one VM is active */
-  assert( p->bIsReader );
+  assert( db->activeVdbeCnt>0 );  /* At least this one VM is active */
 
-  if( desiredAutoCommit!=db->autoCommit ){
+  if( turnOnAC && iRollback && db->activeVdbeCnt>1 ){
+    /* If this instruction implements a ROLLBACK and other VMs are
+    ** still running, and a transaction is active, return an error indicating
+    ** that the other VMs must complete first. 
+    */
+    sqlite3SetString(&p->zErrMsg, db, "cannot rollback transaction - "
+        "SQL statements in progress");
+    rc = SQLITE_BUSY;
+  }else if( turnOnAC && !iRollback && db->writeVdbeCnt>1 ){
+    /* If this instruction implements a COMMIT and other VMs are writing
+    ** return an error indicating that the other VMs must complete first. 
+    */
+    sqlite3SetString(&p->zErrMsg, db, "cannot commit transaction - "
+        "SQL statements in progress");
+    rc = SQLITE_BUSY;
+  }else if( desiredAutoCommit!=db->autoCommit ){
     if( iRollback ){
       assert( desiredAutoCommit==1 );
-      sqlite3RollbackAll(db, SQLITE_ABORT_ROLLBACK);
+      sqlite3RollbackAll(db);
       db->autoCommit = 1;
-    }else if( desiredAutoCommit && db->nVdbeWrite>0 ){
-      /* If this instruction implements a COMMIT and other VMs are writing
-      ** return an error indicating that the other VMs must complete first. 
-      */
-      sqlite3VdbeError(p, "cannot commit transaction - "
-                          "SQL statements in progress");
-      rc = SQLITE_BUSY;
-      goto abort_due_to_error;
-    }else if( (rc = sqlite3VdbeCheckFk(p, 1))!=SQLITE_OK ){
-      goto vdbe_return;
     }else{
       db->autoCommit = (u8)desiredAutoCommit;
-    }
-    if( sqlite3VdbeHalt(p)==SQLITE_BUSY ){
-      p->pc = (int)(pOp - aOp);
-      db->autoCommit = (u8)(1-desiredAutoCommit);
-      p->rc = rc = SQLITE_BUSY;
-      goto vdbe_return;
+      if( sqlite3VdbeHalt(p)==SQLITE_BUSY ){
+        p->pc = pc;
+        db->autoCommit = (u8)(1-desiredAutoCommit);
+        p->rc = rc = SQLITE_BUSY;
+        goto vdbe_return;
+      }
     }
     assert( db->nStatement==0 );
     sqlite3CloseSavepoints(db);
     if( p->rc==SQLITE_OK ){
       rc = SQLITE_DONE;
     }else{
       rc = SQLITE_ERROR;
     }
     goto vdbe_return;
   }else{
-    sqlite3VdbeError(p,
+    sqlite3SetString(&p->zErrMsg, db,
         (!desiredAutoCommit)?"cannot start a transaction within a transaction":(
         (iRollback)?"cannot rollback - no transaction is active":
                    "cannot commit - no transaction is active"));
          
     rc = SQLITE_ERROR;
-    goto abort_due_to_error;
   }
   break;
 }
 
-/* Opcode: Transaction P1 P2 P3 P4 P5
+/* Opcode: Transaction P1 P2 * * *
 **
-** Begin a transaction on database P1 if a transaction is not already
-** active.
-** If P2 is non-zero, then a write-transaction is started, or if a 
-** read-transaction is already active, it is upgraded to a write-transaction.
-** If P2 is zero, then a read-transaction is started.
+** Begin a transaction.  The transaction ends when a Commit or Rollback
+** opcode is encountered.  Depending on the ON CONFLICT setting, the
+** transaction might also be rolled back if an error is encountered.
 **
 ** P1 is the index of the database file on which the transaction is
 ** started.  Index 0 is the main database file and index 1 is the
 ** file used for temporary tables.  Indices of 2 or more are used for
 ** attached databases.
 **
-** If a write-transaction is started and the Vdbe.usesStmtJournal flag is
-** true (this flag is set if the Vdbe may modify more than one row and may
-** throw an ABORT exception), a statement transaction may also be opened.
-** More specifically, a statement transaction is opened iff the database
-** connection is currently not in autocommit mode, or if there are other
-** active statements. A statement transaction allows the changes made by this
-** VDBE to be rolled back after an error without having to roll back the
-** entire transaction. If no error is encountered, the statement transaction
-** will automatically commit when the VDBE halts.
+** If P2 is non-zero, then a write-transaction is started.  A RESERVED lock is
+** obtained on the database file when a write-transaction is started.  No
+** other process can start another write transaction while this transaction is
+** underway.  Starting a write transaction also creates a rollback journal. A
+** write transaction must be started before any changes can be made to the
+** database.  If P2 is 2 or greater then an EXCLUSIVE lock is also obtained
+** on the file.
 **
-** If P5!=0 then this opcode also checks the schema cookie against P3
-** and the schema generation counter against P4.
-** The cookie changes its value whenever the database schema changes.
-** This operation is used to detect when that the cookie has changed
-** and that the current process needs to reread the schema.  If the schema
-** cookie in P3 differs from the schema cookie in the database header or
-** if the schema generation counter in P4 differs from the current
-** generation counter, then an SQLITE_SCHEMA error is raised and execution
-** halts.  The sqlite3_step() wrapper function might then reprepare the
-** statement and rerun it from the beginning.
+** If P2 is zero, then a read-lock is obtained on the database file.
 */
 case OP_Transaction: {
+  int i;
   Btree *pBt;
-  int iMeta;
-  int iGen;
 
-  assert( p->bIsReader );
-  assert( p->readOnly==0 || pOp->p2==0 );
-  assert( pOp->p1>=0 && pOp->p1<db->nDb );
-  assert( DbMaskTest(p->btreeMask, pOp->p1) );
-  if( pOp->p2 && (db->flags & SQLITE_QueryOnly)!=0 ){
-    rc = SQLITE_READONLY;
-    goto abort_due_to_error;
-  }
-  pBt = db->aDb[pOp->p1].pBt;
+  i = pOp->p1;
+  assert( i>=0 && i<db->nDb );
+  assert( (p->btreeMask & (1<<i))!=0 );
+  pBt = db->aDb[i].pBt;
 
   if( pBt ){
     rc = sqlite3BtreeBeginTrans(pBt, pOp->p2);
-    testcase( rc==SQLITE_BUSY_SNAPSHOT );
-    testcase( rc==SQLITE_BUSY_RECOVERY );
-    if( rc!=SQLITE_OK ){
-      if( (rc&0xff)==SQLITE_BUSY ){
-        p->pc = (int)(pOp - aOp);
-        p->rc = rc;
-        goto vdbe_return;
-      }
-      goto abort_due_to_error;
-    }
-
-    if( pOp->p2 && p->usesStmtJournal 
-     && (db->autoCommit==0 || db->nVdbeRead>1) 
-    ){
-      assert( sqlite3BtreeIsInTrans(pBt) );
-      if( p->iStatement==0 ){
-        assert( db->nStatement>=0 && db->nSavepoint>=0 );
-        db->nStatement++; 
-        p->iStatement = db->nSavepoint + db->nStatement;
-      }
-
-      rc = sqlite3VtabSavepoint(db, SAVEPOINT_BEGIN, p->iStatement-1);
-      if( rc==SQLITE_OK ){
-        rc = sqlite3BtreeBeginStmt(pBt, p->iStatement);
-      }
-
-      /* Store the current value of the database handles deferred constraint
-      ** counter. If the statement transaction needs to be rolled back,
-      ** the value of this counter needs to be restored too.  */
-      p->nStmtDefCons = db->nDeferredCons;
-      p->nStmtDefImmCons = db->nDeferredImmCons;
+    if( rc==SQLITE_BUSY ){
+      p->pc = pc;
+      p->rc = rc = SQLITE_BUSY;
+      goto vdbe_return;
     }
-
-    /* Gather the schema version number for checking:
-    ** IMPLEMENTATION-OF: R-03189-51135 As each SQL statement runs, the schema
-    ** version is checked to ensure that the schema has not changed since the
-    ** SQL statement was prepared.
-    */
-    sqlite3BtreeGetMeta(pBt, BTREE_SCHEMA_VERSION, (u32 *)&iMeta);
-    iGen = db->aDb[pOp->p1].pSchema->iGeneration;
-  }else{
-    iGen = iMeta = 0;
-  }
-  assert( pOp->p5==0 || pOp->p4type==P4_INT32 );
-  if( pOp->p5 && (iMeta!=pOp->p3 || iGen!=pOp->p4.i) ){
-    sqlite3DbFree(db, p->zErrMsg);
-    p->zErrMsg = sqlite3DbStrDup(db, "database schema has changed");
-    /* If the schema-cookie from the database file matches the cookie 
-    ** stored with the in-memory representation of the schema, do
-    ** not reload the schema from the database file.
-    **
-    ** If virtual-tables are in use, this is not just an optimization.
-    ** Often, v-tables store their data in other SQLite tables, which
-    ** are queried from within xNext() and other v-table methods using
-    ** prepared queries. If such a query is out-of-date, we do not want to
-    ** discard the database schema, as the user code implementing the
-    ** v-table would have to be ready for the sqlite3_vtab structure itself
-    ** to be invalidated whenever sqlite3_step() is called from within 
-    ** a v-table method.
-    */
-    if( db->aDb[pOp->p1].pSchema->schema_cookie!=iMeta ){
-      sqlite3ResetOneSchema(db, pOp->p1);
+    if( rc!=SQLITE_OK && rc!=SQLITE_READONLY /* && rc!=SQLITE_BUSY */ ){
+      goto abort_due_to_error;
     }
-    p->expired = 1;
-    rc = SQLITE_SCHEMA;
   }
-  if( rc ) goto abort_due_to_error;
   break;
 }
 
 /* Opcode: ReadCookie P1 P2 P3 * *
 **
 ** Read cookie number P3 from database P1 and write it into register P2.
