static int fts3SetHasStat(Fts3Table *p){
  int rc = SQLITE_OK;
  if( p->bHasStat==2 ){
    char *zTbl = sqlite3_mprintf("%s_stat", p->zName);
    if( zTbl ){
      int res = sqlite3_table_column_metadata(p->db, p->zDb, zTbl, 0,0,0,0,0,0);
      sqlite3_free(zTbl);
      p->bHasStat = (res==SQLITE_OK);
    }else{
      rc = SQLITE_NOMEM;
    }
  }
  return rc;
}