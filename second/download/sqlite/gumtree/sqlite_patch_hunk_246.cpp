 **    May you find forgiveness for yourself and forgive others.
 **    May you share freely, never taking more than you give.
 **
 *************************************************************************
 **
 ** This file contains code used to implement incremental BLOB I/O.
-**
-** $Id: vdbeblob.c,v 1.33 2009/06/01 19:53:31 drh Exp $
 */
 
 #include "sqliteInt.h"
 #include "vdbeInt.h"
 
 #ifndef SQLITE_OMIT_INCRBLOB
 
 /*
 ** Valid sqlite3_blob* handles point to Incrblob structures.
 */
 typedef struct Incrblob Incrblob;
 struct Incrblob {
-  int flags;              /* Copy of "flags" passed to sqlite3_blob_open() */
   int nByte;              /* Size of open blob, in bytes */
   int iOffset;            /* Byte offset of blob in cursor data */
+  u16 iCol;               /* Table column this handle is open on */
   BtCursor *pCsr;         /* Cursor pointing at blob row */
   sqlite3_stmt *pStmt;    /* Statement holding cursor open */
   sqlite3 *db;            /* The associated database */
+  char *zDb;              /* Database name */
+  Table *pTab;            /* Table object */
 };
 
+
+/*
+** This function is used by both blob_open() and blob_reopen(). It seeks
+** the b-tree cursor associated with blob handle p to point to row iRow.
+** If successful, SQLITE_OK is returned and subsequent calls to
+** sqlite3_blob_read() or sqlite3_blob_write() access the specified row.
+**
+** If an error occurs, or if the specified row does not exist or does not
+** contain a value of type TEXT or BLOB in the column nominated when the
+** blob handle was opened, then an error code is returned and *pzErr may
+** be set to point to a buffer containing an error message. It is the
+** responsibility of the caller to free the error message buffer using
+** sqlite3DbFree().
+**
+** If an error does occur, then the b-tree cursor is closed. All subsequent
+** calls to sqlite3_blob_read(), blob_write() or blob_reopen() will 
+** immediately return SQLITE_ABORT.
+*/
+static int blobSeekToRow(Incrblob *p, sqlite3_int64 iRow, char **pzErr){
+  int rc;                         /* Error code */
+  char *zErr = 0;                 /* Error message */
+  Vdbe *v = (Vdbe *)p->pStmt;
+
+  /* Set the value of register r[1] in the SQL statement to integer iRow. 
+  ** This is done directly as a performance optimization
+  */
+  v->aMem[1].flags = MEM_Int;
+  v->aMem[1].u.i = iRow;
+
+  /* If the statement has been run before (and is paused at the OP_ResultRow)
+  ** then back it up to the point where it does the OP_SeekRowid.  This could
+  ** have been down with an extra OP_Goto, but simply setting the program
+  ** counter is faster. */
+  if( v->pc>3 ){
+    v->pc = 3;
+    rc = sqlite3VdbeExec(v);
+  }else{
+    rc = sqlite3_step(p->pStmt);
+  }
+  if( rc==SQLITE_ROW ){
+    VdbeCursor *pC = v->apCsr[0];
+    u32 type = pC->nHdrParsed>p->iCol ? pC->aType[p->iCol] : 0;
+    testcase( pC->nHdrParsed==p->iCol );
+    testcase( pC->nHdrParsed==p->iCol+1 );
+    if( type<12 ){
+      zErr = sqlite3MPrintf(p->db, "cannot open value of type %s",
+          type==0?"null": type==7?"real": "integer"
+      );
+      rc = SQLITE_ERROR;
+      sqlite3_finalize(p->pStmt);
+      p->pStmt = 0;
+    }else{
+      p->iOffset = pC->aType[p->iCol + pC->nField];
+      p->nByte = sqlite3VdbeSerialTypeLen(type);
+      p->pCsr =  pC->uc.pCursor;
+      sqlite3BtreeIncrblobCursor(p->pCsr);
+    }
+  }
+
+  if( rc==SQLITE_ROW ){
+    rc = SQLITE_OK;
+  }else if( p->pStmt ){
+    rc = sqlite3_finalize(p->pStmt);
+    p->pStmt = 0;
+    if( rc==SQLITE_OK ){
+      zErr = sqlite3MPrintf(p->db, "no such rowid: %lld", iRow);
+      rc = SQLITE_ERROR;
+    }else{
+      zErr = sqlite3MPrintf(p->db, "%s", sqlite3_errmsg(p->db));
+    }
+  }
+
+  assert( rc!=SQLITE_OK || zErr==0 );
+  assert( rc!=SQLITE_ROW && rc!=SQLITE_DONE );
+
+  *pzErr = zErr;
+  return rc;
+}
+
 /*
 ** Open a blob handle.
 */
 int sqlite3_blob_open(
   sqlite3* db,            /* The database connection */
   const char *zDb,        /* The attached database containing the blob */
   const char *zTable,     /* The table containing the blob */
   const char *zColumn,    /* The column containing the blob */
   sqlite_int64 iRow,      /* The row containing the glob */
-  int flags,              /* True -> read/write access, false -> read-only */
+  int wrFlag,             /* True -> read/write access, false -> read-only */
   sqlite3_blob **ppBlob   /* Handle for accessing the blob returned here */
 ){
   int nAttempt = 0;
   int iCol;               /* Index of zColumn in row-record */
-
-  /* This VDBE program seeks a btree cursor to the identified 
-  ** db/table/row entry. The reason for using a vdbe program instead
-  ** of writing code to use the b-tree layer directly is that the
-  ** vdbe program will take advantage of the various transaction,
-  ** locking and error handling infrastructure built into the vdbe.
-  **
-  ** After seeking the cursor, the vdbe executes an OP_ResultRow.
-  ** Code external to the Vdbe then "borrows" the b-tree cursor and
-  ** uses it to implement the blob_read(), blob_write() and 
-  ** blob_bytes() functions.
-  **
-  ** The sqlite3_blob_close() function finalizes the vdbe program,
-  ** which closes the b-tree cursor and (possibly) commits the 
-  ** transaction.
-  */
-  static const VdbeOpList openBlob[] = {
-    {OP_Transaction, 0, 0, 0},     /* 0: Start a transaction */
-    {OP_VerifyCookie, 0, 0, 0},    /* 1: Check the schema cookie */
-
-    /* One of the following two instructions is replaced by an
-    ** OP_Noop before exection.
-    */
-    {OP_OpenRead, 0, 0, 0},        /* 2: Open cursor 0 for reading */
-    {OP_OpenWrite, 0, 0, 0},       /* 3: Open cursor 0 for read/write */
-
-    {OP_Variable, 1, 1, 1},        /* 4: Push the rowid to the stack */
-    {OP_NotExists, 0, 8, 1},       /* 5: Seek the cursor */
-    {OP_Column, 0, 0, 1},          /* 6  */
-    {OP_ResultRow, 1, 0, 0},       /* 7  */
-    {OP_Close, 0, 0, 0},           /* 8  */
-    {OP_Halt, 0, 0, 0},            /* 9 */
-  };
-
-  Vdbe *v = 0;
   int rc = SQLITE_OK;
   char *zErr = 0;
   Table *pTab;
-  Parse *pParse;
+  Incrblob *pBlob = 0;
+  Parse sParse;
 
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( ppBlob==0 ){
+    return SQLITE_MISUSE_BKPT;
+  }
+#endif
   *ppBlob = 0;
-  sqlite3_mutex_enter(db->mutex);
-  pParse = sqlite3StackAllocRaw(db, sizeof(*pParse));
-  if( pParse==0 ){
-    rc = SQLITE_NOMEM;
-    goto blob_open_out;
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( !sqlite3SafetyCheckOk(db) || zTable==0 ){
+    return SQLITE_MISUSE_BKPT;
   }
-  do {
-    memset(pParse, 0, sizeof(Parse));
-    pParse->db = db;
+#endif
+  wrFlag = !!wrFlag;                /* wrFlag = (wrFlag ? 1 : 0); */
 
-    if( sqlite3SafetyOn(db) ){
-      sqlite3DbFree(db, zErr);
-      sqlite3StackFree(db, pParse);
-      sqlite3_mutex_leave(db->mutex);
-      return SQLITE_MISUSE;
-    }
+  sqlite3_mutex_enter(db->mutex);
+
+  pBlob = (Incrblob *)sqlite3DbMallocZero(db, sizeof(Incrblob));
+  do {
+    memset(&sParse, 0, sizeof(Parse));
+    if( !pBlob ) goto blob_open_out;
+    sParse.db = db;
+    sqlite3DbFree(db, zErr);
+    zErr = 0;
 
     sqlite3BtreeEnterAll(db);
-    pTab = sqlite3LocateTable(pParse, 0, zTable, zDb);
+    pTab = sqlite3LocateTable(&sParse, 0, zTable, zDb);
     if( pTab && IsVirtual(pTab) ){
       pTab = 0;
-      sqlite3ErrorMsg(pParse, "cannot open virtual table: %s", zTable);
+      sqlite3ErrorMsg(&sParse, "cannot open virtual table: %s", zTable);
+    }
+    if( pTab && !HasRowid(pTab) ){
+      pTab = 0;
+      sqlite3ErrorMsg(&sParse, "cannot open table without rowid: %s", zTable);
     }
 #ifndef SQLITE_OMIT_VIEW
     if( pTab && pTab->pSelect ){
       pTab = 0;
-      sqlite3ErrorMsg(pParse, "cannot open view: %s", zTable);
+      sqlite3ErrorMsg(&sParse, "cannot open view: %s", zTable);
     }
 #endif
     if( !pTab ){
-      if( pParse->zErrMsg ){
+      if( sParse.zErrMsg ){
         sqlite3DbFree(db, zErr);
-        zErr = pParse->zErrMsg;
-        pParse->zErrMsg = 0;
+        zErr = sParse.zErrMsg;
+        sParse.zErrMsg = 0;
       }
       rc = SQLITE_ERROR;
-      (void)sqlite3SafetyOff(db);
       sqlite3BtreeLeaveAll(db);
       goto blob_open_out;
     }
+    pBlob->pTab = pTab;
+    pBlob->zDb = db->aDb[sqlite3SchemaToIndex(db, pTab->pSchema)].zDbSName;
 
     /* Now search pTab for the exact column. */
-    for(iCol=0; iCol < pTab->nCol; iCol++) {
+    for(iCol=0; iCol<pTab->nCol; iCol++) {
       if( sqlite3StrICmp(pTab->aCol[iCol].zName, zColumn)==0 ){
         break;
       }
     }
     if( iCol==pTab->nCol ){
       sqlite3DbFree(db, zErr);
       zErr = sqlite3MPrintf(db, "no such column: \"%s\"", zColumn);
       rc = SQLITE_ERROR;
-      (void)sqlite3SafetyOff(db);
       sqlite3BtreeLeaveAll(db);
       goto blob_open_out;
     }
 
     /* If the value is being opened for writing, check that the
-    ** column is not indexed. It is against the rules to open an
-    ** indexed column for writing.
+    ** column is not indexed, and that it is not part of a foreign key. 
     */
-    if( flags ){
+    if( wrFlag ){
+      const char *zFault = 0;
       Index *pIdx;
+#ifndef SQLITE_OMIT_FOREIGN_KEY
+      if( db->flags&SQLITE_ForeignKeys ){
+        /* Check that the column is not part of an FK child key definition. It
+        ** is not necessary to check if it is part of a parent key, as parent
+        ** key columns must be indexed. The check below will pick up this 
+        ** case.  */
+        FKey *pFKey;
+        for(pFKey=pTab->pFKey; pFKey; pFKey=pFKey->pNextFrom){
+          int j;
+          for(j=0; j<pFKey->nCol; j++){
+            if( pFKey->aCol[j].iFrom==iCol ){
+              zFault = "foreign key";
+            }
+          }
+        }
+      }
+#endif
       for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
         int j;
-        for(j=0; j<pIdx->nColumn; j++){
-          if( pIdx->aiColumn[j]==iCol ){
-            sqlite3DbFree(db, zErr);
-            zErr = sqlite3MPrintf(db,
-                             "cannot open indexed column for writing");
-            rc = SQLITE_ERROR;
-            (void)sqlite3SafetyOff(db);
-            sqlite3BtreeLeaveAll(db);
-            goto blob_open_out;
+        for(j=0; j<pIdx->nKeyCol; j++){
+          /* FIXME: Be smarter about indexes that use expressions */
+          if( pIdx->aiColumn[j]==iCol || pIdx->aiColumn[j]==XN_EXPR ){
+            zFault = "indexed";
           }
         }
       }
+      if( zFault ){
+        sqlite3DbFree(db, zErr);
+        zErr = sqlite3MPrintf(db, "cannot open %s column for writing", zFault);
+        rc = SQLITE_ERROR;
+        sqlite3BtreeLeaveAll(db);
+        goto blob_open_out;
+      }
     }
 
-    v = sqlite3VdbeCreate(db);
-    if( v ){
+    pBlob->pStmt = (sqlite3_stmt *)sqlite3VdbeCreate(&sParse);
+    assert( pBlob->pStmt || db->mallocFailed );
+    if( pBlob->pStmt ){
+      
+      /* This VDBE program seeks a btree cursor to the identified 
+      ** db/table/row entry. The reason for using a vdbe program instead
+      ** of writing code to use the b-tree layer directly is that the
+      ** vdbe program will take advantage of the various transaction,
+      ** locking and error handling infrastructure built into the vdbe.
+      **
+      ** After seeking the cursor, the vdbe executes an OP_ResultRow.
+      ** Code external to the Vdbe then "borrows" the b-tree cursor and
+      ** uses it to implement the blob_read(), blob_write() and 
+      ** blob_bytes() functions.
+      **
+      ** The sqlite3_blob_close() function finalizes the vdbe program,
+      ** which closes the b-tree cursor and (possibly) commits the 
+      ** transaction.
+      */
+      static const int iLn = VDBE_OFFSET_LINENO(2);
+      static const VdbeOpList openBlob[] = {
+        {OP_TableLock,      0, 0, 0},  /* 0: Acquire a read or write lock */
+        {OP_OpenRead,       0, 0, 0},  /* 1: Open a cursor */
+        /* blobSeekToRow() will initialize r[1] to the desired rowid */
+        {OP_NotExists,      0, 5, 1},  /* 2: Seek the cursor to rowid=r[1] */
+        {OP_Column,         0, 0, 1},  /* 3  */
+        {OP_ResultRow,      1, 0, 0},  /* 4  */
+        {OP_Halt,           0, 0, 0},  /* 5  */
+      };
+      Vdbe *v = (Vdbe *)pBlob->pStmt;
       int iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
-      sqlite3VdbeAddOpList(v, sizeof(openBlob)/sizeof(VdbeOpList), openBlob);
+      VdbeOp *aOp;
 
-      /* Configure the OP_Transaction */
-      sqlite3VdbeChangeP1(v, 0, iDb);
-      sqlite3VdbeChangeP2(v, 0, (flags ? 1 : 0));
-
-      /* Configure the OP_VerifyCookie */
-      sqlite3VdbeChangeP1(v, 1, iDb);
-      sqlite3VdbeChangeP2(v, 1, pTab->pSchema->schema_cookie);
+      sqlite3VdbeAddOp4Int(v, OP_Transaction, iDb, wrFlag, 
+                           pTab->pSchema->schema_cookie,
+                           pTab->pSchema->iGeneration);
+      sqlite3VdbeChangeP5(v, 1);
+      assert( sqlite3VdbeCurrentAddr(v)==2 || db->mallocFailed );
+      aOp = sqlite3VdbeAddOpList(v, ArraySize(openBlob), openBlob, iLn);
 
       /* Make sure a mutex is held on the table to be accessed */
       sqlite3VdbeUsesBtree(v, iDb); 
 
-      /* Remove either the OP_OpenWrite or OpenRead. Set the P2 
-      ** parameter of the other to pTab->tnum. 
-      */
-      flags = !!flags;
-      sqlite3VdbeChangeToNoop(v, 3 - flags, 1);
-      sqlite3VdbeChangeP2(v, 2 + flags, pTab->tnum);
-      sqlite3VdbeChangeP3(v, 2 + flags, iDb);
-
-      /* Configure the number of columns. Configure the cursor to
-      ** think that the table has one more column than it really
-      ** does. An OP_Column to retrieve this imaginary column will
-      ** always return an SQL NULL. This is useful because it means
-      ** we can invoke OP_Column to fill in the vdbe cursors type 
-      ** and offset cache without causing any IO.
-      */
-      sqlite3VdbeChangeP4(v, 2+flags, SQLITE_INT_TO_PTR(pTab->nCol+1),P4_INT32);
-      sqlite3VdbeChangeP2(v, 6, pTab->nCol);
-      if( !db->mallocFailed ){
-        sqlite3VdbeMakeReady(v, 1, 1, 1, 0);
+      if( db->mallocFailed==0 ){
+        assert( aOp!=0 );
+        /* Configure the OP_TableLock instruction */
+#ifdef SQLITE_OMIT_SHARED_CACHE
+        aOp[0].opcode = OP_Noop;
+#else
+        aOp[0].p1 = iDb;
+        aOp[0].p2 = pTab->tnum;
+        aOp[0].p3 = wrFlag;
+        sqlite3VdbeChangeP4(v, 2, pTab->zName, P4_TRANSIENT);
+      }
+      if( db->mallocFailed==0 ){
+#endif
+
+        /* Remove either the OP_OpenWrite or OpenRead. Set the P2 
+        ** parameter of the other to pTab->tnum.  */
+        if( wrFlag ) aOp[1].opcode = OP_OpenWrite;
+        aOp[1].p2 = pTab->tnum;
+        aOp[1].p3 = iDb;   
+
+        /* Configure the number of columns. Configure the cursor to
+        ** think that the table has one more column than it really
+        ** does. An OP_Column to retrieve this imaginary column will
+        ** always return an SQL NULL. This is useful because it means
+        ** we can invoke OP_Column to fill in the vdbe cursors type 
+        ** and offset cache without causing any IO.
+        */
+        aOp[1].p4type = P4_INT32;
+        aOp[1].p4.i = pTab->nCol+1;
+        aOp[3].p2 = pTab->nCol;
+
+        sParse.nVar = 0;
+        sParse.nMem = 1;
+        sParse.nTab = 1;
+        sqlite3VdbeMakeReady(v, &sParse);
       }
     }
    
+    pBlob->iCol = iCol;
+    pBlob->db = db;
     sqlite3BtreeLeaveAll(db);
-    rc = sqlite3SafetyOff(db);
-    if( NEVER(rc!=SQLITE_OK) || db->mallocFailed ){
-      goto blob_open_out;
-    }
-
-    sqlite3_bind_int64((sqlite3_stmt *)v, 1, iRow);
-    rc = sqlite3_step((sqlite3_stmt *)v);
-    if( rc!=SQLITE_ROW ){
-      nAttempt++;
-      rc = sqlite3_finalize((sqlite3_stmt *)v);
-      sqlite3DbFree(db, zErr);
-      zErr = sqlite3MPrintf(db, sqlite3_errmsg(db));
-      v = 0;
-    }
-  } while( nAttempt<5 && rc==SQLITE_SCHEMA );
-
-  if( rc==SQLITE_ROW ){
-    /* The row-record has been opened successfully. Check that the
-    ** column in question contains text or a blob. If it contains
-    ** text, it is up to the caller to get the encoding right.
-    */
-    Incrblob *pBlob;
-    u32 type = v->apCsr[0]->aType[iCol];
-
-    if( type<12 ){
-      sqlite3DbFree(db, zErr);
-      zErr = sqlite3MPrintf(db, "cannot open value of type %s",
-          type==0?"null": type==7?"real": "integer"
-      );
-      rc = SQLITE_ERROR;
-      goto blob_open_out;
-    }
-    pBlob = (Incrblob *)sqlite3DbMallocZero(db, sizeof(Incrblob));
     if( db->mallocFailed ){
-      sqlite3DbFree(db, pBlob);
       goto blob_open_out;
     }
-    pBlob->flags = flags;
-    pBlob->pCsr =  v->apCsr[0]->pCursor;
-    sqlite3BtreeEnterCursor(pBlob->pCsr);
-    sqlite3BtreeCacheOverflow(pBlob->pCsr);
-    sqlite3BtreeLeaveCursor(pBlob->pCsr);
-    pBlob->pStmt = (sqlite3_stmt *)v;
-    pBlob->iOffset = v->apCsr[0]->aOffset[iCol];
-    pBlob->nByte = sqlite3VdbeSerialTypeLen(type);
-    pBlob->db = db;
-    *ppBlob = (sqlite3_blob *)pBlob;
-    rc = SQLITE_OK;
-  }else if( rc==SQLITE_OK ){
-    sqlite3DbFree(db, zErr);
-    zErr = sqlite3MPrintf(db, "no such rowid: %lld", iRow);
-    rc = SQLITE_ERROR;
-  }
+    rc = blobSeekToRow(pBlob, iRow, &zErr);
+  } while( (++nAttempt)<SQLITE_MAX_SCHEMA_RETRY && rc==SQLITE_SCHEMA );
 
 blob_open_out:
-  if( v && (rc!=SQLITE_OK || db->mallocFailed) ){
-    sqlite3VdbeFinalize(v);
+  if( rc==SQLITE_OK && db->mallocFailed==0 ){
+    *ppBlob = (sqlite3_blob *)pBlob;
+  }else{
+    if( pBlob && pBlob->pStmt ) sqlite3VdbeFinalize((Vdbe *)pBlob->pStmt);
+    sqlite3DbFree(db, pBlob);
   }
-  sqlite3Error(db, rc, zErr);
+  sqlite3ErrorWithMsg(db, rc, (zErr ? "%s" : 0), zErr);
   sqlite3DbFree(db, zErr);
-  sqlite3StackFree(db, pParse);
+  sqlite3ParserReset(&sParse);
   rc = sqlite3ApiExit(db, rc);
   sqlite3_mutex_leave(db->mutex);
   return rc;
 }
 
 /*
