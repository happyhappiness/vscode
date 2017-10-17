constraint:
  rtreeRelease(pRtree);
  return rc;
}

/*
** Called when a transaction starts.
*/
static int rtreeBeginTransaction(sqlite3_vtab *pVtab){
  Rtree *pRtree = (Rtree *)pVtab;
  assert( pRtree->inWrTrans==0 );
  pRtree->inWrTrans++;
  return SQLITE_OK;
}

/*
** Called when a transaction completes (either by COMMIT or ROLLBACK).
** The sqlite3_blob object should be released at this point.
*/
static int rtreeEndTransaction(sqlite3_vtab *pVtab){
  Rtree *pRtree = (Rtree *)pVtab;
  pRtree->inWrTrans = 0;
  nodeBlobReset(pRtree);
  return SQLITE_OK;
}

/*
** The xRename method for rtree module virtual tables.
*/
static int rtreeRename(sqlite3_vtab *pVtab, const char *zNewName){
  Rtree *pRtree = (Rtree *)pVtab;
  int rc = SQLITE_NOMEM;
  char *zSql = sqlite3_mprintf(
