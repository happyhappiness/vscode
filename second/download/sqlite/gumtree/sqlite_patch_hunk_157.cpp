   if( db->nDb>=db->aLimit[SQLITE_LIMIT_ATTACHED]+2 ){
     zErrDyn = sqlite3MPrintf(db, "too many attached databases - max %d", 
       db->aLimit[SQLITE_LIMIT_ATTACHED]
     );
     goto attach_error;
   }
-  if( !db->autoCommit ){
-    zErrDyn = sqlite3MPrintf(db, "cannot ATTACH database within transaction");
-    goto attach_error;
-  }
   for(i=0; i<db->nDb; i++){
-    char *z = db->aDb[i].zName;
+    char *z = db->aDb[i].zDbSName;
     assert( z && zName );
     if( sqlite3StrICmp(z, zName)==0 ){
       zErrDyn = sqlite3MPrintf(db, "database %s is already in use", zName);
       goto attach_error;
     }
   }
 
-  /* Allocate the new entry in the db->aDb[] array and initialise the schema
+  /* Allocate the new entry in the db->aDb[] array and initialize the schema
   ** hash tables.
   */
   if( db->aDb==db->aDbStatic ){
-    aNew = sqlite3DbMallocRaw(db, sizeof(db->aDb[0])*3 );
+    aNew = sqlite3DbMallocRawNN(db, sizeof(db->aDb[0])*3 );
     if( aNew==0 ) return;
     memcpy(aNew, db->aDb, sizeof(db->aDb[0])*2);
   }else{
     aNew = sqlite3DbRealloc(db, db->aDb, sizeof(db->aDb[0])*(db->nDb+1) );
     if( aNew==0 ) return;
   }
   db->aDb = aNew;
-  aNew = &db->aDb[db->nDb];
-  memset(aNew, 0, sizeof(*aNew));
+  pNew = &db->aDb[db->nDb];
+  memset(pNew, 0, sizeof(*pNew));
 
   /* Open the database file. If the btree is successfully opened, use
   ** it to obtain the database schema. At this point the schema may
-  ** or may not be initialised.
+  ** or may not be initialized.
   */
-  rc = sqlite3BtreeFactory(db, zFile, 0, SQLITE_DEFAULT_CACHE_SIZE,
-                           db->openFlags | SQLITE_OPEN_MAIN_DB,
-                           &aNew->pBt);
+  flags = db->openFlags;
+  rc = sqlite3ParseUri(db->pVfs->zName, zFile, &flags, &pVfs, &zPath, &zErr);
+  if( rc!=SQLITE_OK ){
+    if( rc==SQLITE_NOMEM ) sqlite3OomFault(db);
+    sqlite3_result_error(context, zErr, -1);
+    sqlite3_free(zErr);
+    return;
+  }
+  assert( pVfs );
+  flags |= SQLITE_OPEN_MAIN_DB;
+  rc = sqlite3BtreeOpen(pVfs, zPath, db, &pNew->pBt, 0, flags);
+  sqlite3_free( zPath );
   db->nDb++;
+  db->skipBtreeMutex = 0;
   if( rc==SQLITE_CONSTRAINT ){
     rc = SQLITE_ERROR;
     zErrDyn = sqlite3MPrintf(db, "database is already attached");
   }else if( rc==SQLITE_OK ){
     Pager *pPager;
-    aNew->pSchema = sqlite3SchemaGet(db, aNew->pBt);
-    if( !aNew->pSchema ){
-      rc = SQLITE_NOMEM;
-    }else if( aNew->pSchema->file_format && aNew->pSchema->enc!=ENC(db) ){
+    pNew->pSchema = sqlite3SchemaGet(db, pNew->pBt);
+    if( !pNew->pSchema ){
+      rc = SQLITE_NOMEM_BKPT;
+    }else if( pNew->pSchema->file_format && pNew->pSchema->enc!=ENC(db) ){
       zErrDyn = sqlite3MPrintf(db, 
         "attached databases must use the same text encoding as main database");
       rc = SQLITE_ERROR;
     }
-    pPager = sqlite3BtreePager(aNew->pBt);
+    sqlite3BtreeEnter(pNew->pBt);
+    pPager = sqlite3BtreePager(pNew->pBt);
     sqlite3PagerLockingMode(pPager, db->dfltLockMode);
-    sqlite3PagerJournalMode(pPager, db->dfltJournalMode);
+    sqlite3BtreeSecureDelete(pNew->pBt,
+                             sqlite3BtreeSecureDelete(db->aDb[0].pBt,-1) );
+#ifndef SQLITE_OMIT_PAGER_PRAGMAS
+    sqlite3BtreeSetPagerFlags(pNew->pBt,
+                      PAGER_SYNCHRONOUS_FULL | (db->flags & PAGER_FLAGS_MASK));
+#endif
+    sqlite3BtreeLeave(pNew->pBt);
+  }
+  pNew->safety_level = SQLITE_DEFAULT_SYNCHRONOUS+1;
+  pNew->zDbSName = sqlite3DbStrDup(db, zName);
+  if( rc==SQLITE_OK && pNew->zDbSName==0 ){
+    rc = SQLITE_NOMEM_BKPT;
   }
-  aNew->zName = sqlite3DbStrDup(db, zName);
-  aNew->safety_level = 3;
 
-#if SQLITE_HAS_CODEC
-  {
+
+#ifdef SQLITE_HAS_CODEC
+  if( rc==SQLITE_OK ){
     extern int sqlite3CodecAttach(sqlite3*, int, const void*, int);
     extern void sqlite3CodecGetKey(sqlite3*, int, void**, int*);
     int nKey;
     char *zKey;
     int t = sqlite3_value_type(argv[2]);
     switch( t ){
