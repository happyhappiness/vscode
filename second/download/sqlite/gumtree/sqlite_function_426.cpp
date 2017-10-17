int sqlite3InitCallback(void *pInit, int argc, char **argv, char **NotUsed){
  InitData *pData = (InitData*)pInit;
  sqlite3 *db = pData->db;
  int iDb = pData->iDb;

  assert( argc==3 );
  UNUSED_PARAMETER2(NotUsed, argc);
  assert( sqlite3_mutex_held(db->mutex) );
  DbClearProperty(db, iDb, DB_Empty);
  if( db->mallocFailed ){
    corruptSchema(pData, argv[0], 0);
    return SQLITE_NOMEM;
  }

  assert( iDb>=0 && iDb<db->nDb );
  if( argv==0 ) return 0;   /* Might happen if EMPTY_RESULT_CALLBACKS are on */
  if( argv[1]==0 ){
    corruptSchema(pData, argv[0], 0);
  }else if( argv[2] && argv[2][0] ){
    /* Call the parser to process a CREATE TABLE, INDEX or VIEW.
    ** But because db->init.busy is set to 1, no VDBE code is generated
    ** or executed.  All the parser does is build the internal data
    ** structures that describe the table, index, or view.
    */
    char *zErr;
    int rc;
    assert( db->init.busy );
    db->init.iDb = iDb;
    db->init.newTnum = atoi(argv[1]);
    rc = sqlite3_exec(db, argv[2], 0, 0, &zErr);
    db->init.iDb = 0;
    assert( rc!=SQLITE_OK || zErr==0 );
    if( SQLITE_OK!=rc ){
      pData->rc = rc;
      if( rc==SQLITE_NOMEM ){
        db->mallocFailed = 1;
      }else if( rc!=SQLITE_INTERRUPT && (rc&0xff)!=SQLITE_LOCKED ){
        corruptSchema(pData, argv[0], zErr);
      }
      sqlite3DbFree(db, zErr);
    }
  }else if( argv[0]==0 ){
    corruptSchema(pData, 0, 0);
  }else{
    /* If the SQL column is blank it means this is an index that
    ** was created to be the PRIMARY KEY or to fulfill a UNIQUE
    ** constraint for a CREATE TABLE.  The index should have already
    ** been created when we processed the CREATE TABLE.  All we have
    ** to do here is record the root page number for that index.
    */
    Index *pIndex;
    pIndex = sqlite3FindIndex(db, argv[0], db->aDb[iDb].zName);
    if( pIndex==0 || pIndex->tnum!=0 ){
      /* This can occur if there exists an index on a TEMP table which
      ** has the same name as another index on a permanent index.  Since
      ** the permanent table is hidden by the TEMP table, we can also
      ** safely ignore the index on the permanent table.
      */
      /* Do Nothing */;
    }else{
      pIndex->tnum = atoi(argv[1]);
    }
  }
  return 0;
}