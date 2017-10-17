int sqlite3AnalysisLoad(sqlite3 *db, int iDb){
  analysisInfo sInfo;
  HashElem *i;
  char *zSql;
  int rc;

  assert( iDb>=0 && iDb<db->nDb );
  assert( db->aDb[iDb].pBt!=0 );
  assert( sqlite3BtreeHoldsMutex(db->aDb[iDb].pBt) );

  /* Clear any prior statistics */
  for(i=sqliteHashFirst(&db->aDb[iDb].pSchema->idxHash);i;i=sqliteHashNext(i)){
    Index *pIdx = sqliteHashData(i);
    sqlite3DefaultRowEst(pIdx);
  }

  /* Check to make sure the sqlite_stat1 table existss */
  sInfo.db = db;
  sInfo.zDatabase = db->aDb[iDb].zName;
  if( sqlite3FindTable(db, "sqlite_stat1", sInfo.zDatabase)==0 ){
     return SQLITE_ERROR;
  }


  /* Load new statistics out of the sqlite_stat1 table */
  zSql = sqlite3MPrintf(db, "SELECT idx, stat FROM %Q.sqlite_stat1",
                        sInfo.zDatabase);
  if( zSql==0 ){
    rc = SQLITE_NOMEM;
  }else{
    (void)sqlite3SafetyOff(db);
    rc = sqlite3_exec(db, zSql, analysisLoader, &sInfo, 0);
    (void)sqlite3SafetyOn(db);
    sqlite3DbFree(db, zSql);
    if( rc==SQLITE_NOMEM ) db->mallocFailed = 1;
  }
  return rc;
}