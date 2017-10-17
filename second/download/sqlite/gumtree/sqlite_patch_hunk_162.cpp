   const char *zDestDb,                  /* Name of database within pDestDb */
   sqlite3* pSrcDb,                      /* Database connection to read from */
   const char *zSrcDb                    /* Name of database within pSrcDb */
 ){
   sqlite3_backup *p;                    /* Value to return */
 
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( !sqlite3SafetyCheckOk(pSrcDb)||!sqlite3SafetyCheckOk(pDestDb) ){
+    (void)SQLITE_MISUSE_BKPT;
+    return 0;
+  }
+#endif
+
   /* Lock the source database handle. The destination database
   ** handle is not locked in this routine, but it is locked in
   ** sqlite3_backup_step(). The user is required to ensure that no
   ** other thread accesses the destination handle for the duration
   ** of the backup operation.  Any attempt to use the destination
   ** database connection while a backup is in progress may cause
   ** a malfunction or a deadlock.
   */
   sqlite3_mutex_enter(pSrcDb->mutex);
   sqlite3_mutex_enter(pDestDb->mutex);
 
   if( pSrcDb==pDestDb ){
-    sqlite3Error(
+    sqlite3ErrorWithMsg(
         pDestDb, SQLITE_ERROR, "source and destination must be distinct"
     );
     p = 0;
   }else {
-    /* Allocate space for a new sqlite3_backup object */
-    p = (sqlite3_backup *)sqlite3_malloc(sizeof(sqlite3_backup));
+    /* Allocate space for a new sqlite3_backup object...
+    ** EVIDENCE-OF: R-64852-21591 The sqlite3_backup object is created by a
+    ** call to sqlite3_backup_init() and is destroyed by a call to
+    ** sqlite3_backup_finish(). */
+    p = (sqlite3_backup *)sqlite3MallocZero(sizeof(sqlite3_backup));
     if( !p ){
-      sqlite3Error(pDestDb, SQLITE_NOMEM, 0);
+      sqlite3Error(pDestDb, SQLITE_NOMEM_BKPT);
     }
   }
 
   /* If the allocation succeeded, populate the new object. */
   if( p ){
-    memset(p, 0, sizeof(sqlite3_backup));
     p->pSrc = findBtree(pDestDb, pSrcDb, zSrcDb);
     p->pDest = findBtree(pDestDb, pDestDb, zDestDb);
     p->pDestDb = pDestDb;
     p->pSrcDb = pSrcDb;
     p->iNext = 1;
     p->isAttached = 0;
 
-    if( 0==p->pSrc || 0==p->pDest ){
-      /* One (or both) of the named databases did not exist. An error has
-      ** already been written into the pDestDb handle. All that is left
-      ** to do here is free the sqlite3_backup structure.
-      */
+    if( 0==p->pSrc || 0==p->pDest 
+     || checkReadTransaction(pDestDb, p->pDest)!=SQLITE_OK 
+     ){
+      /* One (or both) of the named databases did not exist or an OOM
+      ** error was hit. Or there is a transaction open on the destination
+      ** database. The error has already been written into the pDestDb 
+      ** handle. All that is left to do here is free the sqlite3_backup 
+      ** structure.  */
       sqlite3_free(p);
       p = 0;
     }
   }
   if( p ){
     p->pSrc->nBackup++;
