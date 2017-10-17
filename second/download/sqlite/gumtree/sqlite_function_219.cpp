int sqlite3_blob_open(
  sqlite3* db,            /* The database connection */
  const char *zDb,        /* The attached database containing the blob */
  const char *zTable,     /* The table containing the blob */
  const char *zColumn,    /* The column containing the blob */
  sqlite_int64 iRow,      /* The row containing the glob */
  int wrFlag,             /* True -> read/write access, false -> read-only */
  sqlite3_blob **ppBlob   /* Handle for accessing the blob returned here */
){
  int nAttempt = 0;
  int iCol;               /* Index of zColumn in row-record */
  int rc = SQLITE_OK;
  char *zErr = 0;
  Table *pTab;
  Incrblob *pBlob = 0;
  Parse sParse;

#ifdef SQLITE_ENABLE_API_ARMOR
  if( ppBlob==0 ){
    return SQLITE_MISUSE_BKPT;
  }
#endif
  *ppBlob = 0;
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) || zTable==0 ){
    return SQLITE_MISUSE_BKPT;
  }
#endif
  wrFlag = !!wrFlag;                /* wrFlag = (wrFlag ? 1 : 0); */

  sqlite3_mutex_enter(db->mutex);

  pBlob = (Incrblob *)sqlite3DbMallocZero(db, sizeof(Incrblob));
  do {
    memset(&sParse, 0, sizeof(Parse));
    if( !pBlob ) goto blob_open_out;
    sParse.db = db;
    sqlite3DbFree(db, zErr);
    zErr = 0;

    sqlite3BtreeEnterAll(db);
    pTab = sqlite3LocateTable(&sParse, 0, zTable, zDb);
    if( pTab && IsVirtual(pTab) ){
      pTab = 0;
      sqlite3ErrorMsg(&sParse, "cannot open virtual table: %s", zTable);
    }
    if( pTab && !HasRowid(pTab) ){
      pTab = 0;
      sqlite3ErrorMsg(&sParse, "cannot open table without rowid: %s", zTable);
    }
#ifndef SQLITE_OMIT_VIEW
    if( pTab && pTab->pSelect ){
      pTab = 0;
      sqlite3ErrorMsg(&sParse, "cannot open view: %s", zTable);
    }
#endif
    if( !pTab ){
      if( sParse.zErrMsg ){
        sqlite3DbFree(db, zErr);
        zErr = sParse.zErrMsg;
        sParse.zErrMsg = 0;
      }
      rc = SQLITE_ERROR;
      sqlite3BtreeLeaveAll(db);
      goto blob_open_out;
    }
    pBlob->pTab = pTab;
    pBlob->zDb = db->aDb[sqlite3SchemaToIndex(db, pTab->pSchema)].zDbSName;

    /* Now search pTab for the exact column. */
    for(iCol=0; iCol<pTab->nCol; iCol++) {
      if( sqlite3StrICmp(pTab->aCol[iCol].zName, zColumn)==0 ){
        break;
      }
    }
    if( iCol==pTab->nCol ){
      sqlite3DbFree(db, zErr);
      zErr = sqlite3MPrintf(db, "no such column: \"%s\"", zColumn);
      rc = SQLITE_ERROR;
      sqlite3BtreeLeaveAll(db);
      goto blob_open_out;
    }

    /* If the value is being opened for writing, check that the
    ** column is not indexed, and that it is not part of a foreign key. 
    */
    if( wrFlag ){
      const char *zFault = 0;
      Index *pIdx;
#ifndef SQLITE_OMIT_FOREIGN_KEY
      if( db->flags&SQLITE_ForeignKeys ){
        /* Check that the column is not part of an FK child key definition. It
        ** is not necessary to check if it is part of a parent key, as parent
        ** key columns must be indexed. The check below will pick up this 
        ** case.  */
        FKey *pFKey;
        for(pFKey=pTab->pFKey; pFKey; pFKey=pFKey->pNextFrom){
          int j;
          for(j=0; j<pFKey->nCol; j++){
            if( pFKey->aCol[j].iFrom==iCol ){
              zFault = "foreign key";
            }
          }
        }
      }
#endif
      for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
        int j;
        for(j=0; j<pIdx->nKeyCol; j++){
          /* FIXME: Be smarter about indexes that use expressions */
          if( pIdx->aiColumn[j]==iCol || pIdx->aiColumn[j]==XN_EXPR ){
            zFault = "indexed";
          }
        }
      }
      if( zFault ){
        sqlite3DbFree(db, zErr);
        zErr = sqlite3MPrintf(db, "cannot open %s column for writing", zFault);
        rc = SQLITE_ERROR;
        sqlite3BtreeLeaveAll(db);
        goto blob_open_out;
      }
    }

    pBlob->pStmt = (sqlite3_stmt *)sqlite3VdbeCreate(&sParse);
    assert( pBlob->pStmt || db->mallocFailed );
    if( pBlob->pStmt ){
      
      /* This VDBE program seeks a btree cursor to the identified 
      ** db/table/row entry. The reason for using a vdbe program instead
      ** of writing code to use the b-tree layer directly is that the
      ** vdbe program will take advantage of the various transaction,
      ** locking and error handling infrastructure built into the vdbe.
      **
      ** After seeking the cursor, the vdbe executes an OP_ResultRow.
      ** Code external to the Vdbe then "borrows" the b-tree cursor and
      ** uses it to implement the blob_read(), blob_write() and 
      ** blob_bytes() functions.
      **
      ** The sqlite3_blob_close() function finalizes the vdbe program,
      ** which closes the b-tree cursor and (possibly) commits the 
      ** transaction.
      */
      static const int iLn = VDBE_OFFSET_LINENO(2);
      static const VdbeOpList openBlob[] = {
        {OP_TableLock,      0, 0, 0},  /* 0: Acquire a read or write lock */
        {OP_OpenRead,       0, 0, 0},  /* 1: Open a cursor */
        /* blobSeekToRow() will initialize r[1] to the desired rowid */
        {OP_NotExists,      0, 5, 1},  /* 2: Seek the cursor to rowid=r[1] */
        {OP_Column,         0, 0, 1},  /* 3  */
        {OP_ResultRow,      1, 0, 0},  /* 4  */
        {OP_Halt,           0, 0, 0},  /* 5  */
      };
      Vdbe *v = (Vdbe *)pBlob->pStmt;
      int iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
      VdbeOp *aOp;

      sqlite3VdbeAddOp4Int(v, OP_Transaction, iDb, wrFlag, 
                           pTab->pSchema->schema_cookie,
                           pTab->pSchema->iGeneration);
      sqlite3VdbeChangeP5(v, 1);
      assert( sqlite3VdbeCurrentAddr(v)==2 || db->mallocFailed );
      aOp = sqlite3VdbeAddOpList(v, ArraySize(openBlob), openBlob, iLn);

      /* Make sure a mutex is held on the table to be accessed */
      sqlite3VdbeUsesBtree(v, iDb); 

      if( db->mallocFailed==0 ){
        assert( aOp!=0 );
        /* Configure the OP_TableLock instruction */
#ifdef SQLITE_OMIT_SHARED_CACHE
        aOp[0].opcode = OP_Noop;
#else
        aOp[0].p1 = iDb;
        aOp[0].p2 = pTab->tnum;
        aOp[0].p3 = wrFlag;
        sqlite3VdbeChangeP4(v, 2, pTab->zName, P4_TRANSIENT);
      }
      if( db->mallocFailed==0 ){
#endif

        /* Remove either the OP_OpenWrite or OpenRead. Set the P2 
        ** parameter of the other to pTab->tnum.  */
        if( wrFlag ) aOp[1].opcode = OP_OpenWrite;
        aOp[1].p2 = pTab->tnum;
        aOp[1].p3 = iDb;   

        /* Configure the number of columns. Configure the cursor to
        ** think that the table has one more column than it really
        ** does. An OP_Column to retrieve this imaginary column will
        ** always return an SQL NULL. This is useful because it means
        ** we can invoke OP_Column to fill in the vdbe cursors type 
        ** and offset cache without causing any IO.
        */
        aOp[1].p4type = P4_INT32;
        aOp[1].p4.i = pTab->nCol+1;
        aOp[3].p2 = pTab->nCol;

        sParse.nVar = 0;
        sParse.nMem = 1;
        sParse.nTab = 1;
        sqlite3VdbeMakeReady(v, &sParse);
      }
    }
   
    pBlob->iCol = iCol;
    pBlob->db = db;
    sqlite3BtreeLeaveAll(db);
    if( db->mallocFailed ){
      goto blob_open_out;
    }
    rc = blobSeekToRow(pBlob, iRow, &zErr);
  } while( (++nAttempt)<SQLITE_MAX_SCHEMA_RETRY && rc==SQLITE_SCHEMA );

blob_open_out:
  if( rc==SQLITE_OK && db->mallocFailed==0 ){
    *ppBlob = (sqlite3_blob *)pBlob;
  }else{
    if( pBlob && pBlob->pStmt ) sqlite3VdbeFinalize((Vdbe *)pBlob->pStmt);
    sqlite3DbFree(db, pBlob);
  }
  sqlite3ErrorWithMsg(db, rc, (zErr ? "%s" : 0), zErr);
  sqlite3DbFree(db, zErr);
  sqlite3ParserReset(&sParse);
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}