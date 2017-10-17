   ** the schema-version is potentially dangerous and may lead to program
   ** crashes or database corruption. Use with caution!
   **
   ** The user-version is not used internally by SQLite. It may be used by
   ** applications for any purpose.
   */
-  case PragTyp_HEADER_VALUE: {
-    int iCookie = pPragma->iArg;  /* Which cookie to read or write */
+  if( sqlite3StrICmp(zLeft, "schema_version")==0 
+   || sqlite3StrICmp(zLeft, "user_version")==0 
+   || sqlite3StrICmp(zLeft, "freelist_count")==0 
+  ){
+    int iCookie;   /* Cookie index. 1 for schema-cookie, 6 for user-cookie. */
     sqlite3VdbeUsesBtree(v, iDb);
-    if( zRight && (pPragma->mPragFlg & PragFlg_ReadOnly)==0 ){
+    switch( zLeft[0] ){
+      case 'f': case 'F':
+        iCookie = BTREE_FREE_PAGE_COUNT;
+        break;
+      case 's': case 'S':
+        iCookie = BTREE_SCHEMA_VERSION;
+        break;
+      default:
+        iCookie = BTREE_USER_VERSION;
+        break;
+    }
+
+    if( zRight && iCookie!=BTREE_FREE_PAGE_COUNT ){
       /* Write the specified cookie value */
       static const VdbeOpList setCookie[] = {
         { OP_Transaction,    0,  1,  0},    /* 0 */
-        { OP_SetCookie,      0,  0,  0},    /* 1 */
+        { OP_Integer,        0,  1,  0},    /* 1 */
+        { OP_SetCookie,      0,  0,  1},    /* 2 */
       };
-      VdbeOp *aOp;
-      sqlite3VdbeVerifyNoMallocRequired(v, ArraySize(setCookie));
-      aOp = sqlite3VdbeAddOpList(v, ArraySize(setCookie), setCookie, 0);
-      if( ONLY_IF_REALLOC_STRESS(aOp==0) ) break;
-      aOp[0].p1 = iDb;
-      aOp[1].p1 = iDb;
-      aOp[1].p2 = iCookie;
-      aOp[1].p3 = sqlite3Atoi(zRight);
+      int addr = sqlite3VdbeAddOpList(v, ArraySize(setCookie), setCookie);
+      sqlite3VdbeChangeP1(v, addr, iDb);
+      sqlite3VdbeChangeP1(v, addr+1, atoi(zRight));
+      sqlite3VdbeChangeP1(v, addr+2, iDb);
+      sqlite3VdbeChangeP2(v, addr+2, iCookie);
     }else{
       /* Read the specified cookie value */
       static const VdbeOpList readCookie[] = {
-        { OP_Transaction,     0,  0,  0},    /* 0 */
-        { OP_ReadCookie,      0,  1,  0},    /* 1 */
+        { OP_ReadCookie,      0,  1,  0},    /* 0 */
         { OP_ResultRow,       1,  1,  0}
       };
-      VdbeOp *aOp;
-      sqlite3VdbeVerifyNoMallocRequired(v, ArraySize(readCookie));
-      aOp = sqlite3VdbeAddOpList(v, ArraySize(readCookie),readCookie,0);
-      if( ONLY_IF_REALLOC_STRESS(aOp==0) ) break;
-      aOp[0].p1 = iDb;
-      aOp[1].p1 = iDb;
-      aOp[1].p3 = iCookie;
-      sqlite3VdbeReusable(v);
+      int addr = sqlite3VdbeAddOpList(v, ArraySize(readCookie), readCookie);
+      sqlite3VdbeChangeP1(v, addr, iDb);
+      sqlite3VdbeChangeP3(v, addr, iCookie);
+      sqlite3VdbeSetNumCols(v, 1);
+      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, zLeft, SQLITE_TRANSIENT);
     }
-  }
-  break;
+  }else
 #endif /* SQLITE_OMIT_SCHEMA_VERSION_PRAGMAS */
 
