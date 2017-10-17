       pSavepoint && sqlite3StrICmp(pSavepoint->zName, zName);
       pSavepoint = pSavepoint->pNext
     ){
       iSavepoint++;
     }
     if( !pSavepoint ){
-      sqlite3SetString(&p->zErrMsg, db, "no such savepoint: %s", zName);
+      sqlite3VdbeError(p, "no such savepoint: %s", zName);
       rc = SQLITE_ERROR;
-    }else if( 
-        db->writeVdbeCnt>0 || (p1==SAVEPOINT_ROLLBACK && db->activeVdbeCnt>1) 
-    ){
+    }else if( db->nVdbeWrite>0 && p1==SAVEPOINT_RELEASE ){
       /* It is not possible to release (commit) a savepoint if there are 
-      ** active write statements. It is not possible to rollback a savepoint
-      ** if there are any active statements at all.
+      ** active write statements.
       */
-      sqlite3SetString(&p->zErrMsg, db, 
-        "cannot %s savepoint - SQL statements in progress",
-        (p1==SAVEPOINT_ROLLBACK ? "rollback": "release")
-      );
+      sqlite3VdbeError(p, "cannot release savepoint - "
+                          "SQL statements in progress");
       rc = SQLITE_BUSY;
     }else{
 
       /* Determine whether or not this is a transaction savepoint. If so,
       ** and this is a RELEASE command, then the current transaction 
       ** is committed. 
       */
       int isTransaction = pSavepoint->pNext==0 && db->isTransactionSavepoint;
       if( isTransaction && p1==SAVEPOINT_RELEASE ){
+        if( (rc = sqlite3VdbeCheckFk(p, 1))!=SQLITE_OK ){
+          goto vdbe_return;
+        }
         db->autoCommit = 1;
         if( sqlite3VdbeHalt(p)==SQLITE_BUSY ){
-          p->pc = pc;
+          p->pc = (int)(pOp - aOp);
           db->autoCommit = 0;
           p->rc = rc = SQLITE_BUSY;
           goto vdbe_return;
         }
         db->isTransactionSavepoint = 0;
         rc = p->rc;
       }else{
+        int isSchemaChange;
         iSavepoint = db->nSavepoint - iSavepoint - 1;
+        if( p1==SAVEPOINT_ROLLBACK ){
+          isSchemaChange = (db->mDbFlags & DBFLAG_SchemaChange)!=0;
+          for(ii=0; ii<db->nDb; ii++){
+            rc = sqlite3BtreeTripAllCursors(db->aDb[ii].pBt,
+                                       SQLITE_ABORT_ROLLBACK,
+                                       isSchemaChange==0);
+            if( rc!=SQLITE_OK ) goto abort_due_to_error;
+          }
+        }else{
+          isSchemaChange = 0;
+        }
         for(ii=0; ii<db->nDb; ii++){
           rc = sqlite3BtreeSavepoint(db->aDb[ii].pBt, p1, iSavepoint);
           if( rc!=SQLITE_OK ){
             goto abort_due_to_error;
           }
         }
-        if( p1==SAVEPOINT_ROLLBACK && (db->flags&SQLITE_InternChanges)!=0 ){
+        if( isSchemaChange ){
           sqlite3ExpirePreparedStatements(db);
-          sqlite3ResetInternalSchema(db, 0);
+          sqlite3ResetAllSchemasOfConnection(db);
+          db->mDbFlags |= DBFLAG_SchemaChange;
         }
       }
   
       /* Regardless of whether this is a RELEASE or ROLLBACK, destroy all 
       ** savepoints nested inside of the savepoint being operated on. */
       while( db->pSavepoint!=pSavepoint ){
         pTmp = db->pSavepoint;
         db->pSavepoint = pTmp->pNext;
         sqlite3DbFree(db, pTmp);
         db->nSavepoint--;
       }
 
-      /* If it is a RELEASE, then destroy the savepoint being operated on too */
+      /* If it is a RELEASE, then destroy the savepoint being operated on 
+      ** too. If it is a ROLLBACK TO, then set the number of deferred 
+      ** constraint violations present in the database to the value stored
+      ** when the savepoint was created.  */
       if( p1==SAVEPOINT_RELEASE ){
         assert( pSavepoint==db->pSavepoint );
         db->pSavepoint = pSavepoint->pNext;
         sqlite3DbFree(db, pSavepoint);
         if( !isTransaction ){
           db->nSavepoint--;
         }
+      }else{
+        db->nDeferredCons = pSavepoint->nDeferredCons;
+        db->nDeferredImmCons = pSavepoint->nDeferredImmCons;
+      }
+
+      if( !isTransaction || p1==SAVEPOINT_ROLLBACK ){
+        rc = sqlite3VtabSavepoint(db, p1, iSavepoint);
+        if( rc!=SQLITE_OK ) goto abort_due_to_error;
       }
     }
   }
+  if( rc ) goto abort_due_to_error;
 
   break;
 }
 
 /* Opcode: AutoCommit P1 P2 * * *
 **
