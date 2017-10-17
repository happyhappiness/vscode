int sqlite3_declare_vtab(sqlite3 *db, const char *zCreateTable){
  VtabCtx *pCtx;
  int rc = SQLITE_OK;
  Table *pTab;
  char *zErr = 0;
  Parse sParse;

#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) || zCreateTable==0 ){
    return SQLITE_MISUSE_BKPT;
  }
#endif
  sqlite3_mutex_enter(db->mutex);
  pCtx = db->pVtabCtx;
  if( !pCtx || pCtx->bDeclared ){
    sqlite3Error(db, SQLITE_MISUSE);
    sqlite3_mutex_leave(db->mutex);
    return SQLITE_MISUSE_BKPT;
  }
  pTab = pCtx->pTab;
  assert( IsVirtual(pTab) );

  memset(&sParse, 0, sizeof(sParse));
  sParse.declareVtab = 1;
  sParse.db = db;
  sParse.nQueryLoop = 1;
  if( SQLITE_OK==sqlite3RunParser(&sParse, zCreateTable, &zErr) 
   && sParse.pNewTable
   && !db->mallocFailed
   && !sParse.pNewTable->pSelect
   && !IsVirtual(sParse.pNewTable)
  ){
    if( !pTab->aCol ){
      Table *pNew = sParse.pNewTable;
      Index *pIdx;
      pTab->aCol = pNew->aCol;
      pTab->nCol = pNew->nCol;
      pTab->tabFlags |= pNew->tabFlags & (TF_WithoutRowid|TF_NoVisibleRowid);
      pNew->nCol = 0;
      pNew->aCol = 0;
      assert( pTab->pIndex==0 );
      assert( HasRowid(pNew) || sqlite3PrimaryKeyIndex(pNew)!=0 );
      if( !HasRowid(pNew)
       && pCtx->pVTable->pMod->pModule->xUpdate!=0
       && sqlite3PrimaryKeyIndex(pNew)->nKeyCol!=1
      ){
        /* WITHOUT ROWID virtual tables must either be read-only (xUpdate==0)
        ** or else must have a single-column PRIMARY KEY */
        rc = SQLITE_ERROR;
      }
      pIdx = pNew->pIndex;
      if( pIdx ){
        assert( pIdx->pNext==0 );
        pTab->pIndex = pIdx;
        pNew->pIndex = 0;
        pIdx->pTable = pTab;
      }
    }
    pCtx->bDeclared = 1;
  }else{
    sqlite3ErrorWithMsg(db, SQLITE_ERROR, (zErr ? "%s" : 0), zErr);
    sqlite3DbFree(db, zErr);
    rc = SQLITE_ERROR;
  }
  sParse.declareVtab = 0;

  if( sParse.pVdbe ){
    sqlite3VdbeFinalize(sParse.pVdbe);
  }
  sqlite3DeleteTable(db, sParse.pNewTable);
  sqlite3ParserReset(&sParse);

  assert( (rc&0xff)==rc );
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}