-#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
-  /*
-  **   PRAGMA compile_options
-  **
-  ** Return the names of all compile-time options used in this build,
-  ** one option per row.
-  */
-  case PragTyp_COMPILE_OPTIONS: {
-    int i = 0;
-    const char *zOpt;
-    pParse->nMem = 1;
-    while( (zOpt = sqlite3_compileoption_get(i++))!=0 ){
-      sqlite3VdbeLoadString(v, 1, zOpt);
-      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 1);
-    }
-    sqlite3VdbeReusable(v);
-  }
-  break;
-#endif /* SQLITE_OMIT_COMPILEOPTION_DIAGS */
-
-#ifndef SQLITE_OMIT_WAL
-  /*
-  **   PRAGMA [schema.]wal_checkpoint = passive|full|restart|truncate
-  **
-  ** Checkpoint the database.
-  */
-  case PragTyp_WAL_CHECKPOINT: {
-    int iBt = (pId2->z?iDb:SQLITE_MAX_ATTACHED);
-    int eMode = SQLITE_CHECKPOINT_PASSIVE;
-    if( zRight ){
-      if( sqlite3StrICmp(zRight, "full")==0 ){
-        eMode = SQLITE_CHECKPOINT_FULL;
-      }else if( sqlite3StrICmp(zRight, "restart")==0 ){
-        eMode = SQLITE_CHECKPOINT_RESTART;
-      }else if( sqlite3StrICmp(zRight, "truncate")==0 ){
-        eMode = SQLITE_CHECKPOINT_TRUNCATE;
-      }
-    }
-    pParse->nMem = 3;
-    sqlite3VdbeAddOp3(v, OP_Checkpoint, iBt, eMode, 1);
-    sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
-  }
-  break;
-
-  /*
-  **   PRAGMA wal_autocheckpoint
-  **   PRAGMA wal_autocheckpoint = N
-  **
-  ** Configure a database connection to automatically checkpoint a database
-  ** after accumulating N frames in the log. Or query for the current value
-  ** of N.
-  */
-  case PragTyp_WAL_AUTOCHECKPOINT: {
-    if( zRight ){
-      sqlite3_wal_autocheckpoint(db, sqlite3Atoi(zRight));
-    }
-    returnSingleInt(v, 
-       db->xWalCallback==sqlite3WalDefaultHook ? 
-           SQLITE_PTR_TO_INT(db->pWalArg) : 0);
-  }
-  break;
-#endif
-
-  /*
-  **  PRAGMA shrink_memory
-  **
-  ** IMPLEMENTATION-OF: R-23445-46109 This pragma causes the database
-  ** connection on which it is invoked to free up as much memory as it
-  ** can, by calling sqlite3_db_release_memory().
-  */
-  case PragTyp_SHRINK_MEMORY: {
-    sqlite3_db_release_memory(db);
-    break;
-  }
-
-  /*
-  **  PRAGMA optimize
-  **  PRAGMA optimize(MASK)
-  **  PRAGMA schema.optimize
-  **  PRAGMA schema.optimize(MASK)
-  **
-  ** Attempt to optimize the database.  All schemas are optimized in the first
-  ** two forms, and only the specified schema is optimized in the latter two.
-  **
-  ** The details of optimizations performed by this pragma are expected
-  ** to change and improve over time.  Applications should anticipate that
-  ** this pragma will perform new optimizations in future releases.
-  **
-  ** The optional argument is a bitmask of optimizations to perform:
-  **
-  **    0x0001    Debugging mode.  Do not actually perform any optimizations
-  **              but instead return one line of text for each optimization
-  **              that would have been done.  Off by default.
-  **
-  **    0x0002    Run ANALYZE on tables that might benefit.  On by default.
-  **              See below for additional information.
-  **
-  **    0x0004    (Not yet implemented) Record usage and performance 
-  **              information from the current session in the
-  **              database file so that it will be available to "optimize"
-  **              pragmas run by future database connections.
-  **
-  **    0x0008    (Not yet implemented) Create indexes that might have
-  **              been helpful to recent queries
-  **
-  ** The default MASK is and always shall be 0xfffe.  0xfffe means perform all
-  ** of the optimizations listed above except Debug Mode, including new
-  ** optimizations that have not yet been invented.  If new optimizations are
-  ** ever added that should be off by default, those off-by-default 
-  ** optimizations will have bitmasks of 0x10000 or larger.
-  **
-  ** DETERMINATION OF WHEN TO RUN ANALYZE
-  **
-  ** In the current implementation, a table is analyzed if only if all of
-  ** the following are true:
-  **
-  ** (1) MASK bit 0x02 is set.
-  **
-  ** (2) The query planner used sqlite_stat1-style statistics for one or
-  **     more indexes of the table at some point during the lifetime of
-  **     the current connection.
-  **
-  ** (3) One or more indexes of the table are currently unanalyzed OR
-  **     the number of rows in the table has increased by 25 times or more
-  **     since the last time ANALYZE was run.
-  **
-  ** The rules for when tables are analyzed are likely to change in
-  ** future releases.
-  */
-  case PragTyp_OPTIMIZE: {
-    int iDbLast;           /* Loop termination point for the schema loop */
-    int iTabCur;           /* Cursor for a table whose size needs checking */
-    HashElem *k;           /* Loop over tables of a schema */
-    Schema *pSchema;       /* The current schema */
-    Table *pTab;           /* A table in the schema */
-    Index *pIdx;           /* An index of the table */
-    LogEst szThreshold;    /* Size threshold above which reanalysis is needd */
-    char *zSubSql;         /* SQL statement for the OP_SqlExec opcode */
-    u32 opMask;            /* Mask of operations to perform */
-
-    if( zRight ){
-      opMask = (u32)sqlite3Atoi(zRight);
-      if( (opMask & 0x02)==0 ) break;
-    }else{
-      opMask = 0xfffe;
-    }
-    iTabCur = pParse->nTab++;
-    for(iDbLast = zDb?iDb:db->nDb-1; iDb<=iDbLast; iDb++){
-      if( iDb==1 ) continue;
-      sqlite3CodeVerifySchema(pParse, iDb);
-      pSchema = db->aDb[iDb].pSchema;
-      for(k=sqliteHashFirst(&pSchema->tblHash); k; k=sqliteHashNext(k)){
-        pTab = (Table*)sqliteHashData(k);
-
-        /* If table pTab has not been used in a way that would benefit from
-        ** having analysis statistics during the current session, then skip it.
-        ** This also has the effect of skipping virtual tables and views */
-        if( (pTab->tabFlags & TF_StatsUsed)==0 ) continue;
-
-        /* Reanalyze if the table is 25 times larger than the last analysis */
-        szThreshold = pTab->nRowLogEst + 46; assert( sqlite3LogEst(25)==46 );
-        for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
-          if( !pIdx->hasStat1 ){
-            szThreshold = 0; /* Always analyze if any index lacks statistics */
-            break;
-          }
-        }
-        if( szThreshold ){
-          sqlite3OpenTable(pParse, iTabCur, iDb, pTab, OP_OpenRead);
-          sqlite3VdbeAddOp3(v, OP_IfSmaller, iTabCur, 
-                         sqlite3VdbeCurrentAddr(v)+2+(opMask&1), szThreshold);
-          VdbeCoverage(v);
-        }
-        zSubSql = sqlite3MPrintf(db, "ANALYZE \"%w\".\"%w\"",
-                                 db->aDb[iDb].zDbSName, pTab->zName);
-        if( opMask & 0x01 ){
-          int r1 = sqlite3GetTempReg(pParse);
-          sqlite3VdbeAddOp4(v, OP_String8, 0, r1, 0, zSubSql, P4_DYNAMIC);
-          sqlite3VdbeAddOp2(v, OP_ResultRow, r1, 1);
-        }else{
-          sqlite3VdbeAddOp4(v, OP_SqlExec, 0, 0, 0, zSubSql, P4_DYNAMIC);
-        }
-      }
-    }
-    sqlite3VdbeAddOp0(v, OP_Expire);
-    break;
-  }
-
-  /*
-  **   PRAGMA busy_timeout
-  **   PRAGMA busy_timeout = N
-  **
-  ** Call sqlite3_busy_timeout(db, N).  Return the current timeout value
-  ** if one is set.  If no busy handler or a different busy handler is set
-  ** then 0 is returned.  Setting the busy_timeout to 0 or negative
-  ** disables the timeout.
-  */
-  /*case PragTyp_BUSY_TIMEOUT*/ default: {
-    assert( pPragma->ePragTyp==PragTyp_BUSY_TIMEOUT );
-    if( zRight ){
-      sqlite3_busy_timeout(db, sqlite3Atoi(zRight));
-    }
-    returnSingleInt(v, db->busyTimeout);
-    break;
-  }
-
-  /*
-  **   PRAGMA soft_heap_limit
-  **   PRAGMA soft_heap_limit = N
-  **
-  ** IMPLEMENTATION-OF: R-26343-45930 This pragma invokes the
-  ** sqlite3_soft_heap_limit64() interface with the argument N, if N is
-  ** specified and is a non-negative integer.
-  ** IMPLEMENTATION-OF: R-64451-07163 The soft_heap_limit pragma always
-  ** returns the same integer that would be returned by the
-  ** sqlite3_soft_heap_limit64(-1) C-language function.
-  */
-  case PragTyp_SOFT_HEAP_LIMIT: {
-    sqlite3_int64 N;
-    if( zRight && sqlite3DecOrHexToI64(zRight, &N)==SQLITE_OK ){
-      sqlite3_soft_heap_limit64(N);
-    }
-    returnSingleInt(v, sqlite3_soft_heap_limit64(-1));
-    break;
-  }
-
-  /*
-  **   PRAGMA threads
-  **   PRAGMA threads = N
-  **
-  ** Configure the maximum number of worker threads.  Return the new
-  ** maximum, which might be less than requested.
-  */
-  case PragTyp_THREADS: {
-    sqlite3_int64 N;
-    if( zRight
-     && sqlite3DecOrHexToI64(zRight, &N)==SQLITE_OK
-     && N>=0
-    ){
-      sqlite3_limit(db, SQLITE_LIMIT_WORKER_THREADS, (int)(N&0x7fffffff));
-    }
-    returnSingleInt(v, sqlite3_limit(db, SQLITE_LIMIT_WORKER_THREADS, -1));
-    break;
-  }
-
 #if defined(SQLITE_DEBUG) || defined(SQLITE_TEST)
   /*
   ** Report the current state of file logs for all databases
   */
