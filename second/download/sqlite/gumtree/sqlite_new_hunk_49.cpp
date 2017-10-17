  db->nSavepoint = 0;
  db->nStatement = 0;
  db->isTransactionSavepoint = 0;
}

/*
** Close an existing SQLite database
*/
int sqlite3_close(sqlite3 *db){
  HashElem *i;
  int j;

  if( !db ){
    return SQLITE_OK;
  }
  if( !sqlite3SafetyCheckSickOrOk(db) ){
    return SQLITE_MISUSE;
  }
  sqlite3_mutex_enter(db->mutex);

#ifdef SQLITE_SSE
  {
    extern void sqlite3SseCleanup(sqlite3*);
    sqlite3SseCleanup(db);
  }
#endif 

  sqlite3ResetInternalSchema(db, 0);

  /* If a transaction is open, the ResetInternalSchema() call above
  ** will not have called the xDisconnect() method on any virtual
  ** tables in the db->aVTrans[] array. The following sqlite3VtabRollback()
  ** call will do so. We need to do this before the check for active
  ** SQL statements below, as the v-table implementation may be storing
  ** some prepared statements internally.
  */
  sqlite3VtabRollback(db);

  /* If there are any outstanding VMs, return SQLITE_BUSY. */
  if( db->pVdbe ){
    sqlite3Error(db, SQLITE_BUSY, 
        "unable to close due to unfinalised statements");
    sqlite3_mutex_leave(db->mutex);
    return SQLITE_BUSY;
  }
  assert( sqlite3SafetyCheckSickOrOk(db) );

  for(j=0; j<db->nDb; j++){
    Btree *pBt = db->aDb[j].pBt;
    if( pBt && sqlite3BtreeIsInBackup(pBt) ){
      sqlite3Error(db, SQLITE_BUSY, 
          "unable to close due to unfinished backup operation");
      sqlite3_mutex_leave(db->mutex);
      return SQLITE_BUSY;
    }
  }

  /* Free any outstanding Savepoint structures. */
  sqlite3CloseSavepoints(db);

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
  sqlite3ResetInternalSchema(db, 0);

  /* Tell the code in notify.c that the connection no longer holds any
  ** locks and does not require any further unlock-notify callbacks.
  */
  sqlite3ConnectionClosed(db);

  assert( db->nDb<=2 );
  assert( db->aDb==db->aDbStatic );
  for(j=0; j<ArraySize(db->aFunc.a); j++){
    FuncDef *pNext, *pHash, *p;
    for(p=db->aFunc.a[j]; p; p=pHash){
      pHash = p->pHash;
      while( p ){
        pNext = p->pNext;
        sqlite3DbFree(db, p);
        p = pNext;
      }
    }
  }
  for(i=sqliteHashFirst(&db->aCollSeq); i; i=sqliteHashNext(i)){
    CollSeq *pColl = (CollSeq *)sqliteHashData(i);
    /* Invoke any destructors registered for collation sequence user data. */
    for(j=0; j<3; j++){
      if( pColl[j].xDel ){
        pColl[j].xDel(pColl[j].pUser);
