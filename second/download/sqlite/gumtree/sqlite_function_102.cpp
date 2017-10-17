void sqlite3RowidConstraint(
  Parse *pParse,    /* Parsing context */
  int onError,      /* Conflict resolution algorithm */
  Table *pTab       /* The table with the non-unique rowid */ 
){
  char *zMsg;
  int rc;
  if( pTab->iPKey>=0 ){
    zMsg = sqlite3MPrintf(pParse->db, "%s.%s", pTab->zName,
                          pTab->aCol[pTab->iPKey].zName);
    rc = SQLITE_CONSTRAINT_PRIMARYKEY;
  }else{
    zMsg = sqlite3MPrintf(pParse->db, "%s.rowid", pTab->zName);
    rc = SQLITE_CONSTRAINT_ROWID;
  }
  sqlite3HaltConstraint(pParse, rc, onError, zMsg, P4_DYNAMIC,
                        P5_ConstraintUnique);
}