-  case PragTyp_LOCK_STATUS: {
+  if( sqlite3StrICmp(zLeft, "lock_status")==0 ){
     static const char *const azLockName[] = {
       "unlocked", "shared", "reserved", "pending", "exclusive"
     };
     int i;
+    sqlite3VdbeSetNumCols(v, 2);
     pParse->nMem = 2;
+    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "database", SQLITE_STATIC);
+    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "status", SQLITE_STATIC);
     for(i=0; i<db->nDb; i++){
       Btree *pBt;
+      Pager *pPager;
       const char *zState = "unknown";
       int j;
-      if( db->aDb[i].zDbSName==0 ) continue;
+      if( db->aDb[i].zName==0 ) continue;
+      sqlite3VdbeAddOp4(v, OP_String8, 0, 1, 0, db->aDb[i].zName, P4_STATIC);
       pBt = db->aDb[i].pBt;
-      if( pBt==0 || sqlite3BtreePager(pBt)==0 ){
+      if( pBt==0 || (pPager = sqlite3BtreePager(pBt))==0 ){
         zState = "closed";
-      }else if( sqlite3_file_control(db, i ? db->aDb[i].zDbSName : 0, 
+      }else if( sqlite3_file_control(db, i ? db->aDb[i].zName : 0, 
                                      SQLITE_FCNTL_LOCKSTATE, &j)==SQLITE_OK ){
          zState = azLockName[j];
       }
-      sqlite3VdbeMultiLoad(v, 1, "ss", db->aDb[i].zDbSName, zState);
+      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, zState, P4_STATIC);
+      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 2);
     }
