struct analysisInfo {
  sqlite3 *db;
  const char *zDatabase;
};

/*
** This callback is invoked once for each index when reading the
** sqlite_stat1 table.  
**
**     argv[0] = name of the index
**     argv[1] = results of analysis - on integer for each column
*/
static int analysisLoader(void *pData, int argc, char **argv, char **NotUsed){
  analysisInfo *pInfo = (analysisInfo*)pData;
  Index *pIndex;
  int i, c;
  unsigned int v;
  const char *z;

  assert( argc==2 );
  UNUSED_PARAMETER2(NotUsed, argc);

  if( argv==0 || argv[0]==0 || argv[1]==0 ){
    return 0;
  }
  pIndex = sqlite3FindIndex(pInfo->db, argv[0], pInfo->zDatabase);
  if( pIndex==0 ){
    return 0;
  }
  z = argv[1];
  for(i=0; *z && i<=pIndex->nColumn; i++){
    v = 0;
    while( (c=z[0])>='0' && c<='9' ){
      v = v*10 + c - '0';
      z++;
    }
    pIndex->aiRowEst[i] = v;
    if( *z==' ' ) z++;
  }
  return 0;
}

/*
** Load the content of the sqlite_stat1 table into the index hash tables.
*/
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


#endif /* SQLITE_OMIT_ANALYZE */
