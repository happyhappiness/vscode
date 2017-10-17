       db = 0;
       goto opendb_out;
     }
   }
   sqlite3_mutex_enter(db->mutex);
   db->errMask = 0xff;
-  db->priorNewRowid = 0;
   db->nDb = 2;
   db->magic = SQLITE_MAGIC_BUSY;
   db->aDb = db->aDbStatic;
 
   assert( sizeof(db->aLimit)==sizeof(aHardLimit) );
   memcpy(db->aLimit, aHardLimit, sizeof(db->aLimit));
+  db->aLimit[SQLITE_LIMIT_WORKER_THREADS] = SQLITE_DEFAULT_WORKER_THREADS;
   db->autoCommit = 1;
   db->nextAutovac = -1;
+  db->szMmap = sqlite3GlobalConfig.szMmap;
   db->nextPagesize = 0;
-  db->flags |= SQLITE_ShortColNames
+  db->nMaxSorterMmap = 0x7FFFFFFF;
+  db->flags |= SQLITE_ShortColNames | SQLITE_EnableTrigger | SQLITE_CacheSpill
+#if !defined(SQLITE_DEFAULT_AUTOMATIC_INDEX) || SQLITE_DEFAULT_AUTOMATIC_INDEX
+                 | SQLITE_AutoIndex
+#endif
+#if SQLITE_DEFAULT_CKPTFULLFSYNC
+                 | SQLITE_CkptFullFSync
+#endif
 #if SQLITE_DEFAULT_FILE_FORMAT<4
                  | SQLITE_LegacyFileFmt
 #endif
 #ifdef SQLITE_ENABLE_LOAD_EXTENSION
                  | SQLITE_LoadExtension
 #endif
+#if SQLITE_DEFAULT_RECURSIVE_TRIGGERS
+                 | SQLITE_RecTriggers
+#endif
+#if defined(SQLITE_DEFAULT_FOREIGN_KEYS) && SQLITE_DEFAULT_FOREIGN_KEYS
+                 | SQLITE_ForeignKeys
+#endif
+#if defined(SQLITE_REVERSE_UNORDERED_SELECTS)
+                 | SQLITE_ReverseOrder
+#endif
+#if defined(SQLITE_ENABLE_OVERSIZE_CELL_CHECK)
+                 | SQLITE_CellSizeCk
+#endif
+#if defined(SQLITE_ENABLE_FTS3_TOKENIZER)
+                 | SQLITE_Fts3Tokenizer
+#endif
+#if defined(SQLITE_ENABLE_QPSG)
+                 | SQLITE_EnableQPSG
+#endif
       ;
   sqlite3HashInit(&db->aCollSeq);
 #ifndef SQLITE_OMIT_VIRTUALTABLE
   sqlite3HashInit(&db->aModule);
 #endif
 
-  db->pVfs = sqlite3_vfs_find(zVfs);
-  if( !db->pVfs ){
-    rc = SQLITE_ERROR;
-    sqlite3Error(db, rc, "no such vfs: %s", zVfs);
-    goto opendb_out;
-  }
-
   /* Add the default collation sequence BINARY. BINARY works for both UTF-8
   ** and UTF-16, so add a version for each to avoid any unnecessary
   ** conversions. The only error that can occur here is a malloc() failure.
+  **
+  ** EVIDENCE-OF: R-52786-44878 SQLite defines three built-in collating
+  ** functions:
   */
-  createCollation(db, "BINARY", SQLITE_UTF8, 0, binCollFunc, 0);
-  createCollation(db, "BINARY", SQLITE_UTF16BE, 0, binCollFunc, 0);
-  createCollation(db, "BINARY", SQLITE_UTF16LE, 0, binCollFunc, 0);
+  createCollation(db, sqlite3StrBINARY, SQLITE_UTF8, 0, binCollFunc, 0);
+  createCollation(db, sqlite3StrBINARY, SQLITE_UTF16BE, 0, binCollFunc, 0);
+  createCollation(db, sqlite3StrBINARY, SQLITE_UTF16LE, 0, binCollFunc, 0);
+  createCollation(db, "NOCASE", SQLITE_UTF8, 0, nocaseCollatingFunc, 0);
   createCollation(db, "RTRIM", SQLITE_UTF8, (void*)1, binCollFunc, 0);
   if( db->mallocFailed ){
     goto opendb_out;
   }
-  db->pDfltColl = sqlite3FindCollSeq(db, SQLITE_UTF8, "BINARY", 0);
+  /* EVIDENCE-OF: R-08308-17224 The default collating function for all
+  ** strings is BINARY. 
+  */
+  db->pDfltColl = sqlite3FindCollSeq(db, SQLITE_UTF8, sqlite3StrBINARY, 0);
   assert( db->pDfltColl!=0 );
 
