int sqlite3AnalysisLoad(sqlite3 *db, int iDb){
  analysisInfo sInfo;
  HashElem *i;
  char *zSql;
  int rc = SQLITE_OK;
  Schema *pSchema = db->aDb[iDb].pSchema;

  assert( iDb>=0 && iDb<db->nDb );
  assert( db->aDb[iDb].pBt!=0 );

  /* Clear any prior statistics */
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
  for(i=sqliteHashFirst(&pSchema->tblHash); i; i=sqliteHashNext(i)){
    Table *pTab = sqliteHashData(i);
    pTab->tabFlags &= ~TF_HasStat1;
  }
  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
    Index *pIdx = sqliteHashData(i);
    pIdx->hasStat1 = 0;
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
    sqlite3DeleteIndexSamples(db, pIdx);
    pIdx->aSample = 0;
#endif
  }

  /* Load new statistics out of the sqlite_stat1 table */
  sInfo.db = db;
  sInfo.zDatabase = db->aDb[iDb].zDbSName;
  if( sqlite3FindTable(db, "sqlite_stat1", sInfo.zDatabase)!=0 ){
    zSql = sqlite3MPrintf(db, 
        "SELECT tbl,idx,stat FROM %Q.sqlite_stat1", sInfo.zDatabase);
    if( zSql==0 ){
      rc = SQLITE_NOMEM_BKPT;
    }else{
      rc = sqlite3_exec(db, zSql, analysisLoader, &sInfo, 0);
      sqlite3DbFree(db, zSql);
    }
  }

  /* Set appropriate defaults on all indexes not in the sqlite_stat1 table */
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
    Index *pIdx = sqliteHashData(i);
    if( !pIdx->hasStat1 ) sqlite3DefaultRowEst(pIdx);
  }

  /* Load the statistics from the sqlite_stat4 table. */
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( rc==SQLITE_OK && OptimizationEnabled(db, SQLITE_Stat34) ){
    db->lookaside.bDisable++;
    rc = loadStat4(db, sInfo.zDatabase);
    db->lookaside.bDisable--;
  }
  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
    Index *pIdx = sqliteHashData(i);
    sqlite3_free(pIdx->aiRowEst);
    pIdx->aiRowEst = 0;
  }
#endif

  if( rc==SQLITE_NOMEM ){
    sqlite3OomFault(db);
  }
  return rc;
}