-    break;
-  }
+
+  }else
 #endif
 
-#ifdef SQLITE_HAS_CODEC
-  case PragTyp_KEY: {
-    if( zRight ) sqlite3_key_v2(db, zDb, zRight, sqlite3Strlen30(zRight));
-    break;
-  }
-  case PragTyp_REKEY: {
-    if( zRight ) sqlite3_rekey_v2(db, zDb, zRight, sqlite3Strlen30(zRight));
-    break;
-  }
-  case PragTyp_HEXKEY: {
-    if( zRight ){
-      u8 iByte;
-      int i;
-      char zKey[40];
-      for(i=0, iByte=0; i<sizeof(zKey)*2 && sqlite3Isxdigit(zRight[i]); i++){
-        iByte = (iByte<<4) + sqlite3HexToInt(zRight[i]);
-        if( (i&1)!=0 ) zKey[i/2] = iByte;
-      }
-      if( (zLeft[3] & 0xf)==0xb ){
-        sqlite3_key_v2(db, zDb, zKey, i/2);
-      }else{
-        sqlite3_rekey_v2(db, zDb, zKey, i/2);
-      }
+#ifdef SQLITE_SSE
+  /*
+  ** Check to see if the sqlite_statements table exists.  Create it
+  ** if it does not.
+  */
+  if( sqlite3StrICmp(zLeft, "create_sqlite_statement_table")==0 ){
+    extern int sqlite3CreateStatementsTable(Parse*);
+    sqlite3CreateStatementsTable(pParse);
+  }else
+#endif
+
+#if SQLITE_HAS_CODEC
+  if( sqlite3StrICmp(zLeft, "key")==0 && zRight ){
+    sqlite3_key(db, zRight, sqlite3Strlen30(zRight));
+  }else
+  if( sqlite3StrICmp(zLeft, "rekey")==0 && zRight ){
+    sqlite3_rekey(db, zRight, sqlite3Strlen30(zRight));
+  }else
+  if( zRight && (sqlite3StrICmp(zLeft, "hexkey")==0 ||
+                 sqlite3StrICmp(zLeft, "hexrekey")==0) ){
+    int i, h1, h2;
+    char zKey[40];
+    for(i=0; (h1 = zRight[i])!=0 && (h2 = zRight[i+1])!=0; i+=2){
+      h1 += 9*(1&(h1>>6));
+      h2 += 9*(1&(h2>>6));
+      zKey[i/2] = (h2 & 0x0f) | ((h1 & 0xf)<<4);
     }
-    break;
-  }
+    if( (zLeft[3] & 0xf)==0xb ){
+      sqlite3_key(db, zKey, i/2);
+    }else{
+      sqlite3_rekey(db, zKey, i/2);
+    }
+  }else
 #endif
-#if defined(SQLITE_HAS_CODEC) || defined(SQLITE_ENABLE_CEROD)
-  case PragTyp_ACTIVATE_EXTENSIONS: if( zRight ){
-#ifdef SQLITE_HAS_CODEC
+#if SQLITE_HAS_CODEC || defined(SQLITE_ENABLE_CEROD)
+  if( sqlite3StrICmp(zLeft, "activate_extensions")==0 ){
+#if SQLITE_HAS_CODEC
     if( sqlite3StrNICmp(zRight, "see-", 4)==0 ){
+      extern void sqlite3_activate_see(const char*);
       sqlite3_activate_see(&zRight[4]);
     }
 #endif
 #ifdef SQLITE_ENABLE_CEROD
     if( sqlite3StrNICmp(zRight, "cerod-", 6)==0 ){
+      extern void sqlite3_activate_cerod(const char*);
       sqlite3_activate_cerod(&zRight[6]);
     }
 #endif
-  }
-  break;
+  }else
 #endif
 
-  } /* End of the PRAGMA switch */
+ 
+  {/* Empty ELSE clause */}
 
