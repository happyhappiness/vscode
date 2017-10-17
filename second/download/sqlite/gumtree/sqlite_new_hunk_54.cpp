** A new lower limit does not shrink existing constructs.
** It merely prevents new constructs that exceed the limit
** from forming.
*/
int sqlite3_limit(sqlite3 *db, int limitId, int newLimit){
  int oldLimit;
  if( limitId<0 || limitId>=SQLITE_N_LIMIT ){
    return -1;
  }
  oldLimit = db->aLimit[limitId];
  if( newLimit>=0 ){
    if( newLimit>aHardLimit[limitId] ){
      newLimit = aHardLimit[limitId];
    }
    db->aLimit[limitId] = newLimit;
  }
  return oldLimit;
}

/*
** This routine does the work of opening a database on behalf of
** sqlite3_open() and sqlite3_open16(). The database filename "zFilename"  
** is UTF-8 encoded.
*/
static int openDatabase(
