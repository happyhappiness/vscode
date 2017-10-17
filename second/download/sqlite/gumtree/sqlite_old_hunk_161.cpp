** error message to pErrorDb.
*/
static Btree *findBtree(sqlite3 *pErrorDb, sqlite3 *pDb, const char *zDb){
  int i = sqlite3FindDbName(pDb, zDb);

  if( i==1 ){
    Parse *pParse;
    int rc = 0;
    pParse = sqlite3StackAllocZero(pErrorDb, sizeof(*pParse));
    if( pParse==0 ){
      sqlite3Error(pErrorDb, SQLITE_NOMEM, "out of memory");
      rc = SQLITE_NOMEM;
    }else{
      pParse->db = pDb;
      if( sqlite3OpenTempDatabase(pParse) ){
        sqlite3ErrorClear(pParse);
        sqlite3Error(pErrorDb, pParse->rc, "%s", pParse->zErrMsg);
        rc = SQLITE_ERROR;
      }
      sqlite3StackFree(pErrorDb, pParse);
    }
    if( rc ){
      return 0;
    }
  }

  if( i<0 ){
    sqlite3Error(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
    return 0;
  }

  return pDb->aDb[i].pBt;
}

/*
** Create an sqlite3_backup process to copy the contents of zSrcDb from
** connection handle pSrcDb to zDestDb in pDestDb. If successful, return
** a pointer to the new sqlite3_backup object.
**
** If an error occurs, NULL is returned and an error code and error message
** stored in database handle pDestDb.