-  /* The following block is a no-op unless SQLITE_DEBUG is defined. Its only
-  ** purpose is to execute assert() statements to verify that if the
-  ** PragFlg_NoColumns1 flag is set and the caller specified an argument
-  ** to the PRAGMA, the implementation has not added any OP_ResultRow 
-  ** instructions to the VM.  */
-  if( (pPragma->mPragFlg & PragFlg_NoColumns1) && zRight ){
-    sqlite3VdbeVerifyNoResultRow(v);
-  }
+  /* Code an OP_Expire at the end of each PRAGMA program to cause
+  ** the VDBE implementing the pragma to expire. Most (all?) pragmas
+  ** are only valid for a single execution.
+  */
+  sqlite3VdbeAddOp2(v, OP_Expire, 1, 0);
 
+  /*
+  ** Reset the safety level, in case the fullfsync flag or synchronous
+  ** setting changed.
+  */
+#ifndef SQLITE_OMIT_PAGER_PRAGMAS
+  if( db->autoCommit ){
+    sqlite3BtreeSetSafetyLevel(pDb->pBt, pDb->safety_level,
+               (db->flags&SQLITE_FullFSync)!=0);
+  }
+#endif
 pragma_out:
   sqlite3DbFree(db, zLeft);
   sqlite3DbFree(db, zRight);
 }
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-/*****************************************************************************
-** Implementation of an eponymous virtual table that runs a pragma.
-**
-*/
-typedef struct PragmaVtab PragmaVtab;
-typedef struct PragmaVtabCursor PragmaVtabCursor;
-struct PragmaVtab {
-  sqlite3_vtab base;        /* Base class.  Must be first */
-  sqlite3 *db;              /* The database connection to which it belongs */
-  const PragmaName *pName;  /* Name of the pragma */
-  u8 nHidden;               /* Number of hidden columns */
-  u8 iHidden;               /* Index of the first hidden column */
-};
-struct PragmaVtabCursor {
-  sqlite3_vtab_cursor base; /* Base class.  Must be first */
-  sqlite3_stmt *pPragma;    /* The pragma statement to run */
-  sqlite_int64 iRowid;      /* Current rowid */
-  char *azArg[2];           /* Value of the argument and schema */
-};
-
-/* 
-** Pragma virtual table module xConnect method.
-*/
-static int pragmaVtabConnect(
-  sqlite3 *db,
-  void *pAux,
-  int argc, const char *const*argv,
-  sqlite3_vtab **ppVtab,
-  char **pzErr
-){
-  const PragmaName *pPragma = (const PragmaName*)pAux;
-  PragmaVtab *pTab = 0;
-  int rc;
-  int i, j;
-  char cSep = '(';
-  StrAccum acc;
-  char zBuf[200];
-
-  UNUSED_PARAMETER(argc);
-  UNUSED_PARAMETER(argv);
-  sqlite3StrAccumInit(&acc, 0, zBuf, sizeof(zBuf), 0);
-  sqlite3StrAccumAppendAll(&acc, "CREATE TABLE x");
-  for(i=0, j=pPragma->iPragCName; i<pPragma->nPragCName; i++, j++){
-    sqlite3XPrintf(&acc, "%c\"%s\"", cSep, pragCName[j]);
-    cSep = ',';
-  }
-  if( i==0 ){
-    sqlite3XPrintf(&acc, "(\"%s\"", pPragma->zName);
-    cSep = ',';
-    i++;
-  }
-  j = 0;
-  if( pPragma->mPragFlg & PragFlg_Result1 ){
-    sqlite3StrAccumAppendAll(&acc, ",arg HIDDEN");
-    j++;
-  }
-  if( pPragma->mPragFlg & (PragFlg_SchemaOpt|PragFlg_SchemaReq) ){
-    sqlite3StrAccumAppendAll(&acc, ",schema HIDDEN");
-    j++;
-  }
-  sqlite3StrAccumAppend(&acc, ")", 1);
-  sqlite3StrAccumFinish(&acc);
-  assert( strlen(zBuf) < sizeof(zBuf)-1 );
-  rc = sqlite3_declare_vtab(db, zBuf);
-  if( rc==SQLITE_OK ){
-    pTab = (PragmaVtab*)sqlite3_malloc(sizeof(PragmaVtab));
-    if( pTab==0 ){
-      rc = SQLITE_NOMEM;
-    }else{
-      memset(pTab, 0, sizeof(PragmaVtab));
-      pTab->pName = pPragma;
-      pTab->db = db;
-      pTab->iHidden = i;
-      pTab->nHidden = j;
-    }
-  }else{
-    *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(db));
-  }
-
-  *ppVtab = (sqlite3_vtab*)pTab;
-  return rc;
-}
-
-/* 
-** Pragma virtual table module xDisconnect method.
-*/
-static int pragmaVtabDisconnect(sqlite3_vtab *pVtab){
-  PragmaVtab *pTab = (PragmaVtab*)pVtab;
-  sqlite3_free(pTab);
-  return SQLITE_OK;
-}
-
-/* Figure out the best index to use to search a pragma virtual table.
-**
-** There are not really any index choices.  But we want to encourage the
-** query planner to give == constraints on as many hidden parameters as
-** possible, and especially on the first hidden parameter.  So return a
-** high cost if hidden parameters are unconstrained.
-*/
-static int pragmaVtabBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
-  PragmaVtab *pTab = (PragmaVtab*)tab;
-  const struct sqlite3_index_constraint *pConstraint;
-  int i, j;
-  int seen[2];
-
-  pIdxInfo->estimatedCost = (double)1;
-  if( pTab->nHidden==0 ){ return SQLITE_OK; }
-  pConstraint = pIdxInfo->aConstraint;
-  seen[0] = 0;
-  seen[1] = 0;
-  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
-    if( pConstraint->usable==0 ) continue;
-    if( pConstraint->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
-    if( pConstraint->iColumn < pTab->iHidden ) continue;
-    j = pConstraint->iColumn - pTab->iHidden;
-    assert( j < 2 );
-    seen[j] = i+1;
-  }
-  if( seen[0]==0 ){
-    pIdxInfo->estimatedCost = (double)2147483647;
-    pIdxInfo->estimatedRows = 2147483647;
-    return SQLITE_OK;
-  }
-  j = seen[0]-1;
-  pIdxInfo->aConstraintUsage[j].argvIndex = 1;
-  pIdxInfo->aConstraintUsage[j].omit = 1;
-  if( seen[1]==0 ) return SQLITE_OK;
-  pIdxInfo->estimatedCost = (double)20;
-  pIdxInfo->estimatedRows = 20;
-  j = seen[1]-1;
-  pIdxInfo->aConstraintUsage[j].argvIndex = 2;
-  pIdxInfo->aConstraintUsage[j].omit = 1;
-  return SQLITE_OK;
-}
-
-/* Create a new cursor for the pragma virtual table */
-static int pragmaVtabOpen(sqlite3_vtab *pVtab, sqlite3_vtab_cursor **ppCursor){
-  PragmaVtabCursor *pCsr;
-  pCsr = (PragmaVtabCursor*)sqlite3_malloc(sizeof(*pCsr));
-  if( pCsr==0 ) return SQLITE_NOMEM;
-  memset(pCsr, 0, sizeof(PragmaVtabCursor));
-  pCsr->base.pVtab = pVtab;
-  *ppCursor = &pCsr->base;
-  return SQLITE_OK;
-}
-
-/* Clear all content from pragma virtual table cursor. */
-static void pragmaVtabCursorClear(PragmaVtabCursor *pCsr){
-  int i;
-  sqlite3_finalize(pCsr->pPragma);
-  pCsr->pPragma = 0;
-  for(i=0; i<ArraySize(pCsr->azArg); i++){
-    sqlite3_free(pCsr->azArg[i]);
-    pCsr->azArg[i] = 0;
-  }
-}
-
-/* Close a pragma virtual table cursor */
-static int pragmaVtabClose(sqlite3_vtab_cursor *cur){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)cur;
-  pragmaVtabCursorClear(pCsr);
-  sqlite3_free(pCsr);
-  return SQLITE_OK;
-}
-
-/* Advance the pragma virtual table cursor to the next row */
-static int pragmaVtabNext(sqlite3_vtab_cursor *pVtabCursor){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
-  int rc = SQLITE_OK;
-
-  /* Increment the xRowid value */
-  pCsr->iRowid++;
-  assert( pCsr->pPragma );
-  if( SQLITE_ROW!=sqlite3_step(pCsr->pPragma) ){
-    rc = sqlite3_finalize(pCsr->pPragma);
-    pCsr->pPragma = 0;
-    pragmaVtabCursorClear(pCsr);
-  }
-  return rc;
-}
-
-/* 
-** Pragma virtual table module xFilter method.
-*/
-static int pragmaVtabFilter(
-  sqlite3_vtab_cursor *pVtabCursor, 
-  int idxNum, const char *idxStr,
-  int argc, sqlite3_value **argv
-){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
-  PragmaVtab *pTab = (PragmaVtab*)(pVtabCursor->pVtab);
-  int rc;
-  int i, j;
-  StrAccum acc;
-  char *zSql;
-
-  UNUSED_PARAMETER(idxNum);
-  UNUSED_PARAMETER(idxStr);
-  pragmaVtabCursorClear(pCsr);
-  j = (pTab->pName->mPragFlg & PragFlg_Result1)!=0 ? 0 : 1;
-  for(i=0; i<argc; i++, j++){
-    const char *zText = (const char*)sqlite3_value_text(argv[i]);
-    assert( j<ArraySize(pCsr->azArg) );
-    assert( pCsr->azArg[j]==0 );
-    if( zText ){
-      pCsr->azArg[j] = sqlite3_mprintf("%s", zText);
-      if( pCsr->azArg[j]==0 ){
-        return SQLITE_NOMEM;
-      }
-    }
-  }
-  sqlite3StrAccumInit(&acc, 0, 0, 0, pTab->db->aLimit[SQLITE_LIMIT_SQL_LENGTH]);
-  sqlite3StrAccumAppendAll(&acc, "PRAGMA ");
-  if( pCsr->azArg[1] ){
-    sqlite3XPrintf(&acc, "%Q.", pCsr->azArg[1]);
-  }
-  sqlite3StrAccumAppendAll(&acc, pTab->pName->zName);
-  if( pCsr->azArg[0] ){
-    sqlite3XPrintf(&acc, "=%Q", pCsr->azArg[0]);
-  }
-  zSql = sqlite3StrAccumFinish(&acc);
-  if( zSql==0 ) return SQLITE_NOMEM;
-  rc = sqlite3_prepare_v2(pTab->db, zSql, -1, &pCsr->pPragma, 0);
-  sqlite3_free(zSql);
-  if( rc!=SQLITE_OK ){
-    pTab->base.zErrMsg = sqlite3_mprintf("%s", sqlite3_errmsg(pTab->db));
-    return rc;
-  }
-  return pragmaVtabNext(pVtabCursor);
-}
-
-/*
-** Pragma virtual table module xEof method.
-*/
-static int pragmaVtabEof(sqlite3_vtab_cursor *pVtabCursor){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
-  return (pCsr->pPragma==0);
-}
-
-/* The xColumn method simply returns the corresponding column from
-** the PRAGMA.  
-*/
-static int pragmaVtabColumn(
-  sqlite3_vtab_cursor *pVtabCursor, 
-  sqlite3_context *ctx, 
-  int i
-){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
-  PragmaVtab *pTab = (PragmaVtab*)(pVtabCursor->pVtab);
-  if( i<pTab->iHidden ){
-    sqlite3_result_value(ctx, sqlite3_column_value(pCsr->pPragma, i));
-  }else{
-    sqlite3_result_text(ctx, pCsr->azArg[i-pTab->iHidden],-1,SQLITE_TRANSIENT);
-  }
-  return SQLITE_OK;
-}
-
-/* 
-** Pragma virtual table module xRowid method.
-*/
-static int pragmaVtabRowid(sqlite3_vtab_cursor *pVtabCursor, sqlite_int64 *p){
-  PragmaVtabCursor *pCsr = (PragmaVtabCursor*)pVtabCursor;
-  *p = pCsr->iRowid;
-  return SQLITE_OK;
-}
-
-/* The pragma virtual table object */
-static const sqlite3_module pragmaVtabModule = {
-  0,                           /* iVersion */
-  0,                           /* xCreate - create a table */
-  pragmaVtabConnect,           /* xConnect - connect to an existing table */
-  pragmaVtabBestIndex,         /* xBestIndex - Determine search strategy */
-  pragmaVtabDisconnect,        /* xDisconnect - Disconnect from a table */
-  0,                           /* xDestroy - Drop a table */
-  pragmaVtabOpen,              /* xOpen - open a cursor */
-  pragmaVtabClose,             /* xClose - close a cursor */
-  pragmaVtabFilter,            /* xFilter - configure scan constraints */
-  pragmaVtabNext,              /* xNext - advance a cursor */
-  pragmaVtabEof,               /* xEof */
-  pragmaVtabColumn,            /* xColumn - read data */
-  pragmaVtabRowid,             /* xRowid - read data */
-  0,                           /* xUpdate - write data */
-  0,                           /* xBegin - begin transaction */
-  0,                           /* xSync - sync transaction */
-  0,                           /* xCommit - commit transaction */
-  0,                           /* xRollback - rollback transaction */
-  0,                           /* xFindFunction - function overloading */
-  0,                           /* xRename - rename the table */
-  0,                           /* xSavepoint */
-  0,                           /* xRelease */
-  0                            /* xRollbackTo */
-};
-
-/*
-** Check to see if zTabName is really the name of a pragma.  If it is,
-** then register an eponymous virtual table for that pragma and return
-** a pointer to the Module object for the new virtual table.
-*/
-Module *sqlite3PragmaVtabRegister(sqlite3 *db, const char *zName){
-  const PragmaName *pName;
-  assert( sqlite3_strnicmp(zName, "pragma_", 7)==0 );
-  pName = pragmaLocate(zName+7);
-  if( pName==0 ) return 0;
-  if( (pName->mPragFlg & (PragFlg_Result0|PragFlg_Result1))==0 ) return 0;
-  assert( sqlite3HashFind(&db->aModule, zName)==0 );
-  return sqlite3VtabCreateModule(db, zName, &pragmaVtabModule, (void*)pName, 0);
-}
-
-#endif /* SQLITE_OMIT_VIRTUALTABLE */
 
-#endif /* SQLITE_OMIT_PRAGMA */
+#endif /* SQLITE_OMIT_PRAGMA || SQLITE_OMIT_PARSER */
