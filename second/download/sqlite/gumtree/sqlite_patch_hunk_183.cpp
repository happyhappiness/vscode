   db->nSavepoint = 0;
   db->nStatement = 0;
   db->isTransactionSavepoint = 0;
 }
 
 /*
-** Close an existing SQLite database
+** Invoke the destructor function associated with FuncDef p, if any. Except,
+** if this is not the last copy of the function, do not invoke it. Multiple
+** copies of a single function are created when create_function() is called
+** with SQLITE_ANY as the encoding.
+*/
+static void functionDestroy(sqlite3 *db, FuncDef *p){
+  FuncDestructor *pDestructor = p->u.pDestructor;
+  if( pDestructor ){
+    pDestructor->nRef--;
+    if( pDestructor->nRef==0 ){
+      pDestructor->xDestroy(pDestructor->pUserData);
+      sqlite3DbFree(db, pDestructor);
+    }
+  }
+}
+
+/*
+** Disconnect all sqlite3_vtab objects that belong to database connection
+** db. This is called when db is being closed.
+*/
+static void disconnectAllVtab(sqlite3 *db){
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+  int i;
+  HashElem *p;
+  sqlite3BtreeEnterAll(db);
+  for(i=0; i<db->nDb; i++){
+    Schema *pSchema = db->aDb[i].pSchema;
+    if( db->aDb[i].pSchema ){
+      for(p=sqliteHashFirst(&pSchema->tblHash); p; p=sqliteHashNext(p)){
+        Table *pTab = (Table *)sqliteHashData(p);
+        if( IsVirtual(pTab) ) sqlite3VtabDisconnect(db, pTab);
+      }
+    }
+  }
+  for(p=sqliteHashFirst(&db->aModule); p; p=sqliteHashNext(p)){
+    Module *pMod = (Module *)sqliteHashData(p);
+    if( pMod->pEpoTab ){
+      sqlite3VtabDisconnect(db, pMod->pEpoTab);
+    }
+  }
+  sqlite3VtabUnlockList(db);
+  sqlite3BtreeLeaveAll(db);
+#else
+  UNUSED_PARAMETER(db);
+#endif
+}
+
+/*
+** Return TRUE if database connection db has unfinalized prepared
+** statements or unfinished sqlite3_backup objects.  
 */
