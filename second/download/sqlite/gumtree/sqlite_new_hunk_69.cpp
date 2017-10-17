    zRight = sqlite3MPrintf(db, "-%T", pValue);
  }else{
    zRight = sqlite3NameFromToken(db, pValue);
  }

  assert( pId2 );
  zDb = pId2->n>0 ? pDb->zName : 0;
  if( sqlite3AuthCheck(pParse, SQLITE_PRAGMA, zLeft, zRight, zDb) ){
    goto pragma_out;
  }
 
#ifndef SQLITE_OMIT_PAGER_PRAGMAS
  /*
  **  PRAGMA [database.]default_cache_size
  **  PRAGMA [database.]default_cache_size=N
  **
  ** The first form reports the current persistent setting for the
  ** page cache size.  The value returned is the maximum number of
  ** pages in the page cache.  The second form sets both the current
  ** page cache size value and the persistent page cache size value
  ** stored in the database file.
  **
  ** The default cache size is stored in meta-value 2 of page 1 of the
  ** database file.  The cache size is actually the absolute value of
  ** this memory location.  The sign of meta-value 2 determines the
  ** synchronous setting.  A negative value means synchronous is off
  ** and a positive value means synchronous is on.
  */
  if( sqlite3StrICmp(zLeft,"default_cache_size")==0 ){
    static const VdbeOpList getCacheSize[] = {
      { OP_ReadCookie,  0, 1,        BTREE_DEFAULT_CACHE_SIZE},  /* 0 */
      { OP_IfPos,       1, 6,        0},
      { OP_Integer,     0, 2,        0},
      { OP_Subtract,    1, 2,        1},
      { OP_IfPos,       1, 6,        0},
      { OP_Integer,     0, 1,        0},  /* 5 */
      { OP_ResultRow,   1, 1,        0},
    };
    int addr;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    sqlite3VdbeUsesBtree(v, iDb);
    if( !zRight ){
      sqlite3VdbeSetNumCols(v, 1);
      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "cache_size", SQLITE_STATIC);
      pParse->nMem += 2;
      addr = sqlite3VdbeAddOpList(v, ArraySize(getCacheSize), getCacheSize);
      sqlite3VdbeChangeP1(v, addr, iDb);
      sqlite3VdbeChangeP1(v, addr+5, SQLITE_DEFAULT_CACHE_SIZE);
    }else{
      int size = atoi(zRight);
      if( size<0 ) size = -size;
      sqlite3BeginWriteOperation(pParse, 0, iDb);
      sqlite3VdbeAddOp2(v, OP_Integer, size, 1);
      sqlite3VdbeAddOp3(v, OP_ReadCookie, iDb, 2, BTREE_DEFAULT_CACHE_SIZE);
      addr = sqlite3VdbeAddOp2(v, OP_IfPos, 2, 0);
      sqlite3VdbeAddOp2(v, OP_Integer, -size, 1);
      sqlite3VdbeJumpHere(v, addr);
      sqlite3VdbeAddOp3(v, OP_SetCookie, iDb, BTREE_DEFAULT_CACHE_SIZE, 1);
      pDb->pSchema->cache_size = size;
      sqlite3BtreeSetCacheSize(pDb->pBt, pDb->pSchema->cache_size);
    }
  }else

  /*
  **  PRAGMA [database.]page_size
  **  PRAGMA [database.]page_size=N
  **
  ** The first form reports the current setting for the
  ** database page size in bytes.  The second form sets the
  ** database page size value.  The value can only be set if
  ** the database has not yet been created.
  */
  if( sqlite3StrICmp(zLeft,"page_size")==0 ){
    Btree *pBt = pDb->pBt;
    assert( pBt!=0 );
    if( !zRight ){
      int size = ALWAYS(pBt) ? sqlite3BtreeGetPageSize(pBt) : 0;
      returnSingleInt(pParse, "page_size", size);
    }else{
      /* Malloc may fail when setting the page-size, as there is an internal
      ** buffer that the pager module resizes using sqlite3_realloc().
      */
      db->nextPagesize = atoi(zRight);
      if( SQLITE_NOMEM==sqlite3BtreeSetPageSize(pBt, db->nextPagesize, -1, 0) ){
        db->mallocFailed = 1;
      }
    }
  }else

  /*
  **  PRAGMA [database.]max_page_count
  **  PRAGMA [database.]max_page_count=N
  **
  ** The first form reports the current setting for the
  ** maximum number of pages in the database file.  The 
  ** second form attempts to change this setting.  Both
  ** forms return the current setting.
  */
  if( sqlite3StrICmp(zLeft,"max_page_count")==0 ){
    Btree *pBt = pDb->pBt;
    int newMax = 0;
    assert( pBt!=0 );
    if( zRight ){
      newMax = atoi(zRight);
    }
    if( ALWAYS(pBt) ){
      newMax = sqlite3BtreeMaxPageCount(pBt, newMax);
    }
    returnSingleInt(pParse, "max_page_count", newMax);
  }else

  /*
  **  PRAGMA [database.]page_count
  **
  ** Return the number of pages in the specified database.
  */
  if( sqlite3StrICmp(zLeft,"page_count")==0 ){
    int iReg;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    sqlite3CodeVerifySchema(pParse, iDb);
    iReg = ++pParse->nMem;
    sqlite3VdbeAddOp2(v, OP_Pagecount, iDb, iReg);
    sqlite3VdbeAddOp2(v, OP_ResultRow, iReg, 1);
    sqlite3VdbeSetNumCols(v, 1);
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "page_count", SQLITE_STATIC);
  }else

  /*
  **  PRAGMA [database.]locking_mode
  **  PRAGMA [database.]locking_mode = (normal|exclusive)
  */
  if( sqlite3StrICmp(zLeft,"locking_mode")==0 ){
    const char *zRet = "normal";
    int eMode = getLockingMode(zRight);

    if( pId2->n==0 && eMode==PAGER_LOCKINGMODE_QUERY ){
      /* Simple "PRAGMA locking_mode;" statement. This is a query for
      ** the current default locking mode (which may be different to