-  /* Also add a UTF-8 case-insensitive collation sequence. */
-  createCollation(db, "NOCASE", SQLITE_UTF8, 0, nocaseCollatingFunc, 0);
-
-  /* Set flags on the built-in collating sequences */
-  db->pDfltColl->type = SQLITE_COLL_BINARY;
-  pColl = sqlite3FindCollSeq(db, SQLITE_UTF8, "NOCASE", 0);
-  if( pColl ){
-    pColl->type = SQLITE_COLL_NOCASE;
+  /* Parse the filename/URI argument
+  **
+  ** Only allow sensible combinations of bits in the flags argument.  
+  ** Throw an error if any non-sense combination is used.  If we
+  ** do not block illegal combinations here, it could trigger
+  ** assert() statements in deeper layers.  Sensible combinations
+  ** are:
+  **
+  **  1:  SQLITE_OPEN_READONLY
+  **  2:  SQLITE_OPEN_READWRITE
+  **  6:  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE
+  */
+  db->openFlags = flags;
+  assert( SQLITE_OPEN_READONLY  == 0x01 );
+  assert( SQLITE_OPEN_READWRITE == 0x02 );
+  assert( SQLITE_OPEN_CREATE    == 0x04 );
+  testcase( (1<<(flags&7))==0x02 ); /* READONLY */
+  testcase( (1<<(flags&7))==0x04 ); /* READWRITE */
+  testcase( (1<<(flags&7))==0x40 ); /* READWRITE | CREATE */
+  if( ((1<<(flags&7)) & 0x46)==0 ){
+    rc = SQLITE_MISUSE_BKPT;  /* IMP: R-65497-44594 */
+  }else{
+    rc = sqlite3ParseUri(zVfs, zFilename, &flags, &db->pVfs, &zOpen, &zErrMsg);
+  }
+  if( rc!=SQLITE_OK ){
+    if( rc==SQLITE_NOMEM ) sqlite3OomFault(db);
+    sqlite3ErrorWithMsg(db, rc, zErrMsg ? "%s" : 0, zErrMsg);
+    sqlite3_free(zErrMsg);
+    goto opendb_out;
   }
 
   /* Open the backend database driver */
-  db->openFlags = flags;
-  rc = sqlite3BtreeFactory(db, zFilename, 0, SQLITE_DEFAULT_CACHE_SIZE, 
-                           flags | SQLITE_OPEN_MAIN_DB,
-                           &db->aDb[0].pBt);
+  rc = sqlite3BtreeOpen(db->pVfs, zOpen, db, &db->aDb[0].pBt, 0,
+                        flags | SQLITE_OPEN_MAIN_DB);
   if( rc!=SQLITE_OK ){
     if( rc==SQLITE_IOERR_NOMEM ){
-      rc = SQLITE_NOMEM;
+      rc = SQLITE_NOMEM_BKPT;
     }
-    sqlite3Error(db, rc, 0);
+    sqlite3Error(db, rc);
     goto opendb_out;
   }
+  sqlite3BtreeEnter(db->aDb[0].pBt);
   db->aDb[0].pSchema = sqlite3SchemaGet(db, db->aDb[0].pBt);
+  if( !db->mallocFailed ) ENC(db) = SCHEMA_ENC(db);
+  sqlite3BtreeLeave(db->aDb[0].pBt);
   db->aDb[1].pSchema = sqlite3SchemaGet(db, 0);
 
-
-  /* The default safety_level for the main database is 'full'; for the temp
-  ** database it is 'NONE'. This matches the pager layer defaults.  
+  /* The default safety_level for the main database is FULL; for the temp
+  ** database it is OFF. This matches the pager layer defaults.  
   */
-  db->aDb[0].zName = "main";
-  db->aDb[0].safety_level = 3;
-#ifndef SQLITE_OMIT_TEMPDB
-  db->aDb[1].zName = "temp";
-  db->aDb[1].safety_level = 1;
-#endif
+  db->aDb[0].zDbSName = "main";
+  db->aDb[0].safety_level = SQLITE_DEFAULT_SYNCHRONOUS+1;
+  db->aDb[1].zDbSName = "temp";
+  db->aDb[1].safety_level = PAGER_SYNCHRONOUS_OFF;
 
   db->magic = SQLITE_MAGIC_OPEN;
   if( db->mallocFailed ){
     goto opendb_out;
   }
 
   /* Register all built-in functions, but do not attempt to read the
   ** database schema yet. This is delayed until the first time the database
   ** is accessed.
   */
-  sqlite3Error(db, SQLITE_OK, 0);
-  sqlite3RegisterBuiltinFunctions(db);
+  sqlite3Error(db, SQLITE_OK);
+  sqlite3RegisterPerConnectionBuiltinFunctions(db);
+  rc = sqlite3_errcode(db);
+
+#ifdef SQLITE_ENABLE_FTS5
+  /* Register any built-in FTS5 module before loading the automatic
+  ** extensions. This allows automatic extensions to register FTS5 
+  ** tokenizers and auxiliary functions.  */
+  if( !db->mallocFailed && rc==SQLITE_OK ){
+    rc = sqlite3Fts5Init(db);
+  }
+#endif
 
   /* Load automatic extensions - extensions that have been registered
   ** using the sqlite3_automatic_extension() API.
   */
-  sqlite3AutoLoadExtensions(db);
-  rc = sqlite3_errcode(db);
-  if( rc!=SQLITE_OK ){
-    goto opendb_out;
+  if( rc==SQLITE_OK ){
+    sqlite3AutoLoadExtensions(db);
+    rc = sqlite3_errcode(db);
+    if( rc!=SQLITE_OK ){
+      goto opendb_out;
+    }
   }
 
 #ifdef SQLITE_ENABLE_FTS1
   if( !db->mallocFailed ){
     extern int sqlite3Fts1Init(sqlite3*);
     rc = sqlite3Fts1Init(db);
