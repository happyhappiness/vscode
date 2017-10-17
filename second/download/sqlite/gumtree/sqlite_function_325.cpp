static Btree *findBtree(sqlite3 *pErrorDb, sqlite3 *pDb, const char *zDb){
  int i = sqlite3FindDbName(pDb, zDb);

  if( i==1 ){
    Parse sParse;
    int rc = 0;
    memset(&sParse, 0, sizeof(sParse));
    sParse.db = pDb;
    if( sqlite3OpenTempDatabase(&sParse) ){
      sqlite3ErrorWithMsg(pErrorDb, sParse.rc, "%s", sParse.zErrMsg);
      rc = SQLITE_ERROR;
    }
    sqlite3DbFree(pErrorDb, sParse.zErrMsg);
    sqlite3ParserReset(&sParse);
    if( rc ){
      return 0;
    }
  }

  if( i<0 ){
    sqlite3ErrorWithMsg(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
    return 0;
  }

  return pDb->aDb[i].pBt;
}