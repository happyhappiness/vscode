   ** transaction, then there cannot be any savepoints. 
   */
   assert( db->pSavepoint==0 || db->autoCommit==0 );
   assert( p1==SAVEPOINT_BEGIN||p1==SAVEPOINT_RELEASE||p1==SAVEPOINT_ROLLBACK );
   assert( db->pSavepoint || db->isTransactionSavepoint==0 );
   assert( checkSavepointCount(db) );
-  assert( p->bIsReader );
 
   if( p1==SAVEPOINT_BEGIN ){
-    if( db->nVdbeWrite>0 ){
+    if( db->writeVdbeCnt>0 ){
       /* A new savepoint cannot be created if there are active write 
       ** statements (i.e. open read/write incremental blob handles).
       */
-      sqlite3VdbeError(p, "cannot open savepoint - SQL statements in progress");
+      sqlite3SetString(&p->zErrMsg, db, "cannot open savepoint - "
+        "SQL statements in progress");
       rc = SQLITE_BUSY;
     }else{
       nName = sqlite3Strlen30(zName);
 
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-      /* This call is Ok even if this savepoint is actually a transaction
-      ** savepoint (and therefore should not prompt xSavepoint()) callbacks.
-      ** If this is a transaction savepoint being opened, it is guaranteed
-      ** that the db->aVTrans[] array is empty.  */
-      assert( db->autoCommit==0 || db->nVTrans==0 );
-      rc = sqlite3VtabSavepoint(db, SAVEPOINT_BEGIN,
-                                db->nStatement+db->nSavepoint);
-      if( rc!=SQLITE_OK ) goto abort_due_to_error;
-#endif
-
       /* Create a new savepoint structure. */
-      pNew = sqlite3DbMallocRawNN(db, sizeof(Savepoint)+nName+1);
+      pNew = sqlite3DbMallocRaw(db, sizeof(Savepoint)+nName+1);
       if( pNew ){
         pNew->zName = (char *)&pNew[1];
         memcpy(pNew->zName, zName, nName+1);
     
         /* If there is no open transaction, then mark this as a special
         ** "transaction savepoint". */
         if( db->autoCommit ){
           db->autoCommit = 0;
           db->isTransactionSavepoint = 1;
         }else{
           db->nSavepoint++;
         }
-
+    
         /* Link the new savepoint into the database handle's list. */
         pNew->pNext = db->pSavepoint;
         db->pSavepoint = pNew;
-        pNew->nDeferredCons = db->nDeferredCons;
-        pNew->nDeferredImmCons = db->nDeferredImmCons;
       }
     }
   }else{
     iSavepoint = 0;
 
     /* Find the named savepoint. If there is no such savepoint, then an
