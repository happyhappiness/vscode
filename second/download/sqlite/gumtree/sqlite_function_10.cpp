static int fts3CursorSeekStmt(Fts3Cursor *pCsr){
  int rc = SQLITE_OK;
  if( pCsr->pStmt==0 ){
    Fts3Table *p = (Fts3Table *)pCsr->base.pVtab;
    char *zSql;
    if( p->pSeekStmt ){
      pCsr->pStmt = p->pSeekStmt;
      p->pSeekStmt = 0;
    }else{
      zSql = sqlite3_mprintf("SELECT %s WHERE rowid = ?", p->zReadExprlist);
      if( !zSql ) return SQLITE_NOMEM;
      rc = sqlite3_prepare_v3(p->db, zSql,-1,SQLITE_PREPARE_PERSISTENT,&pCsr->pStmt,0);
      sqlite3_free(zSql);
    }
    if( rc==SQLITE_OK ) pCsr->bSeekStmt = 1;
  }
  return rc;
}