-int sqlite3_close(sqlite3 *db){
-  HashElem *i;
+static int connectionIsBusy(sqlite3 *db){
   int j;
+  assert( sqlite3_mutex_held(db->mutex) );
+  if( db->pVdbe ) return 1;
+  for(j=0; j<db->nDb; j++){
+    Btree *pBt = db->aDb[j].pBt;
+    if( pBt && sqlite3BtreeIsInBackup(pBt) ) return 1;
+  }
+  return 0;
+}
 
+/*
+** Close an existing SQLite database
+*/
+static int sqlite3Close(sqlite3 *db, int forceZombie){
   if( !db ){
+    /* EVIDENCE-OF: R-63257-11740 Calling sqlite3_close() or
+    ** sqlite3_close_v2() with a NULL pointer argument is a harmless no-op. */
     return SQLITE_OK;
   }
   if( !sqlite3SafetyCheckSickOrOk(db) ){
-    return SQLITE_MISUSE;
+    return SQLITE_MISUSE_BKPT;
   }
   sqlite3_mutex_enter(db->mutex);
-
-#ifdef SQLITE_SSE
-  {
-    extern void sqlite3SseCleanup(sqlite3*);
-    sqlite3SseCleanup(db);
+  if( db->mTrace & SQLITE_TRACE_CLOSE ){
+    db->xTrace(SQLITE_TRACE_CLOSE, db->pTraceArg, db, 0);
   }
-#endif 
 
-  sqlite3ResetInternalSchema(db, 0);
+  /* Force xDisconnect calls on all virtual tables */
+  disconnectAllVtab(db);
 
-  /* If a transaction is open, the ResetInternalSchema() call above
+  /* If a transaction is open, the disconnectAllVtab() call above
   ** will not have called the xDisconnect() method on any virtual
   ** tables in the db->aVTrans[] array. The following sqlite3VtabRollback()
   ** call will do so. We need to do this before the check for active
   ** SQL statements below, as the v-table implementation may be storing
   ** some prepared statements internally.
   */
   sqlite3VtabRollback(db);
 
-  /* If there are any outstanding VMs, return SQLITE_BUSY. */
-  if( db->pVdbe ){
-    sqlite3Error(db, SQLITE_BUSY, 
-        "unable to close due to unfinalised statements");
+  /* Legacy behavior (sqlite3_close() behavior) is to return
+  ** SQLITE_BUSY if the connection can not be closed immediately.
+  */
+  if( !forceZombie && connectionIsBusy(db) ){
+    sqlite3ErrorWithMsg(db, SQLITE_BUSY, "unable to close due to unfinalized "
+       "statements or unfinished backups");
     sqlite3_mutex_leave(db->mutex);
     return SQLITE_BUSY;
   }
-  assert( sqlite3SafetyCheckSickOrOk(db) );
 
-  for(j=0; j<db->nDb; j++){
-    Btree *pBt = db->aDb[j].pBt;
-    if( pBt && sqlite3BtreeIsInBackup(pBt) ){
-      sqlite3Error(db, SQLITE_BUSY, 
-          "unable to close due to unfinished backup operation");
-      sqlite3_mutex_leave(db->mutex);
-      return SQLITE_BUSY;
-    }
+#ifdef SQLITE_ENABLE_SQLLOG
+  if( sqlite3GlobalConfig.xSqllog ){
+    /* Closing the handle. Fourth parameter is passed the value 2. */
+    sqlite3GlobalConfig.xSqllog(sqlite3GlobalConfig.pSqllogArg, db, 0, 2);
+  }
+#endif
+
+  /* Convert the connection into a zombie and then close it.
+  */
+  db->magic = SQLITE_MAGIC_ZOMBIE;
+  sqlite3LeaveMutexAndCloseZombie(db);
+  return SQLITE_OK;
+}
+
+/*
+** Two variations on the public interface for closing a database
+** connection. The sqlite3_close() version returns SQLITE_BUSY and
+** leaves the connection option if there are unfinalized prepared
+** statements or unfinished sqlite3_backups.  The sqlite3_close_v2()
+** version forces the connection to become a zombie if there are
+** unclosed resources, and arranges for deallocation when the last
+** prepare statement or sqlite3_backup closes.
+*/
+int sqlite3_close(sqlite3 *db){ return sqlite3Close(db,0); }
+int sqlite3_close_v2(sqlite3 *db){ return sqlite3Close(db,1); }
+
+
+/*
+** Close the mutex on database connection db.
+**
+** Furthermore, if database connection db is a zombie (meaning that there
+** has been a prior call to sqlite3_close(db) or sqlite3_close_v2(db)) and
+** every sqlite3_stmt has now been finalized and every sqlite3_backup has
+** finished, then free all resources.
+*/
+void sqlite3LeaveMutexAndCloseZombie(sqlite3 *db){
+  HashElem *i;                    /* Hash table iterator */
+  int j;
+
+  /* If there are outstanding sqlite3_stmt or sqlite3_backup objects
+  ** or if the connection has not yet been closed by sqlite3_close_v2(),
+  ** then just leave the mutex and return.
+  */
+  if( db->magic!=SQLITE_MAGIC_ZOMBIE || connectionIsBusy(db) ){
+    sqlite3_mutex_leave(db->mutex);
+    return;
   }
 
+  /* If we reach this point, it means that the database connection has
+  ** closed all sqlite3_stmt and sqlite3_backup objects and has been
+  ** passed to sqlite3_close (meaning that it is a zombie).  Therefore,
+  ** go ahead and free all resources.
+  */
+
+  /* If a transaction is open, roll it back. This also ensures that if
+  ** any database schemas have been modified by an uncommitted transaction
+  ** they are reset. And that the required b-tree mutex is held to make
+  ** the pager rollback and schema reset an atomic operation. */
+  sqlite3RollbackAll(db, SQLITE_OK);
+
   /* Free any outstanding Savepoint structures. */
   sqlite3CloseSavepoints(db);
 
+  /* Close all database connections */
   for(j=0; j<db->nDb; j++){
     struct Db *pDb = &db->aDb[j];
     if( pDb->pBt ){
       sqlite3BtreeClose(pDb->pBt);
       pDb->pBt = 0;
       if( j!=1 ){
         pDb->pSchema = 0;
       }
     }
   }
-  sqlite3ResetInternalSchema(db, 0);
+  /* Clear the TEMP schema separately and last */
+  if( db->aDb[1].pSchema ){
+    sqlite3SchemaClear(db->aDb[1].pSchema);
+  }
+  sqlite3VtabUnlockList(db);
+
+  /* Free up the array of auxiliary databases */
+  sqlite3CollapseDatabaseArray(db);
+  assert( db->nDb<=2 );
+  assert( db->aDb==db->aDbStatic );
 
   /* Tell the code in notify.c that the connection no longer holds any
   ** locks and does not require any further unlock-notify callbacks.
   */
   sqlite3ConnectionClosed(db);
 
-  assert( db->nDb<=2 );
-  assert( db->aDb==db->aDbStatic );
-  for(j=0; j<ArraySize(db->aFunc.a); j++){
-    FuncDef *pNext, *pHash, *p;
-    for(p=db->aFunc.a[j]; p; p=pHash){
-      pHash = p->pHash;
-      while( p ){
-        pNext = p->pNext;
-        sqlite3DbFree(db, p);
-        p = pNext;
-      }
-    }
+  for(i=sqliteHashFirst(&db->aFunc); i; i=sqliteHashNext(i)){
+    FuncDef *pNext, *p;
+    p = sqliteHashData(i);
+    do{
+      functionDestroy(db, p);
+      pNext = p->pNext;
+      sqlite3DbFree(db, p);
+      p = pNext;
+    }while( p );
   }
+  sqlite3HashClear(&db->aFunc);
   for(i=sqliteHashFirst(&db->aCollSeq); i; i=sqliteHashNext(i)){
     CollSeq *pColl = (CollSeq *)sqliteHashData(i);
     /* Invoke any destructors registered for collation sequence user data. */
     for(j=0; j<3; j++){
       if( pColl[j].xDel ){
         pColl[j].xDel(pColl[j].pUser);
